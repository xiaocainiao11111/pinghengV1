#include "sys.h"

//float AdcValue;                                    //电池电压数字量
float Pitch,Roll,Yaw;						      //角度
short aacx,aacy,aacz;		                        //加速度传感器原始数据
short gyrox,gyroy,gyroz;	                        //陀螺仪原始数据
int PWM1;
int PWM_MAX=6500,PWM_MIN=-6500;	//PWM限幅变量
int Encoder_Motor;	//编码器数据（速度）

int main(void)
{  
	  NVIC_Config();
   	delay_init();
//    Led_Init();
//    Beep_Init();
//    Wave_SRD_Init();
   	uart3_init(9600);
    OLED_Init();			//初始化OLED  
    OLED_Clear();
	  adc_Init();
    MOTOR_1_Init();
    MOTOR_2_Init();
    PWM_Init_TIM3(7199,0);//定时器3初始化PWM 10KHZ，用于驱动动量轮电机 
//    PWM_Init_TIM2(9999, 143);//定时器2初始化PWM 50HZ，用于驱动舵机
//    TIM_SetCompare1(TIM2, 790);//舵机复位
    Init_TIM1(9998,7199);
    Encoder_Init_TIM4(65535,0);//编码器初始化
    OLED_ShowString(25,4,"MPU6050...",16);
    MPU_Init();            //MPU6050初始化  
    while(mpu_dmp_init())
 	{
		OLED_ShowString(25,4,"MPU6050 Error",16);
	}  
    OLED_ShowString(25,4,"MPU6050 OK!",16); 
//    Beep=1;
    delay_ms(400);
//    Beep=0;
    MPU6050_EXTI_Init();
    OLED_Clear();
 	  OLED_ShowString(0,0,"Roll :         C",16);//角度显示
    OLED_ShowString(0,3,"Speed:         R ",16);//速度显示
//    OLED_ShowString(0,6,"Power:        V ",16); //电压显示   
    OLED_ShowString(0,6,"  xiaocainiao",16);  

    while(1)
    {	        
//        Wave_SRD_Strat();        
//        AdcValue=11.09*(3.3*Get_adc_Average(ADC_Channel_4,10)/0x0fff); //ADC值范围为从0-2^12=4095（111111111111）一般情况下对应电压为0-3.3V
        OLED_Showdecimal(55,0,Roll,9,16);  
        OLED_Showdecimal(55,3,Encoder_Motor*0.25,9,16);         
//        OLED_Showdecimal(50,6,AdcValue,9,16);       
	}
}
