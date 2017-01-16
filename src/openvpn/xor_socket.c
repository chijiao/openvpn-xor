/*
 *  OpenVPN -- An application to securely tunnel IP networks
 *             over a single UDP port, with support for SSL/TLS-based
 *             session authentication and key exchange,
 *             packet encryption, packet authentication, and
 *             packet compression.
 *
 *  Copyright (C) 2015 SUMOMO Computer Association ayaka<ayaka@soulik.info>
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License version 2
 *  as published by the Free Software Foundation.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program (see the file COPYING included with this
 *  distribution); if not, write to the Free Software Foundation, Inc.,
 *  59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */
#ifdef HAVE_CONFIG_H
#include "config.h"
#elif defined(_MSC_VER)
#include "config-msvc.h"
#endif

#include "syshead.h"

#include "buffer.h"
#include "xor.h"
#include "xor_socket.h"

static void
append_padding(struct buffer *buf, const char *padding)
{
	const char *data = BPTR(buf);

	if (NULL == padding)
		return;
	const int32_t length = strlen(padding);

	memcpy(data + BLEN(buf), padding, length);
	buf->len += length;
}

static void
remove_padding(struct buffer *buf, const char *padding)
{
	if (NULL == padding)
		return;

	const int32_t length = strlen(padding);
	buf->len -= length;
}

int
link_socket_write_xor (struct link_socket *sock,
		struct buffer *buf,
		struct link_socket_actual *to,
		const struct options opt)
{
  const char *xor_key = opt.xor_secret;
  const char *padding = opt.padding;
  
  append_padding(buf, padding);
  xor_encode(BPTR(buf), BLEN(buf), xor_key);

  return link_socket_write(sock, buf, to);
}



int
link_socket_read_xor (struct link_socket *sock,
		struct buffer *buf,
		int maxsize,
		struct link_socket_actual *from,
		const struct options opt)
{
  const char *xor_key = opt.xor_secret;
  const char *padding = opt.padding;
  int size;

  size = link_socket_read(sock, buf, maxsize, from);
  remove_padding(buf, padding);
  xor_encode(BPTR(buf), BLEN(buf), xor_key);

  return BLEN(buf);
}

