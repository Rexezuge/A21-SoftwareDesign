# Backend - DataBase

A DataBase System implemented with `C++`.

## Compile

Software Requirement
```shell
Linux: G++ Version 11.1.0+
Windows: MinGW Version 9.0.0+
MacOS: G++ Version 10.1.1+
```

[libhv](https://github.com/ithewei/libhv) Libiary Prerequisite

1. Clone the [libhv](https://github.com/ithewei/libhv) Repository.

_NOTE: Tested with Commit [a4b7e73](https://github.com/ithewei/libhv/commit/a4b7e730a60e074cec8166b16f5ec3dd3c4dfd74)_
```shell
git clone https://github.com/ithewei/libhv.git
```

2. Change Directory
```shell
cd ./libhv
```

3. Install [libhv](https://github.com/ithewei/libhv) Library

_NOTE: System Root Permission is Required._
```shell
./configure
make
sudo make install
```

Compile
```shell
AnyOS: g++ -std=gnu++11 -Werror -Wall -Wextra -lm -O2 -I/usr/local/include/hv -lhv -pthread -o EasyContact-DataBase.so DB_Main.cpp DB_Export.cpp
DEBUG: g++ -std=gnu++11 -Werror -Wall -Wextra -lm -I/usr/local/include/hv -lhv -g -D DEBUG -pthread -o EasyContact-DataBase-DEBUG.so DB_Main.cpp DB_Export.cpp
```

## Execute

```shell
./EasyContact-DataBase.so
```

## Reference
[libhv](https://github.com/ithewei/libhv): A C/C++ Network Library for Developing TCP/UDP/SSL/HTTP/WebSocket Client/Server.
