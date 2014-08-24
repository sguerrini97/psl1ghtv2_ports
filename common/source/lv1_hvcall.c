
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

#include <stdint.h>

#define LV1_HVCALL(name, in, out, num)	extern int64_t _lv1_##name(LV1_##in##_IN_##out##_OUT_ARG_DECL);

#include <unistd.h>

#include <lv1_hvcall.h>
#include <lv2_syscall.h>

/*
 * lv2 syscall 615 (3.41)
 */
//#define _LV2_SYSCALL_HVCALL_ADDR	0x8000000000295f24ull

/*
 * lv2 syscall 811 (4.46)
 */
#define _LV2_SYSCALL_HVCALL_ADDR	0x80000000001B5674ull

#define _LV2_SYSCALL_HVCALL_PATCH(num)										\
	uint64_t old_code[4];											\
														\
	old_code[0] = lv2_peek(_LV2_SYSCALL_HVCALL_ADDR);							\
	old_code[1] = lv2_peek(_LV2_SYSCALL_HVCALL_ADDR + 8);							\
	old_code[2] = lv2_peek(_LV2_SYSCALL_HVCALL_ADDR + 16);							\
	old_code[3] = lv2_peek(_LV2_SYSCALL_HVCALL_ADDR + 24);							\
														\
	lv2_poke(_LV2_SYSCALL_HVCALL_ADDR, 0x7c0802a6f8010010ull);						\
	lv2_poke(_LV2_SYSCALL_HVCALL_ADDR + 8, 0x3960000044000022ull | ((uint64_t) num << 32));			\
	lv2_poke(_LV2_SYSCALL_HVCALL_ADDR + 16, 0xe80100107c0803a6ull);						\
	lv2_poke(_LV2_SYSCALL_HVCALL_ADDR + 24, 0x4e80002060000000ull);						\

#define _LV2_SYSCALL_HVCALL_RESTORE										\
	lv2_poke(_LV2_SYSCALL_HVCALL_ADDR, old_code[0]);							\
	lv2_poke(_LV2_SYSCALL_HVCALL_ADDR + 8, old_code[1]);							\
	lv2_poke(_LV2_SYSCALL_HVCALL_ADDR + 16, old_code[2]);							\
	lv2_poke(_LV2_SYSCALL_HVCALL_ADDR + 24, old_code[3]);

#define USLEEP_PAUSE	10000

#define LV1_0_IN_0_OUT(name, num)										\
int64_t lv1_##name(LV1_0_IN_0_OUT_ARG_DECL)									\
{														\
	int64_t ret;												\
														\
	_LV2_SYSCALL_HVCALL_PATCH(num);										\
														\
	ret = _lv1_##name(LV1_0_IN_0_OUT_ARGS);									\
														\
	_LV2_SYSCALL_HVCALL_RESTORE;										\
														\
	usleep(USLEEP_PAUSE);											\
														\
	return ret;												\
}

#define LV1_0_IN_1_OUT(name, num)										\
int64_t lv1_##name(LV1_0_IN_1_OUT_ARG_DECL)									\
{														\
	int64_t ret;												\
														\
	_LV2_SYSCALL_HVCALL_PATCH(num);										\
														\
	ret = _lv1_##name(LV1_0_IN_1_OUT_ARGS);									\
														\
	_LV2_SYSCALL_HVCALL_RESTORE;										\
														\
	usleep(USLEEP_PAUSE);											\
														\
	return ret;												\
}

#define LV1_0_IN_2_OUT(name, num)										\
int64_t lv1_##name(LV1_0_IN_2_OUT_ARG_DECL)									\
{														\
	int64_t ret;												\
														\
	_LV2_SYSCALL_HVCALL_PATCH(num);										\
														\
	ret = _lv1_##name(LV1_0_IN_2_OUT_ARGS);									\
														\
	_LV2_SYSCALL_HVCALL_RESTORE;										\
														\
	usleep(USLEEP_PAUSE);											\
														\
	return ret;												\
}

