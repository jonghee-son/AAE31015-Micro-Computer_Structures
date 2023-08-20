#define _GLCD_C_
#include "GLCD.h"
#undef  _GLCD_C_

OldColorInfo OldColor;
gl_sFONT *LCD_pFont;

UINT32 	LCD_BkColor;
UINT32 	LCD_BrushColor;
UINT32 	LCD_TextColor;
UINT32 	LCD_PenColor;

void LCD_SetBackColor(UINT32 Color){ LCD_BkColor = Color; }
UINT16 LCD_GetBackColor(void){ return LCD_TextColor; }

void LCD_SetTextColor(UINT32 Color){ LCD_TextColor = Color; }
UINT16 LCD_GetTextColor(void){ return LCD_TextColor; }

void LCD_SetPenColor(UINT32 Color){ LCD_PenColor = Color; }
UINT16 LCD_GetPenColor(void){ return LCD_PenColor; }

void LCD_SetBrushColor(UINT32 Color){ LCD_BrushColor = Color; }
UINT16 LCD_GetBrushColor(void){ return LCD_BrushColor; }

void LCD_SetFont(gl_sFONT *pFont){ LCD_pFont = pFont; }
gl_sFONT* LCD_GetFont(void){ return LCD_pFont; }

void SaveOldColor()
{
  OldColor.OldBackColor  = LCD_GetBackColor();
  OldColor.OldTextColor  = LCD_GetTextColor();
  OldColor.OldPenColor   = LCD_GetPenColor();
  OldColor.OldBrushColor = LCD_GetBrushColor();
  OldColor.OldFont       = LCD_GetFont();
}

void RestoreOldColor()
{
  LCD_SetBackColor(OldColor.OldBackColor);
  LCD_SetTextColor(OldColor.OldTextColor);
  LCD_SetPenColor(OldColor.OldPenColor);
  LCD_SetBrushColor(OldColor.OldBrushColor);
  LCD_SetFont(OldColor.OldFont);
}
void LCD_Init(void)
{
    LCD_BkColor = RGB_BLACK;
    LCD_BrushColor = LCD_BkColor;
    LCD_TextColor = RGB_WHITE;
    LCD_PenColor = LCD_TextColor;
    
    LCD_pFont = &Gulim7;  
	
    ILI_Init();    
    LCD_Clear(RGB_WHITE);
}

void LCD_DrawChar(UINT16 x, UINT16 y, char ch)
{
    UINT16 i, w;
    
    if(x+LCD_pFont->Width>=LCD_PIXEL_WIDTH) return;

    ILI_SetWindow(x, y, x + (LCD_pFont->Width-1), y + LCD_pFont->Height-1);
    
    w = LCD_pFont->Width<8?LCD_pFont->Width:8;
      
    ILI_WRITE_START();
    for(i=0;i<LCD_pFont->nData;i++)
    {
          u8 data = LCD_pFont->table[ch*LCD_pFont->nData+i];
          
          for(int ix=0;ix<w;ix++)
          {
              if(data&0x80) ILI_WRITE_RGB( LCD_TextColor);
              else ILI_WRITE_RGB(LCD_BkColor );
              data <<= 1;
          }
    }

    ILI_WRITE_END();
}

void LCD_DrawText(UINT16 x, UINT16 y, char *str)
{
    UINT16 cnt = 0;

    while(*str)
    {
         LCD_DrawChar(x+cnt*LCD_pFont->Width,y,*str++);
         cnt++;
    }
}

void LCD_DrawHorLine(UINT16 x, UINT16 y, UINT16 width)
{
    UINT16 i;

    ILI_SetWindow(x, y, x+width, y);

    ILI_WRITE_START();

    for(i=0;i<width;i++)
    {  		
      ILI_WRITE_RGB(LCD_PenColor);
    }

    ILI_WRITE_END();
}

void LCD_DrawVerLine(UINT16 x, UINT16 y, UINT16 height)
{
    UINT16 i;

    ILI_SetWindow(x, y, x, y+height);

    ILI_WRITE_START();

    for(i=0;i<=height;i++)
    {  		
        ILI_WRITE_RGB(LCD_PenColor);
    }

    ILI_WRITE_END();
}

void LCD_DrawRectangle(UINT16 x, UINT16 y, UINT16 width, UINT16 height)
{
    LCD_DrawHorLine(x,y,width);
    LCD_DrawHorLine(x,y+height,width);
    LCD_DrawVerLine(x,y,height);
    LCD_DrawVerLine(x+width,y,height);
}

void LCD_DrawFillRect(UINT16 x, UINT16 y, UINT16 width, UINT16 height)
{
    UINT32 i;

    ILI_SetWindow(x, y, x+width-1, y+height-1);

    ILI_WRITE_START();

    for(i=0;i<width*height;i++)
    {  		
        ILI_WRITE_RGB(LCD_BrushColor);
    }

    ILI_WRITE_END();
}

