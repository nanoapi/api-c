cmake_minimum_required(VERSION 3.7.1)
include("cmake/HunterGate.cmake")

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
endif ()

# Get Boost
hunter_add_package(Boost COMPONENTS regex system filesystem)
find_package(Boost CONFIG REQUIRED regex system filesystem)

# Get profobuf
# NOTE: On some systems, you may need to change "Protobuf" to "protobuf"
hunter_add_package(Protobuf)
find_package(Protobuf CONFIG REQUIRED)

file(GLOB proto_generated_includes "include/*.pb*")
file(GLOB proto_generated_sources "src/*.pb*")
file(GLOB proto_wrapper_files "src/google/protobuf/wrappers.*")

# Client library, build both static and dynamic libs
set (NANO_API_SRC
    ${proto_generated_includes}
    ${proto_generated_sources}
    ${proto_wrapper_files}
    src/nano.cpp)

include_directories(include)

# The protobuf-c cmake project doesn't work on all platforms,
# so we build it directly from the submodule.
set (PROTOBUF_C_SRC
    fork-protobuf-c/protobuf-c/protobuf-c.h
    fork-protobuf-c/protobuf-c/protobuf-c.c)

add_library(nanoclient SHARED ${NANO_API_SRC} ${PROTOBUF_C_SRC})
add_library(nanoclient_static STATIC ${NANO_API_SRC} ${PROTOBUF_C_SRC})

target_link_libraries(nanoclient Boost::system  protobuf::libprotobuf)
target_link_libraries(nanoclient_static Boost::system protobuf::libprotobuf)

target_include_directories(nanoclient PUBLIC src)
target_include_directories(nanoclient PUBLIC include)
target_include_directories(nanoclient_static PUBLIC src)
target_include_directories(nanoclient_static PUBLIC include)

# Build C example
add_executable(example-client examples/example-client.c)
target_link_libraries(example-client PUBLIC nanoclient_static Boost::regex Boost::system Boost::filesystem)

# Build C++ example
add_executable(example-client-cpp examples/example-client.cpp)
target_link_libraries(example-client-cpp PUBLIC nanoclient_static Boost::regex Boost::system Boost::filesystem)
