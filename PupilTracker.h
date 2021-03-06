/**********************************************************************************************************************
* @file PupilTracker.cpp
* @brief Header for the PupilTracker class
*
* This class encapsulates the canny edge based pupil tracking algorithm
*
* @author Christopher D. McMurrough
***********************************************************************************************************************/

#ifndef PUPIL_TRACKER_H
#define PUPIL_TRACKER_H

#include "opencv2/opencv.hpp"

/**********************************************************************************************************************
* @class PupilTracker
*
* @brief Class for tracking pupils in an occulography image using canny edges
*
* @author Christopher D. McMurrough
***********************************************************************************************************************/
class PupilTracker
{
private:

    // result data structures
    cv::RotatedRect m_ellipseRectangle;

    // algorithm settings
    int m_blur;
    int m_canny_thresh;
    int m_canny_ratio;
    int m_canny_aperture;
    int m_bin_thresh;
    int m_pupilIntensityOffset;
    int m_glintIntensityOffset;
    int m_min_contour_size;
    float m_confidence;

    // debug settings
    bool m_display;

	// inputted mask image
	cv::Mat maskImage;

	// camera feed size and width used for setting image sizes
	int camera_width;
	int camera_height;

public:
	
	// vector of processed images for display interface
	std::vector<cv::Mat> images;

    // constructors
    PupilTracker();

    // accessors
    cv::Point2f getEllipseCentroid();
    cv::RotatedRect getEllipseRectangle();
    
    // utility functions
    bool findPupil(const cv::Mat& eyeImage);
    void setDisplay(bool display);
	void setMaskImage(const cv::Mat& maskImage);
	void showMultipleDisplays(); 
	void setCameraSize(int w, int h);

};

#endif // PUPIL_TRACKER_H
