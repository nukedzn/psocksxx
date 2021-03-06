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

#ifndef NSOCKSTREAM_TEST_H
#define NSOCKSTREAM_TEST_H

#include <cppunit/extensions/HelperMacros.h>


class nsockstream_test : public CppUnit::TestFixture {

	// setup the test suite
	CPPUNIT_TEST_SUITE( nsockstream_test );
	CPPUNIT_TEST( test_constructor_tcp );
	CPPUNIT_TEST( test_constructor_udp );
	CPPUNIT_TEST( test_constructor_streambuf );
	CPPUNIT_TEST( test_set_timeout );
	CPPUNIT_TEST( test_clear_timeout );
	CPPUNIT_TEST_SUITE_END();

public:

	void test_constructor_tcp();
	void test_constructor_udp();
	void test_constructor_streambuf();
	void test_set_timeout();
	void test_clear_timeout();

};

#endif /* !NSOCKSTREAM_TEST_H */

