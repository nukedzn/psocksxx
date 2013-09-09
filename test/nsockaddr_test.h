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

#ifndef NSOCKADDR_TEST_H
#define NSOCKADDR_TEST_H

#include <cppunit/extensions/HelperMacros.h>


class nsockaddr_test : public CppUnit::TestFixture {

	// setup the test suite
	CPPUNIT_TEST_SUITE( nsockaddr_test );
	CPPUNIT_TEST( test_constructor_localhost );
	CPPUNIT_TEST( test_constructor_remote );
	CPPUNIT_TEST( test_constructor_fail );
	CPPUNIT_TEST( test_constructor_local_any );
	CPPUNIT_TEST( test_constructor_local_service );
	CPPUNIT_TEST( test_constructor_remote_service );
	CPPUNIT_TEST_SUITE_END();

public:

	void test_constructor_localhost();
	void test_constructor_remote();
	void test_constructor_fail();
	void test_constructor_local_any();
	void test_constructor_local_service();
	void test_constructor_remote_service();

};

#endif /* !NSOCKADDR_TEST_H */

