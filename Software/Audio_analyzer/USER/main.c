 #include "include.h"
char dis_buff[100];
int data[160],data_1[160];
int max  =  0,max_old  =0;

//宏定义
#define PI2  6.28318530717959  //
#define NPT 1024            /* NPT = No of FFT point FFT的采样点数*/

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
extern uint16_t TableFFT[];
extern volatile uint32_t TimingDelay ;
long lBUFIN[NPT];         /* Complex input vector 输入复数向量*/
long lBUFOUT[NPT];        /* Complex output vector 输出复数向量*/
long lBUFMAG[NPT + NPT/2];/* Magnitude vector 幅度矢量*/
char disbuff[100];
uint8_t key_flag   =  0;
/* Private function prototypes -----------------------------------------------*/
void MyDualSweep(uint8_t ui);									
void MygSin(long nfill, long Ampli);
void powerMag(long nfill, char* strPara);
void In_displayWaveform();
void displayPowerMag();

uint32_t bettery_num = 3221225472;
uint8_t xx = 0;
/* Private functions ---------------------------------------------------------*/
uint8_t flag  = 1;

/**
  * @brief  Main program.
  * @param  None
  * @retval : None
  */
int main(void)
{   
	 delay_init();	    
	 Lcd_Init ();				
	 adc_Init();		
	 LCD_Clear(WHITE);
	 BACK_COLOR=WHITE;
	 adc_Init();
	 key_Init();
  while (1)
  {
		if(flag && !key_flag){
		switch (xx)
		{
			case 0:
				LCD_ShowPicture_2(50,50,50+59,50+58);
			
				break;
			case  1:
				LCD_ShowPicture (50,50,50+59,50+58);
				break;
			case  2:
				set_ui(50,50,50+59,50+58);
				break;
			case  3:
				game_ui(50,50,50+59,50+58);
			break;
			default:
				break;
		}
		flag  = 0;
		}
		if(key_flag){
			switch (xx)
		{
			case 0:
				 MyDualSweep(1);
				break;
			case  1:
				 MyDualSweep(0);
				break;
			case  2:
//				 set_ui(50,50,50+59,50+58);
				break;
			case  3:
//				game_ui(50,50,50+59,50+58);
			break;
			default:
				break;
		}
		 
		}


  }
}








/**********************/
//小按键
void EXTI3_IRQHandler(void)
{

  if(EXTI_GetITStatus(EXTI_Line3) != RESET)
  {
			delay_ms(100);
		while(GPIO_ReadInputDataBit( GPIOC,GPIO_Pin_3) == 0);
		
    EXTI_ClearITPendingBit(EXTI_Line3);
  }
}


/**********************/
//上方波轮
void EXTI2_IRQHandler(void)
{

  if(EXTI_GetITStatus(EXTI_Line2) != RESET)
  {
			delay_ms(100);
		while(GPIO_ReadInputDataBit( GPIOC,GPIO_Pin_2) == 0);
		if(!key_flag)flag  = 1;
		if(!key_flag)xx+=1;
		if(xx>3) xx = 0;
	  EXTI_ClearITPendingBit(EXTI_Line2);
  }
}
/**********************/
//下方波轮
void EXTI0_IRQHandler(void)
{

  if(EXTI_GetITStatus(EXTI_Line0) != RESET)
  {
			delay_ms(100);
		while(GPIO_ReadInputDataBit( GPIOC,GPIO_Pin_0) == 0);
		if(!key_flag)xx=xx-1;
		if(!key_flag)flag  = 1;
		if(xx>100) xx = 3;
	
    EXTI_ClearITPendingBit(EXTI_Line0);
  }
}
/**********************/
//中间波轮
void EXTI1_IRQHandler(void)
{
	int  cln;
	
  if(EXTI_GetITStatus(EXTI_Line1) != RESET)
  {
		delay_ms(100);
		while(GPIO_ReadInputDataBit( GPIOC,GPIO_Pin_1) == 0);
		 LCD_Clear(WHITE);
		key_flag ++;
		if(key_flag   >   1){
		key_flag =  0;
		 LCD_Clear(WHITE);	
		flag  = 1;
			
//			for(cln=1; cln < 512; cln++){
//		    lBUFMAG[cln]   =  0;
//				lBUFIN[cln]  = 0;
//			}
		}
    EXTI_ClearITPendingBit(EXTI_Line1);
  }
}



void MyDualSweep(uint8_t ui)
{

	int time;
		
    MygSin(NPT,  32767); 
    cr4_fft_1024_stm32(lBUFOUT, lBUFIN, NPT);		//调用FFT函数进行计算
    powerMag(1024,"2SIDED");										//计算FFT变换的功率大小  64个数据  不删除频谱的混叠部分			
   if(ui)		In_displayWaveform();
	 else	displayPowerMag();

//			sprintf(disbuff,"        %d HZ     ",max);
//			LCD_ShowString(0,0,disbuff,GBLUE);
}


