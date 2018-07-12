// FaceLivingDetector.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <dlib/image_processing/frontal_face_detector.h>
#include <dlib/image_processing/render_face_detections.h>
#include <dlib/image_processing.h>
#include <dlib/gui_widgets.h>
#include <dlib/image_io.h>
#include <iostream>
#include <opencv2/opencv.hpp>
#include <dlib/opencv.h>

using namespace dlib;
using namespace std;
using namespace cv;

dlib::frontal_face_detector detector;
dlib::shape_predictor predictor;

void init_fece_detector()
{
	const string model_path = "..\\models\\shape_predictor_68_face_landmarks.dat";
	detector = get_frontal_face_detector();	
	deserialize(model_path.c_str()) >> predictor;
}

int main()
{
	init_fece_detector();
	VideoCapture cp(0);
	printf("fdsfds");
	Mat frame;
	while (true) {
		cp >> frame;
		if (frame.empty()) continue;
		dlib::cv_image<dlib::bgr_pixel> img(frame);
		std::vector<dlib::rectangle> faces = detector(img);
		if (!faces.empty()) {
			full_object_detection shape = predictor(img, faces[0]);
			for (int i = 0; i < 68; i++) {
				circle(frame, Point(shape.part(i).x(), shape.part(i).y()), 1, Scalar(0, 255, 0), 2);
			}
		}
		imshow("frame", frame);
		waitKey(10);
	}

    return 0;
}

