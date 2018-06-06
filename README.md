# About

This is the C and C++ client for the Nano Node API. The message format is Proto Buffer v3 and the client supports domain socket and TCP transports. Additional transports, such as shared memory, may be added in the future.

For more information about the API, please see https://nanoapi.github.io/

## Building

[![Build status](https://ci.appveyor.com/api/projects/status/miyhcdcdm5wxpm8j?svg=true)](https://ci.appveyor.com/project/cryptocode/api-c) [![Build Status](https://travis-ci.org/nanoapi/api-c.svg?branch=master)](https://travis-ci.org/nanoapi/api-c)

Clone the repository and update submodules.

```
git clone https://github.com/nanoapi/api-c.git
cd api-c
git submodule update --init --recursive
```

The project is built with CMake. Boost and Protobuf are automatically downloaded and built using the Hunter package manager, while protobuf-c is automatically built using CMake (which was pulled in using the command above)

### Linux

```
cmake -H. -Bbuild -DHUNTER_STATUS_DEBUG=ON -Dprotobuf_BUILD_TESTS=OFF -Dprotobuf_c_BUILD_TESTS=OFF  -DCMAKE_BUILD_TYPE=Debug
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

### Updating generated Protobuffer files

If the `nanoapi/protobuf` repository is updated, new Protobuf files needs to be generated.

Make sure `protobuf` and `protobuf-c` are installed.

When the protobuffer definition has changed, perform the following step to fetch the latest version and generate C and C++ files:

```
scripts/protobuf-generate.sh
```
