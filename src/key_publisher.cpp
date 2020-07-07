#include "ros/ros.h"
#include "key_zzino/key.h"


#define w 0x77
#define d 0x64
#define a 0x61
#define s 0x73


int main(int argc, char **argv)
{

ros::init(argc, argv, "key_publisher");
ros::NodeHandle nh;

ros::Publisher key_zzino_pub = nh.advertise<key_zzino::key>("keycode_msg", 1);
//key_zzino 패키지의 key 메시지 파일을 이용한 퍼블리셔 key_zzino_pub를 작성한다. 토픽명은
//"key_zzino_pub 를 작성한다. 토픽명은 "keycode_msg" 이며 



key_zzino::key msg;

//key 메시지 파일 형식으로 msg 라는 메시지를 선언.


while (ros::ok())
{
printf("input : ");
scanf("%c",&msg.key);

key_zzino_pub.publish(msg);

//퍼블리셔 key_zzino_pub에서 메시지를 발행한다는 의미


//loop_rate.sleep();

}

return 0;

}
