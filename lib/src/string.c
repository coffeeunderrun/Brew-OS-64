#include <string.h>

/* Private variables */
static const char digits[] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f' };
static const char *units[] = { " B", "KB", "MB", "GB", "TB", "PB", "EB" };

/* Global function implementations */
void *mem_set(void *addr, char c, size_t n)
{
	unsigned char *p = (unsigned char *) addr;

	for (; n > 0; *p++ = c, n--);

	return addr;
}

void *mem_cpy(void *dst, const void *src, size_t n)
{
	unsigned char *d = (unsigned char *) dst;
	const unsigned char *s = (const unsigned char *) src;

	if (s > d)
		for (; n > 0; *d++ = *s++, n--);
	else if (s < d)
		for (d += n - 1, s += n - 1; n > 0; *d-- = *s--, n--);

	return dst;
}

unsigned int str_len(const char *s)
{
	const char *p = s;

	for (; *p; p++);

	return p - s;
}

char *str_cpy(char *dst, const char *src)
{
	char *d = dst;
	const char *s = src;

	for (; *s; *d++ = *s++);

	*d = '\0';

	return dst;
}

char *str_cpy_n(char *dst, const char *src, size_t n)
{
	char *d = dst;
	const char *s = src;

	for (; *s && n > 0; *d++ = *s++, n--);

	*d = '\0';

	return dst;
}

char *str_rev(char *s)
{
	char *p1 = s;
	char *p2 = s + str_len(s) - 1;

	for (; p1 && p2 > p1; p1++, p2--)
	{
		*p1 ^= *p2;
		*p2 ^= *p1;
		*p1 ^= *p2;
	}

	return s;
}

char *str_cat(char *s1, const char *s2)
{
	char *p1 = s1 + str_len(s1);
	const char *p2 = s2;

	for (; *p2; *p1++ = *p2++);

	*p1 = '\0';

	return s1;
}

char *str_pad(char *s, char c, int n)
{
	char *p = s;
	unsigned int len = str_len(p);

	if (n < 0)
	{
		for (n *= -1, p += len; n > len; *p++ = c, n--);
		*p = '\0';
	}
	else if (n > len)
	{
		mem_cpy(p + n - len, p, len);
		mem_set(p, c, n - len);
		*(p + n) = '\0';
	}

	return s;
}

unsigned int str_cmp(const char *s1, const char *s2)
{
	const char *p1 = s1;
	const char *p2 = s2;

	for (; *p1 == *p2; p1++, p2++)
	{
		if (!*p1)
			return 0;
	}

	return p1 - s1 + 1;
}

unsigned int str_cmp_i(const char *s1, const char *s2)
{
	const char *p1 = s1;
	const char *p2 = s2;

	for (; TO_LOWER(*p1) == TO_LOWER(*p2); p1++, p2++)
	{
		if (!*p1)
			return 0;
	}

	return p1 - s1 + 1;
}

unsigned int str_cmp_n(const char *s1, const char *s2, size_t n)
{
	const char *p1 = s1;
	const char *p2 = s2;

	for (; *p1 == *p2 && n > 0; p1++, p2++, n--)
	{
		if (!*p1)
			return 0;
	}

	return p1 - s1 + 1;
}

unsigned int str_chr(const char *s, char c)
{
	const char *p = s;

	for (; *p; p++)
	{
		if (*p == c)
			return p - s + 1;
	}

	return 0;
}

unsigned int str_chr_r(const char *s, char c)
{
	const char *p = s + str_len(s);

	for (; p >= s; p--)
	{
		if (*p == c)
			return p - s + 1;
	}

	return 0;
}

char *str_upper(char *s)
{
	char *p = s;

	for (; *p; *p = TO_UPPER(*p), p++);

	return s;
}

char *str_lower(char *s)
{
	char *p = s;

	for (; *p; *p = TO_LOWER(*p), p++);

	return s;
}

int atoi(const char *s)
{
	int sign = 1;
	int result = 0;
	const char *p = s;

	if (s)
	{
		if (*p == '-')
		{
			sign = -1;
			p++;
		}

		for (; *p; p++)
		{
			if (IS_NUM(*p))
				result = (result * 10) + (*p - '0');
			else
				return 0;
		}
	}

	return result * sign;
}

char *itoa(char *buf, int i, int base)
{
	if (buf && base <= 16)
	{
		int sign = 1;
		char *p = buf;

		if (i < 0)
			i *= (sign = -1);

		if (i > 0)
		{
			for (; i != 0; *p++ = digits[i % base], i /= base);

			if (sign < 0)
				*p++ = '-';
		}
		else
		{
			*p++ = '0';
		}

		*p = '\0';

		buf = str_rev(buf);
	}

	return buf;
}

