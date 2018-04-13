/*******************************************************************************************************************//**
* @file PupilTracker.cpp
* @brief Implementation for the PupilTracker class
*
* This class encapsulates the canny edge based pupil tracking algorithm
*
* @author Christopher D. McMurrough
***********************************************************************************************************************/

#include "PupilTracker.h"
#include "opencv2/opencv.hpp"
#include <iostream>

#define CAMERA_FRAME_WIDTH 640
#define CAMERA_FRAME_HEIGHT 360

/*******************************************************************************************************************//**
* @brief Constructor to create a PupilTracker
* @author Christopher D. McMurrough
***********************************************************************************************************************/
PupilTracker::PupilTracker()
{
    // tracker settings
    m_blur = 5;
    m_canny_thresh = 159;
    m_canny_ratio = 2;
    m_canny_aperture = 5;
    m_bin_thresh = 0;
    m_pupilIntensityOffset = 11;
    m_glintIntensityOffset = 5;
    m_min_contour_size = 80;
    m_confidence = 0;

    // set debug display
    setDisplay(false);
}

/*******************************************************************************************************************//**
* @brief Attempt to fit a pupil ellipse in the eye image frame
* @param[in] imageIn the input OpenCV image
* @param[out] result the output tracking data
* @return true if the a pupil was located in the image
* @author Christopher D. McMurrough
***********************************************************************************************************************/
bool PupilTracker::findPupil(const cv::Mat& eyeImage)
{
    bool success = false;
	cv::Mat imageIn;

	// apply the mask to the image if a mask image exists
	if(!maskImage.empty())
	{
		/* A black mask will be picked up as the pupil in the algorithm 
		so we need to make the mask white. */
		
		// first invert the image
		cv::Mat invertedImage;
		bitwise_not(eyeImage, invertedImage);

		// Then apply the mask to the inverted image
		cv::Mat masked;
		invertedImage.copyTo(masked, maskImage);

		// Invert the masked image back so that the mask is now white
		bitwise_not(masked, imageIn);

		//cv::imshow("masked", masked);
	}
	else 
	{
		imageIn = eyeImage;
	}

    // get the normalized grayscale image
    const int rangeMin = 0;
    const int rangeMax = 255;
    cv::Mat imageGray;
    cv::cvtColor(imageIn, imageGray, cv::COLOR_BGR2GRAY);
    cv::normalize(imageGray, imageGray, rangeMin, rangeMax, cv::NORM_MINMAX, CV_8UC1);
    if(m_display)
    {
		images.push_back(imageGray);
        //cv::imshow("imageGray", imageGray);
    }
	

    // compute the intensity histogram
    cv::Mat hist;
    int channels[] = {0};
    int histSize[] = {rangeMax - rangeMin + 1};
    float range[] = {static_cast<float>(rangeMin), static_cast<float>(rangeMax)};
    const float* ranges = {range};
    cv::calcHist(&imageGray, 1, channels, cv::Mat(), hist, 1, histSize, &ranges, true, false);

    // find histogram spikes
    const int minSpikeSize = 40;
    int lowestSpike = rangeMax;
    int highestSpike = rangeMin;
    int numSpikes = 0;
    for(int i = 0; i < histSize[0]; i++)
    {
        // check to see if we have a spike
        if(hist.at<uchar>(0, i) >= minSpikeSize)
        {
            numSpikes++;
            if(i < lowestSpike)
            {
                lowestSpike = i;
            }
            if(i > highestSpike)
            {
                highestSpike = i;
            }
        }
    }
    if(numSpikes < 2)
    {
        // not enough spikes, assign default values
        lowestSpike = 0;
        highestSpike = 255;
    }
    m_bin_thresh = lowestSpike;

    // create a mask for the dark pupil area (assign white to pupil area)
    cv::Mat darkMask;
    cv::inRange(imageGray, cv::InputArray(rangeMin), cv::InputArray(lowestSpike + m_pupilIntensityOffset), darkMask);
    const cv::Mat morphKernel = getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(7, 7));
    cv::dilate(darkMask, darkMask, morphKernel, cv::Point(-1, -1), 2);
    if(m_display)
    {
		images.push_back(darkMask);
        //cv::imshow("darkMask", darkMask);
    }

	

    // create a mask for the light glint area (assign black to glint area)
    cv::Mat glintMask;
    cv::inRange(imageGray, cv::InputArray(rangeMin), cv::InputArray(highestSpike - m_glintIntensityOffset), glintMask);
    cv::erode(glintMask, glintMask, morphKernel, cv::Point(-1, -1), 1);
    if(m_display)
    {
		images.push_back(glintMask);
        //cv::imshow("glintMask", glintMask);
    }

    // apply additional blurring
    cv::Mat imageBlurred;
    if(m_blur > 1)
    {
        cv::blur(imageGray, imageBlurred, cv::Size(m_blur,m_blur));
        //cv::medianBlur(imageGray, imageBlurred, m_blur);
    }
    else
    {
        imageBlurred = imageGray;
    }
    if(m_display)
    {
		images.push_back(imageBlurred);
        //cv::imshow("imageBlurred", imageBlurred);
    }

    // compute canny edges
    cv::Mat edges;
    cv::Canny(imageBlurred, edges, m_canny_thresh, m_canny_thresh * m_canny_ratio, m_canny_aperture);
    if(m_display)
    {	
		images.push_back(edges);
        //cv::imshow("edges", edges);
    }

    // remove edges outside of the white regions in the pupil and glint masks
    cv::Mat edgesPruned;
    cv::min(edges, darkMask, edgesPruned);
    cv::min(edgesPruned, glintMask, edgesPruned);
    if(m_display)
    {	
		images.push_back(edgesPruned);
        //cv::imshow("edgesPruned", edgesPruned);
    }

    // compute the connected components out of the pupil edge candidates
    std::vector<std::vector<cv::Point> > contours;
    cv::findContours(edgesPruned, contours, CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE);

    // determine merge candidacy for contours with sufficient size
    std::vector<bool> contourMergeable(contours.size());
    bool retryContourMerge = true;
    int relaxContourMerge = 0;
    while(retryContourMerge && contours.size() > 0)
    {
        for(int i = 0; i < contours.size(); i++)
        {
            // merge the contour if sufficiently large
            if(contours.at(i).size() < m_min_contour_size - relaxContourMerge)
            {
                // contour is too small, ignore and continue
                contourMergeable.at(i) = false;
                continue;
            }
            else
            {
                contourMergeable.at(i) = true;
                retryContourMerge = false;
            }
        }
        relaxContourMerge += 2;
    }

    // perform the contour merging
    std::vector<cv::Point> contoursMerged;
    for(int i = 0; i < contours.size(); i++)
    {
        if(contourMergeable.at(i))
        {
            success = true;
            contoursMerged.insert(contoursMerged.end(), contours.at(i).begin(), contours.at(i).end());
        }
    }

    // display the contours if necessary
    if(m_display)
    {
        // display both the raw and merged contours
        cv::Mat edgesContoured = cv::Mat::zeros(edgesPruned.size(), CV_8UC1);
        cv::Mat filteredContours = cv::Mat::zeros(edgesPruned.size(), CV_8UC1);
        for(int i = 0; i < contours.size(); i++)
        {
            cv::drawContours(edgesContoured, contours, i, cv::Scalar(255));
            if(contourMergeable.at(i))
            {
                cv::drawContours(filteredContours, contours, i, cv::Scalar(255));
            }
        }
		images.push_back(edgesContoured);
		images.push_back(filteredContours);
        //cv::imshow("edgesContoured", edgesContoured);
        //cv::imshow("filteredContours", filteredContours);
    }

    // perform the ellipse fitting step and return 
    if(success)
    {
        m_ellipseRectangle = cv::fitEllipse(contoursMerged);
        return true;
    }
    else
    {
        // return false if tracking was not successful
        return false;
    }
}

