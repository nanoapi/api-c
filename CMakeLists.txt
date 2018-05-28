cmake_minimum_required(VERSION 3.7.1)
include("cmake/HunterGate.cmake")

# Make sure we get reproducible builds by using a specific Hunter version
HunterGate(
    URL "https://github.com/ruslo/hunter/archive/v0.21.19.tar.gz"
    SHA1 "5ead1e069b437930d0de8a21824b20fb52b37b50"
)

project (nano-api-c)
set(CMAKE_CXX_STANDARD 14)

# Get Boost
hunter_add_package(Boost COMPONENTS regex system filesystem)
find_package(Boost CONFIG REQUIRED regex system filesystem)

# Get profobuf
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
target_link_libraries(nanoclient Boost::system protobuf::libprotobuf protobuf-c::protobuf-c)
target_link_libraries(nanoclient_static Boost::system protobuf::libprotobuf protobuf-c::protobuf-c)

target_include_directories(nanoclient PUBLIC src)
target_include_directories(nanoclient PUBLIC include)
target_include_directories(nanoclient_static PUBLIC src)
target_include_directories(nanoclient_static PUBLIC include)

# Test client
add_executable(example-socket-client examples/example-socket-client.c)
target_link_libraries(example-socket-client PUBLIC nanoclient_static Boost::regex Boost::system Boost::filesystem)
