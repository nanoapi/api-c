# Download latest protobuf definition
mkdir -p protobuf_definition
wget --no-check-certificate https://github.com/nanoapi/protobuf/archive/master.tar.gz
tar xpvf master.tar.gz

# The C API becomes very verbose with the package prefix, so we
# remove package name and place the new core.proto version in the
# root directory.
sed '/package nano.api;/d' protobuf-master/core.proto > core.proto

# Generate .c and .h files
protoc --proto_path=. --c_out=src core.proto
#protoc --proto_path=. --cpp_out=src core.proto

# Move generated header files into include directory
mv src/core.pb-c.h include
#mv src/core.pb.h include
