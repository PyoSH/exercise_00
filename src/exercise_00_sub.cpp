// sub : transform (input Mat => .mp4 file) until node shutdown. 

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
void after_msg(ros::NodeHandle nh1);
void msgcallBack(const exercise_00::VidInfo VidInfo);
void imageCallback(const sensor_msgs::ImageConstPtr &msg1);

// namespace enc = sensor_msgs::image_encodings;
using namespace cv;
using namespace std;

int w_,h_;
double fps_;
int fourcc = VideoWriter::fourcc('D','I','V','X');
// VideoWriter outputvideo;
// int fourcc = cv2.VideoWriter_fourcc(*'X264');
int delay;
exercise_00::VidInfo info_vid; // msg that bring cam & video form data
Mat input_V; // Matrix that saved into avi file 

// VideoWriter outputvideo("/home/output1.avi", fourcc, 30, Size(640,480));
//VideoWriter outputvideo("/home/output.avi", fourcc, fps_, Size(w_,h_));


int main(int argc, char **argv)
{
	ros::init(argc, argv, "exrc_subscriber");
	ros::NodeHandle nh1;
    
    after_msg(nh1);
    
    // delay = cvRound(1000/fps_);

    VideoWriter outputvideo("/home/output2.mp4", fourcc, fps_, Size(w_, h_));
    
    cv::namedWindow("view");
    cv::startWindowThread();

    image_transport::ImageTransport it(nh1);
    

    while(ros::ok()){
        
            cout <<"vid opened..." <<endl;

            
            image_transport::Subscriber img_sub = it.subscribe("/camera/exercise/image_raw",100,imageCallback);
            
            outputvideo.write(input_V);

            imshow("img",input_V);

            cout << "recording....." << endl;

            waitKey(1);
            ros::Rate loop_rate(100);
            ros::spin();
            // loop_rate.sleep();

        // else if(!outputvideo.isOpened()){
        //     cout<<"ewwww"<<endl;
        // }
        
    }  
    
    outputvideo.release();
    cout << "end /" <<endl;

    cv::destroyWindow("view");
}

void msgcallBack(const exercise_00::VidInfo VidInfo){
    info_vid.w= VidInfo.w;
    info_vid.h= VidInfo.h;
    info_vid.fps= VidInfo.fps;

}

void after_msg(ros::NodeHandle nh1){
    ros::Subscriber info_sub = nh1.subscribe<exercise_00::VidInfo>("VidInfo",1,msgcallBack);
    
    w_ = info_vid.w;
    h_ = info_vid.h;
    fps_ = info_vid.fps;

    // fourcc = VideoWriter::fourcc('D', 'I', 'V', 'X');
    // delay = cvRound(1000/fps_);
}

void imageCallback(const sensor_msgs::ImageConstPtr &msg1){
    // if(!output_vid.isOpened()){
    //     cout<<"ewwww"<<endl;
    // }
    
    input_V = cv_bridge::toCvCopy(msg1,"bgr8")->image.clone();       

}





    
