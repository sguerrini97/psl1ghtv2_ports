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
#include <unistd.h>

#include <lv2_syscall.h>

/*
 * main
 */
int main(int argc, char **argv)
{
  
	int fd;

	
	unsigned char buf[0x200];
	uint64_t nread = 1;
	int i=0;
	
	int res = lv2_fs_umount("/dev_flash", 0, 0);
	printf("%08X umount\n",res);
	//sys_fs_mount("CELL_FS_IOS:BUILTIN_FLSH1", "CELL_FS_FAT", "/dev_blind", 0);
	res = sys_fs_mount("CELL_FS_IOS:BUILTIN_FLSH1", "CELL_FS_SIMPLEFS", "/dev_pussy", 0LL);
	printf("%08X mount\n",res);
	res = lv2_fs_open("/dev_pussy", 0, &fd, 0, 0, 0);
	printf("%08X open\n",res);
	FILE * fp = fopen ("/dev_usb001/dump.bin","wb");
	
	for(i=0;i<0xE000000;i=i+0x200){
		res= lv2_fs_read(fd,buf,0x200,&nread);
		printf("%08X read\n",res);
		res = fwrite(buf,0x200,1,fp);
	}
	fclose(fp);
	res = lv2_fs_close(fd);
	printf("%08X close2\n",res);
	
	lv2_sm_ring_buzzer(0x1004, 0xa, 0x1b6); //usb copy finished
	return 0;
}
