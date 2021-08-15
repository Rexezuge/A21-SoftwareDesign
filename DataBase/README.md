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
    cmake .   # For DEBUG Usage: cmake -DEBUG=on .
    cmake --build . && mv ./ecdb DataBase
    ```
    
## Execute

```shell
cd DataBase && ./ecdb
```

## Compile [APIDemo](apidemo.cpp) (Developers Only)

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
    g++ -std=gnu++11 apidemo.cpp -pthread -lm -g -Wall -Wextra -lhv -O2 -o demo.so
    ```

## Execute

```shell
./demo.so
```

## Reference
[libhv](https://github.com/ithewei/libhv): A C/C++ Network Library for Developing TCP/UDP/SSL/HTTP/WebSocket Client/Server.
