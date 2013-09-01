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

#ifndef LECHO_H
#define LECHO_H

#include <unistd.h>


class lecho {
public:
	lecho( const char * path );
	~lecho();

private:
	int _sockfd;
	pid_t _cpid;
	const char * _lsock_path;

	void init_listener();
	void serve_requests();
	void shutdown();
	void wait_connect();

};

#endif /* !LECHO_H */

