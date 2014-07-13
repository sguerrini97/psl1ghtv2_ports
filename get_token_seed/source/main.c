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

#define UPDATE_MGR_PACKET_ID_GET_TOKEN_SEED		0x6009
#define UPDATE_MGR_PACKET_ID_READ_EPROM				0x600b
#define EPROM_QA_FLAG_OFFSET									0x48c0a
#define TOKEN_SIZE														80

//main
int main(int argc, char **argv){
	uint8_t value, seed[TOKEN_SIZE], token[TOKEN_SIZE];
	int i, result;
	
	FILE * out = fopen("/dev_usb000/get_token_seed.log","w");
	if(!out) return -1;
	
	//disable auth check (4.46)
	lv2_lv1_poke(0x16fb64, 0x2f80000048000050ULL);

	fprintf(out,"%s:%d: start\n", __func__, __LINE__);
	
	//lv2syscall7(863, ) Update Manager Interface
	result = lv2_ss_update_mgr_if(UPDATE_MGR_PACKET_ID_READ_EPROM, EPROM_QA_FLAG_OFFSET, (uint64_t) &value, 0, 0, 0, 0);
	if (result) {
		fprintf(out,"%s:%d: lv1_ss_update_mgr_if(READ_EPROM) failed (0x%08x)\n", __func__, __LINE__, result);
		goto done;
	}

	fprintf(out,"%s:%d: QA flag 0x%02x\n", __func__, __LINE__, value);
	
	//lv2syscall7(863, )
	result = lv2_ss_update_mgr_if(UPDATE_MGR_PACKET_ID_GET_TOKEN_SEED, (uint64_t) token, TOKEN_SIZE, (uint64_t) seed, TOKEN_SIZE, 0, 0);
	if (result) {
		fprintf(out,"%s:%d: lv1_ss_update_mgr_if(GET_TOKEN_SEED) failed (0x%08x)\n", __func__, __LINE__, result);
		goto done;
	}

	fprintf(out,"%s: %d: TOKEN SEED:\n", __func__, __LINE__);
	for (i = 0; i < TOKEN_SIZE; i += 16)
		fprintf(out,"%02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x\n",
			seed[i+ 0], seed[i+ 1], seed[i+ 2], seed[i+ 3], seed[i+ 4], seed[i+ 5],
			seed[i+ 6], seed[i+ 7], seed[i+ 8], seed[i+ 9], seed[i+10], seed[i+11],
			seed[i+12], seed[i+13], seed[i+14], seed[i+15]);

	fprintf(out,"%s: %d: TOKEN:\n", __func__, __LINE__);
	for (i = 0; i < TOKEN_SIZE; i += 16)
		fprintf(out,"%02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x\n",
			token[i+ 0], token[i+ 1], token[i+ 2], token[i+ 3], token[i+ 4], token[i+ 5],
			token[i+ 6], token[i+ 7], token[i+ 8], token[i+ 9], token[i+10], token[i+11],
			token[i+12], token[i+13], token[i+14], token[i+15]);

	fprintf(out,"%s:%d: end\n", __func__, __LINE__);
	
	//lv2syscall3(392, )
	lv2_sm_ring_buzzer(0x1004, 0xa, 0x1b6);
	fclose(out);
	
done:

	return 0;
}
