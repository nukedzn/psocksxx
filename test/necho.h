/*
*  psocksxx - A C++ wrapper for POSIX sockets
*  Copyright (C) 2013 Uditha Atukorala
*
*  This software library is free software; you can redistribute it and/or modify
*  it under the terms of the GNU Lesser General Public License as published by
*  the Free Software Foundation; either version 3 of the License, or
*  (at your option) any later version.
*
*  This software library is distributed in the hope that it will be useful,
*  but WITHOUT ANY WARRANTY; without even the implied warranty of
*  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*  GNU Lesser General Public License for more details.
*
*  You should have received a copy of the GNU Lesser General Public License
*  along with this software library. If not, see <http://www.gnu.org/licenses/>.
*
*/

#ifndef NECHO_H
#define NECHO_H

#include <unistd.h>
#include <sys/socket.h>


class necho {
public:

	necho( const char * node, const char * service, int socket_type = SOCK_STREAM );
	virtual ~necho();

protected:

	int _sockfd;
	pid_t _cpid;

	const char * _nsock_node;
	const char * _nsock_service;

	int _socket_type;

	void init_signal_handlers();
	void init_listener();
	void serve_requests();
	void shutdown();
	void wait_connect();

};

#endif /* !NECHO_H */

