#include "cursorCtrl.h"

void GoToXY(int x, int y)
{
    COORD pos = { 2 * x, y };

    // Function that moving cursor position
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void SetCursorType(CURSOR_TYPE c)
{
    CONSOLE_CURSOR_INFO curInfo;

    switch (c) {
    case NOCURSOR:
        curInfo.dwSize = 1;
        curInfo.bVisible = FALSE;
        break;
    case SOLIDCUROR:
        curInfo.dwSize = 100;
        curInfo.dwSize = TRUE;
        break;
    case NORMALCURSOR:
        curInfo.dwSize = 20;
        curInfo.dwSize = TRUE;
        break;
    default:
        break;
    }
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);
}