#define LV1_1_IN_0_OUT(name, num)										\
int64_t lv1_##name(LV1_1_IN_0_OUT_ARG_DECL)									\
{														\
	int64_t ret;												\
														\
	_LV2_SYSCALL_HVCALL_PATCH(num);										\
														\
	ret = _lv1_##name(LV1_1_IN_0_OUT_ARGS);									\
														\
	_LV2_SYSCALL_HVCALL_RESTORE;										\
														\
	usleep(USLEEP_PAUSE);											\
														\
	return ret;												\
}

#define LV1_1_IN_1_OUT(name, num)										\
int64_t lv1_##name(LV1_1_IN_1_OUT_ARG_DECL)									\
{														\
	int64_t ret;												\
														\
	_LV2_SYSCALL_HVCALL_PATCH(num);										\
														\
	ret = _lv1_##name(LV1_1_IN_1_OUT_ARGS);									\
														\
	_LV2_SYSCALL_HVCALL_RESTORE;										\
														\
	usleep(USLEEP_PAUSE);											\
														\
	return ret;												\
}

#define LV1_1_IN_2_OUT(name, num)										\
int64_t lv1_##name(LV1_1_IN_2_OUT_ARG_DECL)									\
{														\
	int64_t ret;												\
														\
	_LV2_SYSCALL_HVCALL_PATCH(num);										\
														\
	ret = _lv1_##name(LV1_1_IN_2_OUT_ARGS);									\
														\
	_LV2_SYSCALL_HVCALL_RESTORE;										\
														\
	usleep(USLEEP_PAUSE);											\
														\
	return ret;												\
}

#define LV1_1_IN_5_OUT(name, num)										\
int64_t lv1_##name(LV1_1_IN_5_OUT_ARG_DECL)									\
{														\
	int64_t ret;												\
														\
	_LV2_SYSCALL_HVCALL_PATCH(num);										\
														\
	ret = _lv1_##name(LV1_1_IN_5_OUT_ARGS);									\
														\
	_LV2_SYSCALL_HVCALL_RESTORE;										\
														\
	usleep(USLEEP_PAUSE);											\
														\
	return ret;												\
}

#define LV1_2_IN_0_OUT(name, num)										\
int64_t lv1_##name(LV1_2_IN_0_OUT_ARG_DECL)									\
{														\
	int64_t ret;												\
														\
	_LV2_SYSCALL_HVCALL_PATCH(num);										\
														\
	ret = _lv1_##name(LV1_2_IN_0_OUT_ARGS);									\
														\
	_LV2_SYSCALL_HVCALL_RESTORE;										\
														\
	usleep(USLEEP_PAUSE);											\
														\
	return ret;												\
}

#define LV1_2_IN_1_OUT(name, num)										\
int64_t lv1_##name(LV1_2_IN_1_OUT_ARG_DECL)									\
{														\
	int64_t ret;												\
														\
	_LV2_SYSCALL_HVCALL_PATCH(num);										\
														\
	ret = _lv1_##name(LV1_2_IN_1_OUT_ARGS);									\
														\
	_LV2_SYSCALL_HVCALL_RESTORE;										\
														\
	usleep(USLEEP_PAUSE);											\
														\
	return ret;												\
}

#define LV1_2_IN_5_OUT(name, num)										\
int64_t lv1_##name(LV1_2_IN_5_OUT_ARG_DECL)									\
{														\
	int64_t ret;												\
														\
	_LV2_SYSCALL_HVCALL_PATCH(num);										\
														\
	ret = _lv1_##name(LV1_2_IN_5_OUT_ARGS);									\
														\
	_LV2_SYSCALL_HVCALL_RESTORE;										\
														\
	usleep(USLEEP_PAUSE);											\
														\
	return ret;												\
}

