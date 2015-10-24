/*
*
*
*/
#include "DEV_OLED.h"
#include "common.h"
#include "Card_Config.h"

uint8 displayGRAM[128][8]={'0'};//显存
/*****************************外部变量声明*************************************/
//常用ASCII表
//偏移量32
//ASCII字符集
//偏移量32
//大小:12*6
const unsigned char ASCII_0608[][6]={
 {0x00, 0x00, 0x00, 0x00, 0x00, 0x00} // 20
,{0x00, 0x00, 0x00, 0x5f, 0x00, 0x00} // 21 !
,{0x00, 0x00, 0x07, 0x00, 0x07, 0x00} // 22 "
,{0x00, 0x14, 0x7f, 0x14, 0x7f, 0x14} // 23 #
,{0x00, 0x24, 0x2a, 0x7f, 0x2a, 0x12} // 24 $
,{0x00, 0x23, 0x13, 0x08, 0x64, 0x62} // 25 %
,{0x00, 0x36, 0x49, 0x55, 0x22, 0x50} // 26 &
,{0x00, 0x00, 0x05, 0x03, 0x00, 0x00} // 27 '
,{0x00, 0x00, 0x1c, 0x22, 0x41, 0x00} // 28 (
,{0x00, 0x00, 0x41, 0x22, 0x1c, 0x00} // 29 )
,{0x00, 0x14, 0x08, 0x3e, 0x08, 0x14} // 2a *
,{0x00, 0x08, 0x08, 0x3e, 0x08, 0x08} // 2b +
,{0x00, 0x00, 0x50, 0x30, 0x00, 0x00} // 2c ,
,{0x00, 0x08, 0x08, 0x08, 0x08, 0x08} // 2d -
,{0x00, 0x00, 0x60, 0x60, 0x00, 0x00} // 2e .
,{0x00, 0x20, 0x10, 0x08, 0x04, 0x02} // 2f /
,{0x00, 0x3e, 0x51, 0x49, 0x45, 0x3e} // 30 0
,{0x00, 0x00, 0x42, 0x7f, 0x40, 0x00} // 31 1
,{0x00, 0x42, 0x61, 0x51, 0x49, 0x46} // 32 2
,{0x00, 0x21, 0x41, 0x45, 0x4b, 0x31} // 33 3
,{0x00, 0x18, 0x14, 0x12, 0x7f, 0x10} // 34 4
,{0x00, 0x27, 0x45, 0x45, 0x45, 0x39} // 35 5
,{0x00, 0x3c, 0x4a, 0x49, 0x49, 0x30} // 36 6
,{0x00, 0x01, 0x71, 0x09, 0x05, 0x03} // 37 7
,{0x00, 0x36, 0x49, 0x49, 0x49, 0x36} // 38 8
,{0x00, 0x06, 0x49, 0x49, 0x29, 0x1e} // 39 9
,{0x00, 0x00, 0x36, 0x36, 0x00, 0x00} // 3a :
,{0x00, 0x00, 0x56, 0x36, 0x00, 0x00} // 3b ;
,{0x00, 0x08, 0x14, 0x22, 0x41, 0x00} // 3c <
,{0x00, 0x14, 0x14, 0x14, 0x14, 0x14} // 3d =
,{0x00, 0x00, 0x41, 0x22, 0x14, 0x08} // 3e >
,{0x00, 0x02, 0x01, 0x51, 0x09, 0x06} // 3f ?
,{0x00, 0x32, 0x49, 0x79, 0x41, 0x3e} // 40 @
,{0x00, 0x7e, 0x11, 0x11, 0x11, 0x7e} // 41 A
,{0x00, 0x7f, 0x49, 0x49, 0x49, 0x36} // 42 B
,{0x00, 0x3e, 0x41, 0x41, 0x41, 0x22} // 43 C
,{0x00, 0x7f, 0x41, 0x41, 0x22, 0x1c} // 44 D
,{0x00, 0x7f, 0x49, 0x49, 0x49, 0x41} // 45 E
,{0x00, 0x7f, 0x09, 0x09, 0x09, 0x01} // 46 F
,{0x00, 0x3e, 0x41, 0x49, 0x49, 0x7a} // 47 G
,{0x00, 0x7f, 0x08, 0x08, 0x08, 0x7f} // 48 H
,{0x00, 0x00, 0x41, 0x7f, 0x41, 0x00} // 49 I
,{0x00, 0x20, 0x40, 0x41, 0x3f, 0x01} // 4a J
,{0x00, 0x7f, 0x08, 0x14, 0x22, 0x41} // 4b K
,{0x00, 0x7f, 0x40, 0x40, 0x40, 0x40} // 4c L
,{0x00, 0x7f, 0x02, 0x0c, 0x02, 0x7f} // 4d M
,{0x00, 0x7f, 0x04, 0x08, 0x10, 0x7f} // 4e N
,{0x00, 0x3e, 0x41, 0x41, 0x41, 0x3e} // 4f O
,{0x00, 0x7f, 0x09, 0x09, 0x09, 0x06} // 50 P
,{0x00, 0x3e, 0x41, 0x51, 0x21, 0x5e} // 51 Q
,{0x00, 0x7f, 0x09, 0x19, 0x29, 0x46} // 52 R
,{0x00, 0x46, 0x49, 0x49, 0x49, 0x31} // 53 S
,{0x00, 0x01, 0x01, 0x7f, 0x01, 0x01} // 54 T
,{0x00, 0x3f, 0x40, 0x40, 0x40, 0x3f} // 55 U
,{0x00, 0x1f, 0x20, 0x40, 0x20, 0x1f} // 56 V
,{0x00, 0x3f, 0x40, 0x38, 0x40, 0x3f} // 57 W
,{0x00, 0x63, 0x14, 0x08, 0x14, 0x63} // 58 X
,{0x00, 0x07, 0x08, 0x70, 0x08, 0x07} // 59 Y
,{0x00, 0x61, 0x51, 0x49, 0x45, 0x43} // 5a Z
,{0x00, 0x00, 0x7f, 0x41, 0x41, 0x00} // 5b [
,{0x00, 0x02, 0x04, 0x08, 0x10, 0x20} // 5c \ //
,{0x00, 0x00, 0x41, 0x41, 0x7f, 0x00} // 5d ]
,{0x00, 0x04, 0x02, 0x01, 0x02, 0x04} // 5e ^
,{0x00, 0x40, 0x40, 0x40, 0x40, 0x40} // 5f _
,{0x00, 0x00, 0x01, 0x02, 0x04, 0x00} // 60 `
,{0x00, 0x20, 0x54, 0x54, 0x54, 0x78} // 61 a
,{0x00, 0x7f, 0x48, 0x44, 0x44, 0x38} // 62 b
,{0x00, 0x38, 0x44, 0x44, 0x44, 0x20} // 63 c
,{0x00, 0x38, 0x44, 0x44, 0x48, 0x7f} // 64 d
,{0x00, 0x38, 0x54, 0x54, 0x54, 0x18} // 65 e
,{0x00, 0x08, 0x7e, 0x09, 0x01, 0x02} // 66 f
,{0x00, 0x0c, 0x52, 0x52, 0x52, 0x3e} // 67 g
,{0x00, 0x7f, 0x08, 0x04, 0x04, 0x78} // 68 h
,{0x00, 0x00, 0x44, 0x7d, 0x40, 0x00} // 69 i
,{0x00, 0x20, 0x40, 0x44, 0x3d, 0x00} // 6a j
,{0x00, 0x7f, 0x10, 0x28, 0x44, 0x00} // 6b k
,{0x00, 0x00, 0x41, 0x7f, 0x40, 0x00} // 6c l
,{0x00, 0x7c, 0x04, 0x18, 0x04, 0x78} // 6d m
,{0x00, 0x7c, 0x08, 0x04, 0x04, 0x78} // 6e n
,{0x00, 0x38, 0x44, 0x44, 0x44, 0x38} // 6f o
,{0x00, 0x7c, 0x14, 0x14, 0x14, 0x08} // 70 p
,{0x00, 0x08, 0x14, 0x14, 0x18, 0x7c} // 71 q
,{0x00, 0x7c, 0x08, 0x04, 0x04, 0x08} // 72 r
,{0x00, 0x48, 0x54, 0x54, 0x54, 0x20} // 73 s
,{0x00, 0x04, 0x3f, 0x44, 0x40, 0x20} // 74 t
,{0x00, 0x3c, 0x40, 0x40, 0x20, 0x7c} // 75 u
,{0x00, 0x1c, 0x20, 0x40, 0x20, 0x1c} // 76 v
,{0x00, 0x3c, 0x40, 0x30, 0x40, 0x3c} // 77 w
,{0x00, 0x44, 0x28, 0x10, 0x28, 0x44} // 78 x
,{0x00, 0x0c, 0x50, 0x50, 0x50, 0x3c} // 79 y
,{0x00, 0x44, 0x64, 0x54, 0x4c, 0x44} // 7a z
,{0x00, 0x00, 0x08, 0x36, 0x41, 0x00} // 7b {
,{0x00, 0x00, 0x00, 0x7f, 0x00, 0x00} // 7c |
,{0x00, 0x00, 0x41, 0x36, 0x08, 0x00} // 7d }
,{0x00, 0x10, 0x08, 0x08, 0x10, 0x08} // 7e ~
,{0x00, 0x78, 0x46, 0x41, 0x46, 0x78} // 7f (delete)
};

