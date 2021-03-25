# This is a Windows PowerShell script
# On windows 7, open cmd.exe, input powershell, hit enter, then you can run this script.
# If you use powershell the first time, excute this cmd first: set-executionpolicy remotesigned
# Build mockcpp and it's tests, and at last run all tests.


# add vcbuild path  and cmake path
# It's better to add to your computer's path environment variable, than to modify $env:path below.
$env:path=$env:path+";C:\Program Files\Microsoft Visual Studio 9.0\VC\vcpackages"
$env:path=$env:path+";D:\Tools\CMD\cmake-2.8.1-win32-x86\bin"

# specify the Visual Studio Version, not set to use default
#$VC_VER="-G `"Visual Studio 9 2008`""
#$VC_VER="-G `"Visual Studio 9 2008 Win64`""   # build for X64
$VC_VER="-G `"Visual Studio 16 2019`"" 

# build Debug only
$env:VCBUILD_DEFAULT_CFG="Debug|Win32"
#$env:VCBUILD_DEFAULT_CFG="Debug|x64"     # build for x64

function build($build_dir, $src_dir) { 
	if (!(test-path $build_dir)) { mkdir $build_dir }
	cd $build_dir
	Invoke-Expression "cmake $src_dir $VC_VER"

	# should add msbuild.exe path to path enviroment.
	# such as: C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\MSBuild\Current\Bin\MSBuild.exe
	Invoke-Expression "msbuild ALL_BUILD.vcxproj"
	#ls *.sln -name | vcbuild   # vcbuild is on VS2008, if you use vs2019, please use VS2019 IDE to open the *.sln and compile.
}

build build_vc\mockcpp ..\..
cd ..\..

build build_vc\mockcpp_testngpp ..\..\tests\3rdparty\testngpp
cd ..\..

build build_vc\mockcpp_tests ..\..\tests

#---------------------------------
# run all tests
cd ut\Debug
$ALL_DLL=(ls *.dll -name)-replace ".dll" | where {$_ -ne "testngppstdoutlistener"}
..\..\..\mockcpp_testngpp\src\runner\Debug\testngpp-runner.exe $ALL_DLL -L"..\..\..\mockcpp_testngpp\src\listeners\Debug" -l"testngppstdoutlistener -c -f" -s
cd ..\..\..\..


