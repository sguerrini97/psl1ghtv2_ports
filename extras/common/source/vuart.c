
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

#include <lv2_syscall.h>
#include <lv1_hvcall.h>
#include <vuart.h>

int vuart_wait_for_rx_data(u64 port)
{
	u64 val;
	int result;

	for (;;)
	{
		result = lv1_get_virtual_uart_param(port, VUART_PARAM_RX_BYTES, &val);
		if (result < 0)
			return result;

		if (val != 0)
			break;
	}

	return val;
}
