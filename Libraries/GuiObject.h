#ifndef _GUI_OBJECT_H_
#define _GUI_OBJECT_H_

#include "Default.h"
#include "GLCD.h"

#ifdef _GUI_OBJECT_C_
	#define GUI_OBJECT_EXT
#else
	#define GUI_OBJECT_EXT extern
#endif

GUI_OBJECT_EXT void InitInstrumentPanel(void);
GUI_OBJECT_EXT void DrawInstrumentPanelBar(int degree);
GUI_OBJECT_EXT void DrawBackGroundInstrumentPanel(void);
GUI_OBJECT_EXT int ChangeCoord(float max1,float max2,int value);
#endif

