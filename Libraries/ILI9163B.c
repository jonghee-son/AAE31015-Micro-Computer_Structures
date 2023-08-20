#define _ILI9163B_C_
#include "ILI9163B.h"
#undef  _ILI9163B_C_

#include "util.h"

u8 ILI_ReadCmd(void)
{
      return LCD_CMD;	
}

u8 ILI_ReadData(void)
{
      return LCD_CMD;	
}

static void ILI_WriteCmd(UINT8 Cmd)
{
      LCD_CMD = Cmd;
}

static void ILI_WriteData(UINT8 data)
{
      LCD_DATA = data;
}

void ILI_READ_START()
{
      ILI_WriteCmd(ILI_CMD_READ_MEM_START);
}

UINT32 ILI_READ_RGB()
{
    UINT32 rgb;
    rgb  = ILI_ReadData()<<16;
    rgb |= ILI_ReadData()<<8;
    rgb |= ILI_ReadData()&0xFF;

    return rgb;
}

void ILI_READ_END()
{
      ILI_WriteCmd(0x00);
}

void ILI_WRITE_START()
{
      ILI_WriteCmd(ILI_CMD_WRITE_MEM_START);
}

void ILI_WRITE_RGB(UINT32 rgb)
{
    ILI_WriteData(rgb>>16);
    ILI_WriteData(rgb>>8);
    ILI_WriteData(rgb);
}

void ILI_WRITE_END()
{
      ILI_WriteCmd(0x00);
}

void FSMC_GPIO_Config(void)
{
      GPIO_InitTypeDef GPIO_InitStructure;
    
      RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD | RCC_AHB1Periph_GPIOF | RCC_AHB1Periph_GPIOE , ENABLE);	
     
      GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
      GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
      GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
      GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_NOPULL;
      
      // LCD Data : PD14 = D0, PD15 = D1, PD0 = D2, PD1 = D3
      GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_14 | GPIO_Pin_15 |GPIO_Pin_0 | GPIO_Pin_1 ;  
      GPIO_Init(GPIOD, &GPIO_InitStructure); 
      
      GPIO_PinAFConfig(GPIOD, GPIO_PinSource14, GPIO_AF_FSMC);
      GPIO_PinAFConfig(GPIOD, GPIO_PinSource15, GPIO_AF_FSMC);
      GPIO_PinAFConfig(GPIOD, GPIO_PinSource0, GPIO_AF_FSMC);
      GPIO_PinAFConfig(GPIOD, GPIO_PinSource1, GPIO_AF_FSMC);
      
      // LCD Data : PE7 = D4, PE8 = D5, PE9 = D6, PE10 = D7    
      GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 ;
      GPIO_Init(GPIOE, &GPIO_InitStructure);
      
      GPIO_PinAFConfig(GPIOE, GPIO_PinSource7 , GPIO_AF_FSMC);
      GPIO_PinAFConfig(GPIOE, GPIO_PinSource8 , GPIO_AF_FSMC);
      GPIO_PinAFConfig(GPIOE, GPIO_PinSource9 , GPIO_AF_FSMC);
      GPIO_PinAFConfig(GPIOE, GPIO_PinSource10 , GPIO_AF_FSMC);    
      
      //PD4 = RD, PD5 = WR, PD7 = CS
      GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_4 | GPIO_Pin_5 |GPIO_Pin_7;
      GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF;
      GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
      GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
      GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_NOPULL;
     
      GPIO_Init(GPIOD,&GPIO_InitStructure);
      
      GPIO_PinAFConfig(GPIOD, GPIO_PinSource4 , GPIO_AF_FSMC);
      GPIO_PinAFConfig(GPIOD, GPIO_PinSource5 , GPIO_AF_FSMC);
      GPIO_PinAFConfig(GPIOD, GPIO_PinSource7 , GPIO_AF_FSMC);
      
      //PF0 = RS
      GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_0;
      
      GPIO_Init(GPIOF,&GPIO_InitStructure);
      GPIO_PinAFConfig(GPIOF, GPIO_PinSource0 , GPIO_AF_FSMC);
      
      //PF1 = RST, PF7 = BACK_LIGHT 
      GPIO_InitStructure.GPIO_Pin=GPIO_Pin_1 | GPIO_Pin_7 ; 
      GPIO_InitStructure.GPIO_Mode=GPIO_Mode_OUT;
      GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
      GPIO_InitStructure.GPIO_OType=GPIO_OType_PP;
      GPIO_InitStructure.GPIO_PuPd=GPIO_PuPd_NOPULL;
      GPIO_Init(GPIOF,&GPIO_InitStructure);
} 

