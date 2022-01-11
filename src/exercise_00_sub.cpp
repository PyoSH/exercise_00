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

// namespace enc = sensor_msgs::image_encodings;
using namespace cv;
using namespace std;

// sub : transform (input Mat => .mp4 file) until node shutdown. 

// int w_,h_;
// double fps_;
int fourcc = VideoWriter::fourcc('D','I','V','X');
// int fourcc = cv2.VideoWriter_fourcc(*'X264');
// int delay;

VideoWriter outputvideo("/home/output.avi", fourcc, 30, Size(680,640));



void imageCallback(const sensor_msgs::ImageConstPtr &msg1){
    //cv::imshow("view", cv_bridge::toCvShare(msg1, "bgr8")->image);

    if(!outputvideo.isOpened()){
        cout<<"ewwww"<<endl;
    }
    else{
        Mat input_V = cv_bridge::toCvCopy(msg1,"bgr8")->image.clone();    
    
    outputvideo.write(input_V);
    imshow("img",input_V);

    cout << "recording....." << endl;

    waitKey(1);
    }   
    
}

int main(int argc, char **argv)
{
	ros::init(argc, argv, "exrc_subscriber");
	ros::NodeHandle nh1;
    

    image_transport::ImageTransport it(nh1);
    image_transport::Subscriber img_sub = it.subscribe("/camera/exercise/image_raw",100,imageCallback);

    
    
    while(ros::ok()){
        ros::Rate loop_rate(100);
        ros::spinOnce();
        loop_rate.sleep();
    }  
    
    outputvideo.release();
    cout << "end /" <<endl;

    // cv::destroyWindow("view");
}




// Mat input_V;
// exercise_00::VidInfo info_vid;

// void msgcallBack(const exercise_00::VidInfo VidInfo){
//     info_vid.w= VidInfo.w;
//     info_vid.h= VidInfo.h;
//     info_vid.fps= VidInfo.fps;

// }

// void after_msg(ros::NodeHandle nh1){
//     ros::Subscriber info_sub = nh1.subscribe<exercise_00::VidInfo>("VidInfo",1,msgcallBack);
    
//     fourcc = VideoWriter::fourcc('D', 'I', 'V', 'X');
//     delay = cvRound(1000/fps_);
// }



    // cv::namedWindow("view");
    // cv::startWindowThread();

    // after_msg(nh1);
    // ros::Subscriber info_sub = nh1.subscribe<exercise_00::VidInfo>("VidInfo",1,msgcallBack);
    
    // w_ = info_vid.w;
    // h_ = info_vid.h;
    // fps_ = info_vid.fps;
    
    // fourcc = VideoWriter::fourcc('m','p','4','v');
    // delay = cvRound(1000/fps_);

    // cv::VideoWriter outputvideo("/home/output.mp4", fourcc, fps_, Size(w_, h_));
    
