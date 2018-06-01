# Generate .cc and .h files
protoc --proto_path=protobuf --cpp_out=src protobuf/core.proto
mv src/core.pb.h include