/*******************************************************************************************************************//**
* @brief Returns the pupil centroid
* @return pupil center as cv::Point2f
* @author Christopher D. McMurrough
***********************************************************************************************************************/
cv::Point2f PupilTracker::getEllipseCentroid()
{
    return m_ellipseRectangle.center;
}

/*******************************************************************************************************************//**
* @brief Returns the pupil ellipse rectangle
* @return pupil ellipse rectangle as cv::RotatedRect
* @author Christopher D. McMurrough
***********************************************************************************************************************/
cv::RotatedRect PupilTracker::getEllipseRectangle()
{
    return m_ellipseRectangle;
}

/*******************************************************************************************************************//**
* @brief Sets the display mode for the pupil tracker
* @param[in] display show debug processing image frames if true
* @author Christopher D. McMurrough
***********************************************************************************************************************/
void PupilTracker::setDisplay(bool display)
{
    m_display = display;
	//m_display = false;
}

void PupilTracker::setMaskImage(const cv::Mat& maskIn)
{
	maskImage = maskIn;
}

void PupilTracker::setPupilImage(const cv::Mat& image)
{
	pupilImage= image;
}

void PupilTracker::showMultipleDisplays() 
{
	using namespace cv;

	int rows = 3;
	int cols = 3;
	int m;
	int n;

	Mat DispImage(CAMERA_FRAME_HEIGHT * rows, CAMERA_FRAME_WIDTH * cols, CV_8UC3);

	for(int i = 0, m = 0, n = 0; i < images.size(); i++, m += CAMERA_FRAME_WIDTH)
	{
		cv::Mat temp;
		temp = images[i];
		cv::Mat image;
		if(temp.type() != CV_8UC3){	
			cvtColor(temp, image, cv::COLOR_GRAY2RGB);
		}
		else {
			image = temp;
		}
		
		//Used to align images
		if(i % cols == 0 && m != 0) {
			m = 0;
			n += (CAMERA_FRAME_HEIGHT);		
		}
		//std::printf("%d, %d\n", image.type(), CV_8UC3);
		Rect ROI(m, n, CAMERA_FRAME_WIDTH, CAMERA_FRAME_HEIGHT);
		image.copyTo(DispImage(ROI));
	}
	
	//putText(DispImage, "Image Gray", cvPoint(CAMERA_FRAME_WIDTH / 4, CAMERA_FRAME_HEIGHT + 20), FONT_HERSHEY_COMPLEX_SMALL, 0.8, cvScalar(200,200,250),1, CV_AA);
  	namedWindow("test", WINDOW_NORMAL);
    imshow("test", DispImage);

	//va_end(args);
 
}
