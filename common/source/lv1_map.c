
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

#include <lv1_map.h>

#include <stdlib.h>

#include <lv1_hvcall.h>
#include <lv2_syscall.h>
#include <mm.h>

#define LV1_PA		0x0000000000000000ull
#define LV1_EA		0x8000000014000000ull
#define LV1_SIZE	(16 * 1024 * 1024)

static uint64_t lv1_lpar;

/*
 * lv1_peek
 */
uint64_t lv1_peek(uint64_t addr)
{
	return lv2_peek(LV1_EA + addr);
}

/*
 * lv1_poke
 */
void lv1_poke(uint64_t addr, uint64_t val)
{
	lv2_poke(LV1_EA + addr, val);
}

/*
 * lv1_poke_8
 */
void lv1_poke_8(uint64_t addr, uint8_t val)
{
	uint64_t val_64;

	val_64 = lv1_peek(addr & ~0x7ull);

	val_64 &= ~(0xffull << ((sizeof(uint64_t) - (addr & 0x7ull) - 1) * 8));
	val_64 |= ((uint64_t) val) << ((sizeof(uint64_t) - (addr & 0x7ull) - 1) * 8);

	lv1_poke(addr & ~0x7ull, val_64);
}

/*
 * lv1_memcpy_to
 */
void lv1_memcpy_to(uint64_t addr, const void *data, unsigned int size)
{
	uint8_t *ptr;
	unsigned int nbytes;

	ptr = (uint8_t *) data;

	if (addr & 0x7ull) {
		nbytes = sizeof(uint64_t) - (addr & 0x7ull);

		size -= nbytes;

		while (nbytes--)
			lv1_poke_8(addr++, *ptr++);
	}

	while (size >= sizeof(uint64_t)) {
		lv1_poke(addr, *(uint64_t *) ptr);

		addr += sizeof(uint64_t);
		ptr += sizeof(uint64_t);
		size -= sizeof(uint64_t);
	}

	while (size--)
		lv1_poke_8(addr++, *ptr++);
}

/*
 * lv1_map
 */
int lv1_map(void)
{
	int result;

	if (lv1_lpar)
		return 0;

	result = lv1_undocumented_function_114(LV1_PA, PAGE_SIZE_4KB, LV1_SIZE, &lv1_lpar);
	if (result)
		return result;

	result = mm_map_lpar_memory_region(0, MM_EA2VA(LV1_EA), lv1_lpar, LV1_SIZE, PAGE_SIZE_4KB, 0, 0);
	if (result) {
		lv1_undocumented_function_115(lv1_lpar);
		lv1_lpar = 0;
		return result;
	}

	return 0;
}

/*
 * lv1_unmap
 */
int lv1_unmap(void)
{
	int result;

	if (!lv1_lpar)
		return 0;

	result = lv1_undocumented_function_115(lv1_lpar);
	if (result)
		return result;

	lv1_lpar = 0;

	return 0;
}
