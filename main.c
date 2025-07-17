

#include	"config.h"
#include	"STC8G_PCA.h"
#include	"STC8G_H_GPIO.h"
#include	"STC8G_H_Delay.h"
#include	"STC8G_H_Switch.h"

/*************   功能说明   ***************



******************************************/

/*************	本地常量声明	**************/


/*************	本地变量声明	**************/

u16	pwm0;
bit	B_PWM0_Dir;	//方向, 0为+, 1为-.

/*************	本地函数声明	**************/


/*************  外部函数和变量声明 *****************/


/******************** IO口配置 ********************/
void	GPIO_config(void)
{
	GPIO_InitTypeDef	GPIO_InitStructure;		//结构定义

	GPIO_InitStructure.Pin  = GPIO_Pin_4;		//指定要初始化的IO, GPIO_Pin_0 ~ GPIO_Pin_7, 或操作
	GPIO_InitStructure.Mode = GPIO_PullUp;		//指定IO的输入或输出方式,GPIO_PullUp,GPIO_HighZ,GPIO_OUT_OD,GPIO_OUT_PP
	GPIO_Inilize(GPIO_P5,&GPIO_InitStructure);	//初始化
	
	GPIO_InitStructure.Pin  = GPIO_Pin_5;		//指定要初始化的IO, GPIO_Pin_0 ~ GPIO_Pin_7, 或操作
	GPIO_InitStructure.Mode = GPIO_OUT_PP;		//指定IO的输入或输出方式,GPIO_PullUp,GPIO_HighZ,GPIO_OUT_OD,GPIO_OUT_PP
	GPIO_Inilize(GPIO_P5,&GPIO_InitStructure);	//初始化
}

/******************** PCA配置 ********************/
void	PCA_config(void)
{
	PCA_InitTypeDef		PCA_InitStructure;

	PCA_InitStructure.PCA_Clock    = PCA_Clock_1T;		//PCA_Clock_1T, PCA_Clock_2T, PCA_Clock_4T, PCA_Clock_6T, PCA_Clock_8T, PCA_Clock_12T, PCA_Clock_Timer0_OF, PCA_Clock_ECI
	PCA_InitStructure.PCA_RUN      = DISABLE;			//ENABLE, DISABLE
	PCA_Init(PCA_Counter,&PCA_InitStructure);			//设置公用Counter

	PCA_InitStructure.PCA_PWM_Wide = PCA_PWM_10bit;		//PCA_PWM_8bit, PCA_PWM_7bit, PCA_PWM_6bit, PCA_PWM_10bit
	PCA_InitStructure.PCA_Value    = 32 << 8;			//对于PWM,高8位为PWM占空比
	PCA_Init(PCA0,&PCA_InitStructure);

	NVIC_PCA_Init(PCA_Counter,PCA_Mode_PWM,Priority_0);
	NVIC_PCA_Init(PCA0,PCA_Mode_PWM,Priority_0);


	PCA_SW(PCA_P24_P25_P26_P27);	//PCA_P12_P11_P10_P37,PCA_P34_P35_P36_P37,PCA_P24_P25_P26_P27
	CR = 1;							//启动PCA
}


/******************** task A **************************/
void main(void)
{
	EAXSFR();		/* 扩展寄存器访问使能 */
    GPIO_config();
    PCA_config();
    pwm0 = 512;

    UpdatePcaPwm(PCA0,pwm0);
//  EA = 1;
	
    while (1)
    {
			int i;
				delay_ms(5);
			
			for (pwm0 = 10;pwm < 1000;p++ )
			{
				UpdatePcaPwm(PCA0,pwm0);
			}
			P55 = 1;
			
			if(P54 == 0)
			{
				for (i = 0;i < 5;i++ )
				{
					delay_ms(1);
				}
				if(P54 == 0)
				{
						for (pwm0 = 1000;pwm > 24;p-- )
						{
							UpdatePcaPwm(PCA0,pwm0);
						}
				}
			}
    }
}



