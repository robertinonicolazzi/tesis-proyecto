/*
 * WrapperCV.h
 *
 *  Created on: 28/6/2018
 *      Author: rober
 */

#ifndef WRAPPERCV_H_
#define WRAPPERCV_H_
#include <string>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
using namespace std;

class WrapperCV {
	std::vector<cv::Point> puntosHomografia;

public:

	WrapperCV();
	virtual ~WrapperCV();
    void ObtenerHomografia(cv::String videopath);
    static void onMouse(int evt, int x, int y, int flags, void* param);
};

#endif /* WRAPPERCV_H_ */
