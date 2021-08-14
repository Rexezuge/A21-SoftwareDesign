# Backend - DataBase

A DataBase System implemented with `C++`.

## Compile With CMake

- Software Requirement
    ```shell
    Linux: G++ Version 11.1.0+
    Windows: MinGW Version 9.0.0+
    MacOS: G++ Version 10.1.1+
    ```

- [libhv](https://github.com/ithewei/libhv) Submodule Initialization

    ```shell
    git submodule update --init --recursive
    ```

- Compile DataBase

    ```shell
    cmake .   # For DEBUG Usage: cmake -DEBUG=on .
    cmake --build .
    ```

## Compile [APIDemo](apidemo.cpp)

- Initialize Submodule

    ```shell
    git submodule update --init --recursive
    ```

- Compile [libhv](https://github.com/ithewei/libhv)

    ```shell
    cd DataBase/libhv
    ./configure
    make
    sudo make install
    ```

- Compile [APIDemo](apidemo.cpp)

    ```shell
    cd ..
    g++ -std=gnu++11 apidemo.cpp -pthread -lm -g -Wall -Wextra -lhv
    ```

## Execute

```shell
./ecdb
```

## Reference
[libhv](https://github.com/ithewei/libhv): A C/C++ Network Library for Developing TCP/UDP/SSL/HTTP/WebSocket Client/Server.
