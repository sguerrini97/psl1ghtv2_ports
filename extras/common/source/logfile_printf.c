
/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; version 2 of the License.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 */

#include <logfile_printf.h>

#include <stdio.h>
#include <stdarg.h>
#include <string.h>

static FILE *fp;

/*
 * logfile_printf_init
 */
int logfile_printf_init(const char *path) {
	fp = fopen(path, "a+");
	if (!fp)
		return -1;

	return 0;
}

/*
 * logfile_printf_deinit
 */
void logfile_printf_deinit(void) {
	if (fp)
		fclose(fp);
}

/*
 * logfile_printf
 */
int logfile_printf(const char *fmt, ...) {
	char buf[4096];
	va_list ap;
	int result;

	va_start(ap, fmt);

	vsnprintf(buf, sizeof(buf), fmt, ap);

	va_end(ap);

	result = fprintf(fp, "%s", buf);

	fflush(fp);

	return result;
}
