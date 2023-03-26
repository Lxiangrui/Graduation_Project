#ifndef __FFT_H
#define __FFT_H		


//宏定义
#define PI2  6.28318530717959  //
#define NPT 1024            /* NPT = No of FFT point FFT的采样点数*/

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

long lBUFIN[NPT];         /* Complex input vector 输入复数向量*/
long lBUFOUT[NPT];        /* Complex output vector 输出复数向量*/
long lBUFMAG[NPT + NPT/2];/* Magnitude vector 幅度矢量*/
char disbuff[100];
char dis_buff[100];
int data[160],data_1[160];
int max  =  0,max_old  =0;


void MyDualSweep();									
void MygSin(long nfill, long Ampli);
void powerMag(long nfill, char* strPara);
void In_displayWaveform();
void displayPowerMag();
					  		 
#endif  
	 
	 