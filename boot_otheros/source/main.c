
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
#define VFLASH5_HEADER_SECTORS			0x2ull

/*
 * main
 */
int main(int argc, char **argv)
{
	uint32_t dev_handle;
	int start_sector, sector_count;
	struct storage_device_info info;
	uint8_t buf[VFLASH5_SECTOR_SIZE * 16];
	struct os_area_header *hdr;
	struct os_area_params *params;
	uint32_t unknown2;
	int result;

	//netInitialize();

	//udp_printf_init();

	printf("%s:%d: start\n", __func__, __LINE__);

	dev_handle = 0;

	result = lv2_storage_get_device_info(VFLASH5_DEV_ID, &info);
	if (result) {
		printf("%s:%d: lv2_storage_get_device_info failed (0x%08x)\n", __func__, __LINE__, result);
		goto done;
	}

	printf("%s:%d: capacity (0x%016llx)\n", __func__, __LINE__, info.capacity);

	if (info.capacity < VFLASH5_HEADER_SECTORS) {
		printf("%s:%d: device capacity too small\n", __func__, __LINE__);
		goto done;
	}

	result = lv2_storage_open(VFLASH5_DEV_ID, &dev_handle);
	if (result) {
		printf("%s:%d: lv2_storage_open failed (0x%08x)\n", __func__, __LINE__, result);
		goto done;
	}

	/* write os header and params */

	start_sector = 0;
	sector_count = VFLASH5_HEADER_SECTORS;

	printf("%s:%d: reading header start_sector (0x%08x) sector_count (0x%08x)\n",
		__func__, __LINE__, start_sector, sector_count);

	memset(buf, 0, sizeof(buf));
	hdr = (struct os_area_header *) buf;
	params = (struct os_area_params *) (buf + OS_AREA_SEGMENT_SIZE);

	result = lv2_storage_read(dev_handle, 0, start_sector, sector_count, buf, &unknown2, 0);
	if (result) {
		printf("%s:%d: lv2_storage_read failed (0x%08x)\n", __func__, __LINE__, result);
		goto done;
	}

	if (strncmp((const char *) hdr->magic, HEADER_MAGIC, sizeof(hdr->magic))) {
		printf("%s:%d: invalid header magic\n", __func__, __LINE__);
		goto done;
	}

	if (hdr->version != HEADER_VERSION) {
		printf("%s:%d: invalid header version\n", __func__, __LINE__);
		goto done;
	}

	if (params->boot_flag == PARAM_BOOT_FLAG_GAME_OS) {
		params->boot_flag = PARAM_BOOT_FLAG_OTHER_OS;

		result = lv2_storage_write(dev_handle, 0, start_sector, sector_count, buf, &unknown2, 0);
		if (result) {
			printf("%s:%d: lv2_storage_write failed (0x%08x)\n", __func__, __LINE__, result);
			goto done;
		}
	}

	printf("%s:%d: end\n", __func__, __LINE__);

	lv2_sm_ring_buzzer(0x1004, 0xa, 0x1b6);

done:

	result = lv2_storage_close(dev_handle);
	if (result)
		printf("%s:%d: lv2_storage_close failed (0x%08x)\n", __func__, __LINE__, result);

	//udp_printf_deinit();

	//netDeinitialize();

	return 0;
}
