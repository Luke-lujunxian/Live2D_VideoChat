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
#include <helper.h>

using namespace dlib;
using namespace nlohmann;

void pointReader(std::vector<dlib::full_object_detection> dets, std::vector<RawFacePos>* rawPoses);

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

			// Detect faces 
			std::vector<dlib::rectangle> faces = detector(cimg);
			// Find the pose of each face.
			std::vector<dlib::full_object_detection> shapes;
			for (unsigned long i = 0; i < faces.size(); ++i)
				shapes.push_back(pose_model(cimg, faces[i]));

			std::vector<RawFacePos> rawPoses(shapes.size());
			pointReader(shapes, &rawPoses);

			//Capture one fram as nutural face
			if (captureNuturalFaceFlag) {
				this->nuturalFace = rawPoses[0];
				captureNuturalFaceFlag = false;
			}

			// Display it all on the screen
			if (debug) {
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
				int minX = 0, maxX = 0, maxY = 0;
				for (unsigned long i = 1; i <= 16; ++i) {
					minX = minX < d.part(i).x() ? minX : d.part(i).x();
					maxX = maxX > d.part(i).x() ? maxX : d.part(i).x();
					maxY = maxY > d.part(i).y() ? maxY : d.part(i).y();
				}
				pos.faceLeftX = minX;
				pos.faceRightX = maxX;
				pos.faceDownY = maxY;
			}
			
			// Line on top of nose
			{
				int minX = 0, maxX = 0, minY = 0, maxY = 0;
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
				pos.angle = atan(((double)maxY - minY) / (maxX - minX));
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
				int minX = 0, maxX = 0, minY = 0, maxY = 0;
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
				int minX = 0, maxX = 0, minY = 0, maxY = 0;
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
				int minY = 0, maxY = 0;
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
	ret["ID"];
	ret["data"]["head"];
}

json praseRawData2JSON(RawFacePos& pos) {
	json head;
}