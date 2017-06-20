#ifndef __PANIC_H__
#define __PANIC_H__

/**
 * Write a formatted string to the screen at cursor position. A variable list
 * of parameters can be added after fmt to be used in the formatted string.
 * @param fmt Format of the string to be written.
 * "[%[*<char>[-]<len>][l|L](b|d|u|x|X|s|c)]"
 */
void panic(const unsigned char *fmt, ...);

#endif // __PANIC_H__
