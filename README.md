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


