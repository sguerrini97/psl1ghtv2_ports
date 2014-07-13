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

#include <unistd.h>

#include <lv1_hvcall.h>
#include <lv2_syscall.h>

void patch_proc_checks(){
	//disable product mode check
	lv2_lv1_poke(0x720670, 0x2F3E000060000000ULL);
	lv2_lv1_poke(0x720680, 0x7FA3EB7860000000ULL);
	//disable auth check
	lv2_lv1_poke(0x16fb64, 0x2f80000048000050ULL);
}

/* main */
int main(int argc, char **argv){
	
	usleep(10000);
	
	patch_proc_checks();
	
	usleep(10000);

	lv1_panic(1);

	return 0;
}
