#!/bin/bash
# build and install

# Set the xxunit test framework name
#test_framework=gtest
test_framework=catch2

# gtest: there is a $xunit_home/include/gtest/gtest.h
# catch2: there is a $xunit_home/include/catch2/catch_test_macros.hpp
xunit_home=/usr/local

install_dir=/home/jelly/Programming/mockcpp-samples/mockcpp4gtest/mockcpp


function build() {
	mkdir $1 2>/dev/null
	cd $1
	cmake -DCMAKE_INSTALL_PREFIX=$install_dir -DMOCKCPP_XUNIT=$test_framework -DMOCKCPP_XUNIT_HOME=$xunit_home $2
	make install
}

build ../build_mockcpp_to_install4xxxunit ../mockcpp

cd ../mockcpp
