#include <opencv2/opencv.hpp>
#include <iostream>
#include <stdio.h>
#include <ros/ros.h>
#include "std_msgs/Int32.h"
#include <std_msgs/Float64.h>
#include <sstream>
#include <image_transport/image_transport.h>
#include <cv_bridge/cv_bridge.h>
#include "/home/catkin_ws/devel/include/exercise_00/VidInfo.h"
using namespace cv;
using namespace std;


// pub :  pub -> sub camera output Mat. 
// sub : transform (input Mat => .mp4 file) until node shutdown. 
// Use comtomized msg 

// void imageCallback(const sensor_msgs::ImageConstPtr &msg);


exercise_00::VidInfo VidInfoWrite(VideoCapture camera,exercise_00::VidInfo info){
	info.w = camera.get(CAP_PROP_FRAME_WIDTH);
	info.h = camera.get(CAP_PROP_FRAME_HEIGHT);
	info.fps = camera.get(CAP_PROP_FPS);
	return info;
}


int main(int argc, char **argv)
{
	ros::init(argc, argv, "exrc_publisher");
	ros::NodeHandle nh1;

	image_transport::ImageTransport it(nh1);
	image_transport::Publisher image_raw_pub = it.advertise("/camera/exercise/image_raw",100);
	
	sensor_msgs::ImagePtr msg1;
	Mat frame;	

	VideoCapture cap1(0); //전방 정면캠

	cap1.open(0);
	int w = cap1.set(cv::CAP_PROP_FRAME_WIDTH, 640);
	int h = cap1.set(cv::CAP_PROP_FRAME_HEIGHT, 480);


	ros::Publisher VidInfo = nh1.advertise<exercise_00::VidInfo>("VidInfo",100);
	exercise_00::VidInfo vidinfo_msg;

	ros::Rate loop_rate(50);
	
	while (ros::ok())
	{
		//cap1.read(frame);
		waitKey(1);
		cap1 >> frame;

		msg1 = cv_bridge::CvImage(std_msgs::Header(), "bgr8", frame).toImageMsg();
		image_raw_pub.publish(msg1);
		
		if (!cap1.isOpened())
		{
			cerr << "finish!\n"
				 << endl;
		}
		
		imshow("frame1",frame);
		
		// VidInfoWrite(cap1, vidinfo_msg);
		VidInfo.publish(VidInfoWrite(cap1, vidinfo_msg));

		ros::spinOnce();
		loop_rate.sleep();
	}

	return 0;
}
