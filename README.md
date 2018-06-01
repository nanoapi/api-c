# About

This is the C and C++ client for the Nano Node API. The message format is protobuffer v3 and the client supports domain socket and TCP transports. Additional transports, such as shared memory, may be added in the future.

## Building

[![Build status](https://ci.appveyor.com/api/projects/status/miyhcdcdm5wxpm8j?svg=true)](https://ci.appveyor.com/project/cryptocode/api-c)

Clone the repository and update submodules.

```
git clone https://github.com/nanoapi/api-c.git
cd api-c
git submodule update --init --recursive
```

The project is built with CMake. Dependencies such as Boost and Protobuf are automatically downloaded and built using the Hunter package manager.

### Linux 

```
cmake -H. -Bbuild -DHUNTER_STATUS_DEBUG=ON -Dprotobuf_BUILD_TESTS=OFF -Dprotobuf_c_BUILD_TESTS=OFF -DCMAKE_BUILD_TYPE=Debug
cd build && make
```

### macOS

```
cmake -H. -Bbuild -DHUNTER_STATUS_DEBUG=ON -Dprotobuf_BUILD_TESTS=OFF -Dprotobuf_c_BUILD_TESTS=OFF -DCMAKE_BUILD_TYPE=Debug
cd build && make
```

Not that some system are case sensitive regarding the Protbuf package. Try switching from "Protobuf" to "protobuf" in the CMake file if the package is not found.

### Windows

Use the "Developer Command Prompt for VS 2017"

```
cmake -G "Visual Studio 15 2017 Win64" -DHUNTER_STATUS_DEBUG=ON -Dprotobuf_BUILD_TESTS=OFF -Dprotobuf_c_BUILD_TESTS=OFF -DCMAKE_BUILD_TYPE=Debug
```

## Updating generated Protobuffer files

Make sure `protoc` and `proto-gen-c` are on the path.

When the protobuffer definition has changed, perform the following steps to fetch the latest version and generate C and header files:

```
cd protobuf
git checkout master
git pull
cd ..
./protobuf-c.sh
./protobuf-cpp.sh
```
