#ifndef __cursorCtrl_H__
#define __cursorCtrl_H__

#include <Windows.h>

// console variables
extern CONSOLE_CURSOR_INFO curInfo;
extern COORD pos;

typedef enum CURSOR_TYPE {
	NOCURSOR,
	SOLIDCUROR,
	NORMALCURSOR
}CURSOR_TYPE;

// Console Functions
extern void GoToXY(int x, int y);
extern void SetCursorType(CURSOR_TYPE c);

#endif