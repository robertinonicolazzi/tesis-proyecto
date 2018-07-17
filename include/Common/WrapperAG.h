/*
 * WrapperCV.h
 *
 *  Created on: 28/6/2018
 *      Author: rober
 */

#ifndef WRAPPERAG_H_
#define WRAPPERAG_H_
#include <string>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <aruco/markerdetector.h>

using namespace std;
using namespace cv;
using namespace aruco;

class WrapperAG {

private:
	string st_InputPath;
	string st_IntrinsicFilePath;
	bool The3DInfoAvailable = false;
	float TheMarkerSize = -1;
	MarkerDetector markerDetector;
	VideoCapture videoCapturer;
	Marker marker;
	Mat actualFrame;
	Mat TheInputImage, TheUndInputImage, TheResizedImage;
	CameraParameters TheCameraParams;
public:
	WrapperAG();
	virtual ~WrapperAG();
};

#endif /* WRAPPERCV_H_ */
