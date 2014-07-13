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

#include <lv2_syscall.h>

#define UPDATE_MGR_PACKET_ID_READ_EPROM		0x600b
#define UPDATE_MGR_PACKET_ID_WRITE_EPROM	0x600c
#define EPROM_RECOVER_MODE_OFFSET					0x48c61

void patch_proc_checks(){
	//disable product mode check
	//lv2_lv1_poke(0x720670, 0x2F3E000060000000ULL);
	//lv2_lv1_poke(0x720680, 0x7FA3EB7860000000ULL);
	
	//disable auth check (4.46)
	lv2_lv1_poke(0x16fb64, 0x2f80000048000050ULL);
	
	//UM EEPROM Write Access (4.46)
	lv2_lv1_poke(0xFEB88, 0x4802D20938000000ULL);
}

//main
int main(int argc, char **argv){
	uint8_t value;
	int result;

	printf("%s:%d: start\n", __func__, __LINE__);

	patch_proc_checks();
	
	result = lv2_ss_update_mgr_if(UPDATE_MGR_PACKET_ID_READ_EPROM, EPROM_RECOVER_MODE_OFFSET, (uint64_t) &value, 0, 0, 0, 0);
	if (result) {
		printf("%s:%d: lv1_ss_update_mgr_if(READ_EPROM) failed (0x%08x)\n", __func__, __LINE__, result);
		goto done;
	}

	printf("%s:%d: current recover mode 0x%02x\n", __func__, __LINE__, value);

	if (value == 0xff) {
		/* enable */

		printf("%s:%d: enabling recover mode\n", __func__, __LINE__);

		value = 0x0;

		result = lv2_ss_update_mgr_if(UPDATE_MGR_PACKET_ID_WRITE_EPROM, EPROM_RECOVER_MODE_OFFSET, value, 0, 0, 0, 0);
		if (result) {
			printf("%s:%d: lv2_ss_update_mgr_if(WRITE_EPROM) failed (0x%08x)\n", __func__, __LINE__, result);
			goto done;
		}
	} else {
		/* disable */

		printf("%s:%d: disabling recover mode\n", __func__, __LINE__);

		value = 0xff;

		result = lv2_ss_update_mgr_if(UPDATE_MGR_PACKET_ID_WRITE_EPROM, EPROM_RECOVER_MODE_OFFSET, value, 0, 0, 0, 0);
		if (result) {
			printf("%s:%d: lv2_ss_update_mgr_if(WRITE_EPROM) failed (0x%08x)\n", __func__, __LINE__, result);
			goto done;
		}
	}

	printf("%s:%d: end\n", __func__, __LINE__);

	lv2_sm_ring_buzzer(0x1004, 0xa, 0x1b6);

done:

	return 0;
}
