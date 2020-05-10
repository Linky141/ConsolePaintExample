#ifndef _XYIO_
#define _XYIO_

#ifdef __cplusplus
extern "C" {
#endif

#if defined(_MSC_VER) && (_MSC_VER < 1800)
	static int vsscanf(const char* s, const char* fmt, va_list ap); /* brak implementacji przed VC++ 12 (VS 2013) */
#endif

	void setcursor(int x, int y);
	void getcursor(int* x, int* y);
	void getrange(int* maxx, int* maxy);
	void getscreen(int* xorg, int* yorg, int* xend, int* yend);
	int xyscanf(int x, int y, const char* format, ...);
	int xyprintf(int x, int y, const char* format, ...);
	int xycscanf(int x, int y, const char* BGcolor, const char* FGcolor, const char* format, ...);
	int xycprintf(int x, int y, const char* BGcolor, const char* FGcolor, const char* format, ...);
	void clear(void);
	void fill(const char* BGcolor);

#ifdef __cplusplus
}
#endif

#endif
