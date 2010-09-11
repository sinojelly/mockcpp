#!/bin/bash
# build mockcpp and it's tests, and at last run all tests.

function build() { 
	mkdir $1 2>nul
	cd $1
	cmake $2
	make
}

build ../../build_mockcpp ../mockcpp/mockcpp

build ../build_testngpp ../mockcpp/mockcpp/tests/3rdparty/testngpp

build ../build_tests ../mockcpp/mockcpp/tests

cd ut
../../build_testngpp/src/runner/testngpp-runner $(ls *.so) -L"../../build_testngpp/src/listeners" -l"testngppstdoutlistener -c -f"

