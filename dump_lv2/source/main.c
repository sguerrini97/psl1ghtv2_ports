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

#define DUMP_FILENAME				"lv2.bin"

static const char *dump_path[] = {
	"/dev_usb000/",
	"/dev_usb001/",
	"/dev_usb002/",
	"/dev_usb003/",
	"/dev_usb004/",
	"/dev_usb005/",
	"/dev_usb006/",
	"/dev_usb007/",
};

static struct {
	uint64_t offset;
	uint64_t size;
} segments[] = {
	{ 0x8000000000000000ull, 0x800000ull },
	{ 0x8000000300000000ull, 0x80000ull }
};

/* open_dump */
static FILE *open_dump(const char *filename)
{
#define N(a)	(sizeof(a) / sizeof(a[0]))

	FILE *fp;
	char path[512];
	int i;

	fp = NULL;

	for (i = 0; i < N(dump_path); i++) {
		snprintf(path, sizeof(path), "%s/%s", dump_path[i], filename);

		PRINTF("%s:%d: trying path '%s'\n", __func__, __LINE__, path);

		fp = fopen(path, "w");
		if (fp)
			break;
	}

	if (fp)
		PRINTF("%s:%d: path '%s'\n", __func__, __LINE__, path);
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
#define N(a)	(sizeof(a) / sizeof(a[0]))

	FILE *fp;
	char filename[512];
	uint64_t off, val;
	int i, result;

	netInitialize();

	udp_printf_init();

	PRINTF("%s:%d: start\n", __func__, __LINE__);

	for (i = 0; i < N(segments); i++) {
		PRINTF("%s:%d: dumping segment %d offset 0x%016lx size 0x%016lx\n", __func__, __LINE__, i, segments[i].offset, segments[i].size);

		snprintf(filename, sizeof(filename), "%s.%d", DUMP_FILENAME, i);

		fp = open_dump(filename);
		if (!fp)
			goto done;

		for (off = segments[i].offset; off < segments[i].offset + segments[i].size; off += sizeof(uint64_t)) {
			val = lv2_peek(off);

			result = fwrite(&val, 1, sizeof(val), fp);
			if (result != sizeof(val)) {
				PRINTF("%s:%d: fwrite failed (0x%08x)\n", __func__, __LINE__, result);
				goto done;
			}
		}

		fclose(fp);
	}

	PRINTF("%s:%d: end\n", __func__, __LINE__);

	lv2_sm_ring_buzzer(0x1004, 0xa, 0x1b6);

done:

	if (fp)
		fclose(fp);

	udp_printf_deinit();

	netDeinitialize();

	return 0;

#undef N
}
