
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

#ifndef _MM_H_
#define _MM_H_

#include <ppu-types.h>

#define HTAB_HASH_MASK						0x7FFULL
#define HPTES_PER_GROUP						8

#define HPTE_V_AVPN_SHIFT					7
#define HPTE_V_BOLTED						0x0000000000000010ULL
#define HPTE_V_LARGE						0x0000000000000004ULL
#define HPTE_V_VALID						0x0000000000000001ULL
#define HPTE_V_FLAGS_MASK					0x000000000000007FULL

#define HPTE_R_R							0x0000000000000100ULL
#define HPTE_R_C							0x0000000000000080ULL
#define HPTE_R_W							0x0000000000000040ULL
#define HPTE_R_I							0x0000000000000020ULL
#define HPTE_R_M							0x0000000000000010ULL
#define HPTE_R_G							0x0000000000000008ULL
#define HPTE_R_N							0x0000000000000004ULL
#define HPTE_R_FLAGS_MASK					0x000000000000FFFFULL

#define PAGE_SIZES(_ps0, _ps1)				(((u64) (_ps0) << 56) | ((u64) (_ps1) << 48))
#define PAGE_SIZE_4KB						12
#define PAGE_SIZE_64KB						16
#define PAGE_SIZE_1MB						20
#define PAGE_SIZE_16MB						24

#define GAMEOS_HTAB_BASE					0x800000000F000000ULL
#define GAMEOS_HTAB_OFFSET					0xF000000ULL
#define GAMEOS_HTAB_SIZE					0x40000

#define MM_LOAD_BASE(ptr, offset)			\
	__asm__ __volatile__ (					\
		"li %0, 1\n\t"						\
		"rldicr %0, %0, 63, 0\n\t"			\
		"oris %0, %0, %1\n\t"				\
		"ori %0, %0, %2\n\t" :				\
		"=r"(ptr) :							\
		"g"(((offset) >> 16) & 0xFFFF),		\
		"g"((offset) & 0xFFFF))

#define MM_EA2VA(ea)						((ea) & ~(1ULL << 63))

int mm_init(void);

int mm_insert_htab_entry(unsigned long vas_id, u64 va_addr, u64 lpar_addr,
	u64 page_shift, u64 vflags, u64 rflags, u64 *index);

int mm_map_lpar_memory_region(unsigned long vas_id, u64 va_start_addr, u64 lpar_start_addr,
	u64 size, u64 page_shift, u64 vflags, u64 rflags);

int mm_lpar_addr_to_ra(u64 lpar_addr, u64 *ra);

int mm_phys_ra_to_lpar_addr(u64 ra, u64 *lpar_addr);

#endif
