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


using namespace dlib;
using namespace nlohmann;

FacialLandmarkDetector* FacialLandmarkDetector::facialLandmarkDetector = nullptr;

void pointReader(std::vector<dlib::full_object_detection> dets, std::vector<RawFacePos>* rawPoses);

json praseRawData2JSON(RawFacePos& pos, RawFacePos& nutral);

json praseRawData2JSON(RawFacePos& pos);

cv::Vec3f eyeDetection(cv::Mat image, CvRect size);

cv::Mat EdgeDetect(cv::Mat& edgeimg);

std::vector<cv::Vec3f> Hough(cv::Mat& midImage, CvRect size);

void FacialLandmarkDetector::detection()
{
	try
	{
		cv::VideoCapture cap(0);
		if (!cap.isOpened())
		{
			std::cerr << "Unable to connect to camera" << std::endl;
			return;
		}

		image_window win;

		// Load face detection and pose estimation models.
		frontal_face_detector detector = get_frontal_face_detector();
		shape_predictor pose_model;
		deserialize("E:\\project\\Live2D_VideoChat\\res\\shape_predictor_68_face_landmarks.dat") >> pose_model; //TODO:Fix Path

		// Grab and process frames until the main window is closed by the user.
		while (!win.is_closed())
		{
			// Grab a frame
			cv::Mat temp;
			if (!cap.read(temp))
			{
				break;
			}
			// Turn OpenCV's Mat into something dlib can deal with.  Note that this just
			// wraps the Mat object, it doesn't copy anything.  So cimg is only valid as
			// long as temp is valid.  Also don't do anything to temp that would cause it
			// to reallocate the memory which stores the image as that will make cimg
			// contain dangling pointers.  This basically means you shouldn't modify temp
			// while using cimg.
			cv_image<dlib::bgr_pixel> cimg(temp);
			if (temp.empty())
				continue;
			// Detect faces 
			std::vector<dlib::rectangle> faces = detector(cimg);
			json data;
			
				// Find the pose of each face.
				std::vector<dlib::full_object_detection> shapes;
				for (unsigned long i = 0; i < faces.size(); ++i)
					shapes.push_back(pose_model(cimg, faces[i]));

				std::vector<RawFacePos> rawPoses(shapes.size());
				pointReader(shapes, &rawPoses);

			if (faces.size() != 0) {
				//Capture one fram as nutural face
				if (captureNuturalFaceFlag) {
					this->nuturalFace = rawPoses[1];

					RawFacePos pos = rawPoses[1];
					int margin = 10;
					CvRect Lrect(pos.leftEyeMinX - margin, pos.leftEyeMinY - margin, pos.leftEyeMaxX - pos.leftEyeMinX + margin, pos.leftEyeMaxY - pos.leftEyeMinY + margin);
					cv::Mat Leye = temp(Lrect);
					CvRect Rrect(pos.rightEyeMinX - margin, pos.rightEyeMinY - margin, pos.rightEyeMaxX - pos.rightEyeMinX + margin, pos.rightEyeMaxY - pos.rightEyeMinY + margin);
					cv::Mat Reye = temp(Rrect);
					this->nuturalFace.leftIris = eyeDetection(Leye, Lrect);
					this->nuturalFace.rightIris = eyeDetection(Reye, Rrect);

					captureNuturalFaceFlag = false;
				}

				if (nuturalFace.inited)
					data = praseRawData2JSON(rawPoses[1], nuturalFace);
				else
					data = praseRawData2JSON(rawPoses[1]);

				//eyeProcess
				{
					RawFacePos pos = rawPoses[1];
					int margin = 10;
					CvRect Lrect = CvRect(pos.leftEyeMinX - margin, pos.leftEyeMinY - margin, pos.leftEyeMaxX - pos.leftEyeMinX + margin, pos.leftEyeMaxY - pos.leftEyeMinY + margin);
					std::cout << Lrect.x << Lrect.y << std::endl;
        			cv::Mat Leye = temp(Lrect);
					CvRect Rrect(pos.rightEyeMinX - margin, pos.rightEyeMinY - margin, pos.rightEyeMaxX - pos.rightEyeMinX + margin, pos.rightEyeMaxY - pos.rightEyeMinY + margin);
					cv::Mat Reye = temp(Rrect);
					cv::Vec3f Lpos = eyeDetection(Leye, Lrect);
					cv::Vec3f Rpos = eyeDetection(Reye, Rrect);
					if (this->nuturalFace.inited) {
						data["eye"]["eyeBallX"] = (((Lpos[1] / (this->nuturalFace.leftIris[1])) - 1) + ((Rpos[1] / (this->nuturalFace.rightIris[1])) - 1)) / 2;
						data["eye"]["eyeBallY"] = (((Lpos[1] / (this->nuturalFace.leftIris[2])) - 1) + ((Rpos[1] / (this->nuturalFace.rightIris[2])) - 1)) / 2;
					}
					else {
						data["eye"]["eyeBallX"] = (((Lpos[1] / (Lrect.width / 2.0)) - 1) + ((Rpos[1] / (Rrect.width / 2.0)) - 1)) / 2;
						data["eye"]["eyeBallY"] = (((Lpos[2] / (Lrect.width / 2.0)) - 1) + ((Rpos[2] / (Rrect.width / 2.0)) - 1)) / 2;
					}

				}

			}
			// Display it all on the screen
			if (debug) {
				std::cout << data.dump(1) << std::endl;
				system("cls");
				win.clear_overlay();
				win.set_image(cimg);
				win.add_overlay(render_face_detections(shapes));
			}

		}
	}
	catch (serialization_error & e)
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
					pos.angle = 90 - atan(((double)maxY - minY) / (maxX - minX));
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
	ret["head"]["angleX"] = ((pos.rightEyeMinX - pos.faceRightX)/(pos.rightEyeMaxX-pos.rightEyeMinX+1)-1)*30;//Face ratial + -?
	//The distance between top face and eye middle line / eye hight *30
	ret["head"]["angleY"] = (pos.faceTopY - (((pos.leftEyeMaxY + pos.rightEyeMaxY) / 2 - (pos.leftEyeMinY + pos.rightEyeMinY) / 2) / 2 + (pos.leftEyeMinY + pos.rightEyeMinY) / 2)) / ((pos.leftEyeMaxY + pos.rightEyeMaxY) / 2 - (pos.leftEyeMinY + pos.rightEyeMinY) / 2 + 1) * 30;
	if (pos.leftEyeMaxY - pos.leftEyeMinY < 0.25 * (pos.leftEyeMaxX - pos.leftEyeMinX))
		ret["eye"]["eyeLOpen"] = 0.0;
	else 
		ret["eye"]["eyeLOpen"] = 2.0;
	ret["mouthOpen"] = (pos.LipsInnerMaxY - pos.LipsInnerMinY) / ((pos.noseMiddleMaxY - pos.noseMiddleMinY + 1 ) / 2.0);
	return ret;

}

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
	cv::cvtColor(edgeimg, edgeimg, cv::COLOR_BGR2GRAY);// 彩色图转换成灰度图
	cv::GaussianBlur(edgeimg, edgeimg, cv::Size(9, 9), 2, 2);// 高斯平滑
	equalizeHist(edgeimg, edgeimg);//直方图均值化
	Canny(edgeimg, edgeout, 100, 200, 3);//输入图像,输出图像,低阈值,高阈值，opencv建议是低阈值的3倍,内部sobel滤波器大小
	return edgeout;
}
//	————————————————
//		版权声明：本文为CSDN博主「zhouyongxiu」的原创文章，遵循 CC 4.0 BY - SA 版权协议，转载请附上原文出处链接及本声明。
//		原文链接：https ://blog.csdn.net/zyx1990412/article/details/51219076

using namespace cv;

std::vector<Vec3f> Hough(Mat& midImage, CvRect size)
{
	std::vector<Vec3f> circles;
	HoughCircles(midImage, circles, HOUGH_GRADIENT, 1.5, 5, 100, 20, size.height / 4, size.height / 3);
	return circles;
}
