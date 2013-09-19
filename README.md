psocksxx
========

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


### Dependencies

* CppUnit >= 1.12.1 (for unit tests)
* Doxygen (for doxygen documentation, of course)


### Bugs and Feature Requests

Please report all bugs and feature requests in [bugzilla](http://bugs.geniusse.com/) under the
[psocksxx](http://bugs.geniusse.com/enter_bug.cgi?product=psocksxx) project.
Known issues can be found [here](http://bugs.geniusse.com/buglist.cgi?query_format=specific&order=relevance%20desc&bug_status=__open__&product=psocksxx&list_id=130).


### Version history

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

Or you can grab the latest source distribution tar from [CI artifacts](http://jenkins.geniusse.com/job/psocksxx/).

After that you can use the usual `./configure && make`


### Notes
#### Continuous Integration

There is a continuous integration Jenkins job hosted [here](http://jenkins.geniusse.com/job/psocksxx/)
which contains the latest artifacts, unit test results and documentation etc.


#### Doxygen documentation

The latest doxygen documentation can be found at http://jenkins.geniusse.com/job/psocksxx/doxygen/.

