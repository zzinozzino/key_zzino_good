#include "ros/ros.h"
#include "key_zzino/key.h"
#include "key_zzino/wasd.h"

int speed=0;
int steer=0;
bool write_E_stop;
int write_gear=0;
int write_speed=0;
int write_break=1;
int write_steer=0;
//메시지 콜백 함수로써, 밑에서 설정한 keycode_msg 라는 이름의 토픽 메시지를 수신하였을때 동작하는 함수이다.
// 입력 메시지로는 key_zzino 패키지의 key 메시지를 받도록 되어있다.

void msgCallback(const key_zzino::key::ConstPtr&msg)
{
if(msg->key==119) {
speed = speed +5;
}

if(msg->key==115) {
speed = 0;
steer = 0;
}

if(msg->key==97) {
steer = steer - 100;
}

if(msg->key==100) {
steer = steer + 100;
}

if(speed >= 200) {
speed = 200;
}

if(steer >= 2000) steer = 2000;
if(steer <= -2000) steer = -2000;

write_speed = speed;
write_steer = steer;

ROS_INFO("speed = %d, steer = %d",speed,steer);


}


int main(int argc, char **argv)
{
ros::init(argc, argv, "key_subscriber");

ros::NodeHandle nh;

ros::Subscriber key_zzino_sub = nh.subscribe("keycode_msg", 1, msgCallback);
ros::Publisher keycode_pub = nh.advertise<key_zzino::wasd>("key_write", 1);

//key_write 라는 토픽 선언.

//ros::Rate loop_rate(10);

key_zzino::wasd msg;

//wasd 메시지 파일형식으로 msg라는 메시지를 선언.


while (ros::ok())
{
msg.write_E_stop = write_E_stop;
msg.write_gear = write_gear;
msg.write_speed = write_speed;
msg.write_brake = write_break;
msg.write_steer = write_steer;

keycode_pub.publish(msg);

//loop_rate.sleep();

ros::spinOnce();
}



return 0;

}
