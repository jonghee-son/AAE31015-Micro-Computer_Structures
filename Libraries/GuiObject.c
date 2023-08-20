#define _GUI_OBJECT_C_
#include "GuiObject.h"
#undef  _GUI_OBJECT_C_

#include <math.h>

typedef struct {
    UINT32 OrgX;
    UINT32 OrgY;
    UINT32 Radius;
    UINT32 StructColor;
    UINT32 BackColor;
    UINT32 LineColor;
}INSTRUMENT_PANEL;

INSTRUMENT_PANEL sInstPanel;

void DrawBackGroundInstrumentPanel(void);

void InitInstrumentPanel(void)
{
    sInstPanel.OrgX = LCD_PIXEL_WIDTH/2;
    sInstPanel.OrgY = LCD_PIXEL_HEIGHT - 5;
    sInstPanel.Radius = LCD_PIXEL_WIDTH*3/7;
    sInstPanel.StructColor = RGB_BLACK;
    sInstPanel.BackColor = RGB_WHITE;
    sInstPanel.LineColor = RGB_RED;
}

#define RADIAN(x)       (((x)/(180.f))*(3.141592f))

void DrawBackGroundInstrumentPanel(void)
{
    INSTRUMENT_PANEL *p = &sInstPanel;
    int x,y,len;
    double vCos,vSin;
    int thickness = 2;
    
    x = p->OrgX - p->Radius - thickness;
    y = p->OrgY;
    len = (p->Radius+thickness)*2;
    
    LCD_SetPenColor(p->StructColor);
    LCD_DrawHorLine(x,y,len);
   
    for(int theta= 1800; theta > 0; theta--)
    {
        vCos = cos(RADIAN((double)theta/10.f));
        vSin = sin(RADIAN((double)theta/10.f));
        
        for(thickness = 2; thickness>0; thickness--)
        {
            x = ((double)p->Radius+thickness)*vCos + p->OrgX;
            y = -1.f*((double)p->Radius+thickness)*vSin + p->OrgY; 
            LCD_DrawPixel(x,y);
        }
    }
}

void DrawInstrumentPanelBar(int degree)
{
    INSTRUMENT_PANEL *p = &sInstPanel;
    static int prev_degree = 0xffff; 
    int x,y;
    int offset = 2;
    
    double vCos,vSin;
    double radius = p->Radius - offset;
    
    degree = -1*degree + 180;
    
    if(degree > 180)
      degree = 180;
    if(degree < 0)
      degree = 0;
    
    if(prev_degree != degree)
    {
        if(prev_degree == 0xffff)
        {
            LCD_SetPenColor(p->LineColor);

            vCos = cos(RADIAN((double)degree));
            vSin = sin(RADIAN((double)degree));
            x = radius*vCos + p->OrgX;
            y = -1.f*radius*vSin + p->OrgY; 
                
            LCD_DrawLine(p->OrgX,p->OrgY-offset,x,y-offset);
            prev_degree = degree;
            return;
        }
        
        LCD_SetPenColor(p->BackColor);

        vCos = cos(RADIAN((double)prev_degree));
        vSin = sin(RADIAN((double)prev_degree));
        x = radius*vCos + p->OrgX;
        y = -1.f*radius*vSin + p->OrgY; 
            
        LCD_DrawLine(p->OrgX,p->OrgY-offset,x,y-offset);
      
        LCD_SetPenColor(p->LineColor);

        vCos = cos(RADIAN((double)degree));
        vSin = sin(RADIAN((double)degree));
        x = radius*vCos + p->OrgX;
        y = -1.f*radius*vSin + p->OrgY; 
            
        LCD_DrawLine(p->OrgX,p->OrgY-offset,x,y-offset);
        prev_degree = degree;
    }
}

int ChangeCoord(float max1,float max2,int value)
{
    return (int)(max2/max1*value);
}
