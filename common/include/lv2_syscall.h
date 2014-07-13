
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

#ifndef _LV2_SYSCALL_H_
#define _LV2_SYSCALL_H_

#include <stdint.h>

#include <ppu-lv2.h>

struct storage_device_info {
	uint8_t res1[32];
	uint32_t vendor_id;
	uint32_t device_id;
	uint64_t capacity;
	uint32_t sector_size;
	uint32_t media_count;
	uint8_t res2[8];
};

struct platform_info {
	uint32_t firmare_version;
	uint8_t res1[4];
	uint64_t platform_id;
	uint32_t unknown;
	uint8_t res2[4];
};

/*
 * lv2_peek
 */
static inline uint64_t lv2_peek(uint64_t addr)
{
	lv2syscall1(6, addr);
	return_to_user_prog(uint64_t);
}

/*
 * lv2_poke
 */
static inline void lv2_poke(uint64_t addr, uint64_t val)
{
	lv2syscall2(7, addr, val);
}

/*
 * lv2_lv1_peek
 */
static inline uint64_t lv2_lv1_peek(uint64_t addr)
{
	lv2syscall1(8, addr);
	return_to_user_prog(uint64_t);
}

/*
 * lv2_lv1_poke
 */
static inline void lv2_lv1_poke(uint64_t addr, uint64_t val)
{
	lv2syscall2(9, addr, val);
}

/*
 * lv2_av_send
 */
static inline int lv2_av_send(const void *buf, uint64_t size, uint64_t flags)
{
	lv2syscall3(369, (uint64_t) buf, size, flags);
	return_to_user_prog(int);
}

/*
 * lv2_sm_shutdown
 */
static inline int lv2_sm_shutdown(uint16_t op, const void *buf, uint64_t size)
{
	lv2syscall3(379, op, (uint64_t) buf, size);
	return_to_user_prog(int);
}

/*
 * lv2_sm_get_params
 */
static inline int lv2_sm_get_params(uint64_t *unknown1, uint64_t *unknown2,
	uint64_t *unknown3, uint64_t *unknown4)
{
	lv2syscall4(380, (uint64_t) unknown1, (uint64_t) unknown2,
		(uint64_t) unknown3, (uint64_t) unknown4);
	return_to_user_prog(int);
}

/*
 * lv2_sm_control_led
 */
static inline int lv2_sm_control_led(uint8_t p, uint8_t s)
{
	lv2syscall2(386, p, s);
	return_to_user_prog(int);
}

/*
 * lv2_get_platform_info
 */
static inline int lv2_get_platform_info(struct platform_info *info)
{
	lv2syscall1(387, (uint64_t) info);
	return_to_user_prog(int);
}

/*
 * lv2_sm_ring_buzzer
 */
static inline int lv2_sm_ring_buzzer(uint64_t unknown1, uint8_t unknown2, uint32_t unknown3)
{
	lv2syscall3(392, unknown1, unknown2, unknown3);
	return_to_user_prog(int);
}

/*
 * lv2_get_sys_hw_config
 */
static inline int lv2_get_sys_hw_config(uint8_t *res, uint64_t *val)
{
	lv2syscall2(393, (uint64_t) res, (uint64_t) val);
	return_to_user_prog(int);
}

/*
 * lv2_lv1_log_write
 */
static inline int lv2_lv1_log_write(const char *s, unsigned int len)
{
	lv2syscall2(398, (uint64_t) s, len);
	return_to_user_prog(int);
}

/*
 * lv2_storage_open
 */
static inline int lv2_storage_open(uint64_t dev_id, uint32_t *dev_handle)
{
	lv2syscall4(600, dev_id, 0, (uint64_t) dev_handle, 0);
	return_to_user_prog(int);
}

/*
 * lv2_storage_close
 */
static inline int lv2_storage_close(uint32_t dev_handle)
{
	lv2syscall1(601, dev_handle);
	return_to_user_prog(int);
}

/*
 * lv2_storage_read
 */
static inline int lv2_storage_read(uint32_t dev_handle, uint64_t unknown1, uint64_t start_sector, uint64_t sector_count,
	const void *buf, uint32_t *unknown2, uint64_t flags)
{
	lv2syscall7(602, dev_handle, unknown1, start_sector, sector_count,
		(uint64_t ) buf, (uint64_t) unknown2, flags);
	return_to_user_prog(int);
}

/*
 * lv2_storage_write
 */
static inline int lv2_storage_write(uint32_t dev_handle, uint64_t unknown1, uint64_t start_sector, uint64_t sector_count,
	const void *buf, uint32_t *unknown2, uint64_t flags)
{
	lv2syscall7(603, dev_handle, unknown1, start_sector, sector_count,
		(uint64_t ) buf, (uint64_t) unknown2, flags);
	return_to_user_prog(int);
}

