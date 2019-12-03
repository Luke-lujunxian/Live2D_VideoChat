// The contents of this file are in the public domain. See LICENSE_FOR_EXAMPLE_PROGRAMS.txt
/*

	This example program shows how to find frontal human faces in an image and
	estimate their pose.  The pose takes the form of 68 landmarks.  These are
	points on the face such as the corners of the mouth, along the eyebrows, on
	the eyes, and so forth.


	This example is essentially just a version of the face_landmark_detection_ex.cpp
	example modified to use OpenCV's VideoCapture object to read from a camera instead
	of files.


	Finally, note that the face detector is fastest when compiled with at least
	SSE2 instructions enabled.  So if you are using a PC with an Intel or AMD
	chip then you should enable at least SSE2 instructions.  If you are using
	cmake to compile this program you can enable them by using one of the
	following commands when you create the build project:
		cmake path_to_dlib_root/examples -DUSE_SSE2_INSTRUCTIONS=ON
		cmake path_to_dlib_root/examples -DUSE_SSE4_INSTRUCTIONS=ON
		cmake path_to_dlib_root/examples -DUSE_AVX_INSTRUCTIONS=ON
	This will set the appropriate compiler options for GCC, clang, Visual
	Studio, or the Intel compiler.  If you are using another compiler then you
	need to consult your compiler's manual to determine how to enable these
	instructions.  Note that AVX is the fastest but requires a CPU from at least
	2011.  SSE4 is the next fastest and is supported by most current machines.
*/

#include <dlib/opencv.h>
#include <opencv2/highgui/highgui.hpp>
#include <dlib/image_processing/frontal_face_detector.h>
#include <dlib/image_processing/render_face_detections.h>
#include <dlib/image_processing.h>
#include <dlib/gui_widgets.h>
#include <detection.h>
#include <cmath>


using namespace dlib;
using namespace nlohmann;

FacialLandmarkDetector* FacialLandmarkDetector::facialLandmarkDetector = nullptr;

void pointReader(std::vector<dlib::full_object_detection> dets, std::vector<RawFacePos>* rawPoses);

json praseRawData2JSON(RawFacePos& pos, RawFacePos& nutral);

json praseRawData2JSON(RawFacePos& pos);



double meter(double A, double B, double C, double x, double y)
{
	double diversion = A * x + B * y + C;
	return diversion / sqrt(pow(A, 2) + pow(B, 2));
}

double eyebrow_move(dlib::point& p1, dlib::point& p2, double slope, double last, double rate)
{
	double bias = p1.y() - slope * p1.x();
	double distance = sqrt(pow(p1.x() - p2.x(), 2) + pow(p1.y() - p2.y(), 2));
	double diversion = meter(slope, -1, bias, p2.x(), p2.y());
	double result = (diversion / distance - 0.45) * 6;
	result = last * (1 - rate) + result * rate;
	return result;
}

double eye_open(dlib::point& p1, dlib::point& p2, dlib::point& v11, dlib::point& v12, dlib::point& v21, dlib::point& v22, double last, double rate)
{
	double distance = sqrt(pow(p1.x() - p2.x(), 2) + pow(p1.y() - p2.y(), 2));
	double slope = (double)(p2.y() - p1.y()) / (double)(p2.x() - p1.x());
	double bias = p2.y() - slope * p2.x();
	double d1 = abs(meter(slope, -1, bias, v11.x(), v11.y()));
	double d2 = abs(meter(slope, -1, bias, v12.x(), v12.y()));
	double diversion = d1 > d2 ? d1 : d2;
	d1 = abs(meter(slope, -1, bias, v21.x(), v21.y()));
	d2 = abs(meter(slope, -1, bias, v22.x(), v22.y()));
	diversion += d1 > d2 ? d1 : d2;
	double ratio = (diversion / distance - 0.18) * 8;
	ratio = ((int)(ratio * 10.0)) / 10.0;
	ratio = last * (1 - rate) + ratio * rate;
	return ratio;
}