void FSMC_LCD_Init(void)
{
      FSMC_NORSRAMInitTypeDef  FSMC_NORSRAMInitStructure;
      FSMC_NORSRAMTimingInitTypeDef  p;
      
      RCC_AHB3PeriphClockCmd(RCC_AHB3Periph_FSMC, ENABLE);

      p.FSMC_AddressSetupTime = 3; //0~15
      p.FSMC_AddressHoldTime = 3;  //1~15
      p.FSMC_DataSetupTime = 3;  //1~256
      p.FSMC_BusTurnAroundDuration = 0;   //0~15 
      p.FSMC_CLKDivision = 2;  //2~16
      p.FSMC_DataLatency = 2;  //2~17
      p.FSMC_AccessMode = FSMC_AccessMode_B; 

      FSMC_NORSRAMInitStructure.FSMC_Bank = FSMC_Bank1_NORSRAM1;
      FSMC_NORSRAMInitStructure.FSMC_DataAddressMux = FSMC_DataAddressMux_Disable;
      FSMC_NORSRAMInitStructure.FSMC_MemoryType = FSMC_MemoryType_SRAM;
      FSMC_NORSRAMInitStructure.FSMC_MemoryDataWidth = FSMC_MemoryDataWidth_8b;
      FSMC_NORSRAMInitStructure.FSMC_BurstAccessMode = FSMC_BurstAccessMode_Disable;
      FSMC_NORSRAMInitStructure.FSMC_AsynchronousWait = FSMC_AsynchronousWait_Disable;  
      FSMC_NORSRAMInitStructure.FSMC_WaitSignalPolarity = FSMC_WaitSignalPolarity_Low;
      FSMC_NORSRAMInitStructure.FSMC_WrapMode = FSMC_WrapMode_Disable;
      FSMC_NORSRAMInitStructure.FSMC_WaitSignalActive = FSMC_WaitSignalActive_BeforeWaitState;
      FSMC_NORSRAMInitStructure.FSMC_WriteOperation = FSMC_WriteOperation_Enable;
      FSMC_NORSRAMInitStructure.FSMC_WaitSignal = FSMC_WaitSignal_Disable;
      FSMC_NORSRAMInitStructure.FSMC_ExtendedMode = FSMC_ExtendedMode_Disable;
      FSMC_NORSRAMInitStructure.FSMC_WriteBurst = FSMC_WriteBurst_Disable;
      FSMC_NORSRAMInitStructure.FSMC_ReadWriteTimingStruct = &p;
      FSMC_NORSRAMInitStructure.FSMC_WriteTimingStruct = &p;	  
    
      FSMC_NORSRAMInit(&FSMC_NORSRAMInitStructure); 
      
      FSMC_NORSRAMCmd(FSMC_Bank1_NORSRAM1, ENABLE);  
}

