# Download latest protobuf definition
mkdir -p protobuf-master/google/protobuf
wget --quiet --no-check-certificate https://raw.githubusercontent.com/cryptocode/raiblocks/c-api/protobuf/core.proto -O protobuf-master/core.proto
wget --quiet --no-check-certificate https://raw.githubusercontent.com/cryptocode/raiblocks/c-api/protobuf/accounts.proto -O protobuf-master/accounts.proto
wget --quiet --no-check-certificate https://raw.githubusercontent.com/cryptocode/raiblocks/c-api/protobuf/util.proto -O protobuf-master/util.proto
wget --quiet --no-check-certificate https://raw.githubusercontent.com/cryptocode/raiblocks/c-api/protobuf/google/protobuf/wrappers.proto -O protobuf-master/google/protobuf/wrappers.proto

# The C API becomes very verbose with the package prefix, so we
# remove package name and place the new *.proto version in the
# root directory.
sed '/package nano.api;/d' protobuf-master/core.proto > core.proto
sed '/package nano.api;/d' protobuf-master/accounts.proto > accounts.proto
sed '/package nano.api;/d' protobuf-master/util.proto > util.proto

# Generate .c and .h files
protoc --proto_path=. --c_out=src core.proto
protoc --proto_path=. --c_out=src accounts.proto
protoc --proto_path=. --c_out=src util.proto

# Move generated header files into include directory
mv src/core.pb-c.h include
mv src/accounts.pb-c.h include
mv src/util.pb-c.h include
