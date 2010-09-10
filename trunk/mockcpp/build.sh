#!/bin/bash
# build mockcpp and it's tests, and at last run all tests.

function build() { 
	mkdir $1
	cd $1
	cmake $2
}

build ../../build_mockcpp ../mockcpp/mockcpp
make

build ../build_testngpp ../mockcpp/mockcpp/tests/3rdparty/testngpp
make

build ../build_tests ../mockcpp/mockcpp/tests
make

cd ut
../../build_testngpp/src/runner/testngpp-runner $(ls *.so) -L"../../build_testngpp/src/listeners" -l"testngppstdoutlistener -c -f"

