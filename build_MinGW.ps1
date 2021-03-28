# This is a Windows PowerShell script
# On windows 7, open cmd.exe, input powershell, hit enter, then you can run this script.
# If you use powershell the first time, excute this cmd first: set-executionpolicy remotesigned
# Build mockcpp and it's tests, and at last run all tests.


# add vcbuild path  and cmake path
# It's better to add to your computer's path environment variable, than to modify $env:path below.
#$env:path=$env:path+";C:\Program Files\Microsoft Visual Studio 9.0\VC\vcpackages"
#$env:path=$env:path+";D:\Tools\CMD\cmake-2.8.1-win32-x86\bin"

# specify the Visual Studio Version, not set to use default
$VC_VER="-G `"MinGW Makefiles`""
#$VC_VER="-G `"Visual Studio 9 2008 Win64`""   # build for X64

# build Debug only
#$env:VCBUILD_DEFAULT_CFG="Debug|Win32"
#$env:VCBUILD_DEFAULT_CFG="Debug|x64"     # build for x64

function build($build_dir, $src_dir) { 
	if (!(test-path $build_dir)) { mkdir $build_dir }
	cd $build_dir
	Invoke-Expression "cmake $src_dir $VC_VER"
	#ls *.sln -name | vcbuild
	make
}

build build_mingw\mockcpp ..\..
cd ..\..

build build_mingw\mockcpp_testngpp ..\..\tests\3rdparty\testngpp

build build_mingw\mockcpp_tests ..\..\tests


#---------------------------------
# run all tests
cd ut
$ALL_DLL=(ls *.dll -name)-replace ".dll" | where {$_ -ne "libtestngppstdoutlistener"}
..\..\mockcpp_testngpp\src\runner\testngpp-runner.exe $ALL_DLL -L"..\..\mockcpp_testngpp\src\listeners" -l"testngppstdoutlistener -c -v" -m  #-s
cd ..\..\..
