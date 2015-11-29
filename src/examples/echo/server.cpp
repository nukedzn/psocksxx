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


int main( int argc, char **argv ) {

	// tcp socket stream
	psocksxx::tcpnsockstream ss;

	// network address to bind to
	psocksxx::nsockaddr naddr( "localhost", "21555" );

	// bind
	try {
		ss.bind( &naddr, true );
	} catch( psocksxx::sockexception &e ) {
		std::cerr << "[server] failed to bind to socket, exception: " << e.what() << std::endl;
		return 1;
	}

	// listen
	try {
		ss.listen();
	} catch( psocksxx::sockexception &e ) {
		std::cerr << "[server] failed to listen on socket, exception: " << e.what() << std::endl;
		return 1;
	}


	// client socket stream
	psocksxx::nsockstream * css;

	// message buffer
	std::string msg;

	for (;;) {

		// accept a new client
		css = ss.accept();

		(* css) >> msg;
		std::cout << "[client] " << msg << std::endl;

		// echo back
		(* css) << msg << std::endl;

		// close/cleanup client
		delete css;

	}

	return 0;

}

