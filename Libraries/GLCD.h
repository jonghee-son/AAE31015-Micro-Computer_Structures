#ifndef	_GLCD_H_
#define	_GLCD_H_

//#include "BitmapInclude.h"
#include "FontInclude.h"
#include "ILI9163B.h"

#define GET_RGB(R,G,B)  ( ((R) << 16) | ((G) << 8) | ((B) & 0xFF) ) 
#define LCD_ROW(x)      ((x) * (LCD_GetFont()->Height+1))
#define LCD_COL(x)      ((x) * (LCD_GetFont()->Width))

#define RGB_BLACK	GET_RGB(0, 0, 0)
#define RGB_WHITE	GET_RGB(0xFF, 0xFF, 0xFF)
#define RGB_RED		GET_RGB(255, 0, 0)
#define RGB_GREEN	GET_RGB(0,  255, 0)
#define RGB_YELLOW	GET_RGB(255, 255, 0)
#define RGB_BLUE 	GET_RGB(0, 0, 255)
#define RGB_GRAY 	GET_RGB(240, 240, 240)


#ifdef _GLCD_C_
	#define LCD_EXT  		  	
#else
	#define LCD_EXT extern
#endif

typedef struct OldColorInfo
{
  UINT16 OldBackColor ;
  UINT16 OldTextColor ;
  UINT16 OldPenColor ;
  UINT16 OldBrushColor ;
  gl_sFONT* OldFont ;
}OldColorInfo;


LCD_EXT void LCD_Init(void);
LCD_EXT void RestoreOldColor();
LCD_EXT void SaveOldColor();

void      LCD_SetBackColor(UINT32 _Color);
UINT16    LCD_GetBackColor(void);
void      LCD_SetTextColor(UINT32 _Color);
UINT16    LCD_GetTextColor(void);
void      LCD_SetPenColor(UINT32 Color);
UINT16    LCD_GetPenColor(void);
void      LCD_SetBrushColor(UINT32 Color);
UINT16    LCD_GetBrushColor(void);
void      LCD_SetFont(gl_sFONT *pFont);
gl_sFONT* LCD_GetFont(void);

void      LCD_Clear(UINT32 Color);

void      LCD_DrawChar(UINT16 x, UINT16 y, char ch);
void      LCD_DrawText(UINT16 x, UINT16 y, char *str);
void      LCD_DrawHorLine(UINT16 x, UINT16 y, UINT16 width);
void      LCD_DrawVerLine(UINT16 x, UINT16 y, UINT16 height);
void      LCD_DrawRectangle(UINT16 x, UINT16 y, UINT16 width, UINT16 height);
void      LCD_DrawFillRect(UINT16 x, UINT16 y, UINT16 width, UINT16 height);
//void      LCD_BitmapDisplay(uint16_t x, uint16_t y, Bitmap *bitmap);
void      LCD_DrawLine(UINT16 x1, UINT16 y1, UINT16 x2, UINT16 y2);
void      LCD_DrawPixel(UINT16 x, UINT16 y);

void      LCD_ClearLine(UINT16 Row);
void      LCD_DisplayChar(UINT16 Row, UINT16 Col, char ch);
void      LCD_DisplayText(UINT16 Row, UINT16 Col, char *str);


#endif
