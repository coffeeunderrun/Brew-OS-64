#include <console.h>
#include <cpu.h>
#include <kernel.h>
#include <string.h>

#define COLS					80
#define ROWS					25
#define VIDMEM_SIZE				(COLS * ROWS * 2)
#define CURSOR_POS(x, y)		(COLS * y + x)
#define VIDMEM_POS(x, y)		(CURSOR_POS(x, y) * 2)
#define COLOR(fg, bg)			(((bg & 0x0F) << 4) | (fg & 0x0F))

/* Private variables */
static volatile unsigned char *vid_mem;
static int color_fg, color_bg, cursor_x, cursor_y;
static unsigned char buf[1024];

/* Private function headers */
static void update_cursor();
static void scroll_screen();
static int parse_color(unsigned char c);

/* Global function implementations */
void init_con()
{
	// Make sure we're in control and not data mode
	in_port(VGA_STATUS_PORT);

	// Select the attribute control register
	out_port(VGA_ATTR_ADDR_PORT, VGA_ATTR_PAS | VGA_ATTR_CONTROL_IDX);

	// Get the current attribute control settings
	uint8_t attr = in_port(VGA_ATTR_DATA_PORT);

	// Disable blinking
	out_port(VGA_ATTR_ADDR_PORT, attr & ~VGA_ATTR_BLINK);

	vid_mem = (volatile unsigned char *) (0xB8000 + KERNEL_VMA);

	con_set_color_fg(CON_COLOR_WHITE);
	con_set_color_bg(CON_COLOR_LIGHTBLUE);
	con_clear();
}

void con_clear()
{
	cursor_x = 0;
	cursor_y = 0;
	update_cursor();

	for (volatile unsigned char *p = vid_mem; p < vid_mem + VIDMEM_SIZE;)
	{
		*p++ = 0;
		*p++ = COLOR(color_fg, color_bg);
	}
}

void con_set_cursor_x(int x)
{
	cursor_x = x % COLS;
	update_cursor();
}

void con_set_cursor_y(int y)
{
	cursor_y = y % ROWS;
	update_cursor();
}

int con_get_cursor_x()
{
	return cursor_x;
}

int con_get_cursor_y()
{
	return cursor_y;
}

void con_set_color_fg(int c)
{
	color_fg = c % 16;
}

void con_set_color_bg(int c)
{
	color_bg = c % 16;
}

int con_get_color_fg()
{
	return color_fg;
}

int con_get_color_bg()
{
	return color_bg;
}

void con_write_ch(unsigned char c)
{
	if (c == 0x08 && cursor_x > 0)			// backspace
	{
		cursor_x--;
	}
	else if (c == 0x09)						// tab
	{
		cursor_x += 8;
	}
	else if (c == '\r')						// carriage return
	{
		cursor_x = 0;
	}
	else if (c == '\n')						// line feed
	{
		cursor_x = 0;
		cursor_y++;
	}
	else if (c >= ' ')						// printable characters
	{
		unsigned int pos = VIDMEM_POS(cursor_x, cursor_y);
		vid_mem[pos] = c;
		vid_mem[pos + 1] = COLOR(color_fg, color_bg);
		cursor_x++;
	}

	// Wrap if we hit the edge of the screen
	if (cursor_x >= COLS)
	{
		cursor_x = 0;
		cursor_y++;
	}

	scroll_screen();
	update_cursor();
}

void con_write(const unsigned char *s)
{
	const unsigned char *p = s;

	for (; *p; p++)
		con_write_ch(*p);
}

void con_write_ln(const unsigned char *s)
{
	con_write(s);
	con_write_ch('\n');
}

void con_write_fmt(const unsigned char *fmt, ...)
{
	va_list args;
	va_start(args, fmt);
	vstr_fmt(buf, fmt, args);
	va_end(args);

	bool fg = false;
	bool bg = false;

	uint8_t bgc_org = con_get_color_bg();
	uint8_t fgc_org = con_get_color_fg();

	uint8_t bgc = bgc_org;
	uint8_t fgc = fgc_org;

	for (unsigned char *pf = buf; *pf; pf++)
	{
		if (bg)
		{
			bg = false;
			int c = parse_color(*pf);

			if (c < 0 || c > 15)
			{
				switch (*pf)
				{
				case 'x':					// Reset
				case 'X':
					bgc = bgc_org;
					break;
				default:
					con_write_ch(*pf);
					break;
				}
			}
			else
			{
				bgc = c;
			}

			con_set_color_bg(bgc);
		}
		else if (fg)
		{
			fg = false;
			int c = parse_color(*pf);

			if (c < 0 || c > 15)
			{
				switch (*pf)
				{
				case 'x':					// Reset
				case 'X':
					fgc = fgc_org;
					break;
				default:
					con_write_ch(*pf);
					break;
				}
			}
			else
			{
				fgc = c;
			}

			con_set_color_fg(fgc);
		}
		else if (*pf == '^')
		{
			bg = true;
		}
		else if (*pf == '&')
		{
			fg = true;
		}
		else
		{
			con_write_ch(*pf);
		}
	}
}

/* Private function implementations */
static void update_cursor()
{
	unsigned int pos = CURSOR_POS(cursor_x, cursor_y);

	out_port(VGA_CRTC_ADDR_PORT, VGA_CURSOR_POS_LO_IDX);
	out_port(VGA_CRTC_DATA_PORT, pos & 0xFF);
	out_port(VGA_CRTC_ADDR_PORT, VGA_CURSOR_POS_HI_IDX);
	out_port(VGA_CRTC_DATA_PORT, (pos >> 8) & 0xFF);
}

static void scroll_screen()
{
	if (cursor_y >= ROWS)
	{
		mem_cpy(
		    (unsigned char *) vid_mem,
		    (unsigned char *) (vid_mem + COLS * 2),
		    VIDMEM_SIZE - COLS * 2);

		for (volatile unsigned char *p = vid_mem + VIDMEM_SIZE - COLS * 2;
		        p < vid_mem + VIDMEM_SIZE;)
		{
			*p++ = 0;
			*p++ = COLOR(color_fg, color_bg);
		}

		cursor_y = ROWS - 1;
	}
}

static int parse_color(unsigned char c)
{
	switch (c)
	{
	case 'b':
		return CON_COLOR_BLUE;				// Blue
	case 'B':
		return CON_COLOR_LIGHTBLUE;			// Light blue
	case 'c':
		return CON_COLOR_CYAN;				// Cyan
	case 'C':
		return CON_COLOR_LIGHTCYAN;			// Light cyan
	case 'd':
		return CON_COLOR_BLACK;				// Black
	case 'D':
		return CON_COLOR_DARKGRAY;			// Dark gray
	case 'g':
		return CON_COLOR_GREEN;				// Green
	case 'G':
		return CON_COLOR_LIGHTGREEN;		// Light green
	case 'm':
		return CON_COLOR_MAGENTA;			// Magenta
	case 'M':
		return CON_COLOR_LIGHTMAGENTA;		// Light magenta
	case 'r':
		return CON_COLOR_RED;				// Red
	case 'R':
		return CON_COLOR_LIGHTRED;			// Light red
	case 'w':
		return CON_COLOR_WHITE;				// White
	case 'W':
		return CON_COLOR_GRAY;				// Gray
	case 'y':
		return CON_COLOR_YELLOW;			// Yellow
	case 'Y':
		return CON_COLOR_BROWN;				// Brown
	default:
		return -1;
	}
}
