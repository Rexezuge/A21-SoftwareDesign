# Backend - DataBase

A DataBase System implemented with `C++`.

## Compile

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
    cmake -DEBUG .   # Eliminate -DEBUG in production
    cmake --build .
    ```

## Execute

```shell
./ecdb
```

## Reference
[libhv](https://github.com/ithewei/libhv): A C/C++ Network Library for Developing TCP/UDP/SSL/HTTP/WebSocket Client/Server.
