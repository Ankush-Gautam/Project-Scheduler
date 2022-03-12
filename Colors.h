#ifndef COLORS_H_INCLUDED
#define COLORS_H_INCLUDED
#include <windows.h>

HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
// text color from 0x1-0x9
// text background color from 0x10-0x90
/*             0 = Black       8 = Gray
 *             1 = Blue        9 = Light Blue
 *             2 = Green       A = Light Green
 *             3 = Aqua        B = Light Aqua
 *             4 = Red         C = Light Red
 *             5 = Purple      D = Light Purple
 *             6 = Yellow      E = Light Yellow
 *             7 = White       F = Bright White
 */
inline void black()
{
    SetConsoleTextAttribute(h,0x00 | 0xf8);
}
inline void darkblue()
{
    SetConsoleTextAttribute(h,0x01 | 0xf8);
}
inline void darkgreen()
{
    SetConsoleTextAttribute(h,0x02 | 0xf8);
}
inline void darkcyan()
{
    SetConsoleTextAttribute(h,0x03 | 0xf8);
}
inline void darkred()
{
    SetConsoleTextAttribute(h,0x04 | 0xf8);
}
inline void darkpurple()
{
    SetConsoleTextAttribute(h,0x05 | 0xf8);
}
inline void darkyellow()
{
    SetConsoleTextAttribute(h,0x06 | 0xf8);
}
inline void darkwhite()
{
    SetConsoleTextAttribute(h,0x07 | 0xf8);
}
inline void gray()
{
    SetConsoleTextAttribute(h,0x08 | 0xf8);
}
inline void blue()
{
    SetConsoleTextAttribute(h,0x09 | 0xf8);
}
inline void green()
{
    SetConsoleTextAttribute(h,0x0a | 0xf8);
}
inline void cyan()
{
    SetConsoleTextAttribute(h,0x0b | 0xf8);
}
inline void red()
{
    SetConsoleTextAttribute(h, 0x0c | 0xf8);
}
inline void purple()
{
    SetConsoleTextAttribute(h,0x0d | 0xf8);
}
inline void yellow()
{
    SetConsoleTextAttribute(h,0x0e | 0xf8);
}
inline void white()
{
    SetConsoleTextAttribute(h,0x0f | 0xf8);
}
#endif // COLORS_H_INCLUDED
