/*
 * WrapperCV.cpp
 *
 *  Created on: 28/6/2018
 *      Author: rober
 */

#include <Common/WrapperCV.h>
using namespace std;
using namespace cv;

WrapperCV::WrapperCV() {
	// TODO Auto-generated constructor stub

}

WrapperCV::~WrapperCV() {
	// TODO Auto-generated destructor stub
}
cv::Mat img;
void WrapperCV::ObtenerHomografia(String videopath){
	Point2f src_vertices[4];
	Point2f dst_vertices[4];
	try {
		namedWindow("SeleccionarPuntos",cv::WINDOW_AUTOSIZE);
		cv::setMouseCallback("SeleccionarPuntos", onMouse, &puntosHomografia);
		VideoCapture cap("/home/rober/Vídeos/in-tenis01.mp4");
		if( !cap.isOpened()){
			 cout << "Cannot open the video file" << endl;
			 return;
		}
		Mat primerFrame;
		bool success = cap.read(primerFrame);
		img = primerFrame;
		if (!success){
		  cout << "Cannot read  frame " << endl;
		  return;
		}
		int key = 0;
		while(key != 27)
		{
			imshow("SeleccionarPuntos", primerFrame);
			key = cv::waitKey(1);
			primerFrame = img;
		    if (puntosHomografia.size() == 4)
		        break;
		}

		int i = 0;
		for (auto it = puntosHomografia.begin(); it != puntosHomografia.end(); ++it)
		{
			src_vertices[i] = (*it);
			i++;
		}

		dst_vertices[0] = Point(0, 0);
		dst_vertices[1] = Point(11,0);
		dst_vertices[2] = Point(11,23);
		dst_vertices[3] = Point(0,23);

		Mat warpMatrix = cv::getPerspectiveTransform(src_vertices, dst_vertices);
		Mat M;
		cv::invert(warpMatrix,M);
		std::vector<Point2f> camera_corners;
		std::vector<Point2f> world_corners;
		world_corners.push_back(Point(0,-23));
		world_corners.push_back(Point(11,-23));

		cv::perspectiveTransform(world_corners,camera_corners, M);

		for (auto it = camera_corners.begin(); it != camera_corners.end(); ++it)
		{

			cv::circle(primerFrame,(*it),5,Scalar( 255, 0, 0 ),-1);
		}

		cv::imshow("image", primerFrame);
		cv::waitKey(40000);


		cout<<"Transformación calculada con éxito!"<<endl;
	} catch (exception& e) {
		cout << e.what() << '\n';
	}

}

void WrapperCV::onMouse(int evt, int x, int y, int flags, void* param) {
    if(evt == cv::EVENT_LBUTTONDOWN) {
    	cout<<x<<'\t'<<y<<endl;
        std::vector<cv::Point>* ptPtr = (std::vector<cv::Point>*)param;
        ptPtr->push_back(cv::Point(x,y));
        cv::circle(img,cv::Point(x,y),10,10,-1);
    }
}

