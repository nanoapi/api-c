# Generate .cc and .h files
#protoc --proto_path=protobuf --cpp_out=src protobuf/core.proto

# Download latest protobuf definition
mkdir -p protobuf_definition
rm master.tar.gz
wget --no-check-certificate https://github.com/nanoapi/protobuf/archive/master.tar.gz
tar xpvf master.tar.gz

# Generate C++ files
protoc --proto_path=protobuf-master --cpp_out=src protobuf-master/core.proto

# Move generated protobuf header into include directory
mv src/core.pb.h include
