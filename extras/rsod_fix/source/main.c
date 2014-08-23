#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <lv2_syscall.h>

uint64_t backup_flash()
{
	return lv2_ss_vtrm_mgr_if(0x2001, 0, 0, 0, 0);
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
	long long unsigned int res;
	
	patch_proc_checks();
	res = backup_flash();

	fp = fopen("/dev_usb000/rsod_fix.log","w");
	if(fp){
		fprintf(fp, "rsod fix: %llx\n", res);
		fclose(fp);
	}
	
	if(!res)
		lv2_sm_ring_buzzer(0x1004, 0xa, 0x1b6);

	return 0;
}

