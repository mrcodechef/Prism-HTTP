#!/bin/bash

apt-get update
apt-get install -y git build-essential wget automake \
  cmake libtool libssl-dev pkg-config libelf-dev

# bcc dependencies
apt-get -y install bison build-essential cmake flex git libedit-dev \
  libllvm6.0 llvm-6.0-dev libclang-6.0-dev python zlib1g-dev libelf-dev

cd $BUILD_ROOT

wget https://github.com/libtom/tomsfastmath/releases/download/v0.13.1/tfm-0.13.1.tar.xz
wget https://github.com/libtom/libtomcrypt/archive/v1.18.2.tar.gz
wget https://github.com/libuv/libuv/archive/v1.26.0.tar.gz
wget https://github.com/protocolbuffers/protobuf/archive/v3.6.0.1.tar.gz
wget https://github.com/google/leveldb/archive/1.21.tar.gz
git clone -b prism https://github.com/YutaroHayakawa/netmap
git clone -b v0.10.0 https://github.com/iovisor/bcc
git clone https://github.com/micchie/creme

tar xvf tfm-0.13.1.tar.xz
tar xvf v1.18.2.tar.gz
tar xvf v1.26.0.tar.gz
tar xvf v3.6.0.1.tar.gz
tar xvf 1.21.tar.gz

cd $BUILD_ROOT/bcc
mkdir build
cd build
cmake ../
make -j $NWORKERS
make -j $NWORKERS install

cd $BUILD_ROOT/tomsfastmath-0.13.1
make -j $NWORKERS
INSTALL_GROUP=root make install

cd $BUILD_ROOT/libtomcrypt-1.18.2
make -j4 CFLAGS="-DUSE_TFM -DTFM_DESC" EXTRALIBS="-ltfm"
make install

cd $BUILD_ROOT/libuv-1.26.0
./autogen.sh
./configure
make -j $NWORKERS install
cat include/uv/unix.h | sed -e 's/netinet\/tcp.h/linux\/tcp.h/g' > /usr/local/include/uv/unix.h

cd $BUILD_ROOT/protobuf-3.6.0.1
./autogen.sh
./configure
make -j $NWORKERS install

cd $BUILD_ROOT/leveldb-1.21
mkdir build
cd build
cmake ../
make -j $NWORKERS install

ldconfig

cd $BUILD_ROOT/Prism-HTTP/src/proto
bash gen.sh
