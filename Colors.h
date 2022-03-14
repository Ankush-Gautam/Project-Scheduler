#ifndef COLORS_H_INCLUDED
#define COLORS_H_INCLUDED
#include <windows.h>

HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
// text color from 0x1-0x9
// text background color from 0x10-0x90
/* Name            FG  BG
 * Black           30  40
 * Red             31  41
 * Green           32  42
 * Yellow          33  43
 * Blue            34  44
 * Magenta         35  45
 * Cyan            36  46
 * White           37  47
 * Bright Black    90  100
 * Bright Red      91  101
 * Bright Green    92  102
 * Bright Yellow   93  103
 * Bright Blue     94  104
 * Bright Magenta  95  105
 * Bright Cyan     96  106
 * Bright White    97  107
 */

inline void black()
{
    SetConsoleTextAttribute(h, 240);
}
inline void blue()
{
    SetConsoleTextAttribute(h, 241);
}
inline void green()
{
    SetConsoleTextAttribute(h, 242);
}
inline void cyan()
{
    SetConsoleTextAttribute(h, 243);
}
inline void red()
{
    SetConsoleTextAttribute(h, 244);
}
inline void purple()
{
    SetConsoleTextAttribute(h, 245);
}
inline void yellow()
{
    SetConsoleTextAttribute(h, 246);
}
inline void white()
{
    SetConsoleTextAttribute(h, 247);
}
// lighter shaded
inline void gray()
{
    SetConsoleTextAttribute(h, 248);
}
inline void lightblue()
{
    SetConsoleTextAttribute(h, 249);
}
inline void lightgreen()
{
    SetConsoleTextAttribute(h, 250);
}
inline void lightcyan()
{
    SetConsoleTextAttribute(h, 251);
}
inline void lightred()
{
    SetConsoleTextAttribute(h, 252);
}
inline void lightpurple()
{
    SetConsoleTextAttribute(h, 253);
}
inline void lightyellow()
{
    SetConsoleTextAttribute(h, 254);
}
inline void lightwhite()
{
    SetConsoleTextAttribute(h, 255);
}
#endif // COLORS_H_INCLUDED
