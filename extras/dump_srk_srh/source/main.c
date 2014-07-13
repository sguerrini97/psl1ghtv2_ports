#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <lv2_syscall.h>

uint64_t backup_srk(uint8_t *data)
{
	return lv2_ss_vtrm_mgr_if(0x2014, 0x80, (uint64_t)data,0,0);
}

void patch_proc_checks()
{
	//disable product mode check
	lv2_lv1_poke(0x720670, 0x2F3E000060000000ULL);
	lv2_lv1_poke(0x720680, 0x7FA3EB7860000000ULL);
	//disable auth check
	lv2_lv1_poke(0x16fb64, 0x2f80000048000050ULL);
}

int main()
{
	FILE *fp;
	patch_proc_checks();
	usleep(50000);
	
	uint8_t data[0x80];
	long long unsigned int res;

	memset(data, 0, 0x80);
	res = backup_srk(data);
	
	printf("backup srk: %llx\n", res);
	
	fp = fopen ("/dev_usb000/backup_srk_srh.bin","w");
	if(fp){
		for(int i=0x00; i < 0x80; ++i)
			fputc(data[i], fp);
	}
	
	lv2_sm_ring_buzzer(0x1004, 0xa, 0x1b6);
	
	return 0;
}