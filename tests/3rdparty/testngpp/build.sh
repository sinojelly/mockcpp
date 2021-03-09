#!/bin/bash
# build mockcpp and it's tests, and at last run all tests.

function build() { 
	mkdir $1 2>/dev/null
	cd $1
	cmake $2
	make
}

build ../../../../build_testngpp ../mockcpp/tests/3rdparty/testngpp

build ../build_testngpp_testngppst ../mockcpp/tests/3rdparty/testngpp/tests/3rdparty/testngppst

build ../build_testngpp_tests ../mockcpp/tests/3rdparty/testngpp/tests

#run samples
#cd ../build_testngpp/samples
#./run-sample 

#run ut
cd ut

if [ "$OSTYPE" = "cygwin" ]; then
  ../../build_testngpp_testngppst/src/runner/testngppst-runner $(ls *.dll) -L"../../build_testngpp_testngppst/src/listeners" -l"testngppstdoutlistener -c -v"
else
  ../../build_testngpp_testngppst/src/runner/testngppst-runner $(ls *.so) -L"../../build_testngpp_testngppst/src/listeners" -l"testngppstdoutlistener -c -v"
fi

