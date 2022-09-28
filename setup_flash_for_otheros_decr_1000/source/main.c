
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

#include <string.h>
#include <unistd.h>
#include <stdio.h>

//#include <psl1ght/lv2/net.h>

#include <lv2_syscall.h>
//#include <udp_printf.h>

#define PARTITION_TABLE_MAGIC1				0x000000000face0ffull
#define PARTITION_TABLE_MAGIC2				0x00000000c01dbeefull

/* VFLASH */

#define VFLASH_DEV_ID					0x100000000000001ull
#define VFLASH_SECTOR_SIZE				0x200ull
#define VFLASH_START_SECTOR				0x0ull
#define VFLASH_SECTOR_COUNT				0x2ull
#define VFLASH_FLAGS					0x6ull

#define VFLASH_PARTITION_TABLE_5TH_REGION_OFFSET	0x270ull
#define VFLASH_5TH_REGION_NEW_SECTOR_COUNT		0xc000ull

#define VFLASH_PARTITION_TABLE_6TH_REGION_OFFSET	0x300ull
#define VFLASH_6TH_REGION_NEW_START_SECTOR		0x7fa00ull

/* NAND FLASH */

#define FLASH_DEV_ID					0x100000000000001ull
#define FLASH_SECTOR_SIZE				0x200ull
#define FLASH_START_SECTOR				0x7600ull
#define FLASH_SECTOR_COUNT				0x2ull
#define FLASH_FLAGS					0x6ull

#define FLASH_PARTITION_TABLE_5TH_REGION_OFFSET		0x1E0ull
#define FLASH_5TH_REGION_NEW_START_SECTOR		0x73600ull
#define FLASH_5TH_REGION_NEW_SECTOR_COUNT		0x4200ull

#define FLASH_PARTITION_TABLE_6TH_REGION_OFFSET		0x270ull //0x4E000
#define FLASH_6TH_REGION_NEW_START_SECTOR		0x77800ull
#define FLASH_6TH_REGION_NEW_SECTOR_COUNT		0x200ull

#define FLASH_REGION_LPAR_AUTH_ID			0x1070000002000001ull /* GameOS LPAR auth id */
#define FLASH_REGION_ACL				0x3ull

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
 * setup_vflash
 */
static int setup_vflash(void)
{
	uint32_t dev_handle;
	int start_sector, sector_count;
	uint32_t unknown2;
	uint8_t buf[VFLASH_SECTOR_SIZE * VFLASH_SECTOR_COUNT];
	uint64_t *ptr;
	int result;

	printf("%s:%d: start\n", __func__, __LINE__);

	dev_handle = 0;

	result = lv2_storage_open(VFLASH_DEV_ID, &dev_handle);
	if (result) {
		printf("%s:%d: lv2_storage_open failed (0x%08x)\n", __func__, __LINE__, result);
		goto done;
	}

	start_sector = VFLASH_START_SECTOR;
	sector_count = VFLASH_SECTOR_COUNT;

	printf("%s:%d: reading data start_sector (0x%08x) sector_count (0x%08x)\n",
		__func__, __LINE__, start_sector, sector_count);

	result = lv2_storage_read(dev_handle, 0, start_sector, sector_count, buf, &unknown2, VFLASH_FLAGS);
	if (result) {
		printf("%s:%d: lv2_storage_read failed (0x%08x)\n", __func__, __LINE__, result);
		goto done;
	}

	usleep(10000);

	/* check partition table magic */

	if ((*((uint64_t *) buf + 2) != PARTITION_TABLE_MAGIC1) ||
		(*((uint64_t *) buf + 3) != PARTITION_TABLE_MAGIC2)) {
		printf("%s:%d: invalid partition table magic\n", __func__, __LINE__);
		goto done;
	}

	/* patch sector count of VFLASH 5TH region */

	ptr = (uint64_t *) (buf + VFLASH_PARTITION_TABLE_5TH_REGION_OFFSET + 0x8ull);

	printf("%s:%d: VFLASH 5TH region old sector_count (0x%016llx) new sector_count (0x%016llx)\n",
		__func__, __LINE__, *ptr, VFLASH_5TH_REGION_NEW_SECTOR_COUNT);

	*ptr = VFLASH_5TH_REGION_NEW_SECTOR_COUNT;

	/* patch start sector of VFLASH 6TH region */

	ptr = (uint64_t *) (buf + VFLASH_PARTITION_TABLE_6TH_REGION_OFFSET);

	printf("%s:%d: VFLASH 6TH region old start_sector (0x%016llx) new start_sector (0x%016llx)\n",
		__func__, __LINE__, *ptr, VFLASH_6TH_REGION_NEW_START_SECTOR);

	*ptr = VFLASH_6TH_REGION_NEW_START_SECTOR;

	printf("%s:%d: writing data start_sector (0x%08x) sector_count (0x%08x)\n",
		__func__, __LINE__, start_sector, sector_count);

	result = lv2_storage_write(dev_handle, 0, start_sector, sector_count, buf, &unknown2, VFLASH_FLAGS);
	if (result) {
		printf("%s:%d: lv2_storage_write failed (0x%08x)\n", __func__, __LINE__, result);
		goto done;
	}

	usleep(10000);

	printf("%s:%d: end\n", __func__, __LINE__);

	return 0;

done:

	result = lv2_storage_close(dev_handle);
	if (result)
		printf("%s:%d: lv2_storage_close failed (0x%08x)\n", __func__, __LINE__, result);

	return result;
}

