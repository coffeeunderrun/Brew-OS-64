#ifndef __CONSOLE_H__
#define __CONSOLE_H__

#include "types.h"

#define CON_COLOR_BLACK			0x00
#define CON_COLOR_BLUE			0x01
#define CON_COLOR_GREEN			0x02
#define CON_COLOR_CYAN			0x03
#define CON_COLOR_RED			0x04
#define CON_COLOR_MAGENTA		0x05
#define CON_COLOR_BROWN			0x06
#define CON_COLOR_GRAY			0x07
#define CON_COLOR_DARKGRAY		0x08
#define CON_COLOR_LIGHTBLUE		0x09
#define CON_COLOR_LIGHTGREEN	0x0A
#define CON_COLOR_LIGHTCYAN		0x0B
#define CON_COLOR_LIGHTRED		0x0C
#define CON_COLOR_LIGHTMAGENTA	0x0D
#define CON_COLOR_YELLOW		0x0E
#define CON_COLOR_WHITE			0x0F

/**
 * Initialize the text console.
 */
void init_con();

/**
 * Clear the screen.
 */
void con_clear();

/**
 * Set the X position of the screen cursor.
 * @param x Zero-indexed screen x-coordinate. (0-79)
 */
void con_set_cursor_x(int x);

/**
 * Set the Y position of the screen cursor.
 * @param y Zero-indexed screen y-coordinate. (0-24)
 */
void con_set_cursor_y(int y);

/**
 * Get the X position of the screen cursor.
 * @return Zero-indexed screen x-coordinate. (0-79)
 */
int con_get_cursor_x();

/**
 * Get the Y position of the screen cursor.
 * @return Zero-indexed screen y-coordinate. (0-24)
 */
int con_get_cursor_y();

/**
 * Set the foreground color for any screen content written after this change.
 * @param c Zero-indexed foreground color. (0-15)
 */
void con_set_color_fg(int c);

/**
 * Set the background color for any screen content written after this change.
 * @param c Zero-indexed background color. (0-15)
 */
void con_set_color_bg(int c);

/**
 * Get the current foreground color.
 * @return Zero-indexed foreground color. (0-15)
 */
int con_get_color_fg();

/**
 * Get the current foreground color.
 * @return Zero-indexed background color. (0-15)
 */
int con_get_color_bg();

/**
 * Write a character to the screen at cursor position.
 * @param c Character to write.
 */
void con_write_ch(unsigned char c);

/**
 * Write a string to the screen at cursor position.
 * @param s Array of characters to write.
 */
void con_write(const unsigned char *s);

/**
 * Write a string to the screen at cursor position with a newline after.
 * @param s Array of characters to write.
 */
void con_write_ln(const unsigned char *s);

/**
 * Write a formatted string to the screen at cursor position. A variable list
 * of parameters can be added after fmt to be used in the formatted string.
 * @param fmt Format of the string to be written.
 * "[%[*<char>[-]<len>][l|L](b|d|u|x|X|s|c)][(^|&)(b|B|c|C|d|D|g|G|m|M|r|R|w|W|y|Y|x|X)]"
 */
void con_write_fmt(const unsigned char *fmt, ...);

#endif // __CONSOLE_H__
