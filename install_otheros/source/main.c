
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
#include <string.h>
#include <unistd.h>

//#include <psl1ght/lv2/net.h>

#include <flash_os_area.h>
#include <lv2_syscall.h>
//#include <udp_printf.h>

#define VFLASH5_DEV_ID				0x100000500000001ull
#define VFLASH5_SECTOR_SIZE			0x200ull
#define VFLASH5_SECTORS				0xc000ull
#define VFLASH5_HEADER_SECTORS			0x2ull
#define VFLASH5_OS_DB_AREA_SECTORS		0x2ull

#define PETITBOOT_FILENAME			"dtbImage.ps3.bin"

static const char *petitboot_path[] = {
	"/dev_usb000/" PETITBOOT_FILENAME,
	"/dev_usb001/" PETITBOOT_FILENAME,
	"/dev_usb002/" PETITBOOT_FILENAME,
	"/dev_usb003/" PETITBOOT_FILENAME,
	"/dev_usb004/" PETITBOOT_FILENAME,
	"/dev_usb005/" PETITBOOT_FILENAME,
	"/dev_usb006/" PETITBOOT_FILENAME,
	"/dev_usb007/" PETITBOOT_FILENAME,
};

/*
 * open_petitboot
 */
static FILE *open_petitboot(void)
{
#define N(a)	(sizeof(a) / sizeof(a[0]))

	FILE *fp;
	int i;

	fp = NULL;

	for (i = 0; i < N(petitboot_path); i++) {
		printf("%s:%d: trying path '%s'\n", __func__, __LINE__, petitboot_path[i]);

		fp = fopen(petitboot_path[i], "r");
		if (fp)
			break;
	}

	if (fp)
		printf("%s:%d: path '%s'\n", __func__, __LINE__, petitboot_path[i]);
	else
		printf("%s:%d: file not found\n", __func__, __LINE__);

	return fp;

#undef N
}

/*
 * main
 */
int main(int argc, char **argv)
{
#define MIN(a, b)	((a) <= (b) ? (a) : (b))

	uint32_t dev_handle;
	FILE *fp;
	int file_size, file_sectors, start_sector, sector_count;
	struct storage_device_info info;
	uint8_t buf[VFLASH5_SECTOR_SIZE * 16];
	struct os_area_header *hdr;
	struct os_area_params *params;
	struct os_area_db *db;
	uint32_t unknown2;
	int result;

	//netInitialize();

	//udp_printf_init();

	printf("%s:%d: start\n", __func__, __LINE__);

	dev_handle = 0;
	fp = NULL;

	fp = open_petitboot();
	if (!fp)
		goto done;

	result = fseek(fp, 0, SEEK_END);
	if (result) {
		printf("%s:%d: fseek failed (0x%08x)\n", __func__, __LINE__, result);
		goto done;
	}

	file_size = ftell(fp);
	file_sectors = (file_size + VFLASH5_SECTOR_SIZE - 1) / VFLASH5_SECTOR_SIZE;

	if (file_sectors > (VFLASH5_SECTORS - VFLASH5_HEADER_SECTORS - VFLASH5_OS_DB_AREA_SECTORS)) {
		printf("%s:%d: file too large\n", __func__, __LINE__);
		goto done;
	}

	printf("%s:%d: file size (0x%08x) sectors (0x%08x)\n", __func__, __LINE__, file_size, file_sectors);

	result = fseek(fp, 0, SEEK_SET);
	if (result) {
		printf("%s:%d: fseek failed (0x%08x)\n", __func__, __LINE__, result);
		goto done;
	}

	result = lv2_storage_get_device_info(VFLASH5_DEV_ID, &info);
	if (result) {
		printf("%s:%d: lv2_storage_get_device_info failed (0x%08x)\n", __func__, __LINE__, result);
		goto done;
	}

	printf("%s:%d: capacity (0x%016llx)\n", __func__, __LINE__, info.capacity);

	if (info.capacity < (VFLASH5_HEADER_SECTORS + VFLASH5_OS_DB_AREA_SECTORS + file_sectors)) {
		printf("%s:%d: device capacity too small\n", __func__, __LINE__);
		goto done;
	}

	result = lv2_storage_open(VFLASH5_DEV_ID, &dev_handle);
	if (result) {
		printf("%s:%d: lv2_storage_open failed (0x%08x)\n", __func__, __LINE__, result);
		goto done;
	}

	/* write os header and db area */

	start_sector = 0;
	sector_count = VFLASH5_HEADER_SECTORS + VFLASH5_OS_DB_AREA_SECTORS;

	printf("%s:%d: writing header start_sector (0x%08x) sector_count (0x%08x)\n",
		__func__, __LINE__, start_sector, sector_count);

	memset(buf, 0, sizeof(buf));
	hdr = (struct os_area_header *) buf;
	params = (struct os_area_params *) (buf + OS_AREA_SEGMENT_SIZE);
	db = (struct os_area_db *) (buf + VFLASH5_HEADER_SECTORS * OS_AREA_SEGMENT_SIZE);

	strncpy((char *) hdr->magic, HEADER_MAGIC, sizeof(hdr->magic));
	hdr->version = HEADER_VERSION;
	hdr->db_area_offset = VFLASH5_HEADER_SECTORS; /* in sectors */
	hdr->ldr_area_offset = VFLASH5_HEADER_SECTORS + VFLASH5_OS_DB_AREA_SECTORS; /* in sectors */
	hdr->ldr_format = HEADER_LDR_FORMAT_RAW; /* we do not use gzip format !!! */
	hdr->ldr_size = file_size;

	params->boot_flag = PARAM_BOOT_FLAG_GAME_OS;
	params->num_params = 0;

	db->magic = DB_MAGIC;
	db->version = DB_VERSION;
	db->index_64 = 24;
	db->count_64 = 57;
	db->index_32 = 544;
	db->count_32 = 57;
	db->index_16 = 836;
	db->count_16 = 57;

	result = lv2_storage_write(dev_handle, 0, start_sector, sector_count, buf, &unknown2, 0);
	if (result) {
		printf("%s:%d: lv2_storage_write failed (0x%08x)\n", __func__, __LINE__, result);
		goto done;
	}

	start_sector += VFLASH5_HEADER_SECTORS + VFLASH5_OS_DB_AREA_SECTORS;

	while (file_sectors) {
		sector_count = MIN(file_sectors, 16);

		result = fread(buf, 1, sector_count * VFLASH5_SECTOR_SIZE, fp);
		if (result < 0) {
			printf("%s:%d: fread failed (0x%08x)\n", __func__, __LINE__, result);
			goto done;
		}

		printf("%s:%d: writing data start_sector (0x%08x) sector_count (0x%08x)\n",
			__func__, __LINE__, start_sector, sector_count);

		result = lv2_storage_write(dev_handle, 0, start_sector, sector_count, buf, &unknown2, 0);
		if (result) {
			printf("%s:%d: lv2_storage_write failed (0x%08x)\n", __func__, __LINE__, result);
			goto done;
		}

		usleep(10000);

		file_sectors -= sector_count;
		start_sector += sector_count;
	}

	printf("%s:%d: end\n", __func__, __LINE__);

	lv2_sm_ring_buzzer(0x1004, 0xa, 0x1b6);

done:

	if (fp)
		fclose(fp);

	result = lv2_storage_close(dev_handle);
	if (result)
		printf("%s:%d: lv2_storage_close failed (0x%08x)\n", __func__, __LINE__, result);

	//udp_printf_deinit();

	//netDeinitialize();

	return 0;

#undef MIN
}
