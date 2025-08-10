

git clone https://github.com/protocolbuffers/protobuf.git

cd protobuf

cmake -DCMAKE_BUILD_TYPE=Release -B./build

cd build

make all -j8