void LCD_DrawPixel(UINT16 x, UINT16 y)
{
    ILI_SetWindow(x, y, x, y);

    ILI_WRITE_START();
    ILI_WRITE_RGB(LCD_PenColor);
    ILI_WRITE_END();
}

void LCD_DrawLine(UINT16 x1, UINT16 y1, UINT16 x2, UINT16 y2)
{
    uint8_t steep = 0; // Steepness of line,0 - non-steep (angle 45?),1 - steep (45?) 
    uint16_t TempPos = 0;
    uint16_t x = 0, y = 0;
    uint16_t deltax = 0, deltay = 0;
    int16_t errorX = 0;
    int8_t ystep = 0;

    //Case the both points are identical
    if ((x1 == x2) && (y1 == y2))
    {
      LCD_DrawPixel(x1, y1);
    }
    //Case the line are pure horizontal
    else if (y1 == y2)
    {
      //Swap X positions if it is necessary
      if (x1 > x2)
      {
        TempPos = x2;
        x2 = x1;
        x1 = TempPos;
      }

      for (x = x1 ; x <= x2;x++)
      {
        LCD_DrawPixel(x, y1);
      }
    }
    //Case the line are pure vertical
    else if (x1 == x2)
    {
      //Swap Y positions if it is necessary
      if (y1 > y2)
      {
        TempPos = y2;
        y2 = y1;
        y1 = TempPos;
      }

      for (y = y1 ; y <= y2; y++)
      {
        LCD_DrawPixel(x1, y);
      }

    }
    //The general line
    else
    {
      //Calculate steepness. If elevation angle is smaller than 45?steep is reset to 0
      steep = ((y1 > y2) ? (y1 - y2) : (y2 - y1)) > ((x1 > x2) ? (x1 - x2) : (x2 - x1));

      //Coordinators X and Y are swapped with each other in case of steep = 1
      if (steep != 0x00)
      {
        TempPos = y1;
        y1 = x1;
        x1 = TempPos;

        TempPos = y2;
        y2 = x2;
        x2 = TempPos;
      }
      //Coordinators X and Y are swapped separetely if it is necessary.
      if (x1 > x2)
      {
        TempPos = y1;
        y1 = y2;
        y2 = TempPos;

        TempPos = x2;
        x2 = x1;
        x1 = TempPos;
      }

      //Bresenham line algorithm 
      deltax = x2 - x1;
      deltay = ((y1 > y2) ? (y1 - y2) : (y2 - y1));
      errorX = -(deltax + 1) / 2;
      y = y1;
      if (y1 < y2)
      {
        ystep = 1;
      }
      else
      {
        ystep = -1;
      }

      for (x = x1; x <= x2 ; x++)
      {
        if (steep != 0x00)
        {
          {
            LCD_DrawPixel(y, x);
          }
        }
        else
        {
          {
            LCD_DrawPixel(x, y);
          }
        }

        errorX = errorX + deltay;
        if (errorX >= 0)
        {
          y = y + ystep;
          errorX = errorX - deltax;
        }
      }
    }
   
}

#define WIDTHBYTES(bits)        (((bits)+31)/32*4)
/*
void LCD_BitmapDisplay(uint16_t x, uint16_t y, Bitmap *bitmap)
{
  uint16_t width = bitmap->width;
  uint16_t height = bitmap->height;
  const uint8_t *image = bitmap->image;
  uint16_t rwsize = WIDTHBYTES(24*width);
  
  ILI_SetWindow(x, y, x+width-1, y+height-1);
  
  ILI_WRITE_START();

  for(int j=0; j<height; j++)
    for(int i=0; i<width*3; i+=3)
    {
      ILI_WRITE_RGB(GET_RGB(image[j*rwsize+i],image[j*rwsize+i+1],image[j*rwsize+i+2]));
    }
  
}
*/
void LCD_Clear(UINT32 Color)
{ 
    ILI_Clear(Color);
}

void LCD_ClearLine(UINT16 Row)
{
    int y= LCD_ROW(Row);
    unsigned int n,m;
    
    ILI_SetWindow(0, y,LCD_PIXEL_WIDTH, y+LCD_pFont->Height-1);

    ILI_WRITE_START();
    
    for(m=y;m<y+LCD_pFont->Height;m++)
       for(n=0; n<LCD_PIXEL_WIDTH; n++)	ILI_WRITE_RGB(LCD_BkColor);

    ILI_WRITE_END();
}

void LCD_DisplayChar(UINT16 Row, UINT16 Col, char ch)
{
      LCD_DrawChar(LCD_COL(Col), LCD_ROW(Row), ch);
}

void LCD_DisplayText(UINT16 Row, UINT16 Col, char *str)
{
      LCD_DrawText(LCD_COL(Col), LCD_ROW(Row), str);
}

   
