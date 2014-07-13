
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

#include <udp_printf.h>

#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <unistd.h>

#include <net/net.h>
#include <netinet/in.h>

#define UDP_PORT		9999

static int sock;

/*
 * udp_printf_init
 */
int udp_printf_init(void)
{
	int error, broadcast;
        struct sockaddr_in sockaddr;

	sock = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);
        if (sock < 0)
                return sock;

	broadcast = 1;
	error = setsockopt(sock, SOL_SOCKET, SO_BROADCAST, &broadcast, sizeof(broadcast));
	if (error)
		goto failed;

        memset(&sockaddr, 0, sizeof(sockaddr));
        sockaddr.sin_len = sizeof(sockaddr);
        sockaddr.sin_family = AF_INET;
        sockaddr.sin_addr.s_addr = htonl(INADDR_BROADCAST);
        sockaddr.sin_port = htons(UDP_PORT);

	error = connect(sock, (const struct sockaddr *) &sockaddr, sizeof(sockaddr));
	if (error)
		goto failed;

	return 0;

failed:

	if (sock >= 0) {
		close(sock);
		sock = -1;
	}

	return error;
}

/*
 * udp_printf_deinit
 */
void udp_printf_deinit(void)
{
	if (sock >= 0)
		close(sock);
}

/*
 * udp_printf
 */
int udp_printf(const char *fmt, ...)
{
	char buf[4096];
	va_list ap;

	if (sock < 0)
		return -1;

	va_start(ap, fmt);

	vsnprintf(buf, sizeof(buf), fmt, ap);

	va_end(ap);

	return write(sock, buf, strlen(buf));
}