void FacialLandmarkDetector::detection()
{
	dlib::frontal_face_detector detector;
	dlib::shape_predictor pose_model;
	cv::CascadeClassifier haarcascade_eye_tree_eyeglasses;
	// live2d parameters
	float x_rotate = 0.0f;
	float y_rotate = 0.0f;
	float z_rotate = 0.0f;

	float left_eye = 1.0f;
	float right_eye = 1.0f;

	float eyebrow_left = 0.0f;
	float eyebrow_right = 0.0f;

	float eyeBallX = 0.0f;
	float eyeBallY = 0.0f;

	float mouth_open = 0.0f;
	int leftEyeMaxX = 0;
	int leftEyeMinX = 0;
	int leftEyeMinY = 0;
	int leftEyeMaxY = 0;
	int rightEyeMaxX = 0;
	int rightEyeMinX = 0;
	int rightEyeMinY = 0;
	int rightEyeMaxY = 0;
	try
	{
		cv::VideoCapture camera(0);
		if (!camera.isOpened())
		{
			std::cerr << "Unable to connect to camera" << std::endl;
			return;
		}

		//image_window win;

		// Load face detection and pose estimation models.
		frontal_face_detector detector = get_frontal_face_detector();
		shape_predictor pose_model;
		haarcascade_eye_tree_eyeglasses.load("E:\\opencv-4.1.2\\data\\haarcascades\\haarcascade_eye_tree_eyeglasses.xml");
		deserialize("E:\\project\\Live2D_VideoChat\\res\\shape_predictor_68_face_landmarks.dat") >> pose_model; //TODO:Fix Path

		// Grab and process frames until the main window is closed by the user.
		while (camera.isOpened())
		{
			cv::Mat buff, temp;
			camera.read(temp);
			//cv::GaussianBlur(temp, buff, cv::Size(5, 5), 5, 5);
			cv::flip(temp, temp, 1);

			dlib::cv_image<dlib::bgr_pixel> cimg(temp);
			std::vector<dlib::rectangle> faces = detector(cimg);
			std::vector<dlib::full_object_detection> shapes;

			for (unsigned long i = 0; i < faces.size(); ++i)
				shapes.push_back(pose_model(cimg, faces[i]));

			if (!shapes.empty()) {
				for (int i = 0; i < 68; i++) {
					cv::circle(temp, cvPoint(shapes[0].part(i).x(), shapes[0].part(i).y()), 2, cv::Scalar(0, 0, 255), -1);
				}

				int div_x = shapes[0].part(16).x() - shapes[0].part(0).x();
				int div_y = shapes[0].part(16).y() - shapes[0].part(0).y();
				double center_x = shapes[0].part(0).x() + div_x / 2.0;
				double center_y = shapes[0].part(0).y() + div_y / 2.0;
				double slope = (double)(div_y) / (double)(div_x);
				double bias = center_y - slope * center_x;
				double x_proj = (slope * (shapes[0].part(30).y() - bias) + shapes[0].part(30).x()) / (1 + pow(slope, 2));
				double y_proj = slope * x_proj + bias;
				double diversion = sqrt(pow(x_proj - shapes[0].part(0).x(), 2) + pow(y_proj - shapes[0].part(0).y(), 2));
				double distance = sqrt(pow(shapes[0].part(16).x() - shapes[0].part(0).x(), 2) + pow(shapes[0].part(16).y() - shapes[0].part(0).y(), 2));

				double rate = 0.5;
				// Ax+By+C/sqrt(A^2+B^2)
				x_rotate = x_rotate * (1 - rate) + asin(diversion / distance - 0.5) * 3.14 * 40.0 * rate;

				// nose to eye around 1/6 head
				diversion = meter(slope, -1, bias, shapes[0].part(30).x(), shapes[0].part(30).y());
				diversion = diversion + 1.0 / 6 * distance;
				y_rotate = y_rotate * (1 - rate) + asin(diversion / distance) * 3.14 * 40.0 * rate;

				z_rotate = z_rotate * (1 - rate) + atan(slope) * 3.14 * 40 * rate;

				// eye
				left_eye = eye_open(shapes[0].part(36), shapes[0].part(39), shapes[0].part(37), shapes[0].part(38), shapes[0].part(40), shapes[0].part(41), left_eye, rate);
				right_eye = eye_open(shapes[0].part(42), shapes[0].part(45), shapes[0].part(43), shapes[0].part(44), shapes[0].part(46), shapes[0].part(47), right_eye, rate);

				// eyebrow
				eyebrow_left = eyebrow_move(shapes[0].part(17), shapes[0].part(19), slope, eyebrow_left, rate);
				eyebrow_right = eyebrow_move(shapes[0].part(26), shapes[0].part(24), slope, eyebrow_right, rate);

				// mouth
				diversion = sqrt(pow(shapes[0].part(62).x() - shapes[0].part(66).x(), 2) + pow(shapes[0].part(62).y() - shapes[0].part(66).y(), 2));
				distance = sqrt(pow(shapes[0].part(60).x() - shapes[0].part(64).x(), 2) + pow(shapes[0].part(60).y() - shapes[0].part(64).y(), 2));
				mouth_open = (diversion / distance - 0.15) * 2;


				dlib::full_object_detection& d = shapes[0];
				{

					int minX = INT_MAX, maxX = 0, minY = INT_MAX, maxY = 0;
					for (unsigned long i = 37; i <= 41; ++i) {
						minX = minX < d.part(i).x() ? minX : d.part(i).x();
						maxX = maxX > d.part(i).x() ? maxX : d.part(i).x();
						minY = minY < d.part(i).y() ? minY : d.part(i).y();
						maxY = maxY > d.part(i).y() ? maxY : d.part(i).y();
					}
					leftEyeMaxX = maxX;
					leftEyeMinX = minX;
					leftEyeMinY = minY;
					leftEyeMaxY = maxY;

				}

				// Right eye
				{
					int minX = INT_MAX, maxX = 0, minY = INT_MAX, maxY = 0;
					for (unsigned long i = 43; i <= 47; ++i) {
						minX = minX < d.part(i).x() ? minX : d.part(i).x();
						maxX = maxX > d.part(i).x() ? maxX : d.part(i).x();
						minY = minY < d.part(i).y() ? minY : d.part(i).y();
						maxY = maxY > d.part(i).y() ? maxY : d.part(i).y();
					}
					rightEyeMaxX = maxX;
					rightEyeMinX = minX;
					rightEyeMinY = minY;
					rightEyeMaxY = maxY;
				}

				try {
					std::vector<cv::Rect> eyes;
					cv::Mat eyesRaw;
					camera.read(eyesRaw);
					cv::flip(eyesRaw, eyesRaw, 1);
					cv::cvtColor(eyesRaw, eyesRaw, cv::COLOR_BGR2GRAY);// ��ɫͼת���ɻҶ�ͼ
					equalizeHist(eyesRaw, eyesRaw);//ֱ��ͼ��ֵ��
					haarcascade_eye_tree_eyeglasses.detectMultiScale(eyesRaw, eyes,
						1.1, 2, 0
						//|CV_HAAR_FIND_BIGGEST_OBJECT
						//|CV_HAAR_DO_ROUGH_SEARCH
						| cv::CASCADE_SCALE_IMAGE
						,
						cv::Size(30, 30));



					for (std::vector<cv::Rect>::const_iterator r = eyes.begin(); r != eyes.end(); r++)
					{
						cv::Point center;
						int radius;
						//center������Ϊͫ�׵�����
						center.x = cvRound(r->x + r->width * 0.5);
						center.y = cvRound(r->y + r->height * 0.5);
						//radius = (int)(cvRound(r->width + r->height)*0.25);
						radius = 2;
						//cv::imshow("eyesRaw", eyesRaw);
						int margin = 10;
						if (center.x < rightEyeMaxX + margin && center.x > rightEyeMinX - margin && center.y < rightEyeMaxY + margin && center.y > rightEyeMinY - margin) {
							eyeBallX = (center.x - ((rightEyeMaxX - rightEyeMinX) / 2.0f + rightEyeMinX)) / (rightEyeMaxX - rightEyeMinX) * 2;
							eyeBallY = (center.y - ((rightEyeMaxY - rightEyeMinY) / 2.0f + rightEyeMinY)) / (rightEyeMaxY - rightEyeMinY) * 2;
							cv::circle(temp, center, radius, cv::Scalar(255, 0, 0), 3, 8, 0);

						}
						else if (center.x < leftEyeMaxX + margin && center.x > leftEyeMinX - margin && center.y < leftEyeMaxY + margin && center.y > leftEyeMinY - margin) {
							eyeBallX = (center.x - ((leftEyeMaxX - leftEyeMinX) / 2.0f + leftEyeMinX)) / (leftEyeMaxX - leftEyeMinX) * 2;
							eyeBallY = (center.y - ((leftEyeMaxY - leftEyeMinY) / 2.0f + leftEyeMinY)) / (leftEyeMaxY - leftEyeMinY) * 2;
							cv::circle(temp, center, radius, cv::Scalar(255, 0, 0), 3, 8, 0);

						}
						else {
							cv::circle(temp, center, radius, cv::Scalar(0, 255, 0), 3, 8, 0);
						}

					}
				}
				catch (std::exception e) {
					std::cout << e.what();
				}


				//��������������������������������
				//	��Ȩ����������ΪCSDN������IT�޵��ߡ���ԭ�����£���ѭ CC 4.0 BY - SA ��ȨЭ�飬ת���븽��ԭ�ĳ������Ӽ���������
				//	ԭ�����ӣ�https ://blog.csdn.net/computerme/article/details/38142125

				//Finalize and put into Json
				{
					json data;
					data["head"]["angleZ"] = z_rotate;
					data["head"]["angleX"] = x_rotate;
					data["head"]["angleY"] = y_rotate;
					data["eye"]["eyeLOpen"] = left_eye;
					data["eye"]["eyeROpen"] = right_eye;
					data["eye"]["eyeBallX"] = eyeBallX;
					data["eye"]["eyeBallY"] = eyeBallY;
					data["brow"]["browLY"] = eyebrow_left;
					data["brow"]["browRY"] = eyebrow_right;
					data["mouthOpen"] = mouth_open;

					Network::getInstance()->getSendJson()->erase("data");
					Network::getInstance()->getSendJson()->emplace("data",data);
					
				}

			}
			else
			{
				x_rotate = 0.0f;
				y_rotate = 0.0f;
				z_rotate = 0.0f;
				left_eye = 1.0f;
				right_eye = 1.0f;
				eyebrow_left = 0.0f;
				eyebrow_right = 0.0f;
				mouth_open = 0.0f;
				eyeBallX = 0.0f;
				eyeBallY = 0.0f;
			}

			//double t = (live2d::UtSystem::getUserTimeMSec() / 1000.0) * 2 * 3.14;
			//live2DModel->setParamFloat("PARAM_ANGLE_Z", (float)(30 * sin(t / 3.0)));
			
			//cv::waitKey(30);
			//Display it all on the screen  
			//
			// Display it all on the screen
			if (debug) {
				//system("cls");
				std::cout << "x_rotate" << x_rotate << "\n"
					<< "y_rotate" << y_rotate << "\n"
					<< "z_rotate" << z_rotate << "\n"
					<< "left_eye" << left_eye << "\n"
					<< "right_eye" << right_eye << "\n"
					<< "eyebrow_left" << eyebrow_left << "\n"
					<< "eyebrow_right" << eyebrow_right << "\n"
					<< "mouth_open" << mouth_open << "\n"
					<< "eyeBallX" << eyeBallX << "\n"
					<< "eyeBallY" << eyeBallY << "\n" << std::endl;
				cv::imshow("Feature points", temp);
				cv::waitKey(30);

			}
		}
			

		
	}catch (serialization_error & e)
	{
		std::cerr << "Fail to load model" << std::endl;
		this->ModelLoadError = true;
		return;
	}
	catch (std::exception & e)
	{
		std::cerr << e.what() << std::endl;
		return;
	}
}

