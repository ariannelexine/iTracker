/***********************************************************************************************************************
FILENAME:   main.cpp
AUTHORS:    Christopher D. McMurrough

DESCRIPTION:
USB implementation of the robust pupil tracker by Lech Swirski
http://www.cl.cam.ac.uk/research/rainbow/projects/pupiltracking/

REVISION HISTORY:
10.30.2012   CDM     original file creation
***********************************************************************************************************************/

// include necessary dependencies
#include <iostream>
#include <stdio.h>
#include <time.h>
#include <opencv/highgui.h>
#include "lib/PupilTracker.h"
#include "lib/cvx.h"

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
CvScalar COLOR_WHITE = CV_RGB(255,255,255);
CvScalar COLOR_RED = CV_RGB(255,0,0);
CvScalar COLOR_GREEN = CV_RGB(0,255,0);
CvScalar COLOR_BLUE = CV_RGB(0,0,255);
CvScalar COLOR_YELLOW = CV_RGB(255,255,0);

// define the result struct
struct TrackingData
{
    float pupil_x;
    float pupil_y;
    float pupil_size;
    float cr_x;
    float cr_y;
    float cr_size;
    float dv_x;
    float dv_y;
};

/***********************************************************************************************************************
CvCapture* initializeCamera(int cameraIndex)
initialize the camera capture, cameraIndex is the USB camera number
***********************************************************************************************************************/
CvCapture* initializeCamera(int cameraIndex)
{
    CvCapture* capture = cvCaptureFromCAM(cameraIndex);
    cvSetCaptureProperty(capture, CV_CAP_PROP_FRAME_WIDTH, CAMERA_FRAME_WIDTH);
    cvSetCaptureProperty(capture, CV_CAP_PROP_FRAME_HEIGHT, CAMERA_FRAME_HEIGHT);

    if (!capture)
    {
        fprintf( stderr, "ERROR: unable to initialize camera %d \n", cameraIndex);
        return NULL;
    }

    printf("Camera %d opened successfully \n", cameraIndex);
    return capture;
}

/***********************************************************************************************************************
void closeCamera(CvCapture* capture)
close a camera capture
***********************************************************************************************************************/
void closeCamera(CvCapture* capture)
{
    cvReleaseCapture(&capture);
}

/***********************************************************************************************************************
bool getImageFrame(CvCapture* pupilCapture, IplImage*& rawImage, bool flipImage)
get the pupil image from the capture object
***********************************************************************************************************************/
bool getImageFrame(CvCapture* pupilCapture, IplImage*& rawImage, bool flipImage)
{
    // get the raw image
    IplImage* frame = cvQueryFrame(pupilCapture);
    //IplImage* frame = cvLoadImage("eye.jpg");

    // return false if no image was acquired
    if(!frame)
    {
        return false;
    }

    // flip the image if necessary
    rawImage = frame;
    if(flipImage)
    {
        cvFlip(rawImage);
    }
    return true;
}

/***********************************************************************************************************************
void processImage(IplImage* rawImage, TrackingData *result)
attempt to fit a pupil ellipse in the eye image frame
***********************************************************************************************************************/
void processImage(IplImage* rawImage, TrackingData *result)
{
    cv::Mat m(rawImage);

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

    // perform the ellipse fitting
    PupilTracker::findPupilEllipse_out out;
    tracker_log log;
    if(PupilTracker::findPupilEllipse(params, m, out, log))
	{

		// annotate the image
		if(out.pPupil.inside(cv::Rect(0, 0, 640, 480)))
		{
			cvx::cross(m, out.pPupil, 5, COLOR_RED);
			cv::ellipse(m, out.elPupil, COLOR_GREEN);
		}

		// package the result in the pupil data structure
		result->pupil_x = out.pPupil.x;
		result->pupil_y = out.pPupil.y;
		result->pupil_size = 0;
		result->cr_x = 0;
		result->cr_y = 0;
		result->cr_size = 0;
		result->dv_x = 0;
		result->dv_y = 0;
	}
	else
	{
		// package the result in the pupil data structure
		result->pupil_x = 0;
		result->pupil_y = 0;
		result->pupil_size = 0;
		result->cr_x = 0;
		result->cr_y = 0;
		result->cr_size = 0;
		result->dv_x = 0;
		result->dv_y = 0;
	}
}

/***********************************************************************************************************************
int main(int argc, char **argv)
program entry point, expects the camera index as command line arguments
***********************************************************************************************************************/
int main(int argc, char **argv)
{
    // store video capture parameters
    int cameraIndex = 0;
    int frameCount = 0;
    int displayMode = 0;
    bool showFrames = false;
    bool flipImage = false;

    // define image pointers
    IplImage *eyeImage = NULL;

    // validate and parse the command line arguments
    if(argc != NUM_COMNMAND_LINE_ARGUMENTS + 1)
    {
        printf("USAGE: %s <camera_index> <display_mode>\n", argv[0]);
        return 0;
    }
    cameraIndex = atoi(argv[1]);
    displayMode = atoi(argv[2]);
    showFrames = displayMode > 0;
    flipImage = displayMode == 2;

    // initialize the eye camera
    CvCapture* pupilCapture = initializeCamera(cameraIndex);
    if(!pupilCapture)
    {
        printf("Unable to initialize camera %u!", cameraIndex);
        return 0;
    }

    // create the debug image windows
    if(showFrames)
    {
        cvNamedWindow("eyeImage");
    }

    // store the tracking result
    struct TrackingData result;

    // store the time between frames
    int startTicks, endTicks;
    float elapsedTime;

    // process data until program termination
    while(true)
    {
        // start the timer
        startTicks = clock();

        // attempt to acquire an image frame
        if(getImageFrame(pupilCapture, eyeImage, flipImage))
        {
            // process the image frame
            processImage(eyeImage, &result);

            // increment the frame counter
            frameCount++;
        }
        else
        {
            printf("DEBUG: UNABLE TO GET IMAGE!");
        }

        // update the GUI windows every nth frame
        if(showFrames && frameCount % 1 == 0)
        {
            cvShowImage("eyeImage", eyeImage);
            cvWaitKey(1);
        }

        // clear the image containers
        eyeImage = 0;
        cvReleaseImage(&eyeImage);

        // stop the timer and print result
        endTicks = clock();
        elapsedTime = ((float) (endTicks - startTicks)) / CLOCKS_PER_SEC;
        printf ("frame processing time: %f \n", elapsedTime );
    }

    // release program resources before returning
    closeCamera(pupilCapture);

    // close the GUI windows
    if(showFrames)
    {
        cvDestroyWindow("eyeImage");
    }
}