/*
 * lv2_storage_get_device_info
 */
static inline int lv2_storage_get_device_info(uint64_t dev_id, struct storage_device_info *info)
{
	lv2syscall2(609, dev_id, (uint64_t) info);
	return_to_user_prog(int);
}

/*
 * lv2_storage_create_region
 */
static inline int lv2_storage_create_region(uint32_t dev_handle, uint64_t start_sector,
	uint64_t sector_count, uint64_t unknown, uint64_t laid, uint64_t *region_id)
{
	lv2syscall6(614, dev_handle, start_sector, sector_count, unknown, laid, (uint64_t) region_id);
	return_to_user_prog(int);
}

/*
 * lv2_storage_delete_region
 */
static inline int lv2_storage_delete_region(uint32_t dev_handle, uint64_t region_id)
{
	lv2syscall2(615, dev_handle, region_id);
	return_to_user_prog(int);
}

/*
 * lv2_storage_execute_device_command
 */
static inline int lv2_storage_execute_device_command(uint32_t dev_handle, uint64_t cmd,
	const void *cmdbuf, uint64_t cmdbuf_size, void *databuf, uint64_t databuf_size,
	uint64_t *unknown)
{
	lv2syscall7(616, dev_handle, cmd, (uint64_t) cmdbuf, cmdbuf_size,
		(uint64_t) databuf, databuf_size, (uint64_t) unknown);
	return_to_user_prog(int);
}

/*
 * lv2_gelic_eurus_control
 */
static inline int lv2_gelic_eurus_control(uint16_t cmd, uint8_t *cmdbuf, uint64_t cmdbuf_size)
{
	lv2syscall3(726, cmd, (uint64_t) cmdbuf, cmdbuf_size);
	return_to_user_prog(int);
}

/*
 * lv2_cell_fs_util_umount
 */
static inline int lv2_cell_fs_util_umount(const char *dir, uint64_t unknown)
{
	lv2syscall2(838, (uint64_t) dir, unknown);
	return_to_user_prog(int);
}

/*
 * lv2_cell_fs_util_sync
 */
static inline int lv2_cell_fs_util_sync(const char *dir)
{
	lv2syscall1(839, (uint64_t) dir);
	return_to_user_prog(int);
}

/*
 * lv2_ss_vtrm_mgr_if
 */
static inline int lv2_ss_vtrm_mgr_if(uint32_t packet_id, uint64_t arg1, uint64_t arg2,
	uint64_t arg3, uint64_t arg4)
{
	lv2syscall5(862, packet_id, arg1, arg2, arg3, arg4);
	return_to_user_prog(int);
}

/*
 * lv2_ss_update_mgr_if
 */
static inline int lv2_ss_update_mgr_if(uint32_t packet_id, uint64_t arg1, uint64_t arg2,
	uint64_t arg3, uint64_t arg4, uint64_t arg5, uint64_t arg6)
{
	lv2syscall7(863, packet_id, arg1, arg2, arg3, arg4, arg5, arg6);
	return_to_user_prog(int);
}

/*
 * lv2_ss_stor_mgr_if
 */
static inline int lv2_ss_stor_mgr_if(uint32_t packet_id, uint64_t arg1)
{
	lv2syscall2(864, packet_id, arg1);
	return_to_user_prog(int);
}

/*
 * lv2_ss_secure_rtc_if
 */
static inline int lv2_ss_secure_rtc_if(uint32_t packet_id, uint64_t arg1, uint64_t arg2, uint64_t arg3)
{
	lv2syscall4(866, packet_id, arg1, arg2, arg3);
	return_to_user_prog(int);
}

/*
 * lv2_ss_aim_if
 */
static inline int lv2_ss_aim_if(uint32_t packet_id, uint64_t arg1)
{
	lv2syscall2(867, packet_id, arg1);
	return_to_user_prog(int);
}

/*
 * lv2_ss_indi_info_mgr_if
 */
static inline int lv2_ss_indi_info_mgr_if(uint32_t packet_id, uint64_t arg1, uint64_t arg2,
	uint64_t arg3, uint64_t arg4)
{
	lv2syscall5(868, packet_id, arg1, arg2, arg3, arg4);
	return_to_user_prog(int);
}

/*
 * lv2_ss_get_cache_of_flash_ext_flag
 */
static inline int lv2_ss_get_cache_of_flash_ext_flag(uint8_t *flag)
{
	lv2syscall1(874, (uint64_t) flag);
	return_to_user_prog(int);
}

/*
 * lv2_get_target_type
 *
 * Types:
 * 	1 - Retail
 * 	2 - Debug
 * 	3 - Reference Tool
 */
static inline int lv2_get_target_type(uint64_t *type)
{
	lv2syscall1(985, (uint64_t) type);
	return_to_user_prog(int);
}

#endif