//[in]dets
//[out]rawPoses
//Part of the code from
// Copyright (C) 2014  Davis E. King (davis@dlib.net)
// License: Boost Software License   See LICENSE.txt for the full license.
void pointReader(std::vector<dlib::full_object_detection> dets, std::vector<RawFacePos>* rawPoses) {
	
	for (unsigned long i = 0; i < dets.size(); ++i)
	{
		DLIB_CASSERT(dets[i].num_parts() == 68 || dets[i].num_parts() == 5,
			"\t std::vector<image_window::overlay_line> render_face_detections()"
			<< "\n\t You have to give either a 5 point or 68 point face landmarking output to this function. "
			<< "\n\t dets[" << i << "].num_parts():  " << dets[i].num_parts()
		);

		const full_object_detection& d = dets[i];
		RawFacePos pos;
		if (d.num_parts() == 5)
		{

		}
		else
		{
			// Around Chin. Ear to Ear
			{
				volatile int minX = INT_MAX, maxX = 0, minY = INT_MAX, maxY = 0;
				for (unsigned long i = 1; i <= 16; ++i) {
					minX = minX < d.part(i).x() ? minX : d.part(i).x();
					maxX = maxX > d.part(i).x() ? maxX : d.part(i).x();
					minY = minY < d.part(i).y() ? minY : d.part(i).y();
					maxY = maxY > d.part(i).y() ? maxY : d.part(i).y();
				}
				pos.faceLeftX = minX;
				pos.faceRightX = maxX;
				pos.faceDownY = maxY;
				pos.faceTopY = minY;
			}
			
			// Line on top of nose
			{
				int minX = INT_MAX, maxX = 0, minY = INT_MAX, maxY = 0;
				for (unsigned long i = 28; i <= 30; ++i) {
					minX = minX < d.part(i).x() ? minX : d.part(i).x();
					maxX = maxX > d.part(i).x() ? maxX : d.part(i).x();
					minY = minY < d.part(i).y() ? minY : d.part(i).y();
					maxY = maxY > d.part(i).y() ? maxY : d.part(i).y();
				}
				pos.noseMiddleMaxX = maxX;
				pos.noseMiddleMinX = minX;
				pos.noseMiddleMaxY = maxY;
				pos.noseMiddleMinX = minY;
				if (maxX - minX != 0)
					pos.angle = atan(((double)(maxX - minX) /(double)maxY - minY));
				else
					pos.angle = 0;
			}

			// left eyebrow
			{
				int sum = 0;
				for (unsigned long i = 18; i <= 21; ++i) {
					sum += d.part(i).y();
				}
				pos.leftEyebrowY = sum / 4;
			}

			// Right eyebrow
			{
				int sum = 0;
				for (unsigned long i = 23; i <= 26; ++i) {
					sum += d.part(i).y();
				}
				pos.rightEyebrowY = sum / 4;
			}
			// Bottom part of the nose
			//for (unsigned long i = 31; i <= 35; ++i){}
			// Line from the nose to the bottom part above

			// Left eye
			{
				int minX = INT_MAX, maxX = 0, minY = INT_MAX, maxY = 0;
				for (unsigned long i = 37; i <= 41; ++i){
					minX = minX < d.part(i).x() ? minX : d.part(i).x();
					maxX = maxX > d.part(i).x() ? maxX : d.part(i).x();
					minY = minY < d.part(i).y() ? minY : d.part(i).y();
					maxY = maxY > d.part(i).y() ? maxY : d.part(i).y();
				}
				pos.leftEyeMaxX = maxX;
				pos.leftEyeMinX = minX;
				pos.leftEyeMinY = minY;
				pos.leftEyeMaxY = maxY;

			}

			// Right eye
			{
				int minX = INT_MAX, maxX = 0, minY = INT_MAX, maxY = 0;
				for (unsigned long i = 43; i <= 47; ++i) {
					minX = minX < d.part(i).x() ? minX : d.part(i).x();
					maxX = maxX > d.part(i).x() ? maxX : d.part(i).x();
					minY = minY < d.part(i).y() ? minY : d.part(i).y();
					maxY = maxY > d.part(i).y() ? maxY : d.part(i).y();
				}
				pos.rightEyeMaxX = maxX;
				pos.rightEyeMinX = minX;
				pos.rightEyeMinY = minY;
				pos.rightEyeMaxY = maxY;
			}


			// Lips outer part
			for (unsigned long i = 49; i <= 59; ++i){}


			// Lips inside part
			{
				int minY = INT_MAX, maxY = 0;
				for (unsigned long i = 61; i <= 67; ++i) {
					minY = minY < d.part(i).y() ? minY : d.part(i).y();
					maxY = maxY > d.part(i).y() ? maxY : d.part(i).y();
				}
				pos.LipsInnerMaxY = maxY;
				pos.LipsInnerMinY = minY;

			}

		}

		rawPoses->push_back(pos);
	}

}

