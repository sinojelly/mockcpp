#!/bin/bash
# build mockcpp and it's tests, and at last run all tests.

function build() { 
	mkdir $1 2>/dev/null
	cd $1
	cmake $2
	make
}

build ../build_testngpp ../test-ng-pp

build ../build_testngppst ../test-ng-pp/tests/3rdparty/testngppst

build ../build_tests ../test-ng-pp/tests

#run samples
cd ../build_testngpp/samples
./run-sample 

#run ut
cd ../../build_tests/ut

if [ "$OSTYPE" = "cygwin" ]; then
  ../../build_testngppst/src/runner/testngppst-runner $(ls *.dll) -L"../../build_testngpp/src/listeners" -l"testngppstdoutlistener -c -f"
else
  ../../build_testngppst/src/runner/testngppst-runner $(ls *.so) -L"../../build_testngpp/src/listeners" -l"testngppstdoutlistener -c -f"
fi

