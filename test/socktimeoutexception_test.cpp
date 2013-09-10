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

#include "socktimeoutexception_test.h"

#include <psocksxx/socktimeoutexception.h>


// register the fixture into the 'registry'
CPPUNIT_TEST_SUITE_REGISTRATION( socktimeoutexception_test );

// use namespace psocksxx
using namespace psocksxx;


void socktimeoutexception_test::test_constructor_message() {

	std::string message = "test exception message";
	socktimeoutexception tex( message.c_str() );

	CPPUNIT_ASSERT( message == std::string( tex.what() ) );

}


void socktimeoutexception_test::test_constructor_timeout() {

	timeval t;
	t.tv_sec  = 1;
	t.tv_usec = 500;

	socktimeoutexception tex( &t );
	CPPUNIT_ASSERT( std::string( "timed out (1.500s)" ) == std::string( tex.what() ) );

}


void socktimeoutexception_test::test_constructor_timeout_method() {

	timeval t;
	t.tv_sec  = 5;
	t.tv_usec = 230;

	socktimeoutexception tex( &t, "test()" );
	CPPUNIT_ASSERT( std::string( "test() timed out (5.230s)" ) == std::string( tex.what() ) );

}

