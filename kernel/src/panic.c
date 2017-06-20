#include <console.h>
#include <string.h>

/* Private variables */
static unsigned char buf[1024];

/* Global function implementations */
void panic(const unsigned char *fmt, ...)
{
	va_list args;
	va_start(args, fmt);

	int bgc_org = con_get_color_bg();
	int fgc_org = con_get_color_fg();

	con_set_color_bg(CON_COLOR_LIGHTRED);
	con_set_color_fg(CON_COLOR_WHITE);

	con_write_ln(vstr_fmt(buf, fmt, args));

	con_set_color_bg(bgc_org);
	con_set_color_fg(fgc_org);

	va_end(args);
}