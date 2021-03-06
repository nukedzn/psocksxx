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

#include "udpnsockstream_test.h"

#include <psocksxx/udpnsockstream.h>


// register the fixture into the 'registry'
CPPUNIT_TEST_SUITE_REGISTRATION( udpnsockstream_test );

// use namespace psocksxx
using namespace psocksxx;


void udpnsockstream_test::test_constructors() {

	// default constructor
	CPPUNIT_ASSERT_NO_THROW( udpnsockstream ss );

}

