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

#define UPDATE_MGR_PACKET_ID_GET_APPL_VER		0x6011

struct update_mgr_get_appl_ver {
	uint64_t lower;
	uint8_t res1[8];
	uint64_t upper;
	uint8_t res2[8];
};

/*
 * main
 */
int main(int argc, char **argv)
{
	struct update_mgr_get_appl_ver get_appl_ver;
	int result;

	FILE * logfile = fopen("/dev_usb000/get_applicable_version.log","w");
	if(!logfile) return -1;
	
	//disable auth check (4.46)
	lv2_lv1_poke(0x16fb64, 0x2f80000048000050ULL);

	fprintf(logfile, "%s:%d: start\n", __func__, __LINE__);

	result = lv2_ss_update_mgr_if(UPDATE_MGR_PACKET_ID_GET_APPL_VER, 1, (uint64_t) &get_appl_ver, 0, 0, 0, 0);
	if (result) {
		fprintf(logfile, "%s:%d: lv1_ss_update_mgr_if(GET_APPL_VER) failed (0x%08x)\n",
			__func__, __LINE__, result);
		goto done;
	}

	fprintf(logfile, "%s:%d: lower 0x%016lx upper 0x%016lx\n", __func__, __LINE__, get_appl_ver.lower, get_appl_ver.upper);

	fprintf(logfile, "%s:%d: end\n", __func__, __LINE__);

	lv2_sm_ring_buzzer(0x1004, 0xa, 0x1b6);
	fclose(logfile);

done:

	return 0;
}
