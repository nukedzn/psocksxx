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

#ifndef SOCKTIMEOUTEXCEPTION_TEST_H
#define SOCKTIMEOUTEXCEPTION_TEST_H

#include <cppunit/extensions/HelperMacros.h>


class socktimeoutexception_test : public CppUnit::TestFixture {

	// setup the test suite
	CPPUNIT_TEST_SUITE( socktimeoutexception_test );
	CPPUNIT_TEST( test_constructor_message );
	CPPUNIT_TEST( test_constructor_timeout );
	CPPUNIT_TEST( test_constructor_timeout_method );
	CPPUNIT_TEST_SUITE_END();

public:

	void test_constructor_message();
	void test_constructor_timeout();
	void test_constructor_timeout_method();

};

#endif /* !SOCKTIMEOUTEXCEPTION_TEST_H  */

