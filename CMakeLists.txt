cmake_minimum_required(VERSION 3.7.1)
include("cmake/HunterGate.cmake")

# Make sure we get reproducible builds by using a specific Hunter version
HunterGate(
    URL "https://github.com/ruslo/hunter/archive/v0.22.0.tar.gz"
    SHA1 "f91a01c6e0eb53b1dc55a6442cd93580db91da07"
)

project (nano-api-c)
set(CMAKE_CXX_STANDARD 14)

if (UNIX AND NOT APPLE)
    set(CMAKE_CXX_FLAGS "-fPIC" CACHE STRING "CMAKE_CXX_FLAGS")
endif ()

# Get Boost
hunter_add_package(Boost COMPONENTS regex system filesystem)
find_package(Boost CONFIG REQUIRED regex system filesystem)

# Get profobuf
# NOTE: On some systems, you may need to change "Protobuf" to "protobuf"
hunter_add_package(protobuf)
find_package(protobuf CONFIG REQUIRED)
hunter_add_package(protobuf-c)
find_package(protobuf-c REQUIRED)

# Client library, build both static and dynamic libs
set (NANO_API_SRC
    include/nano.h
    src/google/protobuf/wrappers.pb-c.c
    src/google/protobuf/wrappers.pb-c.h
    src/core.pb-c.c
    include/core.pb-c.h
    src/nano.cpp)

add_library(nanoclient SHARED ${NANO_API_SRC})
add_library(nanoclient_static STATIC ${NANO_API_SRC})

set_property(TARGET nanoclient PROPERTY POSITION_INDEPENDENT_CODE ON)
target_link_libraries(nanoclient Boost::system protobuf::libprotobuf protobuf-c::protobuf-c)
target_link_libraries(nanoclient_static Boost::system protobuf::libprotobuf protobuf-c::protobuf-c)

target_include_directories(nanoclient PUBLIC src)
target_include_directories(nanoclient PUBLIC include)
target_include_directories(nanoclient_static PUBLIC src)
target_include_directories(nanoclient_static PUBLIC include)

# Build example
add_executable(example-socket-client examples/example-socket-client.c)
target_link_libraries(example-socket-client PUBLIC nanoclient_static Boost::regex Boost::system Boost::filesystem)
