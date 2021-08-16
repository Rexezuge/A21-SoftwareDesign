# Backend - DataBase

A DataBase System implemented with `C++`.

## Software Requirement

    ```shell
    Linux: G++ Version 11.1.0+; CMake Version 3.5.0+
    Windows: MinGW Version 9.0.0+; CMake Version 3.5.0+
    MacOS: G++ Version 10.1.1+; CMake Version 3.5.0+
    ```

## Compile With CMake

- [libhv](https://github.com/ithewei/libhv) Submodule Initialization

    ```shell
    git submodule update --init --recursive
    ```

- Compile DataBase

    ```shell
    cd DataBase
    cmake ..   # For DEBUG Usage: cmake -DEBUG=on .
    cmake --build ..
    ```

- Execute

    ```shell
    ./ecdb
    ```

## Compile [APIDemo](apidemo.cpp) (Developers Only)

_API Demo IS NOW REMOVED, ROLL BACK TO PREVIOUS COMMITS IF NECESSARY TO CHECKOUT API Demo_

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
    g++ -std=gnu++11 apidemo.cpp -pthread -lm -g -Wall -Wextra -lhv -Og -o APIDemo.so
    ```

- Execute

    ```shell
    ./APIDemo.so
    ```

## Reference
[libhv](https://github.com/ithewei/libhv): A C/C++ Network Library for Developing TCP/UDP/SSL/HTTP/WebSocket Client/Server.
