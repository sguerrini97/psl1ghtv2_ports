#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <lv2_syscall.h>

uint64_t backup_flash(uint8_t *data)
{
	uint64_t nread;	
	return lv2_ss_vtrm_mgr_if(0x2012, 0, 0x8000, (uint64_t)data, (uint64_t)&nread);
}

void patch_proc_checks()
{
	//unicorns (4.46)
	lv2_lv1_poke(0x7203A8, 0x3860000138210080ULL);
	//disable product mode check (4.46)
	lv2_lv1_poke(0x720670, 0x2F3E000060000000ULL);
	lv2_lv1_poke(0x720680, 0x7FA3EB7860000000ULL);
	//disable auth check (4.46)
	lv2_lv1_poke(0x16fb64, 0x2f80000048000050ULL);
}

int main()
{
	FILE * fp = NULL;
	uint8_t data[0x8000];
	long long unsigned int res;
	memset(data, 0, 0x8000);
	
	patch_proc_checks();
	res = backup_flash(data);

	printf("backup vtrm: %llx\n", res);
	
	if(!res){
		fp = fopen ("/dev_usb000/backup_vtrm.bin","w");
		if(fp){
			for(int i=0x00; i < 0x8000; ++i){
				fputc(data[i], fp);
			}
			fclose(fp);
		}
		lv2_sm_ring_buzzer(0x1004, 0xa, 0x1b6);
	}

	return 0;
}