json praseRawData2JSON(RawFacePos& pos, RawFacePos& nutral) {
	json ret;
	ret["head"]["angleZ"] = pos.angle;
	ret["head"]["angleX"] = (((pos.noseMiddleMaxX + pos.noseMiddleMinX) / 2.0 - pos.faceLeftX) / ((nutral.leftEyeMaxY - nutral.leftEyeMinY) * 2) - 1) * 30.0;
	ret["head"]["angleY"] = asin((pos.faceDownY - pos.noseMiddleMaxY) / ((nutral.faceDownY - nutral.noseMiddleMaxY) * ((pos.noseMiddleMaxY - pos.noseMiddleMinY) / (nutral.noseMiddleMaxY - nutral.noseMiddleMinY))+1));
	ret["mouthOpen"] = (pos.LipsInnerMaxY - pos.LipsInnerMinY) / ((pos.noseMiddleMaxY - pos.noseMiddleMinY) / 2.0);
	return ret;
}

json praseRawData2JSON(RawFacePos& pos) {
	json ret;
	ret["head"]["angleZ"] = pos.angle;
	ret["head"]["angleX"] = (((((double)pos.faceRightX - pos.rightEyeMaxX) / ((double)pos.rightEyeMaxX - pos.rightEyeMinX + 1) - 1)) * 30.0 + (((double)pos.leftEyeMinX - pos.faceLeftX) / ((double)pos.leftEyeMaxX - pos.leftEyeMinX + 1) - 1) * -30.0)/2;//Face ratial + -?
	//The distance between top face and eye middle line / eye hight *30
	ret["head"]["angleY"] = (pos.faceTopY - (((pos.leftEyeMaxY + pos.rightEyeMaxY) / 2 - (pos.leftEyeMinY + pos.rightEyeMinY) / 2) / 2 + (pos.leftEyeMinY + pos.rightEyeMinY) / 2)) / ((pos.leftEyeMaxY + pos.rightEyeMaxY) / 2 - (pos.leftEyeMinY + pos.rightEyeMinY) / 2 + 1) * 30;
	if (((double)pos.leftEyeMaxY - pos.leftEyeMinY) / ((double)pos.leftEyeMaxX - pos.leftEyeMinX) < 0.4)
		ret["eye"]["eyeLOpen"] = 0.0;
	else
		ret["eye"]["eyeLOpen"] = 2.0;

	if ((double)pos.rightEyeMaxY - pos.rightEyeMinY < 0.4 * ((double)pos.rightEyeMaxX - pos.rightEyeMinX))
		ret["eye"]["eyeROpen"] = 0.0;
	else
		ret["eye"]["eyeROpen"] = 2.0;
	ret["mouthOpen"] = ((double)pos.LipsInnerMaxY - pos.LipsInnerMinY) / (((pos.noseMiddleMaxY - pos.noseMiddleMinY + 1 ) / 8.0));
	return ret;

}