char *ltoa(char *buf, long long i, int base)
{
	if (buf && base <= 16)
	{
		long long sign = 1;
		char *p = buf;

		if (i < 0)
			i *= (sign = -1);

		if (i > 0)
		{
			for (; i != 0; *p++ = digits[i % base], i /= base);

			if (sign < 0)
				*p++ = '-';
		}
		else
		{
			*p++ = '0';
		}

		*p = '\0';

		buf = str_rev(buf);
	}

	return buf;
}

char *uitoa(char *buf, unsigned int i, int base)
{
	if (buf && base <= 16)
	{
		char *p = buf;

		if (i > 0)
			for (; i != 0; *p++ = digits[i % base], i /= base);
		else
			*p++ = '0';

		*p = '\0';

		buf = str_rev(buf);
	}

	return buf;
}

char *ultoa(char *buf, unsigned long long i, int base)
{
	if (buf && base <= 16)
	{
		char *p = buf;

		if (i > 0)
			for (; i != 0; *p++ = digits[i % base], i /= base);
		else
			*p++ = '0';

		*p = '\0';

		buf = str_rev(buf);
	}

	return buf;
}

char *str_fmt(char *buf, const char *fmt, ...)
{
	va_list args;
	va_start(args, fmt);

	return vstr_fmt(buf, fmt, args);

	va_end(args);
}

char *vstr_fmt(char *buf, const char *fmt, va_list args)
{
	if (buf && fmt)
	{
		bool mod = false;
		bool mod_long = false;
		char *pb = buf;
		const char *pf = fmt;

		int pad_sign = 1;
		int pad_len = 0;
		char pad_ch = 0;

		for (; *pf; pf++)
		{
			if (mod)
			{
				if (*pf == '*')
				{
					pf++;
					pad_ch = *pf++;

					if (*pf == '-')
					{
						pad_sign = -1;
						pf++;
					}

					while (IS_NUM(*pf))
						pad_len = (pad_len * 10) + (*pf++ - '0');

					pad_len *= pad_sign;
				}

				if (*pf == 'l' || *pf == 'L')
				{
					mod_long = true;
					pf++;
				}

				switch (*pf)
				{
				case 'b':					// binary
					if (mod_long)
						pb = ultoa(pb, va_arg(args, unsigned long long), 2);
					else
						pb = uitoa(pb, va_arg(args, unsigned int), 2);

					pb = str_pad(pb, pad_ch, pad_len);
					pb += str_len(pb);
					break;
				case 'd':					// decimal
					if (mod_long)
						pb = ltoa(pb, va_arg(args, long long), 10);
					else
						pb = itoa(pb, va_arg(args, int), 10);

					pb = str_pad(pb, pad_ch, pad_len);
					pb += str_len(pb);
					break;
				case 'u':					// unsigned
					if (mod_long)
						pb = ultoa(pb, va_arg(args, unsigned long long), 10);
					else
						pb = uitoa(pb, va_arg(args, unsigned int), 10);

					pb = str_pad(pb, pad_ch, pad_len);
					pb += str_len(pb);
					break;
				case 'x':					// lower case hex
					if (mod_long)
						pb = ultoa(pb, va_arg(args, unsigned long long), 16);
					else
						pb = uitoa(pb, va_arg(args, unsigned int), 16);

					pb = str_pad(pb, pad_ch, pad_len);
					pb += str_len(pb);
					break;
				case 'X':					// upper case hex
					if (mod_long)
						pb = str_upper(ultoa(pb, va_arg(args, unsigned long long), 16));
					else
						pb = str_upper(uitoa(pb, va_arg(args, unsigned int), 16));

					pb = str_pad(pb, pad_ch, pad_len);
					pb += str_len(pb);
					break;
				case 's':					// string
					pb = str_cpy(pb, va_arg(args, char *));
					pb = str_pad(pb, pad_ch, pad_len);
					pb += str_len(pb);
					break;
				case 'c':					// character
					*pb++ = va_arg(args, int);
					break;
				default:
					*pb++ = *pf;
					break;
				}

				mod = false;
				mod_long = false;
			}
			else if (*pf == '%')
			{
				mod = true;
			}
			else
			{
				*pb++ = *pf;
			}

			pad_sign = 1;
			pad_len = 0;
			pad_ch = 0;
		}

		*pb = '\0';
	}

	return buf;
}

char *unit_fmt(char *buf, unsigned long n, int l)
{
	unsigned int i = 0;

	for (; i < UNIT_MAX && n >= 1024 && l-- > 0; i++, n /= 1024);

	return str_fmt(buf, "%u %s", n, units[i]);
}
