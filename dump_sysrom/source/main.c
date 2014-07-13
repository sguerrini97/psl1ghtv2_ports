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

#include <stdio.h>
#include <unistd.h>

#include <net/net.h>

#include <lv2_syscall.h>
#include <udp_printf.h>

#define DUMP_OFFSET					0x2401fc00000ull
#define DUMP_SIZE						0x40000ull

#define DUMP_FILENAME				"sysrom.bin"

static const char *dump_path[] = {
	"/dev_usb000/" DUMP_FILENAME,
	"/dev_usb001/" DUMP_FILENAME,
	"/dev_usb002/" DUMP_FILENAME,
	"/dev_usb003/" DUMP_FILENAME,
	"/dev_usb004/" DUMP_FILENAME,
	"/dev_usb005/" DUMP_FILENAME,
	"/dev_usb006/" DUMP_FILENAME,
	"/dev_usb007/" DUMP_FILENAME,
};

/*
 * open_dump
 */
static FILE *open_dump(void)
{
#define N(a)	(sizeof(a) / sizeof(a[0]))

	FILE *fp;
	int i;

	fp = NULL;

	for (i = 0; i < N(dump_path); i++) {
		PRINTF("%s:%d: trying path '%s'\n", __func__, __LINE__, dump_path[i]);

		fp = fopen(dump_path[i], "w");
		if (fp)
			break;
	}

	if (fp)
		PRINTF("%s:%d: path '%s'\n", __func__, __LINE__, dump_path[i]);
	else
		PRINTF("%s:%d: file could not be opened\n", __func__, __LINE__);

	return fp;

#undef N
}

/*
 * main
 */
int main(int argc, char **argv)
{
	FILE *fp;
	uint64_t off, val;
	int result;

	netInitialize();

	udp_printf_init();

	PRINTF("%s:%d: start\n", __func__, __LINE__);

	fp = open_dump();
	if (!fp)
		goto done;

	for (off = DUMP_OFFSET; off < DUMP_OFFSET + DUMP_SIZE; off += sizeof(uint64_t)) {
		val = lv2_lv1_peek(off);

		result = fwrite(&val, 1, sizeof(val), fp);
		if (result != sizeof(val)) {
			PRINTF("%s:%d: fwrite failed (0x%08x)\n", __func__, __LINE__, result);
			goto done;
		}
	}

	fclose(fp);

	PRINTF("%s:%d: end\n", __func__, __LINE__);

	lv2_sm_ring_buzzer(0x1004, 0xa, 0x1b6);

done:

	if (fp)
		fclose(fp);

	udp_printf_deinit();

	netDeinitialize();

	return 0;
}