/*
 * setup_flash
 */
static int setup_flash(void)
{
	uint32_t dev_handle;
	int start_sector, sector_count;
	uint32_t unknown2;
	uint8_t buf[FLASH_SECTOR_SIZE * FLASH_SECTOR_COUNT];
	uint64_t *ptr;
	int result;

	printf("%s:%d: start\n", __func__, __LINE__);

	dev_handle = 0;

	result = lv2_storage_open(FLASH_DEV_ID, &dev_handle);
	if (result) {
		printf("%s:%d: lv2_storage_open failed (0x%08x)\n", __func__, __LINE__, result);
		goto done;
	}

	start_sector = FLASH_START_SECTOR;
	sector_count = FLASH_SECTOR_COUNT;

	printf("%s:%d: reading data start_sector (0x%08x) sector_count (0x%08x)\n",
		__func__, __LINE__, start_sector, sector_count);

	result = lv2_storage_read(dev_handle, 0, start_sector, sector_count, buf, &unknown2, FLASH_FLAGS);
	if (result) {
		printf("%s:%d: lv2_storage_read failed (0x%08x)\n", __func__, __LINE__, result);
		goto done;
	}

	usleep(10000);

	/* check partition table magic */

	if ((*((uint64_t *) buf + 2) != PARTITION_TABLE_MAGIC1) ||
		(*((uint64_t *) buf + 3) != PARTITION_TABLE_MAGIC2)) {
		printf("%s:%d: invalid partition table magic\n", __func__, __LINE__);
		goto done;
	}

	/* patch FLASH 5TH region */

	ptr = (uint64_t *) (buf + FLASH_PARTITION_TABLE_5TH_REGION_OFFSET);

	printf("%s:%d: FLASH 5TH region old start_sector (0x%016llx) new start_sector (0x%016llx)\n",
		__func__, __LINE__, *ptr, FLASH_5TH_REGION_NEW_START_SECTOR);

	printf("%s:%d: FLASH 5TH region old sector_count (0x%016llx) new sector_count (0x%016llx)\n",
		__func__, __LINE__, *(ptr + 1), FLASH_5TH_REGION_NEW_SECTOR_COUNT);

	*ptr++ = FLASH_5TH_REGION_NEW_START_SECTOR;
	*ptr++ = FLASH_5TH_REGION_NEW_SECTOR_COUNT;
	*ptr++ = FLASH_REGION_LPAR_AUTH_ID;
	*ptr++ = FLASH_REGION_ACL;

	/* patch FLASH 6TH region */

	ptr = (uint64_t *) (buf + FLASH_PARTITION_TABLE_6TH_REGION_OFFSET);

	printf("%s:%d: FLASH 6TH region old start_sector (0x%016llx) new start_sector (0x%016llx)\n",
		__func__, __LINE__, *ptr, FLASH_6TH_REGION_NEW_START_SECTOR);

	printf("%s:%d: FLASH 6TH region old sector_count (0x%016llx) new sector_count (0x%016llx)\n",
		__func__, __LINE__, *(ptr + 1), FLASH_6TH_REGION_NEW_SECTOR_COUNT);

	*ptr++ = FLASH_6TH_REGION_NEW_START_SECTOR;
	*ptr++ = FLASH_6TH_REGION_NEW_SECTOR_COUNT;
	*ptr++ = FLASH_REGION_LPAR_AUTH_ID;
	*ptr++ = FLASH_REGION_ACL;

	printf("%s:%d: writing data start_sector (0x%08x) sector_count (0x%08x)\n",
		__func__, __LINE__, start_sector, sector_count);

	result = lv2_storage_write(dev_handle, 0, start_sector, sector_count, buf, &unknown2, FLASH_FLAGS);
	if (result) {
		printf("%s:%d: lv2_storage_write failed (0x%08x)\n", __func__, __LINE__, result);
		goto done;
	}

	usleep(10000);

	printf("%s:%d: end\n", __func__, __LINE__);

	return 0;

done:

	result = lv2_storage_close(dev_handle);
	if (result)
		printf("%s:%d: lv2_storage_close failed (0x%08x)\n", __func__, __LINE__, result);

	return result;
}
/*
 * main
 */
int main(int argc, char **argv)
{
	int vflash_on, result;

	//netInitialize();

	//udp_printf_init();

	printf("%s:%d: start\n", __func__, __LINE__);

	vflash_on = is_vflash_on();

	printf("%s:%d: vflash %s\n", __func__, __LINE__, vflash_on ? "on" : "off");

	if (vflash_on) {
		result = setup_vflash();
		if (result) {
			printf("%s:%d: setup_vflash failed (0x%08x)\n", __func__, __LINE__, result);
			goto done;
		}
	} else {
		result = setup_flash();
		if (result) {
			printf("%s:%d: setup_flash failed (0x%08x)\n", __func__, __LINE__, result);
			goto done;
		}
	}

	lv2_sm_ring_buzzer(0x1004, 0xa, 0x1b6);

	printf("%s:%d: end\n", __func__, __LINE__);

done:

	//udp_printf_deinit();

	//netDeinitialize();

	return 0;
}
