# This is a Windows PowerShell script
# build and install

# Set the xxunit test framework name
$test_framework="gtest"
#$test_framework="catch2"

# gtest: there is a $xunit_home/include/gtest/gtest.h
# catch2: there is a $xunit_home/catch2/catch_test_macros.hpp
$xunit_home="D:/Develop/work/googletest/googletest"
#$xunit_home="D:/Develop/work/Catch2/src"

$install_dir="D:\Develop\work\mockcpp_install4xxxunit"
if (!(test-path $install_dir)) { mkdir $install_dir }

$MINGW_VER="-G `"MinGW Makefiles`""

function build($build_dir, $src_dir) {
	if (!(test-path $build_dir)) { mkdir $build_dir }
	cd $build_dir
	Invoke-Expression "cmake -DCMAKE_INSTALL_PREFIX=$install_dir -DMOCKCPP_XUNIT=$test_framework -DMOCKCPP_XUNIT_HOME=$xunit_home $src_dir $MINGW_VER"
	make install
}

build ../build_mockcpp_to_install4xxxunit ../mockcpp

cd ../mockcpp
