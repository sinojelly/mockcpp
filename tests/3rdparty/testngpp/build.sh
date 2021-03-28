#!/bin/bash
# build mockcpp and it's tests, and at last run all tests.

function build() { 
	mkdir -p $1 2>/dev/null
	cd $1
	cmake $2
	make
}

build ../../../build/testngpp ../../tests/3rdparty/testngpp

build ../testngpp_testngppst ../../tests/3rdparty/testngpp/tests/3rdparty/testngppst

build ../testngpp_tests ../../tests/3rdparty/testngpp/tests

#run samples
#cd ../build_testngpp/samples
#./run-sample 

#run ut
cd ut

if [ "$OSTYPE" = "cygwin" ]; then
  ../../testngpp_testngppst/src/runner/testngppst-runner $(ls *.dll) -L"../../testngpp_testngppst/src/listeners" -l"testngppststdoutlistener -c -v"
else
  ../../testngpp_testngppst/src/runner/testngppst-runner $(ls *.so) -L"../../testngpp_testngppst/src/listeners" -l"testngppststdoutlistener -c -v"
fi