static void OLED_SclSet(uint8 status)
{
  OledConfig* oledConfig = NULL;
  GPIO_InitTypeDef sclInfo;
  
  oledConfig = (OledConfig*)GetOledConfig();
  if(NULL == oledConfig)
    return;
  
  sclInfo = oledConfig->SCL_Pin;
  LPLD_GPIO_Output_b(sclInfo.GPIO_PTx, sclInfo.GPIO_Pins, status);
}

static void OLED_SdaSet(uint8 status)
{
  OledConfig* oledConfig = NULL;
  GPIO_InitTypeDef sclInfo;
  
  oledConfig = (OledConfig*)GetOledConfig();
  if(NULL == oledConfig)
    return;
  
  sclInfo = oledConfig->SDA_Pin;
  LPLD_GPIO_Output_b(sclInfo.GPIO_PTx, sclInfo.GPIO_Pins, status);
}

static void OLED_RstSet(uint8 status)
{
  OledConfig* oledConfig = NULL;
  GPIO_InitTypeDef sclInfo;
  
  oledConfig = (OledConfig*)GetOledConfig();
  if(NULL == oledConfig)
    return;
  
  sclInfo = oledConfig->RST_Pin;
  LPLD_GPIO_Output_b(sclInfo.GPIO_PTx, sclInfo.GPIO_Pins, status);
}

