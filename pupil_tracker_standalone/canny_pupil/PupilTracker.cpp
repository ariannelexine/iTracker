/**********************************************************************************************************************
* @FILE PupilTracker.cpp
* @BRIEF Implementation for the PupilTracker class
*
* This class encapsulates the canny edge based pupil tracking algorithm
*
* @AUTHOR Christopher D. McMurrough
**********************************************************************************************************************/

#include "PupilTracker.h"
#include <opencv2/core/core.hpp>

/**********************************************************************************************************************
* @BRIEF Constructor to create a PupilTracker
* @AUTHOR Christopher D. McMurrough
**********************************************************************************************************************/
PupilTracker::PupilTracker()
{
}

/**********************************************************************************************************************
* @BRIEF Attempt to fit a pupil ellipse in the eye image frame
* @PARAM[in] imageIn the input OpenCV image
* @PARAM[out] result the output tracking data
* @RETURN true if the a pupil was located in the image
* @AUTHOR Christopher D. McMurrough
*********************************************************************************************************************/
bool PupilTracker::findPupil(const cv::Mat& imageIn)
{
	bool success = false;

	// perfom the actual tracking step
	success = true;

	// store the tracking result
	if(success)
	{
		m_ellipseCentroid = cv::Point2f(240, 240);
		m_ellipseRectangle = cv::RotatedRect(cv::Point2f(240, 240), cv::Size(10, 20), 0);
		m_crCenter = cv::Point2f(240, 240);
		m_crRadius = 1.0;
		
		return true;
	}
	else
	{
		// return false if tracking was not successful
		return false;
	}
}

/**********************************************************************************************************************
* @BRIEF Returns the pupil centroid
* @RETURN pupil center as cv::Point2f
* @AUTHOR Christopher D. McMurrough
*********************************************************************************************************************/
cv::Point2f PupilTracker::getEllipseCentroid()
{
	return m_ellipseCentroid;
}

/**********************************************************************************************************************
* @BRIEF Returns the pupil ellipse rectangle
* @RETURN pupil ellipse rectangle as cv::RotatedRect
* @AUTHOR Christopher D. McMurrough
*********************************************************************************************************************/
cv::RotatedRect PupilTracker::getEllipseRectangle()
{
	return m_ellipseRectangle;
}
