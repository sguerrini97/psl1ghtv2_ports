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

#include <lv2_syscall.h>

/* VFLASH */

#define VFLASH_DEV_ID				0x100000000000001ull
#define VFLASH_SECTOR_SIZE			0x200ull
#define VFLASH_START_SECTOR			0x0ull
#define VFLASH_SECTOR_COUNT			0x2ull
#define VFLASH_FLAGS				0x6ull

/* NAND FLASH */

#define FLASH_DEV_ID				0x100000000000001ull
#define FLASH_SECTOR_SIZE			0x200ull
#define FLASH_START_SECTOR			0x7600ull
#define FLASH_SECTOR_COUNT			0x2ull
#define FLASH_FLAGS				0x6ull

#define DUMP_FILENAME				"flash_ptab.bin"

FILE * logfile;

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
 * is_vflash_on
 */
static int is_vflash_on(void)
{
	uint8_t flag;

	lv2_ss_get_cache_of_flash_ext_flag(&flag);

	return !(flag & 0x1);
}

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
		fprintf(logfile, "%s:%d: trying path '%s'\n", __func__, __LINE__, dump_path[i]);

		fp = fopen(dump_path[i], "w");
		if (fp)
			break;
	}

	if (fp)
		fprintf(logfile, "%s:%d: path '%s'\n", __func__, __LINE__, dump_path[i]);
	else
		fprintf(logfile, "%s:%d: file could not be opened\n", __func__, __LINE__);

	return fp;

#undef N
}

/*
 * dump_vflash_ptab
 */
int dump_vflash_ptab(void)
{
	uint32_t dev_handle;
	FILE *fp;
	int start_sector, sector_count;
	uint32_t unknown2;
	uint8_t buf[VFLASH_SECTOR_SIZE * VFLASH_SECTOR_COUNT];
	int result;

	dev_handle = 0;
	fp = NULL;

	result = lv2_storage_open(VFLASH_DEV_ID, &dev_handle);
	if (result) {
		fprintf(logfile, "%s:%d: lv2_storage_open failed (0x%08x)\n", __func__, __LINE__, result);
		goto done;
	}

	fp = open_dump();
	if (!fp)
		goto done;

	start_sector = VFLASH_START_SECTOR;
	sector_count = VFLASH_SECTOR_COUNT;

	fprintf(logfile, "%s:%d: reading data start_sector (0x%08x) sector_count (0x%08x)\n",
		__func__, __LINE__, start_sector, sector_count);

	result = lv2_storage_read(dev_handle, 0, start_sector, sector_count, buf, &unknown2, VFLASH_FLAGS);
	if (result) {
		fprintf(logfile, "%s:%d: lv2_storage_read failed (0x%08x)\n", __func__, __LINE__, result);
		goto done;
	}

	usleep(10000);

	fprintf(logfile, "%s:%d: dumping data start_sector (0x%08x) sector_count (0x%08x)\n",
		__func__, __LINE__, start_sector, sector_count);

	result = fwrite(buf, 1, VFLASH_SECTOR_COUNT * VFLASH_SECTOR_SIZE, fp);
	if (result < 0) {
		fprintf(logfile, "%s:%d: fwrite failed (0x%08x)\n", __func__, __LINE__, result);
		goto done;
	}

	fclose(fp);

	return 0;

done:

	if (fp)
		fclose(fp);

	result = lv2_storage_close(dev_handle);
	if (result)
		fprintf(logfile, "%s:%d: lv2_storage_close failed (0x%08x)\n", __func__, __LINE__, result);

	return result;
}

/*
 * dump_flash_ptab
 */
int dump_flash_ptab(void)
{
	uint32_t dev_handle;
	FILE *fp;
	int start_sector, sector_count;
	uint32_t unknown2;
	uint8_t buf[FLASH_SECTOR_SIZE * FLASH_SECTOR_COUNT];
	int result;

	dev_handle = 0;
	fp = NULL;

	result = lv2_storage_open(FLASH_DEV_ID, &dev_handle);
	if (result) {
		fprintf(logfile, "%s:%d: lv2_storage_open failed (0x%08x)\n", __func__, __LINE__, result);
		goto done;
	}

	fp = open_dump();
	if (!fp)
		goto done;

	start_sector = FLASH_START_SECTOR;
	sector_count = FLASH_SECTOR_COUNT;

	fprintf(logfile, "%s:%d: reading data start_sector (0x%08x) sector_count (0x%08x)\n",
		__func__, __LINE__, start_sector, sector_count);

	result = lv2_storage_read(dev_handle, 0, start_sector, sector_count, buf, &unknown2, FLASH_FLAGS);
	if (result) {
		fprintf(logfile, "%s:%d: lv2_storage_read failed (0x%08x)\n", __func__, __LINE__, result);
		goto done;
	}

	usleep(10000);

	fprintf(logfile, "%s:%d: dumping data start_sector (0x%08x) sector_count (0x%08x)\n",
		__func__, __LINE__, start_sector, sector_count);

	result = fwrite(buf, 1, FLASH_SECTOR_COUNT * FLASH_SECTOR_SIZE, fp);
	if (result < 0) {
		fprintf(logfile, "%s:%d: fwrite failed (0x%08x)\n", __func__, __LINE__, result);
		goto done;
	}

	fclose(fp);

	return 0;

done:

	if (fp)
		fclose(fp);

	result = lv2_storage_close(dev_handle);
	if (result)
		fprintf(logfile, "%s:%d: lv2_storage_close failed (0x%08x)\n", __func__, __LINE__, result);

	return result;
}

/*
 * main
 */
int main(int argc, char **argv)
{
	int vflash_on, result;

	logfile = fopen("/dev_usb000/dump_flash_ptab.log","w");
	
	if(!logfile) return -1;

	fprintf(logfile, "%s:%d: start\n", __func__, __LINE__);

	vflash_on = is_vflash_on();

	fprintf(logfile, "%s:%d: vflash %s\n", __func__, __LINE__, vflash_on ? "on" : "off");

	if (vflash_on) {
		result = dump_vflash_ptab();
		if (result) {
			fprintf(logfile, "%s:%d: dump_vflash_ptab failed (0x%08x)\n", __func__, __LINE__, result);
			goto done;
		}
	} else {
		result = dump_flash_ptab();
		if (result) {
			fprintf(logfile, "%s:%d: dump_flash_ptab failed (0x%08x)\n", __func__, __LINE__, result);
			goto done;
		}
	}

	fprintf(logfile, "%s:%d: end\n", __func__, __LINE__);

	lv2_sm_ring_buzzer(0x1004, 0xa, 0x1b6);
	fclose(logfile);

done:

	return 0;
}
