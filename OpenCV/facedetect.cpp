#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include <iostream>
#include <stdio.h>

#define ESC 27

using namespace std;
using namespace cv;

int main(int argc, const char** argv)
{
	CascadeClassifier face_cascade;
	face_cascade.load("haarcascade_frontalface_alt.xml");

	VideoCapture captureDevice;
	captureDevice.open(0);

	Mat captureFrame;
	Mat grayscaleFrame;

	namedWindow("RORI_EYE", 1);

 	bool stop = false;

	while(!stop)
	{
		captureDevice >> captureFrame;

		cvtColor(captureFrame, grayscaleFrame, CV_BGR2GRAY);
		equalizeHist(grayscaleFrame, grayscaleFrame);

		std::vector<Rect> faces;

		//Find Faces
		face_cascade.detectMultiScale(grayscaleFrame, faces, 1.1, 3, CV_HAAR_FIND_BIGGEST_OBJECT|CV_HAAR_SCALE_IMAGE, Size(30,30));

		for(int i = 0; i < faces.size(); i++)
		{
			Point pt1(faces[i].x + faces[i].width, faces[i].y + faces[i].height);
			Point pt2(faces[i].x, faces[i].y);

			rectangle(captureFrame, pt1, pt2, cvScalar(10, 30, 255, 0), 1, 8, 0);
		}

		imshow("RORI_EYE", captureFrame);

		int key = waitKey(10);
		if(key == ESC)
			stop = true;    
	}


	return 0;
}
