
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

#include <mm.h>
#include <ss.h>
#include <vuart.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dispmgr.h>
#include <inttypes.h>
#include <lv1_hvcall.h>
#include <lv2_syscall.h>


#define SC_MGR_READ_EPROM_BASE				0x80000000133A0000ULL
#define SC_MGR_READ_EPROM_OFFSET			0x133A0000ULL
#define SC_MGR_READ_EPROM_PAGE_SIZE			12
#define SC_MGR_READ_EPROM_SIZE				(1 << SC_MGR_READ_EPROM_PAGE_SIZE)

static volatile u64 subject_id[2] = { 0x1070000002000001, 0x10700003FF000001 };

static volatile u32 eprom_offsets[] =
{
	0x2F00,
	0x3000,
	0x48000,
	0x48800,
	0x48C00,
	0x48D00,
};

int main_read_eeprom(void)
{
#define N(a)	(sizeof((a)) / sizeof((a)[0]))

    char eeprom_fname [256];
    FILE* eeprom;
	
	FILE* log = fopen("/dev_usb000/log.txt","w");

	u64 vuart_lpar_addr, muid, nread, nwritten;
	u8 *msgbuf;
	struct dispmgr_header *dispmgr_header;
	struct ss_header *ss_header;
	struct ss_sc_mgr_read_eprom *ss_sc_mgr_read_eprom;
	int i, result;

	result = lv1_allocate_memory(SC_MGR_READ_EPROM_SIZE, SC_MGR_READ_EPROM_PAGE_SIZE,
		0, 0, &vuart_lpar_addr, &muid);
 	if (result != 0)
 		return result;

	MM_LOAD_BASE(msgbuf, SC_MGR_READ_EPROM_OFFSET);

	result = mm_map_lpar_memory_region(0, MM_EA2VA((u64) msgbuf), vuart_lpar_addr,
		SC_MGR_READ_EPROM_SIZE, SC_MGR_READ_EPROM_PAGE_SIZE, 0, 0);
	if (result != 0)
		return result;

	for (i = 0; i < N(eprom_offsets); i++)
	{
		unsigned int offset = eprom_offsets[i];
		sprintf(eeprom_fname, "/dev_usb000/eeprom_0x%08x.bin", offset);
		eeprom = fopen(eeprom_fname, "w");
		
		fprintf(log, "I: %i, LINE: %i\n", i, __LINE__);				//
		memset(msgbuf, 0, SC_MGR_READ_EPROM_SIZE);
		fprintf(log, "I: %i, LINE: %i\n", i, __LINE__);				//
		dispmgr_header = (struct dispmgr_header *) msgbuf;
		fprintf(log, "I: %i, LINE: %i\n", i, __LINE__);				//
		dispmgr_header->request_id = i + 1;
		dispmgr_header->function_id = 0x9000;
		dispmgr_header->request_size = sizeof(struct ss_header);
		dispmgr_header->response_size = sizeof(struct ss_header) +
			sizeof(struct ss_sc_mgr_read_eprom) + 0x100;

		fprintf(log, "I: %i, LINE: %i\n", i, __LINE__);				//
			
		ss_header = (struct ss_header *) (dispmgr_header + 1);
		memset(ss_header, 0, sizeof(struct ss_header));
		fprintf(log, "I: %i, LINE: %i\n", i, __LINE__);				//
		ss_header->packet_id = 0x900B;
		ss_header->function_id = 0x9000;
		ss_header->laid = subject_id[0];
		ss_header->paid = subject_id[1];

		ss_sc_mgr_read_eprom = (struct ss_sc_mgr_read_eprom *) (ss_header + 1);
		memset(ss_sc_mgr_read_eprom, 0, sizeof(struct ss_sc_mgr_read_eprom));
		fprintf(log, "I: %i, LINE: %i\n", i, __LINE__);				//
		ss_sc_mgr_read_eprom->offset = eprom_offsets[i];
		ss_sc_mgr_read_eprom->nread = 0x100;
		ss_sc_mgr_read_eprom->buf_size = 0x100;

		dispmgr_header->request_size += sizeof(struct ss_sc_mgr_read_eprom) +
			ss_sc_mgr_read_eprom->buf_size;

		result = lv1_write_virtual_uart(DISPMGR_VUART_PORT, vuart_lpar_addr,
			sizeof(struct dispmgr_header) + dispmgr_header->request_size, &nwritten);
		if (result < 0)
			return result;
			
		fprintf(log, "I: %i, LINE: %i\n", i, __LINE__);				//

		result = vuart_wait_for_rx_data(DISPMGR_VUART_PORT);
		if (result < 0)
			return result;

		fprintf(log, "I: %i, LINE: %i\n", i, __LINE__);			//
		
		result = lv1_read_virtual_uart(DISPMGR_VUART_PORT, vuart_lpar_addr,
			SC_MGR_READ_EPROM_SIZE, &nread);
		if (result < 0)
			return result;

		//do something with msgbuf here
		fwrite(msgbuf, SC_MGR_READ_EPROM_SIZE, 1, eeprom);
		fclose(eeprom);
	}

	lv2_sm_ring_buzzer(0x1004, 0xa, 0x1b6);

	lv1_panic(1);

	return 0;

#undef N
}

int main(){
	//FILE *fp = fopen ("/dev_usb000/log.txt","w");
	int result = main_read_eeprom();
	if(result){
		//fprintf(fp,"%08x",result);
		return -1;
	}
	return 0;
}
