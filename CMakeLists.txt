cmake_minimum_required(VERSION 3.7.1)
include("cmake/HunterGate.cmake")
#include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)

# Make sure we get reproducible builds by using a specific Hunter version
HunterGate(
    URL "https://github.com/ruslo/hunter/archive/v0.22.0.tar.gz"
    SHA1 "f91a01c6e0eb53b1dc55a6442cd93580db91da07"
)

project (nano-api-c)
set(CMAKE_CXX_STANDARD 14)

# This prevents relocation issues with the shared library on Linux by adding -fPIC
if (UNIX AND NOT APPLE)
    set(
        CMAKE_TOOLCHAIN_FILE
        "${CMAKE_CURRENT_LIST_DIR}/toolchain-gcc-pic.cmake"
        CACHE
        FILEPATH
        "Default toolchain"
    )
#elseif(WIN32)
#    set(
#        CMAKE_TOOLCHAIN_FILE
#        "${CMAKE_CURRENT_LIST_DIR}/toolchain-msvc.cmake"
#        CACHE
#        FILEPATH
#        "Default toolchain"
#    )
endif ()

# Get Boost
hunter_add_package(Boost COMPONENTS regex system filesystem)
find_package(Boost CONFIG REQUIRED regex system filesystem)

# Get profobuf
# NOTE: On some systems, you may need to change "Protobuf" to "protobuf"
hunter_add_package(Protobuf)
find_package(Protobuf CONFIG REQUIRED)
#hunter_add_package(protobuf-c)
#find_package(protobuf-c CONFIG REQUIRED)

#set (protobuf_BUILD_TESTS OFF)
#add_subdirectory("fork-protobuf/cmake") # EXCLUDE_FROM_ALL)
#set (PROTOBUF_LIBRARY "libprotobuf")

#message(STATUS "Modules CMake : ${CMAKE_MODULE_PATH}")
#add_subdirectory("fork-protobuf-c/build-cmake") # EXCLUDE_FROM_ALL)
#set (PROTOBUF_C_LIBRARY "protobuf-c")

# Client library, build both static and dynamic libs
set (NANO_API_SRC
    include/nano.h
    include/core.pb-c.h
    include/core.pb.h
    src/google/protobuf/wrappers.pb-c.c
    src/google/protobuf/wrappers.pb-c.h
    src/google/protobuf/wrappers.pb.cc
    src/google/protobuf/wrappers.pb.h
    src/core.pb-c.c
    src/core.pb.cc
    src/nano.cpp)

set (PROTOBUF_C_SRC
    fork-protobuf-c/protobuf-c/protobuf-c.h
    fork-protobuf-c/protobuf-c/protobuf-c.c)

# TODO: separate libs for C and C++?
add_library(nanoclient SHARED ${NANO_API_SRC} ${PROTOBUF_C_SRC})
add_library(nanoclient_static STATIC ${NANO_API_SRC} ${PROTOBUF_C_SRC})

#set_property(TARGET nanoclient PROPERTY POSITION_INDEPENDENT_CODE ON)
target_link_libraries(nanoclient Boost::system  protobuf::libprotobuf)# protobuf::libprotobuf protobuf-c::protobuf-c)
target_link_libraries(nanoclient_static Boost::system protobuf::libprotobuf)# protobuf::libprotobuf protobuf-c::protobuf-c)

target_include_directories(nanoclient PUBLIC src)
target_include_directories(nanoclient PUBLIC include)
target_include_directories(nanoclient_static PUBLIC src)
target_include_directories(nanoclient_static PUBLIC include)

# Build C example
add_executable(example-socket-client examples/example-socket-client.c)
target_link_libraries(example-socket-client PUBLIC nanoclient_static Boost::regex Boost::system Boost::filesystem)

# Build C++ example
add_executable(example-socket-client-cpp examples/example-socket-client.cpp)
target_link_libraries(example-socket-client-cpp PUBLIC nanoclient_static Boost::regex Boost::system Boost::filesystem)
