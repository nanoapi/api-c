# About

This is the C and C++ client for the Nano Node API. The message format is Proto Buffer v3 and the client supports domain socket and TCP transports.

For more information about the API, please see https://nanoapi.github.io/

### Updating generated Protobuffer files

When the protobuffer definition has changed, run the following command to fetch the latest version and generate C and C++ files:

```
ci/protobuf-gen.sh
```

Rebuild the project.

#### New .proto files

If the Node repository adds new .proto files, follow these steps:

* Update ci/protobuf-c.sh and ci/protobuf-cpp.sh to handle the files (automating this is a TODO)
* Run cmake and rebuild.

## Building

[![Build status](https://ci.appveyor.com/api/projects/status/miyhcdcdm5wxpm8j?svg=true)](https://ci.appveyor.com/project/cryptocode/api-c) [![Build Status](https://travis-ci.org/nanoapi/api-c.svg?branch=master)](https://travis-ci.org/nanoapi/api-c)

Clone the repository and update submodules.

```
git clone https://github.com/nanoapi/api-c.git
cd api-c
git submodule update --init --recursive
```

The project is built with CMake. Boost and Protobuf are automatically downloaded and built using the Hunter package manager, while the protobuf-c submodule is built using CMake.

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

### Release builds

Replace `-DCMAKE_BUILD_TYPE=Debug` with `-DCMAKE_BUILD_TYPE=Release` and rebuild the project.
