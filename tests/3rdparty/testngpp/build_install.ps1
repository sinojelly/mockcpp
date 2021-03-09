# This is a Windows PowerShell script
# On windows 7, open cmd.exe, input powershell, hit enter, then you can run this script.
# If you use powershell the first time, excute this cmd first: set-executionpolicy remotesigned
# Build mockcpp and it's tests, and at last run all tests.

# You can change this testngpp install dir by yourself, it must be an absolute path.
#$TESTNGPP_INSTALL_DIR="D:\Projects\Google\cpp-ut-project\cpp-ut-project\tools\testngpp"
$TESTNGPP_INSTALL_DIR="D:\Develop\work\test-tools\testngpp"
if (!(test-path $TESTNGPP_INSTALL_DIR)) { mkdir $TESTNGPP_INSTALL_DIR }

# add vcbuild path  and cmake path
# It's better to add to your computer's path environment variable, than to modify $env:path below.
#$env:path=$env:path+";C:\Program Files\Microsoft Visual Studio 9.0\VC\vcpackages"
#$env:path=$env:path+";D:\Tools\CMD\cmake-2.8.1-win32-x86\bin"
$env:path=$env:path+";$PSScriptRoot"  # to find premake4.exe

# specify the Visual Studio Version, not set to use default
$VC_VER="-G `"Visual Studio 9 2008`""
#$VC_VER="-G `"Visual Studio 10`""

# build Debug only
$env:VCBUILD_DEFAULT_CFG="Debug|Win32"

function build($build_dir, $src_dir) { 
	if (!(test-path $build_dir)) { mkdir $build_dir }
	cd $build_dir
	Invoke-Expression "cmake -DCMAKE_INSTALL_PREFIX=$TESTNGPP_INSTALL_DIR $src_dir $VC_VER"
	ls *.sln -name | vcbuild
	vcbuild INSTALL.vcproj
}

$MINGW_VER="-G `"MinGW Makefiles`""

function buildMinGW($build_dir, $src_dir) { 
	if (!(test-path $build_dir)) { mkdir $build_dir }
	cd $build_dir
	Invoke-Expression "cmake -DCMAKE_INSTALL_PREFIX=$TESTNGPP_INSTALL_DIR $src_dir $MINGW_VER"
	make install
}

#build ..\..\..\..\build_testngpp_to_install ..\mockcpp\tests\3rdparty\testngpp
buildMinGW ..\..\..\..\build_testngpp_to_install ..\mockcpp\tests\3rdparty\testngpp

cd ..\mockcpp\tests\3rdparty\testngpp

#move $TESTNGPP_INSTALL_DIR\3rdparty $TESTNGPP_INSTALL_DIR\.. -force

# On Windows, to avoid install python, you can make the python scripts to be an .exe, you should install py2exe first.(www.py2exe.org)
# cd testngpp\scripts, run premake4 install, then copy testngppgen.exe to tools\testngpp\bin\ dir.
cd scripts
Invoke-Expression "premake4 install"
cp dist\testngppgen.exe $TESTNGPP_INSTALL_DIR\bin

cd ..