static void OLED_DcSet(uint8 status)
{
  OledConfig* oledConfig = NULL;
  GPIO_InitTypeDef sclInfo;
  
  oledConfig = (OledConfig*)GetOledConfig();
  if(NULL == oledConfig)
    return;
  
  sclInfo = oledConfig->DC_Pin;
  LPLD_GPIO_Output_b(sclInfo.GPIO_PTx, sclInfo.GPIO_Pins, status);
}

/*
* 函 数 名  : OLED_IO_Init
* 功能描述  : 初始化OLED引脚
* 输入参数  : NONE
* 输出参数  : NONE
* 返 回 值  : NONE
*/
void OLED_IO_Init(void)
{
  OledConfig* oledConfig = NULL;
  
  oledConfig = (OledConfig*)GetOledConfig();
  if(NULL == oledConfig)
    return;
  
  (void)LPLD_GPIO_Init(oledConfig->SCL_Pin);
  (void)LPLD_GPIO_Init(oledConfig->SDA_Pin);
  (void)LPLD_GPIO_Init(oledConfig->DC_Pin);
  (void)LPLD_GPIO_Init(oledConfig->RST_Pin);
}

/*
* 函 数 名  : OLED_WrDat
* 功能描述  : 向OLED写数据
* 输入参数  : Dat待写入数据
* 输出参数  : NONE
* 返 回 值  : NONE
*/
static void OLED_WrDat(uint8 dat)//写数据
{
    unsigned char i=8;
    OLED_DcSet(1);
    OLED_SclSet(0);
    
    while(i--)
    {
        if(dat&0x80)
        {
          OLED_SdaSet(1);
        }
        else
        {
          OLED_SdaSet(1);
        }
        
        OLED_SclSet(1);
        asm("nop");
        OLED_SclSet(0);    
        dat<<=1; 
    }
}

