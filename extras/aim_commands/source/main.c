#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <lv2_syscall.h>

#define DATA_SIZE	0x10

#define AIM_PACKET_GET_DEV_TYPE	0x19002 //Get Device Type
#define AIM_PACKET_GET_DEV_ID	0x19003, //Get Device ID
#define AIM_PACKET_GET_PS_CODE	0x19004, //Get PS Code
#define AIM_PACKET_GET_OPEN_PS_ID	0x19005, //Get Open PS ID
#define AIM_PACKET_UNKNOWN	0x19006  //Unknown

uint64_t aim_command(uint32_t packet_id, uint8_t *data)
{
	//lv2_ss_aim_if(uint32_t packet_id, uint64_t arg1)
	return lv2_ss_aim_if(packet_id, (uint64_t)data);
}

void patch_proc_checks()
{
	//unicorns (4.46)
	//lv2_lv1_poke(0x7203A8, 0x3860000138210080ULL);
	//disable product mode check (4.46)
	//lv2_lv1_poke(0x720670, 0x2F3E000060000000ULL);
	//lv2_lv1_poke(0x720680, 0x7FA3EB7860000000ULL);
	//disable auth check (4.46)
	lv2_lv1_poke(0x16fb64, 0x2f80000048000050ULL);
}

int main()
{
	FILE * fp = NULL;
	uint8_t data[DATA_SIZE];
	long long unsigned int res;
	char fname[256];
	
	patch_proc_checks();
	
	for(int i = AIM_PACKET_GET_DEV_TYPE; i < AIM_PACKET_UNKNOWN; ++i){
		memset(data, 0, DATA_SIZE);
		res = aim_command(i, data);
		sprintf(fname, "/dev_usb000/aim_command_0x%x.bin", i);
		fp = fopen(fname, "wb");
		if(fp){
			fwrite(data, sizeof(uint8_t), DATA_SIZE, fp);
			fclose(fp);
		}
		usleep(10000);
	}
		
	lv2_sm_ring_buzzer(0x1004, 0xa, 0x1b6);

	return 0;
}

