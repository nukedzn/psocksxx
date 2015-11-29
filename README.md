psocksxx
========

[![GitHub release](https://img.shields.io/github/release/nukedzn/psocksxx.svg)](https://github.com/nukedzn/psocksxx/releases)
[![Build Status](https://travis-ci.org/nukedzn/psocksxx.svg)](https://travis-ci.org/nukedzn/psocksxx)

A C++ wrapper for POSIX sockets

## Copyright and License

Copyright (C) 2013-2015 Uditha Atukorala.

This software library is free software; you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation; either version 3 of the License, or
(at your option) any later version.

This software library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
[GNU Lesser General Public License](http://www.gnu.org/licenses/lgpl.html)
for more details.


## The Concept

This project was started to add to the features provided by the simple
[socket-library](https://github.com/uditha-atukorala/socket-library) project,
specially socket timeouts. But rather than sticking to the same class structure
it was decided to use [stream buffers](http://gcc.gnu.org/onlinedocs/libstdc++/manual/streambufs.html)
in C++ standard library.

The inspiration to derive from std::streambuf came from the [socket++](http://www.linuxhacker.at/socketxx)
library initially developed by Gnanasekaran Swaminathan. While the
socket++ library seems to be stable and feature rich, the coding style
and the lack of API documentation makes it a little difficult for the
beginners.

psocksxx library attempts to borrow the concepts from socket++ and
socket-library, but not the code, and create a well documented (and
hopefully easy to understand) POSIX socket communication wrapper in
C++. To keep the code simple and clean this project will only support
POSIX sockets.


## Downloads

You can download source distributions from https://github.com/nukedzn/psocksxx/releases.


### Debian/Ubuntu packages

Please check availability for your distribution first ([Debian](https://packages.debian.org/psocksxx), [Ubuntu](http://packages.ubuntu.com/psocksxx)).

	$ sudo aptitude update
	$ sudo aptitude install libpsocksxx-dev


## Dependencies

* CppUnit >= 1.12.1 (for unit tests)
* Doxygen (for doxygen documentation, of course)


## Bugs and Feature Requests

Please report all bugs and feature requests under [issues](https://github.com/nukedzn/psocksxx/issues).


## Compiling from source

If you are using the github source then first you need to initialise
autotools.

	$ libtoolize (glibtoolize in OS X)
	$ aclocal
	$ autoheader
	$ autoconf
	$ automake --add-missing (you will need automake >= 1.13)

After that you can use the usual `./configure && make`


## Usage

Please take a look at [examples](https://github.com/nukedzn/psocksxx/tree/master/src/examples)
for more details.

### Simple Server

``` c++

// tcp socket stream
psocksxx::tcpnsockstream ss;

// network address to bind to
psocksxx::nsockaddr naddr( "localhost", "21555" );

// bind and listen
ss.bind( &naddr, true );
ss.listen();

// accept a connection
psocksxx::nsockstream * css = ss.accept();

```

### Simple Client

``` c++
// tcp socket stream
psocksxx::tcpnsockstream ss;

// connect
ss.connect( "localhost", 21555 );

// send a message
ss << "hello" << std::endl;

// receive a message
std::string msg;
ss >> msg;
```


## API Documentation

* [v1.0](https://nukedzn.github.io/psocksxx/docs/v1.0)

