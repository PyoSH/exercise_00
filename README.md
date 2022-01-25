자율차 연구회 2차 과제물

imgmsg로 pub에서 sub에게 영상이 넘어가면, 
sub에서 imgmsg -> sensor_msgs::ImageConstPtr -> cv::Mat으로 변환을 거쳐 동영상 파일을 저장하게 된다. 
이 때, VideoWriter 클래스를 통해 VideoWriter outputvideo("/home/output.avi", fourcc, 30, Size(680,640)); 

이렇게 동영상의 저장정보를 입력하는데, 프레임과 영상의 사이즈를 카메라에서 입력하는 그대로 받아보고 싶었다. 

그래서 pub에서 카메라의 정보를 새로 만든 VidInfo 토픽-메시지를 통해 폭, 높이, fps의 정보를 sub으로 보낸다.


그런데 sub에서 VideoWrite를 통해 영상을 저장하려면 코덱, 폭, 높이, fps를 정해야 하는데, 이게 main함수 밖에 있자니 순서가 문제다.
=> 이 부분은 조성연 팀장님이 해결해 주셨다!!!

전역변수 a를 놓고, 코드가 실행될 때마다 +1씩 추가되도록 해 VideoWrite 선언이 한 번만 되도록 하는 방법이다. 
