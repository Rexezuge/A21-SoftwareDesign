# Backend - DataBase

A DataBase System implemented with `C++`.

## Compile

- Software Requirement
```shell
Linux: G++ Version 11.1.0+
Windows: MinGW Version 9.0.0+
MacOS: G++ Version 10.1.1+
```

- [libhv](https://github.com/ithewei/libhv) Library Prerequisite

1. Initialize the submodule.

```shell
git submodule init
git submodule update
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

- Compile DataBase
```shell
AnyOS: g++ -std=gnu++11 -Werror -Wall -Wextra -lm -O2 -lhv -pthread -o EasyContact-DataBase.so DB_Main.cpp
DEBUG: g++ -std=gnu++11 -Werror -Wall -Wextra -lm -lhv -g -D DEBUG -pthread -o EasyContact-DataBase-DEBUG.so DB_Main.cpp
```

## Execute

```shell
./EasyContact-DataBase.so
```

## Reference
[libhv](https://github.com/ithewei/libhv): A C/C++ Network Library for Developing TCP/UDP/SSL/HTTP/WebSocket Client/Server.
