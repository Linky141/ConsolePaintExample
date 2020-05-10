#ifndef _XYIO_

#pragma warning(disable:4244)
#pragma warning(disable:4996 4005)
#define _CRT_SECURE_NO_WARNINGS
#define _USE_MATH_DEFINES
#ifdef UNICODE
# undef UNICODE
# define _MBCS
#endif

#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <windows.h>

#include "xyio.h"

#endif

void setcursor(int x, int y)
{
	HANDLE ekran = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD punkt = { (SHORT)x,(SHORT)y };
	SetConsoleCursorPosition(ekran, punkt);
}

void getcursor(int* x, int* y)
{
	HANDLE ekran = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO bufor;
	GetConsoleScreenBufferInfo(ekran, &bufor);
	*x = bufor.dwCursorPosition.X;
	*y = bufor.dwCursorPosition.Y;
}

void getrange(int* maxx, int* maxy)
{
	HANDLE ekran = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO bufor;
	GetConsoleScreenBufferInfo(ekran, &bufor);
	*maxx = bufor.dwMaximumWindowSize.X;
	*maxy = bufor.dwMaximumWindowSize.Y;
}

void getscreen(int* xorg, int* yorg, int* xend, int* yend)
{
	HANDLE ekran = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO bufor;
	GetConsoleScreenBufferInfo(ekran, &bufor);
	*xorg = bufor.srWindow.Left;
	*yorg = bufor.srWindow.Top;
	*xend = bufor.srWindow.Right;
	*yend = bufor.srWindow.Bottom;
}

int xyscanf(int x, int y, const char* format, ...)
{
	HANDLE klawiatura = GetStdHandle(STD_INPUT_HANDLE);
	CHAR tekst[150];
	DWORD znaki;
	BOOL sukces;
	va_list argumenty;
	int rezultat;
	va_start(argumenty, format);
	setcursor(x, y);
	sukces = ReadConsole(klawiatura, tekst, 150, &znaki, NULL);
	if (!sukces) rezultat = EOF;
	else {
		while (znaki > 0 && (tekst[znaki - 1] == '\n' || tekst[znaki - 1] == '\r')) znaki--;
		tekst[znaki] = '\0';
		rezultat = vsscanf(tekst, format, argumenty);
	}
	va_end(argumenty);
	return rezultat;
}

int xyprintf(int x, int y, const char* format, ...)
{
	HANDLE ekran = GetStdHandle(STD_OUTPUT_HANDLE);
	CHAR tekst[150];
	DWORD znaki;
	BOOL sukces;
	va_list argumenty;
	int rezultat;
	va_start(argumenty, format);
	rezultat = vsprintf(tekst, format, argumenty);
	if (rezultat >= 0) {
		znaki = (DWORD)rezultat;
		setcursor(x, y);
		sukces = WriteConsole(ekran, tekst, znaki, NULL, NULL);
		if (!sukces) rezultat = EOF;
	}
	va_end(argumenty);
	return rezultat;
}

int xycscanf(int x, int y, const char* BGcolor, const char* FGcolor, const char* format, ...)
{
	int color;
	if (BGcolor == "black") color = 0;
	else if (BGcolor == "dblue") color = 16 * 1;
	else if (BGcolor == "dgreen") color = 16 * 2;
	else if (BGcolor == "dcyan") color = 16 * 3;
	else if (BGcolor == "dred") color = 16 * 4;
	else if (BGcolor == "dmagenta")color = 16 * 5;
	else if (BGcolor == "dyellow")color = 16 * 6;
	else if (BGcolor == "gray")color = 16 * 7;
	else if (BGcolor == "dgray")color = 16 * 8;
	else if (BGcolor == "blue")color = 16 * 9;
	else if (BGcolor == "green")color = 16 * 10;
	else if (BGcolor == "cyan")color = 16 * 11;
	else if (BGcolor == "red")color = 16 * 12;
	else if (BGcolor == "magenta")color = 16 * 13;
	else if (BGcolor == "yellow")color = 16 * 14;
	else if (BGcolor == "white")color = 16 * 15;
	else return -1;

	if (FGcolor == "black") color += 0;
	else if (FGcolor == "dblue") color += 1;
	else if (FGcolor == "dgreen")color += 2;
	else if (FGcolor == "dcyan")color += 3;
	else if (FGcolor == "dred")color += 4;
	else if (FGcolor == "dmagenta")color += 5;
	else if (FGcolor == "dyellow")color += 6;
	else if (FGcolor == "gray")color += 7;
	else if (FGcolor == "dgray")color += 8;
	else if (FGcolor == "blue")color += 9;
	else if (FGcolor == "green")color += 10;
	else if (FGcolor == "cyan")color += 11;
	else if (FGcolor == "red")color += 12;
	else if (FGcolor == "magenta")color += 13;
	else if (FGcolor == "yellow")color += 14;
	else if (FGcolor == "white")color += 15;
	else return -1;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);

	HANDLE klawiatura = GetStdHandle(STD_INPUT_HANDLE);
	CHAR tekst[150];
	DWORD znaki;
	BOOL sukces;
	va_list argumenty;
	int rezultat;
	va_start(argumenty, format);
	setcursor(x, y);
	sukces = ReadConsole(klawiatura, tekst, 150, &znaki, NULL);
	if (!sukces) rezultat = EOF;
	else {
		while (znaki > 0 && (tekst[znaki - 1] == '\n' || tekst[znaki - 1] == '\r')) znaki--;
		tekst[znaki] = '\0';
		rezultat = vsscanf(tekst, format, argumenty);
	}
	va_end(argumenty);

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (7));
	return rezultat;
}

