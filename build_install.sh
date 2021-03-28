#!/bin/bash
# build and install

install_dir=~/test_tools/mockcpp_install

function build() {
	mkdir -p $1 2>/dev/null
	cd $1
	cmake -DCMAKE_INSTALL_PREFIX=$install_dir $2
	make install
}

build build/mockcpp_to_install ../..

cd ../..

