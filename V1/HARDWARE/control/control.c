#include "control.h" 

float Med_Angle;	//机械中值。---在这里修改你的机械中值即可。
float 
//	Vertical_Kp=0,//直立环KP、KD
//	Vertical_Kd=0;
	Vertical_Kp=950,//直立环KP、KD  810 4.5
	Vertical_Kd=5;

float 
	Velocity_Kp=85,//速度环KP、KI  58  0.25
	Velocity_Ki=0.25;
//	Velocity_Kp=0,//速度环KP、KI
//	Velocity_Ki=0;


int Vertical_out,Velocity_out,Turn_out;//直立环&速度环&转向环 的输出变量

int Vertical(float Med,float Angle,float gyro_x);//函数声明
int Velocity(int encoder_motor);
int Turn(int gyro_Z); 

void EXTI9_5_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line5)!=0)//一级判定
	{
		if(PBin(5)==0)//二级判定
		{
            
			EXTI_ClearITPendingBit(EXTI_Line5);//清除中断标志位
            
			//1.采集编码器数据&MPU6050角度信息。
			Encoder_Motor=Read_Encoder_TIM4();
			
			mpu_dmp_get_data(&Pitch,&Roll,&Yaw);			//角度
			MPU_Get_Gyroscope(&gyrox,&gyroy,&gyroz);	//陀螺仪角速度
			MPU_Get_Accelerometer(&aacx,&aacy,&aacz);	//加速度
            
            Vertical_out=Vertical(Med_Angle,Roll,gyrox);			//直立环
            Velocity_out=Velocity(Encoder_Motor);	//速度环
			
			//角度判断
			if(Roll>-100&&Roll<-70)
			{Med_Angle=-85;}
			else if(Roll>-20&&Roll<10)
			{Med_Angle=-4;}
			else if(Roll>70&&Roll<100)
			{Med_Angle=86;}
			else if((Roll>170&&Roll<180)||(Roll<-160&&Roll>-180))
			{Med_Angle=-173;}
			else
			{Vertical_out=0,Velocity_out=0;}



            
			//3.把控制输出量加载到电机上，完成最终的的控制。
            PWM1=Vertical_out+Velocity_out;//最终输出
			Limit(&PWM1);	 //PWM限幅			
			Load(-PWM1);		 //加载到电机上。
			Stop(&Med_Angle,&Roll);		            
		}
	}
}


/*********************
直立环PD控制器：Kp*Ek+Kd*Ek_D

入口：期望角度、真实角度、真实角速度
出口：直立环输出
*********************/
int Vertical(float Med,float Angle,float gyro_x)
{
	int PWM_out1;
	PWM_out1=Vertical_Kp*(Angle-Med)+Vertical_Kd*(gyro_x);
	return PWM_out1;
}

/*********************
速度环PI：Kp*Ek+Ki*Ek_S
*********************/
int Velocity (int encoder_motor)
{
	static int Encoder_S,EnC_Err_Lowout_last,PWM_out2,Encoder_Err,EnC_Err_Lowout;
	float a=0.7;
	
	//1.计算速度偏差
	Encoder_Err=encoder_motor;
    
	//2.对速度偏差进行低通滤波:low_out=(1-a)*Ek+a*low_out_last
	EnC_Err_Lowout=(1-a)*Encoder_Err+a*EnC_Err_Lowout_last;//使得波形更加平滑，滤除高频干扰，防止速度突变。0.3当前速度加0.7上次速度
	EnC_Err_Lowout_last=EnC_Err_Lowout;                     //防止速度过大的影响直立环的正常工作。
    
	//3.对速度偏差积分，积分出位移
	Encoder_S+=EnC_Err_Lowout;
	//4.积分限幅
	Encoder_S=Encoder_S>10000?10000:(Encoder_S<(-10000)?(-10000):Encoder_S);//积分限制：-10000到10000
	
	//5.速度环控制输出计算
	PWM_out2=Velocity_Kp*EnC_Err_Lowout+Velocity_Ki*Encoder_S;
	return PWM_out2;
}



