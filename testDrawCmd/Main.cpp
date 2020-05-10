#include "xyio.h"
#include <iostream>
#include <Windows.h>
#include <WinUser.h>
#include <windef.h>

char CheckMouseButtonStatus();
void DrawMenuColors();
const char* CheckColorMenu(COORD coord);

int main(void) {
	COORD coord = { 0, 0 }, xy = { 0,1 };

    //DWORD prev_mode;
    //GetConsoleMode(GetStdHandle(STD_OUTPUT_HANDLE), &prev_mode);
    //SetConsoleMode(GetStdHandle(STD_OUTPUT_HANDLE), ENABLE_EXTENDED_FLAGS |
    //(prev_mode & ~ENABLE_QUICK_EDIT_MODE));


    CONSOLE_CURSOR_INFO info;
    info.dwSize = 100;
    info.bVisible = FALSE;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);

    POINT pt;


    RECT rc;


    CONSOLE_SCREEN_BUFFER_INFO inf;
    

    const char* c = "white";

	while (true) {
        DrawMenuColors();
        xycprintf(87, 0, c, "white", " ");
        GetCursorPos(&pt);
        GetClientRect(GetConsoleWindow(), &rc);
        ScreenToClient(GetConsoleWindow(), &pt);
        GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &inf);

        coord.X = MulDiv(pt.x, inf.srWindow.Right, rc.right);
        coord.Y = MulDiv(pt.y, inf.srWindow.Bottom, rc.bottom);

        if (CheckMouseButtonStatus() == 'R') if (CheckColorMenu(coord) != "" && CheckColorMenu(coord) != "X") c = CheckColorMenu(coord);
        else if (coord.X != xy.X || coord.Y != xy.Y)
        {            
            if (CheckMouseButtonStatus() == 'R')xycprintf(coord.X, coord.Y, c, "white", " ");

            xy.X = coord.X;
            xy.Y = coord.Y;
        }

	}
	return 0;
}


char CheckMouseButtonStatus()
{
    if ((GetKeyState(VK_LBUTTON) & 0x80) != 0)
    {
        return 'L';
    }
    //Check the mouse right button is pressed or not
    if ((GetKeyState(VK_RBUTTON) & 0x80) != 0)
    {
        return 'R';
    }
}

void DrawMenuColors() {
    xycprintf(0, 0, "black", "white", "   ");
    xycprintf(3, 0, "dblue", "white", "   ");
    xycprintf(6, 0, "dgreen", "white", "   ");
    xycprintf(9, 0, "dcyan", "white", "   ");
    xycprintf(12, 0, "dred", "white", "   ");
    xycprintf(15, 0, "dmagenta", "white", "   ");
    xycprintf(18, 0, "dyellow", "white", "   ");
    xycprintf(21, 0, "gray", "white", "   ");
    xycprintf(24, 0, "dgray", "white", "   ");
    xycprintf(27, 0, "blue", "white", "   ");
    xycprintf(30, 0, "green", "white", "   ");
    xycprintf(33, 0, "cyan", "white", "   ");
    xycprintf(36, 0, "red", "white", "   ");
    xycprintf(39, 0, "magenta", "white", "   ");
    xycprintf(42, 0, "yellow", "white", "   ");
    xycprintf(45, 0, "white", "white", "   ");
    xycprintf(0, 1, "black", "white", "   ");
    xycprintf(3, 1, "dblue", "white", "   ");
    xycprintf(6, 1, "dgreen", "white", "   ");
    xycprintf(9, 1, "dcyan", "white", "   ");
    xycprintf(12, 1, "dred", "white", "   ");
    xycprintf(15, 1, "dmagenta", "white", "   ");
    xycprintf(18, 1, "dyellow", "white", "   ");
    xycprintf(21, 1, "gray", "white", "   ");
    xycprintf(24, 1, "dgray", "white", "   ");
    xycprintf(27, 1, "blue", "white", "   ");
    xycprintf(30, 1, "green", "white", "   ");
    xycprintf(33, 1, "cyan", "white", "   ");
    xycprintf(36, 1, "red", "white", "   ");
    xycprintf(39, 1, "magenta", "white", "   ");
    xycprintf(42, 1, "yellow", "white", "   ");
    xycprintf(45, 1, "white", "white", "   ");
    xycprintf(48, 0, "black", "white", " <- Bhrshes ");
    xycprintf(48, 1, "black", "white", "            ");
    xycprintf(70, 0, "black", "white", " Current brush ->  ");
    xycprintf(70, 1, "black", "white", "                   ");
}

const char* CheckColorMenu(COORD coord) {
    if (coord.Y <= 1) {
        if (coord.X >= 0 && coord.X <= 2) return "black";
        if (coord.X >= 3 && coord.X <= 5) return "dblue";
        if (coord.X >= 6 && coord.X <= 8) return "dgreen";
        if (coord.X >= 9 && coord.X <= 11) return "dcyan";
        if (coord.X >= 12 && coord.X <= 14) return "dred";
        if (coord.X >= 15 && coord.X <= 17) return "dmagenta";
        if (coord.X >= 18 && coord.X <= 20) return "dyellow";
        if (coord.X >= 21 && coord.X <= 23) return "gray";
        if (coord.X >= 24 && coord.X <= 26) return "dgray";
        if (coord.X >= 27 && coord.X <= 29) return "blue";
        if (coord.X >= 30 && coord.X <= 32) return "green";
        if (coord.X >= 33 && coord.X <= 35) return "cyan";
        if (coord.X >= 36 && coord.X <= 38) return "red";
        if (coord.X >= 39 && coord.X <= 41) return "magenta";
        if (coord.X >= 42 && coord.X <= 44) return "yellow";
        if (coord.X >= 45 && coord.X <= 47) return "white";
        return "X";
    }
    return "";
}