#define LV1_3_IN_0_OUT(name, num)										\
int64_t lv1_##name(LV1_3_IN_0_OUT_ARG_DECL)									\
{														\
	int64_t ret;												\
														\
	_LV2_SYSCALL_HVCALL_PATCH(num);										\
														\
	ret = _lv1_##name(LV1_3_IN_0_OUT_ARGS);									\
														\
	_LV2_SYSCALL_HVCALL_RESTORE;										\
														\
	usleep(USLEEP_PAUSE);											\
														\
	return ret;												\
}

#define LV1_3_IN_1_OUT(name, num)										\
int64_t lv1_##name(LV1_3_IN_1_OUT_ARG_DECL)									\
{														\
	int64_t ret;												\
														\
	_LV2_SYSCALL_HVCALL_PATCH(num);										\
														\
	ret = _lv1_##name(LV1_3_IN_1_OUT_ARGS);									\
														\
	_LV2_SYSCALL_HVCALL_RESTORE;										\
														\
	usleep(USLEEP_PAUSE);											\
														\
	return ret;												\
}

#define LV1_3_IN_2_OUT(name, num)										\
int64_t lv1_##name(LV1_3_IN_2_OUT_ARG_DECL)									\
{														\
	int64_t ret;												\
														\
	_LV2_SYSCALL_HVCALL_PATCH(num);										\
														\
	ret = _lv1_##name(LV1_3_IN_2_OUT_ARGS);									\
														\
	_LV2_SYSCALL_HVCALL_RESTORE;										\
														\
	usleep(USLEEP_PAUSE);											\
														\
	return ret;												\
}

#define LV1_4_IN_0_OUT(name, num)										\
int64_t lv1_##name(LV1_4_IN_0_OUT_ARG_DECL)									\
{														\
	int64_t ret;												\
														\
	_LV2_SYSCALL_HVCALL_PATCH(num);										\
														\
	ret = _lv1_##name(LV1_4_IN_0_OUT_ARGS);									\
														\
	_LV2_SYSCALL_HVCALL_RESTORE;										\
														\
	usleep(USLEEP_PAUSE);											\
														\
	return ret;												\
}

#define LV1_4_IN_1_OUT(name, num)										\
int64_t lv1_##name(LV1_4_IN_1_OUT_ARG_DECL)									\
{														\
	int64_t ret;												\
														\
	_LV2_SYSCALL_HVCALL_PATCH(num);										\
														\
	ret = _lv1_##name(LV1_4_IN_1_OUT_ARGS);									\
														\
	_LV2_SYSCALL_HVCALL_RESTORE;										\
														\
	usleep(USLEEP_PAUSE);											\
														\
	return ret;												\
}

#define LV1_4_IN_2_OUT(name, num)										\
int64_t lv1_##name(LV1_4_IN_2_OUT_ARG_DECL)									\
{														\
	int64_t ret;												\
														\
	_LV2_SYSCALL_HVCALL_PATCH(num);										\
														\
	ret = _lv1_##name(LV1_4_IN_2_OUT_ARGS);									\
														\
	_LV2_SYSCALL_HVCALL_RESTORE;										\
														\
	usleep(USLEEP_PAUSE);											\
														\
	return ret;												\
}

#define LV1_5_IN_0_OUT(name, num)										\
int64_t lv1_##name(LV1_5_IN_0_OUT_ARG_DECL)									\
{														\
	int64_t ret;												\
														\
	_LV2_SYSCALL_HVCALL_PATCH(num);										\
														\
	ret = _lv1_##name(LV1_5_IN_0_OUT_ARGS);									\
														\
	_LV2_SYSCALL_HVCALL_RESTORE;										\
														\
	usleep(USLEEP_PAUSE);											\
														\
	return ret;												\
}

#define LV1_5_IN_1_OUT(name, num)										\
int64_t lv1_##name(LV1_5_IN_1_OUT_ARG_DECL)									\
{														\
	int64_t ret;												\
														\
	_LV2_SYSCALL_HVCALL_PATCH(num);										\
														\
	ret = _lv1_##name(LV1_5_IN_1_OUT_ARGS);									\
														\
	_LV2_SYSCALL_HVCALL_RESTORE;										\
														\
	usleep(USLEEP_PAUSE);											\
														\
	return ret;												\
}

