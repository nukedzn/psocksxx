/*
*  psocksxx - A C++ wrapper for POSIX sockets
*  Copyright (C) 2013-2015 Uditha Atukorala
*
*  This file is part of psocksxx software library.
*
*  psocksxx software library is free software; you can redistribute it and/or modify
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


#include <iostream>
#include <string>
#include <psocksxx/tcpnsockstream.h>


int main() {

	// tcp socket stream
	psocksxx::tcpnsockstream ss;

	// connect
	try {
		ss.connect( "localhost", 21555 );
	} catch ( psocksxx::sockexception &e ) {
		std::cerr << "[client] failed to connect to socket, exception" << e.what() << std::endl;
		return 1;
	}

	// send a message
	ss << "hello" << std::endl;

	// get the echo back from server
	std::string msg;
	ss >> msg;

	// print message
	std::cout << "[server] " << msg << std::endl;

	return 0;

}