/*
cv::Vec3f eyeDetection(cv::Mat image, CvRect size) {

	cv::Mat Lprocessed = EdgeDetect(image);
	std::vector<cv::Vec3f> ret = Hough(Lprocessed, size);
	if (ret.size() >= 2)
		return ret[1];
	else
		return cv::Vec3f(0,0,0);
}

cv::Mat EdgeDetect(cv::Mat& edgeimg)
{
	cv::Mat edgeout;
	cv::cvtColor(edgeimg, edgeimg, cv::COLOR_BGR2GRAY);// ��ɫͼת���ɻҶ�ͼ
	cv::GaussianBlur(edgeimg, edgeimg, cv::Size(9, 9), 2, 2);// ��˹ƽ��
	equalizeHist(edgeimg, edgeimg);//ֱ��ͼ��ֵ��
	Canny(edgeimg, edgeout, 100, 200, 3);//����ͼ��,���ͼ��,����ֵ,����ֵ��opencv�����ǵ���ֵ��3��,�ڲ�sobel�˲�����С
	return edgeout;
}
//	��������������������������������
//		��Ȩ����������ΪCSDN������zhouyongxiu����ԭ�����£���ѭ CC 4.0 BY - SA ��ȨЭ�飬ת���븽��ԭ�ĳ������Ӽ���������
//		ԭ�����ӣ�https ://blog.csdn.net/zyx1990412/article/details/51219076

using namespace cv;

std::vector<Vec3f> Hough(Mat& midImage, CvRect size)
{
	std::vector<Vec3f> circles;
	HoughCircles(midImage, circles, HOUGH_GRADIENT, 1.5, 5, 100, 20, size.height / 4, size.height / 3);
	return circles;
}

*/