#define LV1_5_IN_2_OUT(name, num)										\
int64_t lv1_##name(LV1_5_IN_2_OUT_ARG_DECL)									\
{														\
	int64_t ret;												\
														\
	_LV2_SYSCALL_HVCALL_PATCH(num);										\
														\
	ret = _lv1_##name(LV1_5_IN_2_OUT_ARGS);									\
														\
	_LV2_SYSCALL_HVCALL_RESTORE;										\
														\
	usleep(USLEEP_PAUSE);											\
														\
	return ret;												\
}

#define LV1_6_IN_0_OUT(name, num)										\
int64_t lv1_##name(LV1_6_IN_0_OUT_ARG_DECL)									\
{														\
	int64_t ret;												\
														\
	_LV2_SYSCALL_HVCALL_PATCH(num);										\
														\
	ret = _lv1_##name(LV1_6_IN_0_OUT_ARGS);									\
														\
	_LV2_SYSCALL_HVCALL_RESTORE;										\
														\
	usleep(USLEEP_PAUSE);											\
														\
	return ret;												\
}

#define LV1_6_IN_1_OUT(name, num)										\
int64_t lv1_##name(LV1_6_IN_1_OUT_ARG_DECL)									\
{														\
	int64_t ret;												\
														\
	_LV2_SYSCALL_HVCALL_PATCH(num);										\
														\
	ret = _lv1_##name(LV1_6_IN_1_OUT_ARGS);									\
														\
	_LV2_SYSCALL_HVCALL_RESTORE;										\
														\
	usleep(USLEEP_PAUSE);											\
														\
	return ret;												\
}

#define LV1_6_IN_2_OUT(name, num)										\
int64_t lv1_##name(LV1_6_IN_2_OUT_ARG_DECL)									\
{														\
	int64_t ret;												\
														\
	_LV2_SYSCALL_HVCALL_PATCH(num);										\
														\
	ret = _lv1_##name(LV1_6_IN_2_OUT_ARGS);									\
														\
	_LV2_SYSCALL_HVCALL_RESTORE;										\
														\
	usleep(USLEEP_PAUSE);											\
														\
	return ret;												\
}


#define LV1_6_IN_3_OUT(name, num)										\
int64_t lv1_##name(LV1_6_IN_3_OUT_ARG_DECL)									\
{														\
	int64_t ret;												\
														\
	_LV2_SYSCALL_HVCALL_PATCH(num);										\
														\
	ret = _lv1_##name(LV1_6_IN_3_OUT_ARGS);									\
														\
	_LV2_SYSCALL_HVCALL_RESTORE;										\
														\
	usleep(USLEEP_PAUSE);											\
														\
	return ret;												\
}

#define LV1_7_IN_0_OUT(name, num)										\
int64_t lv1_##name(LV1_7_IN_0_OUT_ARG_DECL)									\
{														\
	int64_t ret;												\
														\
	_LV2_SYSCALL_HVCALL_PATCH(num);										\
														\
	ret = _lv1_##name(LV1_7_IN_0_OUT_ARGS);									\
														\
	_LV2_SYSCALL_HVCALL_RESTORE;										\
														\
	usleep(USLEEP_PAUSE);											\
														\
	return ret;												\
}

#define LV1_7_IN_6_OUT(name, num)										\
int64_t lv1_##name(LV1_7_IN_6_OUT_ARG_DECL)									\
{														\
	int64_t ret;												\
														\
	_LV2_SYSCALL_HVCALL_PATCH(num);										\
														\
	ret = _lv1_##name(LV1_7_IN_6_OUT_ARGS);									\
														\
	_LV2_SYSCALL_HVCALL_RESTORE;										\
														\
	usleep(USLEEP_PAUSE);											\
														\
	return ret;												\
}

#undef LV1_HVCALL
#define LV1_HVCALL(name, in, out, num)	LV1_##in##_IN_##out##_OUT(name, num)

#include <lv1_hvcall.h>