/*
* 函 数 名  : OLED_WrCmd
* 功能描述  : 向OLED写命令
* 输入参数  : Dat待写入命令 
* 输出参数  : NONE
* 返 回 值  : NONE
*/
static void OLED_WrCmd(uint8 cmd)
{
  unsigned char i=8;
  
  OLED_DcSet(0);
  OLED_SclSet(0);
        
  while(i--)
  {
      if(cmd&0x80)
      {
        OLED_SdaSet(1);
      }
      else
      {
        OLED_SdaSet(0);
      }
      
      OLED_SclSet(1);
      asm("nop");
      OLED_SclSet(0);    
      cmd<<=1;    
  }
}
//更新显存到LCD		 
void OLED_Refresh_Gram(void)
{
    uint8 i,n;		    
    for(i=0;i<8;i++)  
    {  
        OLED_WrCmd(0xB0+i);    //设置页地址（0~7）
        OLED_WrCmd(0x00);      //设置显示位置-列低地址
        OLED_WrCmd(0x10);      //设置显示位置-列高地址   
        for(n=132;n>0;n--)
                OLED_WrDat(displayGRAM[n][i]);
    }
}
/*
* 函 数 名  : OLED_SetPos
* 功能描述  : 设置显示坐标
              0xb0+0~7表示页0~7
              0x00+0~16表示将128列分成16组其地址在某组中的第几列
              0x10+0~16表示将128列分成16组其地址所在第几组
* 输入参数  : uint8 X  
             uint8 Y  
* 输出参数  : NONE
* 返 回 值  : NONE
*/
void OLED_SetPos(uint8 x, uint8 y)
{
  OLED_WrCmd(0xb0 + y);
  OLED_WrCmd(((x&0xf0)>>4)|0x10);
  OLED_WrCmd((x&0x0f)|0x01);
} 

/*
* 函 数 名  : OLED_Init
* 功能描述  : OLED初始化
* 输入参数  : void  
* 输出参数  : NONE
* 返 回 值  : NONE
*/
void OLED_Init(void)        
{
    uint16 i;
    
    OLED_IO_Init();
    OLED_SclSet(1);
    OLED_RstSet(0);
    
    for(i=0;i<200;i++)
    {
        ;            //从上电到下面开始初始化要有足够的时间，即等待RC复位完毕
    }
    OLED_RstSet(1);

    OLED_WrCmd(0xAE); //关闭显示
    OLED_WrCmd(0xD5); //设置时钟分频因子,震荡频率
    OLED_WrCmd(0x80); //[3:0],分频因子;[7:4],震荡频率
    OLED_WrCmd(0xA8); //设置驱动路数
    OLED_WrCmd(0x3F); //默认0x3F(1-64)63
    OLED_WrCmd(0xD3); //设置显示偏移(即在设定的基础上自动加上一定的偏移量,专指行地址的偏移，对列地址无影响)
    OLED_WrCmd(0x00); //默认为0
    OLED_WrCmd(0x40); //设置显示开始行[5:0],行数.
    OLED_WrCmd(0x8D); //电荷泵设置
    OLED_WrCmd(0x14); //bit2,开启/关闭 
    OLED_WrCmd(0x20); //设置内存地址模式
    OLED_WrCmd(0x02); //[1:0],00,列地址模式;01,行地址模式;10,页地址模式;默认10; 
    OLED_WrCmd(0xA1); //段重定义设置bit0:0,0->0;1,0->127;
    //A1列扫描顺序均为自左向右，A0列扫描顺序均为自右向左	
    //COM扫描方向：0xC0:COM0-COM63 ; 0xC8:COM63-COM0
    OLED_WrCmd(0xC0);// 设置COM扫描方向;bit3:0,普通模式;1,重定义模式 COM[N-1]->COM0;N:驱动路数
    OLED_WrCmd(0xDA);//设置COM硬件引脚配置
    OLED_WrCmd(0x12); //[5:4]配置
    //第4位0决定是连续扫描COM端(0,1...32...63)还是1交替扫描COM端(0,32,1,33....31,63)
    //注意实际输出顺序为0，32，1，33.....31，63，因此连续扫描对应交替显示，交替扫描对应连续显示
    //第五位决定是否对COM0-COM31与COM32-COM63进行重映射，1为允许，0为禁止

    OLED_WrCmd(0x81); //对比度设置
    OLED_WrCmd(0xEF); //1~255,默认0X7F(亮度设置，越大越亮)
    OLED_WrCmd(0xD9); //设置预充电周期
    OLED_WrCmd(0xF1); //[3:0],PHASE 1;[7:4],PHASE 2;
    OLED_WrCmd(0xDB); //设置VCOMH电压倍率
    OLED_WrCmd(0x30); //[6:4] 000,0.65*vcc;001,0.77*vcc;011,0.83*vcc;
    OLED_WrCmd(0xA4); //全局显示开启bit0:1,开启;0,关闭;(白屏/黑屏 )
    OLED_WrCmd(0xA6); //设置显示方式;bit0:1,反相显示;0,正常显示
    OLED_WrCmd(0xAF); //开启显示	

    OLED_SetPos(0,0);
} 
 
