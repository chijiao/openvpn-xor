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

#ifndef OPENVPN_XOR_SOCKET_H
#define OPENVPN_XOR_SOCKET_H
#include "buffer.h"
#include "common.h"
#include "socket.h"
#include "options.h"

int
link_socket_write_xor (struct link_socket *sock,
		struct buffer *buf,
		struct link_socket_actual *to,
		const struct options opt);



int
link_socket_read_xor (struct link_socket *sock,
		struct buffer *buf,
		int maxsize,
		struct link_socket_actual *from,
		const struct options opt);


#endif
