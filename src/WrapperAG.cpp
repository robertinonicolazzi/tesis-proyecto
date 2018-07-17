/*
 * WrapperCV.cpp
 *
 *  Created on: 28/6/2018
 *      Author: rober
 */

#include <Common/WrapperAG.h>
using namespace std;
using namespace cv;

WrapperAG::WrapperAG(int argc, char** argv) {
	videoCapturer.open(argv[0]);
	markerDetector.setDetectionMode(DM_VIDEO_FAST);
}
void WrapperAG::ProcesarFrameAG() {
	videoCapturer.retrieve(actualFrame);
	vector<Marker> temp = markerDetector.detect(actualFrame);
	if(temp.size() == 0)
		return;
	marker = temp[0];fia
}
WrapperAG::~WrapperAG() {
	// TODO Auto-generated destructor stub
}

