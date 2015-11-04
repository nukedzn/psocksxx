psocksxx
========

[![Build Status](https://travis-ci.org/nukedzn/psocksxx.svg)](https://travis-ci.org/nukedzn/psocksxx)

A C++ wrapper for POSIX sockets

### Copyright and License

Copyright (C) 2013 Uditha Atukorala.

This software library is free software; you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation; either version 3 of the License, or
(at your option) any later version.

This software library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
[GNU Lesser General Public License](http://www.gnu.org/licenses/lgpl.html)
for more details.


### The Concept

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


### Downloads
You can download source distributions from https://github.com/nukedzn/psocksxx/releases.


#### Debian/Ubuntu packages

	$ sudo aptitude update
	$ sudo aptitude install libpsocksxx-dev

*Note:* Check availability for your distribution first ([Debian](https://packages.debian.org/search?searchon=names&keywords=psocksxx), [Ubuntu](http://packages.ubuntu.com/search?suite=wily&section=all&arch=any&keywords=psocksxx&searchon=names)).

### Dependencies

* CppUnit >= 1.12.1 (for unit tests)
* Doxygen (for doxygen documentation, of course)


### Bugs and Feature Requests

Please report all bugs and feature requests under [Issues](https://github.com/nukedzn/psocksxx/issues).


### Version history

__0.0.6__ - _03rd October 2014_
*   Removing obsolete doxygen tags

__0.0.5__ - _29th June 2014_
*   Fixing inconsistent timeout behaviour on different systems

__0.0.4__ - _10th November 2013_
*   bug fix - member functions should not be throwing exceptions if the
	signature does not specify it.

__0.0.3__ - _31st October 2013_
*   Suppress SIGPIPE signals
*   Code cleanup work

__0.0.2__ - _29th September 2013_
*   Added timeout support for socket communications
*   New base socket stream I/O class to reduce redundant code
*   Added install targets for doxygen generated docs

__0.0.1__ - _19th September 2013_
*   Initial release


### Compiling from source

If you are using the github source then first you need to initialise
autotools.

	$ libtoolize (glibtoolize in OS X)
	$ aclocal
	$ autoheader
	$ autoconf
	$ automake --add-missing (you will need automake >= 1.13)

Or you can grab the latest snapshot tar from [CI artifacts](http://jenkins.geniusse.com/job/psocksxx/).

After that you can use the usual `./configure && make`


### Notes
#### Continuous Integration

There is a continuous integration Jenkins job hosted [here](http://jenkins.geniusse.com/job/psocksxx/)
which contains the latest artifacts, unit test results and documentation etc.


#### Doxygen documentation

The latest doxygen documentation can be found at http://jenkins.geniusse.com/job/psocksxx/doxygen/.