void ILI_Init(void)
{
      FSMC_GPIO_Config();    
      FSMC_LCD_Init();    
     
      ILI_BACKLIGHT_HIGH;
      
      ILI_RST_HIGH;
      UTIL_DelayMS(10L);
      ILI_RST_LOW;
      UTIL_DelayMS(10L);
      ILI_RST_HIGH;
      UTIL_DelayMS(50L);

      ILI_WriteCmd(0x01);
      UTIL_DelayMS(50L);      
      
      //Const_Value=0x0040;
      //************* Start Initial Sequence **********//
      ILI_WriteCmd(0x11); //0x11 Exit Sleep
      UTIL_DelayMS(120);
      
      ILI_WriteCmd(0x26); //0x26 Set Default Gamma
      ILI_WriteData(0x04);
      
      ILI_WriteCmd(0xB1);//0xB1
      ILI_WriteData(0x0A);//0x0A;
      ILI_WriteData(0x14); //In Normal mode, line=160, Default value DIVA[4:0]=14, VPA[5:0]=20, Frame rate=61.7Hz
      
      ILI_WriteCmd(0xC0); //0xC0 Set VRH1[4:0] & VC[2:0] for VCI1 & GVDD
      ILI_WriteData(0x08);
      ILI_WriteData(0x00);
      
      ILI_WriteCmd(0xC1); //0xC1 Set BT[2:0] for AVDD & VCL & VGH & VGL
      ILI_WriteData(0x05);
      
      ILI_WriteCmd(0xC5); //0xC5 Set VMH[6:0] & VML[6:0] for VOMH & VCOML
      ILI_WriteData(0x38);
      ILI_WriteData(0x35);
      
      ILI_WriteCmd(0x3A); //0x3A
      ILI_WriteData(0x06);
      
      ILI_WriteCmd(0x2A); //0x2A
      ILI_WriteData(0x00);
      ILI_WriteData(0x00);
      ILI_WriteData(0x00);
      ILI_WriteData(0x7F);
      
      ILI_WriteCmd(0x2B); //0x2B
      ILI_WriteData(0x00);
      ILI_WriteData(0x00);
      ILI_WriteData(0x00);
      ILI_WriteData(0x9F);
      
      ILI_WriteCmd(0x36); //0x36
      ILI_WriteData(0x70);
      
      ILI_WriteCmd(0xB7); //0xB7 ?? 0xBF
      ILI_WriteData(0x00);
      
      ILI_WriteCmd(0xF2); //0xF2 Enable Gamma bit
      ILI_WriteData(0x01);
      
      ILI_WriteCmd(0xE0);
      ILI_WriteData(0x3f);//0x36);//p1
      ILI_WriteData(0x22);//0x29);//p2
      ILI_WriteData(0x20);//0x12);//p3
      ILI_WriteData(0x30);//0x22);//p4
      ILI_WriteData(0x29);//0x1C);//p5
      ILI_WriteData(0x0c);//0x15);//p6
      ILI_WriteData(0x4e);//0x42);//p7
      ILI_WriteData(0xb7);//0xB7);//p8
      ILI_WriteData(0x3c);//0x2F);//p9
      ILI_WriteData(0x19);//0x13);//p10
      ILI_WriteData(0x22);//0x12);//p11
      ILI_WriteData(0x1e);//0x0A);//p12
      ILI_WriteData(0x02);//0x11);//p13
      ILI_WriteData(0x01);//0x0B);//p14
      ILI_WriteData(0x00);//0x06);//p15
      
      ILI_WriteCmd(0xE1);
      ILI_WriteData(0x00);//0x09);//p1
      ILI_WriteData(0x1b);//0x16);//p2
      ILI_WriteData(0x1f);//0x2D);//p3
      ILI_WriteData(0x0f);//0x0D);//p4
      ILI_WriteData(0x16);//0x13);//p5
      ILI_WriteData(0x13);//0x15);//p6
      ILI_WriteData(0x31);//0x40);//p7
      ILI_WriteData(0x84);//0x48);//p8
      ILI_WriteData(0x43);//0x53);//p9
      ILI_WriteData(0x06);//0x0C);//p10
      ILI_WriteData(0x1d);//0x1D);//p11
      ILI_WriteData(0x21);//0x25);//p12
      ILI_WriteData(0x3d);//0x2E);//p13
      ILI_WriteData(0x3e);//0x34);//p14
      ILI_WriteData(0x3f);//0x39);//p15
      
      ILI_WriteCmd(0x29); // Display On
      
      ILI_SetDirection(0,1);
      //-----------------------------------------------------------------------------------//
      //-----------------------------Initial Code End--------------------------------------//
      //-----------------------------------------------------------------------------------//
 }

void ILI_SetWindow(UINT16 StartX, UINT16 StartY, UINT16 EndX, UINT16 EndY)
{
      ILI_WriteCmd(ILI_CMD_COLUMN_ADDRESS); //0x2A
      
      if(EndX>LCD_PIXEL_WIDTH) EndX=LCD_PIXEL_WIDTH;
      if(EndY>LCD_PIXEL_HEIGHT) EndY=LCD_PIXEL_HEIGHT;
      
      ILI_WriteData(0x00);
      ILI_WriteData(StartX);
      
      ILI_WriteData(0x00);
      ILI_WriteData(EndX);
      
      ILI_WriteCmd(ILI_CMD_PAGE_ADDRESS);
      
      ILI_WriteData(0x00);
      ILI_WriteData(StartY);
      
      ILI_WriteData(0x00);
      ILI_WriteData(EndY);
}

#define LCD_bYOrder 	0x80
#define LCD_bXOrder 	0x40
#define LCD_bVertical 	0x20
#define LCD_bRGB 		0x08

void ILI_SetDirection(UINT16 bXOrder, UINT16 bYOrder)
{
      UINT16 Data = LCD_bVertical;
      ILI_WriteCmd(ILI_CMD_ADDRESS_MODE);

      if(bYOrder) Data |= LCD_bYOrder;
      if(bXOrder) Data |= LCD_bXOrder;

      ILI_WriteData(Data);
}

void ILI_Clear(UINT32 BkColor)
{
      unsigned int n,m;

      ILI_SetWindow(0, 0, LCD_PIXEL_WIDTH, LCD_PIXEL_HEIGHT);

      ILI_WRITE_START();

       for(m=0;m<LCD_PIXEL_HEIGHT;m++)
               for(n=0;n<LCD_PIXEL_WIDTH;n++)	ILI_WRITE_RGB(BkColor);

      ILI_WRITE_END();
}


