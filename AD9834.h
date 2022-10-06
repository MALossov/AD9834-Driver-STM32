/*
 * @Description:AD7606驱动声明文件
 * @Author: MALossov
 * @Date: 2022-06-28 16:37:55
 * @LastEditTime: 2022-10-06 02:56:10
 * @LastEditors: MALossov
 * @Reference:
 */
#ifndef __AD9834_H 
#define __AD9834_H 
#include <stdint.h>
#include "stm32f1xx_hal.h"  //这里根据芯片的具体信号选择自己的头文件
#include "main.h"
#include "usart.h"
#include "stdio.h"

 /*--------------------- AD9834控制信号 16Bit ---------------------*/
/**
 * @brief 在这部分当中，包括了AD9834大部分控制信号的定义，包括了控制信号的宏定义
 * @useage 使用函数AD9834_Write_16Bits()来写入控制信号，
 *         或者也可以使用AD9834_Select_Wave()来写入（后者通常用于直接使用某种波形）
 */
 //设置基本的波形，默认使用频率寄存器0
#define Triangle_Wave    0x2002 
#define Sine_Wave  0x2008 
#define Square_Wave 0x2028

//设置使用频率寄存器1
#define Sine_Wave_Reg1 0x2808  
#define Square_Wave_Reg1 0x2828 
#define Triangle_Wave_Reg1 0x2802

//设置通过引脚选择发生波形
#define SelectByPin 0x2208  //设置PIN_SW 位，选择通过引脚选择频率寄存器、相位和是否不发生波
//在如上的Pin中，包括FS，PS，RESET，SLEEP四根引脚，根据自己的情况写入

//重新复位AD9834
#define RESET_AD9834 0x2100

//停止AD9834的DAC输出
#define STOP_DAC 0x2040

//进阶操作部分
//如果部署需数据手册，不要贸然使用这一部分
//如果使用这部分，请对各个宏进行 | 的运算操作赋予或者使用~进行清除，否则容易出现问题。
#define AD9834_B28  0x2000  //设置为28位模式
#define AD9834_HLB  0x0100  //设置为高速模式，不要轻易使用
#define AD9834_RESET 0x0100  //复位AD9834
#define AD9834_SLEEP1 0x0080  //设置为睡眠模式1
#define AD9834_SLEEP12 0x0040  //设置为睡眠模式2
#define AD9834_OPBITEN 0x0020  //设置为输出使能
#define AD9834_DIV2 0x0010  //设置为分频模式
#define AD9834_MODE 0x0002  //设置为三角波模式
#define AD9834_SIGN_PIBIT 0x0001  //设置为正弦波模式
#define AD9834_PHASE 0xC000  //设置相位寄存器0
#define AD98er_PHASE1 0xE000  //设置相位寄存器1


//------------------AD9834控制和器件特性------------------//
/**
 * @brief 在这部分中，包括了AD9834的一些特性，包括了AD9834的一些控制引脚和所用时钟
 * @notice 在使用AD9834时，需要根据自己的情况修改这部分的内容
 */

 /* AD9834晶振频率 */
#define AD9834_SYSTEM_COLCK     75000000UL 


/* AD9834 控制引脚 */
#define AD9834_Control_Port  GPIOB
#define AD9834_FSYNC  GPIO_PIN_15    
#define AD9834_SCLK   GPIO_PIN_14			
#define AD9834_SDATA  GPIO_PIN_13 		
#define AD9834_RESET  GPIO_PIN_10		
#define AD9834_FS  		GPIO_PIN_12		
#define AD9834_PS  		GPIO_PIN_11		

//为兼容标准库，提供如下宏
#define GPIO_SetBits(x,y) HAL_GPIO_WritePin((x),(y),GPIO_PIN_SET)
#define GPIO_ResetBits(x,y) HAL_GPIO_WritePin((x),(y),GPIO_PIN_RESET)

//为了便于操作数据引脚，提供如下宏
#define AD9834_FSYNC_SET   GPIO_SetBits(AD9834_Control_Port ,AD9834_FSYNC) 
#define AD9834_FSYNC_CLR   GPIO_ResetBits(AD9834_Control_Port ,AD9834_FSYNC) 

#define AD9834_SCLK_SET   GPIO_SetBits(AD9834_Control_Port ,AD9834_SCLK) 
#define AD9834_SCLK_CLR   GPIO_ResetBits(AD9834_Control_Port ,AD9834_SCLK) 

#define AD9834_SDATA_SET   GPIO_SetBits(AD9834_Control_Port ,AD9834_SDATA) 
#define AD9834_SDATA_CLR   GPIO_ResetBits(AD9834_Control_Port ,AD9834_SDATA) 

#define AD9834_RESET_SET   GPIO_SetBits(AD9834_Control_Port ,AD9834_RESET) 
#define AD9834_RESET_CLR   GPIO_ResetBits(AD9834_Control_Port ,AD9834_RESET) 

//为了便于操作频率等控制引脚，提供如下宏
#define AD9834_FS_SET   GPIO_SetBits(AD9834_Control_Port ,AD9834_FS)
#define AD9834_FS_CLR   GPIO_ResetBits(AD9834_Control_Port ,AD9834_FS)

#define AD9834_PS_SET   GPIO_SetBits(AD9834_Control_Port ,AD9834_PS)
#define AD9834_PS_CLR   GPIO_ResetBits(AD9834_Control_Port ,AD9834_PS)

#define AD9834_RST_SET   GPIO_SetBits(AD9834_Control_Port ,AD9834_RESET)
#define AD9834_RST_CLR   GPIO_ResetBits(AD9834_Control_Port ,AD9834_RESET)

/*--------------------- AD9834操作位声明 ---------------------*/
/**
 * @brief 这部分包括了AD9834的一些操作位的声明，包括了AD9834的一些操作位的宏定义
 * @useage 使用函数AD9834_Write_16Bits()来写入控制信号。
 * @notice 如果有不明便的地方，查阅数据手册进行更改
 */

 //频率寄存器的控制位
#define FREQ_0      0 
#define FREQ_1      1 
#define PHASE_0     0
#define PHASE_1     1

//各个位的定义，留空为0
//如果需要使用其他位，请自行添加相关的变量/宏的定义
#define DB15        0 
#define DB14        0 
#define DB13        B28 
#define DB12        HLB 
#define DB11        FSEL 
#define DB10        PSEL 
#define DB9         PIN_SW 
#define DB8         RESET
#define DB7         SLEEP1 
#define DB6         SLEEP12 
#define DB5         OPBITEN 
#define DB4         SIGN_PIB 
#define DB3         DIV2 
#define DB2         0 
#define DB1         MODE 
#define DB0         0 

//通过操作位的宏定义，可以得到控制信号的值
//可以通过AD9834_Write_16Bits()函数来直接写入控制信号
#define CONTROL_REGISTER    (DB15<<15)|(DB14<<14)|(DB13<<13)|(DB12<<12)|(DB11<<11)|(DB10<<10)|(DB9<<9)|(DB8<<8)|(DB7<<7)|(DB6<<6)|(DB5<<5)|(DB4<<4)|(DB3<<3)|(DB2<<2)|(DB1<<1)|(DB0<<0) 

 /*--------------------- AD9834函数声明 ---------------------*/
void AD9834_Write_16Bits(unsigned int data);  //写一个字到AD9834 
void AD9834_Select_Wave(unsigned int initdata); //选择输出波形 
void AD9834_Init(void);  					//初始化配置 
void AD9834_Set_Freq(unsigned char freq_number, unsigned long freq);//选择输出寄存器和输出频率值 

#endif /* AD9834_H */ 

