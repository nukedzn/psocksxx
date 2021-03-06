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

#ifndef UDPNSOCKSTREAM_TEST_H
#define UDPNSOCKSTREAM_TEST_H

#include <cppunit/extensions/HelperMacros.h>


class udpnsockstream_test : public CppUnit::TestFixture {

	// setup the test suite
	CPPUNIT_TEST_SUITE( udpnsockstream_test );
	CPPUNIT_TEST( test_constructors );
	CPPUNIT_TEST_SUITE_END();

public:

	void test_constructors();

};

#endif /* !UDPNSOCKSTREAM_TEST_H */

