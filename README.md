본래 의도 : imgmsg로 pub에서 sub에게 영상이 넘어가면, 
sub에서 imgmsg -> sensor_msgs::ImageConstPtr -> cv::Mat으로 변환을 거쳐 동영상 파일을 저장하게 된다. 
이 때, VideoWriter 클래스를 통해 VideoWriter outputvideo("/home/output.avi", fourcc, 30, Size(680,640)); 

이렇게 동영상의 저장정보를 입력하는데, 프레임과 영상의 사이즈를 카메라에서 입력하는 그대로 받아보고 싶었다. 

그래서 pub에서 카메라의 정보
