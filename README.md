# About

This is the C client for the Nano Node API. The message format is protobuffer v3 and the client supports domain socket and TCP transports. Additional transports, such as shared memory, may be added in the future.

## Building

[![Build status](https://ci.appveyor.com/api/projects/status/miyhcdcdm5wxpm8j?svg=true)](https://ci.appveyor.com/project/cryptocode/api-c)


Clone the repository and update submodules.

```
git clone https://github.com/nanoapi/api-c.git
cd api-c
git submodule update --init --recursive
```

Make sure `protoc` and `proto-gen-c` are on the path.

Build with CMake. For instance, on a Unix-like OS, run:

```
cmake -H. -Bbuild -DHUNTER_STATUS_DEBUG=ON -DCMAKE_BUILD_TYPE=Debug
cd build && make
```

Dependencies such as Boost and Protobuf are automatically downloaded and built using the Hunter package manager.

## Updating generated Protobuffer files

When the protobuffer definition has changed, perform the following steps to fetch the latest version and generate C and header files:

```
git submodule foreach git pull origin master
./protobuf-c.sh
```
