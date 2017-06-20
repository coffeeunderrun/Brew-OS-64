#ifndef __STRING_H__
#define __STRING_H__

#include <types.h>

#define IS_NUM(c)		(c >= '0' && c <= '9')
#define IS_LOWER(c)		(c >= 'a' && c <= 'z')
#define IS_UPPER(c)		(c >= 'A' && c <= 'Z')
#define IS_CHAR(c)		(IS_LOWER(c) || IS_UPPER(c))
#define TO_LOWER(c)		(IS_UPPER(c) ? c + 32 : c)
#define TO_UPPER(c)		(IS_LOWER(c) ? c - 32 : c)

#define UNIT_BYTE		0
#define UNIT_KILOBYTE	1
#define UNIT_MEGABYTE	2
#define UNIT_GIGABYTE	3
#define UNIT_TERABYTE	4
#define UNIT_PETABYTE	5
#define UNIT_EXABYTE	6
#define UNIT_MAX		7

/**
 * Set n bytes of memory to c starting at addr.
 * @param addr Start address in memory.
 * @param c Character to put in memory.
 * @param n Number of bytes to set.
 */
void *mem_set(void *addr, char c, size_t n);

/**
 * Copy n bytes of memory from src to dst.
 * @param dst Start address to be copied to.
 * @param src Start address to be copied from.
 * @param n Number of bytes to copy.
 */
void *mem_cpy(void *dst, const void *src, size_t n);

/**
 * Get the length of a string.
 * @param s Pointer to string.
 * @return Length of the string not including the null terminator.
 */
unsigned int str_len(const char *s);

/**
 * Copy string from src to dst.
 * @param dst Pointer to string to copy to.
 * @param src Pointer to string to copy from.
 * @return Pointer to dst.
 */
char *str_cpy(char *dst, const char *src);

/**
 * Copy n bytes of string from src to dst.
 * @param dst Pointer to string to copy to.
 * @param src Pointer to string to copy from.
 * @param n Number of bytes to copy.
 * @return Pointer to dst.
 */
char *str_cpy_n(char *dst, const char *src, size_t n);

/**
 * Reverse the order of bytes within a string.
 * @param s Pointer to string.
 * @return Pointer to s.
 */
char *str_rev(char *s);

/**
 * Appends s2 to the end of s1.
 * @param s1 Pointer to string. Must have enough allocated space for s1 + s2 + \0.
 * @param s2 Pointer to string to append to end of s1..
 * @return Pointer to s1.
 */
char *str_cat(char *s1, const char *s2);

/**
 * Sets width of string to n and fills the added space with c.
 * @param s Pointer to string. Must have enough allocated space for n + \0;
 * @param c Character to pad with.
 * @param n New width of string. (Pad left > 0, Pad right < 0)
 * @return Pointer to s.
 */
char *str_pad(char *s, char c, int n);

/**
 * Determines if two strings are equal.
 * @param s1 Pointer to string.
 * @param s2 Pointer to string.
 * @return 0 if strings are equal or first position where they are different.
 */
unsigned int str_cmp(const char *s1, const char *s2);

/**
 * Determines if two strings are equal, ignoring case.
 * @param s1 Pointer to string.
 * @param s2 Pointer to string.
 * @return 0 if strings are equal or first position where they are different.
 */
unsigned int str_cmp_i(const char *s1, const char *s2);

/**
 * Determines if two strings are equal for n number of bytes.
 * @param s1 Pointer to string.
 * @param s2 Pointer to string.
 * @param n Length of string (in bytes) to compare.
 * @return 0 if strings are equal or first position where they are different.
 */
unsigned int str_cmp_n(const char *s1, const char *s2, size_t n);

/**
 * Find first occurrence of character in string.
 * @param s Pointer to string.
 * @param c Character to find.
 * @return Position of first occurrence in string.
 */
unsigned int str_chr(const char *s, char c);

/**
 * Find last occurrence of character in string.
 * @param s Pointer to string.
 * @param c Character to find.
 * @return Position of last occurrence in string.
 */
unsigned int str_chr_r(const char *s, char c);

/**
 * Changes entire string to upper case.
 * @param s Pointer to string.
 * @return Pointer to s.
 */
char *str_upper(char *s);

/**
 * Changes entire string to lower case.
 * @param s Pointer to string.
 * @return Pointer to s.
 */
char *str_lower(char *s);

/**
 * Converts a numerical value in a string to an integer.
 * @param s Pointer to string.
 * @return 0 if failed or integer of converted number.
 */
int atoi(const char *s);

/**
 * Converts an integer to a string.
 * @param buf Pointer to resulting string.
 * @param i Integer to convert.
 * @param base 2 for binary, 8 for octal, 10 for decimal, 16 for hex
 * @return Pointer to buf.
 */
char *itoa(char *buf, int i, int base);

/**
 * Converts a long integer to a string.
 * @param buf Pointer to resulting string.
 * @param i Integer to convert.
 * @param base 2 for binary, 8 for octal, 10 for decimal, 16 for hex
 * @return Pointer to buf.
 */
char *ltoa(char *buf, long long i, int base);

/**
 * Converts an unsigned integer to a string.
 * @param buf Pointer to resulting string.
 * @param i Unsigned integer to convert.
 * @param base 2 for binary, 8 for octal, 10 for decimal, 16 for hex
 * @return Pointer to buf.
 */
char *uitoa(char *buf, unsigned int i, int base);

/**
 * Converts an unsigned long integer to a string.
 * @param buf Pointer to resulting string.
 * @param i Unsigned integer to convert.
 * @param base 2 for binary, 8 for octal, 10 for decimal, 16 for hex
 * @return Pointer to buf.
 */
char *ultoa(char *buf, unsigned long long i, int base);

/**
 * Return a formatted string. A variable list of parameters can be added
 * after fmt to be used in the formatted string.
 * @param buf Character array to be used for parsing the format.
 * @param fmt Format of the string.
 * @return Pointer to buf.
 */
char *str_fmt(char *buf, const char *fmt, ...);

/**
 * Return a formatted string.
 * @param buf Character array to be used for parsing the format.
 * @param fmt Format of the string. "[%[*<char>[-]<len>][l|L](b|d|u|x|X|s|c)]"
 * @param args Parameters to be used in the formatted string.
 * @return Pointer to buf.
 */
char *vstr_fmt(char *buf, const char *fmt, va_list args);

/**
 *
 */
char *unit_fmt(char *buf, unsigned long n, int l);

#endif // __STRING_H__
