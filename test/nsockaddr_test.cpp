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

#include "nsockaddr_test.h"

#include <psocksxx/nsockaddr.h>
#include <iostream>


// register the fixture into the 'registry'
CPPUNIT_TEST_SUITE_REGISTRATION( nsockaddr_test );

// use namespace psocksxx
using namespace psocksxx;


void nsockaddr_test::test_constructor_localhost() {

	CPPUNIT_ASSERT_NO_THROW( nsockaddr a( "localhost", 1234 ) );
	CPPUNIT_ASSERT_NO_THROW( nsockaddr a( "127.0.0.1", 4321 ) );

}


void nsockaddr_test::test_constructor_remote() {

	CPPUNIT_ASSERT_NO_THROW( nsockaddr a( "www.example.com", 1234 ) );
	CPPUNIT_ASSERT_NO_THROW( nsockaddr a( "1.2.3.4", 80 ) );

}


void nsockaddr_test::test_constructor_fail() {

	CPPUNIT_ASSERT_THROW( nsockaddr a( "invalid.domain", 1234 ), sockexception );
	CPPUNIT_ASSERT_THROW( nsockaddr a( "1.2.3.", 1234 ), sockexception );

}


void nsockaddr_test::test_constructor_local_any() {

	CPPUNIT_ASSERT_NO_THROW( nsockaddr a( 1234 ) );

}


void nsockaddr_test::test_constructor_local_service() {

	CPPUNIT_ASSERT_NO_THROW( nsockaddr a( "localhost", "1234" ) );
	CPPUNIT_ASSERT_NO_THROW( nsockaddr a( NULL, "ftp" ) );

}


void nsockaddr_test::test_constructor_remote_service() {

	CPPUNIT_ASSERT_NO_THROW( nsockaddr a( "www.example.com", "http" ) );

}

