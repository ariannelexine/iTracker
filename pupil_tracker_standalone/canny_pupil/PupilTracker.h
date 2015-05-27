/**********************************************************************************************************************
* @FILE PupilTracker.cpp
* @BRIEF Header for the PupilTracker class
*
* This class encapsulates the canny edge based pupil tracking algorithm
*
* @AUTHOR Christopher D. McMurrough
**********************************************************************************************************************/

#ifndef PUPIL_TRACKER_H
#define PUPIL_TRACKER_H

#include <opencv2/core/core.hpp>

/**********************************************************************************************************************
* @CLASS PupilTracker
*
* @BRIEF Class for tracking pupils in an occulography image using canny edges
*
* The class implements a C++ version of the canny edge based pupil tracker by pupil-labs (originally written in Python)
* https://github.com/pupil-labs/pupil
*
* @AUTHOR Christopher D. McMurrough
**********************************************************************************************************************/
class PupilTracker
{
private:

	// define tracking result parameters
	cv::Point2f m_ellipseCentroid;
	cv::RotatedRect m_ellipseRectangle;
	cv::Point2f m_crCenter;
	float m_crRadius;

public:

	// constructors
	PupilTracker();

	// accessors
	cv::Point2f getEllipseCentroid();
	cv::RotatedRect getEllipseRectangle();

	// utility functions
	bool findPupil(const cv::Mat& imageIn);
};

#endif // PUPIL_TRACKER_H
