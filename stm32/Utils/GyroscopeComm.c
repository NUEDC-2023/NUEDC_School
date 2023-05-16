#include "GyroscopeComm.h"
#include "String.h"

float pitch,roll,yaw;
float pitch_holder, yaw_holder, roll_holder;
float ring=0;
float T;

//Internal
//转圈圈函数
static void ring_check_holder(void)
{
  static float roll_holder_last;
	if(roll_holder_last>=120&&roll<=-120) ring++;
  if(roll_holder_last<=-120&&roll>=120) ring--;
  roll_holder_last=roll;
}

//Public
void Gyroscope_Display_Specs()
{
	OLED_ShowString(1,1,"Gyro roll:");
	OLED_ShowSignedNum(2, 3, roll_holder, 10);
}

void Init_Gyro_Data(){
	ring=0; pitch_holder=0; yaw_holder=0; roll_holder=0; pitch=0; roll=0; yaw=0;
}

void Gyroscope_On_Recieve()
{
	if (sign) 
	{
	   static float angle[3];
//   float a[3],w[3],;
	   memcpy(data_buffer,Recv_buf,11); //copy back agian?
	   
	   if(Recv_buf[0]==0x55)       //检查帧头
	   {
	   	switch(Recv_buf[1])
	   	{
//     	case 0x51: //这个包是加速度包
//     		a[0] = ((short)(Recv_buf[3]<<8 | Recv_buf[2]))/32768.0*16;      //X轴加速度
//     		a[1] = ((short)(Recv_buf[5]<<8 | Recv_buf[4]))/32768.0*16;      //Y轴加速度
//     		a[2] = ((short)(Recv_buf[7]<<8 | Recv_buf[6]))/32768.0*16;      //Z轴加速度
//     		T    = ((short)(Recv_buf[9]<<8 | Recv_buf[8]))/340.0+36.25;      //温度
//     		break;
//     	case 0x52: //标识这个包是角速度包
//     		w[0] = ((short)(Recv_buf[3]<<8| Recv_buf[2]))/32768.0*2000;     //X轴角速度
//     		w[1] = ((short)(Recv_buf[5]<<8| Recv_buf[4]))/32768.0*2000;      //Y轴角速度
//     		w[2] = ((short)(Recv_buf[7]<<8| Recv_buf[6]))/32768.0*2000;      //Z轴角速度
//     		T    = ((short)(Recv_buf[9]<<8| Recv_buf[8]))/340.0+36.25;      //温度
//     		break;
	   		case 0x53: //标识这个包是角度包
	   			angle[0] = ((short)(data_buffer[3]<<8| data_buffer[2]))/32768.0*180;   //X轴滚转角
	   			angle[1] = ((short)(data_buffer[5]<<8| data_buffer[4]))/32768.0*180;   //Y轴滚转角
	   			angle[2] = ((short)(data_buffer[7]<<8| data_buffer[6]))/32768.0*180;   //Z轴偏航角
	   			T        = ((short)(data_buffer[9]<<8| data_buffer[8]))/340.0+36.25;   //温度
	   			break;
	   		default:  break;
	   	}
	   	pitch_holder=-10*angle[1];//角度
	   	yaw_holder=10*angle[0];//航向角度
	   	roll=angle[2];//航向角，只需要用这个
	   	ring_check_holder();
			roll_holder=roll+360*ring;
		}
	}
}
