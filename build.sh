#!/bin/bash
# build mockcpp and it's tests, and at last run all tests.

function build() { 
	mkdir -p $1 2>/dev/null
	cd $1
	cmake $2
	make
}

build build/mockcpp ../..
cd ../..

build build/mockcpp_testngpp ../../tests/3rdparty/testngpp
cd ../..

build build/mockcpp_tests ../../tests

cd ut

if [ "$OSTYPE" = "cygwin" ]; then
    ../../mockcpp_testngpp/src/runner/testngpp-runner $(ls *.dll) -L"../../mockcpp_testngpp/src/listeners" -l"testngppstdoutlistener -c -f"
else
    ../../mockcpp_testngpp/src/runner/testngpp-runner $(ls *.so) -L"../../mockcpp_testngpp/src/listeners" -l"testngppstdoutlistener -c -f " -s
fi

cd ../../..
