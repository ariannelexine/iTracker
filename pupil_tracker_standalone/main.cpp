/**********************************************************************************************************************
 * @FILE main.cpp
 * @BRIEF USB implementation of the robust pupil tracker by Lech Swirski
 *
 * USB implementation of the robust pupil tracker by Lech Swirski
 * http://www.cl.cam.ac.uk/research/rainbow/projects/pupiltracking/
 *
 * @AUTHOR Christopher D. McMurrough
 *********************************************************************************************************************/

#include <iostream>
#include <stdio.h>
#include <time.h>
#include <opencv/highgui.h>
#include "swirski_pupil/PupilTracker.h"
#include "swirski_pupil/cvx.h"

// configuration parameters
#define NUM_COMNMAND_LINE_ARGUMENTS 2
#define CAMERA_FRAME_WIDTH 640
#define CAMERA_FRAME_HEIGHT 480

// define tracking parameters
#define MIN_RADIUS 10;
#define MAX_RADIUS 60
#define CANNY_BLUR 1.6
#define CANNY_THRESH_1 30
#define CANNY_THRESH_2 50
#define STARBURST_POINTS 0
#define PERCENT_INLIERS 40
#define INLIER_ITERATIONS 2
#define IMAGE_AWARE_SUPPORT true
#define EARLY_TERMINATION_PERCENTAGE 95
#define EARLY_REJECTION true
#define SEED_VALUE -1

// color constants
CvScalar COLOR_WHITE = CV_RGB(255, 255, 255);
CvScalar COLOR_RED = CV_RGB(255, 0, 0);
CvScalar COLOR_GREEN = CV_RGB(0, 255, 0);
CvScalar COLOR_BLUE = CV_RGB(0, 0, 255);
CvScalar COLOR_YELLOW = CV_RGB(255, 255, 0);

// define the result struct
struct TrackingData
{
    cv::Point2f pupil_center;
    float pupil_radius;
    cv::Point2f cr_center;
    float cr_radius;
    cv::RotatedRect ellipse_rectangle;
};

/**********************************************************************************************************************
 * @BRIEF Attempt to fit a pupil ellipse in the eye image frame
 * @PARAM[in] imageIn the input OpenCV image
 * @PARAM[out] result the output tracking data
 * @RETURN true if the a pupil was located in the image
 * @AUTHOR Christopher D. McMurrough
 *********************************************************************************************************************/
bool processImage(const cv::Mat& imageIn, TrackingData& result)
{
    // set the tracking parameters for this frame
    PupilTracker::TrackerParams params;
    params.Radius_Min = MIN_RADIUS;
    params.Radius_Max = MAX_RADIUS;
    params.CannyBlur = CANNY_BLUR;
    params.CannyThreshold1 = CANNY_THRESH_1;
    params.CannyThreshold2 = CANNY_THRESH_2;
    params.StarburstPoints = STARBURST_POINTS;
    params.PercentageInliers = PERCENT_INLIERS;
    params.InlierIterations = INLIER_ITERATIONS;
    params.ImageAwareSupport = IMAGE_AWARE_SUPPORT;
    params.EarlyTerminationPercentage = EARLY_TERMINATION_PERCENTAGE;
    params.EarlyRejection = EARLY_REJECTION;
    params.Seed = SEED_VALUE;

    // perform the pupil ellipse fitting
    PupilTracker::findPupilEllipse_out out;
    tracker_log log;
    if(PupilTracker::findPupilEllipse(params, imageIn, out, log))
    {
        // package the result in the pupil data structure
        result.pupil_center = out.pPupil;
        result.pupil_radius = 1;
        result.cr_center = out.pPupil;
        result.cr_radius = 1;
        result.ellipse_rectangle = out.elPupil;
        return true;
    }
    else
    {
        // return false if tracking was not successful
        return false;
    }
}

/**********************************************************************************************************************
 * @BRIEF Program entry point
 *
 * Handles image processing and display of annotated results
 *
 * @PARAM[in] argc command line argument count
 * @PARAM[in] argv command line argument vector
 * @RETURNS return status
 * @AUTHOR Christopher D. McMurrough
 *********************************************************************************************************************/
int main(int argc, char** argv)
{
    // store video capture parameters
    int cameraIndex = 0;
    bool displayMode = true;
    bool flipDisplay = false;
    bool isRunning = true;

    // validate and parse the command line arguments
    if(argc != NUM_COMNMAND_LINE_ARGUMENTS + 1)
    {
        std::printf("USAGE: <camera_index> <display_mode>\n");
        std::printf("Running with default parameters... \n");
    }
    else
    {
        cameraIndex = atoi(argv[1]);
        displayMode = atoi(argv[2]) > 0;
        flipDisplay = atoi(argv[2]) == 2;
    }

    // initialize the eye camera
    cv::VideoCapture occulography(cameraIndex);
    if(!occulography.isOpened())
    {
        std::printf("Unable to initialize camera %u!", cameraIndex);
        return 0;
    }
    occulography.set(CV_CAP_PROP_FRAME_WIDTH, CAMERA_FRAME_WIDTH);
    occulography.set(CV_CAP_PROP_FRAME_HEIGHT, CAMERA_FRAME_HEIGHT);

    // store the frame data
    cv::Mat eyeImage;
    struct TrackingData result;
    bool trackingSuccess = false;

    // store the time between frames
    int frameStartTicks, frameEndTicks, processStartTicks, processEndTicks;
    float processTime, totalTime;

    // process data until program termination
    while(isRunning)
    {
        // start the timer
        frameStartTicks = clock();

        // attempt to acquire an image frame
        if(occulography.read(eyeImage))
        {
            // process the image frame
            processStartTicks = clock();
            trackingSuccess = processImage(eyeImage, result);
            processEndTicks = clock();
            processTime = ((float)(processEndTicks - processStartTicks)) / CLOCKS_PER_SEC;

            if(trackingSuccess)
            {
                //std::printf("TRACKING SUCCESS\n");
            }
            else
            {
                //std::printf("TRACKING FAIL\n");
            }

            // update the display
            if(displayMode)
            {
                cv::Mat displayImage(eyeImage);

                // annotate the image if result is in range
                if(cv::Rect(cv::Point(), displayImage.size()).contains(result.pupil_center))
                {
                    cvx::cross(displayImage, result.pupil_center, 5, COLOR_RED);
                    cv::ellipse(displayImage, result.ellipse_rectangle, COLOR_GREEN);
                }

                if(flipDisplay)
                {
                    // annotate the image
                    cv::Mat displayFlipped;
                    cv::flip(displayImage, displayFlipped, 1);
                    cv::imshow("eyeImage", displayFlipped);

                    // display the annotated image
                    isRunning = cv::waitKey(1) != 'q';
                    displayFlipped.release();
                }
                else
                {
                    // display the annotated image
                    cv::imshow("eyeImage", displayImage);
                    isRunning = cv::waitKey(1) != 'q';
                }

                // release display image
                displayImage.release();
            }
        }
        else
        {
            printf("WARNING: Unable to capture image from source!\n");
            continue;
        }

        // stop the timer and print the elapsed time
        frameEndTicks = clock();
        totalTime = ((float) (frameEndTicks - frameStartTicks)) / CLOCKS_PER_SEC;
        std::printf("Processing time (pupil, total) (result x,y): %.4f %.4f - %.2f %.2f\n", processTime, totalTime, result.pupil_center.x, result.pupil_center.y);
    }

    // release the video source before exiting
    occulography.release();
}