void MygSin(long nfill, long Ampli)
{
  uint32_t i;
  float fZ,fY;
  for (i=0; i < nfill; i++)
  {
		fY =  (float)get_adc()/4096;
    fZ = (float) Ampli * fY;
    lBUFIN[i]= ((short)fZ) << 16 ; 
  }
}


void onesided(long nfill)
{
  uint32_t i;
  
  lBUFMAG[0] = lBUFMAG[0];
  lBUFMAG[nfill/2] = lBUFMAG[nfill/2];
  for (i=1; i < nfill/2; i++)
  {
    lBUFMAG[i] = lBUFMAG[i] + lBUFMAG[nfill-i];
    lBUFMAG[nfill-i] = 0x0;
  }
}


void powerMag(long nfill, char* strPara)
{
  int32_t lX,lY;
  uint32_t i;

  for (i=0; i < nfill; i++)
  {
    lX= (lBUFOUT[i]<<16)>>16; /* sine_cosine --> cos */
    lY= (lBUFOUT[i] >> 16);   /* sine_cosine --> sin */    
    {
      float X=  64*((float)lX)/32768;
      float Y = 64*((float)lY)/32768;
      float Mag = sqrt(X*X+ Y*Y)/nfill;
      lBUFMAG[i] = (uint32_t)(Mag*65536);
    }    
  }
  if (strPara == "1SIDED") onesided(nfill);
}

void In_displayWaveform()
{
  uint16_t cln;
	static long lBUFIN_2[NPT];

	

  for (cln=0; cln < 127; cln++)       /* original upper limit was 60 */
  {	
		LCD_DrawLine(15+cln,			lBUFIN_2[cln]/10000000 - 40,			15+(cln+1),	lBUFIN_2[cln+1]/20000000 - 40,	WHITE);
//		LCD_DrawLine(15+(cln+1),	lBUFIN_2[cln+1]/10000000 ,	15+cln,			lBUFIN_2[cln]/20000000,			WHITE);
		if(flag  == 0)LCD_DrawLine(15+cln,			lBUFIN[cln]/10000000- 40,				15+(cln+1),	lBUFIN[cln+1]/20000000- 40 ,		BLACK);
//		LCD_DrawLine(15+(cln+1),	lBUFIN[cln+1]/10000000 ,		15+cln,			lBUFIN[cln]/20000000,				BLACK);
  	}
	

	
	for(cln = 0 ; cln < 128 ;cln++){
		lBUFIN_2[cln] =  lBUFIN[cln];
	}
}

void displayPowerMag()
{

  uint16_t cln;
	static long lBUFMAG_2[NPT];
	int max_cln =  0;
	max =   0;
	
	for (cln=1; cln < 127; cln++)
  {
		
		LCD_DrawLine(15+cln,70-(lBUFMAG_2[cln*4]+lBUFMAG_2[cln*4+1]+lBUFMAG_2[cln*4+2]+lBUFMAG_2[cln*4+3])/8,15+(cln+1),70-(lBUFMAG_2[(cln+1)*4]+lBUFMAG_2[(cln+1)*4+1]+lBUFMAG_2[(cln+1)*4+2]+lBUFMAG_2[(cln+1)*4+3])/8 ,WHITE);
		
		
//		LCD_DrawLine(15+(cln+1),70-lBUFMAG_2[(cln+1)*4]/2 ,15+cln,70-lBUFMAG_2[cln*4]/2,WHITE);
		if(flag  == 0)LCD_DrawLine(15+cln,70-(lBUFMAG[cln*4]+lBUFMAG[cln*4+1]+lBUFMAG[cln*4+2]+lBUFMAG[cln*4+3])/8,15+(cln+1),70-(lBUFMAG[(cln+1)*4]+lBUFMAG[(cln+1)*4+1]+lBUFMAG[(cln+1)*4+2]+lBUFMAG[(cln+1)*4+3])/8  ,BLACK);
//		LCD_DrawLine(15+(cln+1),70-lBUFMAG[(cln+1)*4]/2 ,15+cln,70-lBUFMAG[cln*4]/2,BLACK);
  }
	for(cln=1; cln < 512; cln++){
		lBUFMAG_2[cln] = lBUFMAG[cln];
		if(max_cln < lBUFMAG[cln]){
			max_cln=  lBUFMAG[cln];
			max  = cln;
		}
	}
	max =(int)((float)max*20000/498);
	if(max_cln<20)max=0;
}