/*函数名：OLED_Clear
* 说明：清屏函数,清完屏,整个屏幕是黑色的，和没点亮一样（只是清数据缓冲，需调用函数OLED_Refresh_Gram）	
* 入口参数：无			 
*/
void OLED_Clear(void)
{
      uint8 i,n;  
      for(i=0;i<8;i++)
              for(n=0;n<132;n++)
                      displayGRAM[n][i]=0x00;  
}

/*函数名：OLED_WriteChar
* 说明：在指定位置显示一个字符,包括部分字符
* 入口参数：x:0~127
*          y:0~63
*          mode:0,反白显示;1,正常显示				 
*/
void OLED_WriteChar(uint8 x,uint8 y,uint8 chr,uint8 mode)
{      			    
   			    
    uint8 t;
    chr=chr-' ';//得到偏移后的值			   
    for(t=0;t<6;t++)//按行写入，一共写size行
    {   
        if(mode) 
        {
            displayGRAM[x+t][y/8]=ASCII_0608[chr][t];  //调用0608字体
        }
        else //反白显示
        {
            displayGRAM[x+t][y/8]=~ASCII_0608[chr][t];  //调用0608字体
        }	
     }
}

/*
 * 函数名：void OLED_DisString
 * 入口参数：x(0~121):字符串起始位置
 * 			y(0~56):字符串行数
 * 			mode:1 正常显示，0 反色显示
 * 作用：显示一串字符串
 */
 void OLED_DisString(uint8 x,uint8 y,uint8 *str,uint8 mode)
 {
	 while(*str && x < 121)
         {
           OLED_WriteChar(x+=6, y, *str,mode);
           str++;
         }
 }

 /*
  * 函数名：void OLED_DisNumber
  * 入口参数：x(0~121):数字的位置
  * 		y(0~56):数字的行数
  * 		num(0~65535):要显示的数字
  * 作用：定位显示数字
  */
void OLED_DisNumber(uint8 x, uint8 y, uint16 num)
{
    signed   char i;
    unsigned char ii;
    unsigned char dat[6];

    for(i = 0; i < 6; i++) dat[i] = 0; 	         //初始化数据
    i = 0;
    while(num / 10)                             //拆位
    {
            dat[i] = num % 10;                   //最低位
            num /= 10; 
            i++;
    }
    dat[i] = num;                                //最高位
    ii = i;                                      //保存dat的位数
    for(; i >= 0; i--)	dat[i] += 48;            //转化成ASCII
    
    for(i = ii; i >= 0; i--)
      OLED_WriteChar(x+=6, y, dat[i],1);        //输出数值
}
