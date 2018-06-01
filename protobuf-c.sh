# The C API becomes very verbose with the package prefix, so we
# remove package name and place the new core.proto version in the 
# root directory.
sed '/package nano.api;/d' protobuf/core.proto > core.proto

# Generate .c and .h files
protoc --proto_path=. --c_out=src core.proto
protoc --proto_path=. --cpp_out=src core.proto
mv src/core.pb-c.h include
mv src/core.pb.h include
