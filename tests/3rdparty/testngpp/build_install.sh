#!/bin/bash
# build and install

# You can change this testngpp install dir by yourself, it must be an absolute path.
install_dir=~/test_tools/testngpp_install


function build() {
	mkdir -p $1 2>/dev/null
	cd $1
	cmake -DCMAKE_INSTALL_PREFIX=$install_dir $2
	make install
}

build ../../../build/testngpp_to_install ../../tests/3rdparty/testngpp

cd ../../tests/3rdparty/testngpp

#mv -f -u $install_dir/3rdparty $install_dir/..

#cd scripts
#python setup_linux.py build
#cp build/exe.linux-i686-2.6/* $install_dir/bin

#cd ..
