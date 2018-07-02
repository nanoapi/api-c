# Download latest protobuf definition
mkdir -p protobuf-master/google/protobuf
wget --quiet --no-check-certificate https://raw.githubusercontent.com/cryptocode/raiblocks/c-api/protobuf/core.proto -O protobuf-master/core.proto
wget --quiet --no-check-certificate https://raw.githubusercontent.com/cryptocode/raiblocks/c-api/protobuf/accounts.proto -O protobuf-master/accounts.proto
wget --quiet --no-check-certificate https://raw.githubusercontent.com/cryptocode/raiblocks/c-api/protobuf/util.proto -O protobuf-master/util.proto
wget --quiet --no-check-certificate https://raw.githubusercontent.com/cryptocode/raiblocks/c-api/protobuf/google/protobuf/wrappers.proto -O protobuf-master/google/protobuf/wrappers.proto

# Generate C++ files
protoc --proto_path=protobuf-master --cpp_out=src protobuf-master/core.proto
protoc --proto_path=protobuf-master --cpp_out=src protobuf-master/accounts.proto
protoc --proto_path=protobuf-master --cpp_out=src protobuf-master/util.proto

# Move generated protobuf header into include directory
mv src/core.pb.h include
mv src/accounts.pb.h include
mv src/util.pb.h include