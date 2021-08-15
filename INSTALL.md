# Installation

This guide will walk through the installation process.

## BackEnd

```shell
git submodule update --init --recursive
cmake .
cmake --build . && mv ./ecdb DataBase
```

## FrontEnd

```shell
npm install
npm install node-fetch
```

## Execute

```shell
cd DataBase && ./ecdb &
cd ../Web && node server.js
```

## Terminate

Use `Ctrl+C` to terminate the application.