int xycprintf(int x, int y, const char* BGcolor, const char* FGcolor, const char* format, ...)
{
	int color;
	if (BGcolor == "black") color = 0;
	else if (BGcolor == "dblue") color = 16 * 1;
	else if (BGcolor == "dgreen") color = 16 * 2;
	else if (BGcolor == "dcyan") color = 16 * 3;
	else if (BGcolor == "cred") color = 16 * 4;
	else if (BGcolor == "dmagenta")color = 16 * 5;
	else if (BGcolor == "dyellow")color = 16 * 6;
	else if (BGcolor == "gray")color = 16 * 7;
	else if (BGcolor == "dgray")color = 16 * 8;
	else if (BGcolor == "blue")color = 16 * 9;
	else if (BGcolor == "green")color = 16 * 10;
	else if (BGcolor == "cyan")color = 16 * 11;
	else if (BGcolor == "red")color = 16 * 12;
	else if (BGcolor == "magenta")color = 16 * 13;
	else if (BGcolor == "yellow")color = 16 * 14;
	else if (BGcolor == "white")color = 16 * 15;
	else return -1;

	if (FGcolor == "black") color += 0;
	else if (FGcolor == "dblue") color += 1;
	else if (FGcolor == "dgreen")color += 2;
	else if (FGcolor == "dcyan")color += 3;
	else if (FGcolor == "cred")color += 4;
	else if (FGcolor == "dmagenta")color += 5;
	else if (FGcolor == "dyellow")color += 6;
	else if (FGcolor == "gray")color += 7;
	else if (FGcolor == "dgray")color += 8;
	else if (FGcolor == "blue")color += 9;
	else if (FGcolor == "green")color += 10;
	else if (FGcolor == "cyan")color += 11;
	else if (FGcolor == "red")color += 12;
	else if (FGcolor == "magenta")color += 13;
	else if (FGcolor == "yellow")color += 14;
	else if (FGcolor == "white")color += 15;
	else return -1;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);

	HANDLE ekran = GetStdHandle(STD_OUTPUT_HANDLE);
	CHAR tekst[150];
	DWORD znaki;
	BOOL sukces;
	va_list argumenty;
	int rezultat;
	va_start(argumenty, format);
	rezultat = vsprintf(tekst, format, argumenty);
	if (rezultat >= 0) {
		znaki = (DWORD)rezultat;
		setcursor(x, y);
		sukces = WriteConsole(ekran, tekst, znaki, NULL, NULL);
		if (!sukces) rezultat = EOF;
	}
	va_end(argumenty);

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (7));
	return rezultat;
}

void clear(void)
{
	HANDLE ekran = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO bufor;
	COORD poczatek = { 0,0 };
	DWORD znaki;
	GetConsoleScreenBufferInfo(ekran, &bufor);
	FillConsoleOutputCharacter(ekran, ' ', bufor.dwSize.X * bufor.dwSize.Y, poczatek, &znaki);
	SetConsoleCursorPosition(ekran, poczatek);
}

void fill(const char* BGcolor)
{
	int color;
	if (BGcolor == "black") color = 0;
	else if (BGcolor == "dblue") color = 16 * 1;
	else if (BGcolor == "dgreen") color = 16 * 2;
	else if (BGcolor == "dcyan") color = 16 * 3;
	else if (BGcolor == "dred") color = 16 * 4;
	else if (BGcolor == "dmagenta")color = 16 * 5;
	else if (BGcolor == "dyellow")color = 16 * 6;
	else if (BGcolor == "gray")color = 16 * 7;
	else if (BGcolor == "dgray")color = 16 * 8;
	else if (BGcolor == "blue")color = 16 * 9;
	else if (BGcolor == "green")color = 16 * 10;
	else if (BGcolor == "cyan")color = 16 * 11;
	else if (BGcolor == "red")color = 16 * 12;
	else if (BGcolor == "magenta")color = 16 * 13;
	else if (BGcolor == "yellow")color = 16 * 14;
	else if (BGcolor == "white")color = 16 * 15;
	else return;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);

	setcursor(0, 0);
	for (int clk = 50; clk > 0; clk--) {
		printf("                                                                                                                                                                                                                                  ");
	}

	HANDLE ekran = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO bufor;
	COORD poczatek = { 0,0 };
	DWORD znaki;
	GetConsoleScreenBufferInfo(ekran, &bufor);
	FillConsoleOutputCharacter(ekran, ' ', bufor.dwSize.X * bufor.dwSize.Y, poczatek, &znaki);
	SetConsoleCursorPosition(ekran, poczatek);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (7));
}

#if defined(_MSC_VER) && (_MSC_VER < 1800)
static int vsscanf(const char* buffer, const char* format, va_list argPtr)
{
	void* a[10];
	int i;
	for (i = 0; i < sizeof(a) / sizeof(a[0]); i++)
		a[i] = va_arg(argPtr, void*);
	return sscanf(buffer, format, a[0], a[1], a[2], a[3], a[4], a[5], a[6], a[7], a[8], a[9]);
}
#endif