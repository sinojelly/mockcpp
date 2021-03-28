# This is a Windows PowerShell script
# On windows 7, open cmd.exe, input powershell, hit enter, then you can run this script.
# If you use powershell the first time, excute this cmd first: set-executionpolicy remotesigned
# Build mockcpp and it's tests, and at last run all tests.

# $args[0]  --- compiler name  (GNU, MSVC)
# $args[1]  --- [optional] compiler major version  (The first part of cxx compiler version)

$global:MY_OS_NAME=$null
$global:MY_CXX_COMPILER_NAME=$null
$global:MY_CXX_COMPILER_MAJOR_VERSION=$null
$global:CMAKE_COMPILER_PARAM=$null
$global:MAKE_BUILD_TYPE=$null

function InitEnviroment {
	param (
		$compiler_name,
		$compiler_major_version
	)
	# Running Powershell must be Windows
    $global:MY_OS_NAME="Windows"

	$global:MY_CXX_COMPILER_NAME=$compiler_name

	# Assuming MSVC is VS2019 and GNU is MinGW GCC 8
	if ($compiler_name -eq "MSVC") {
		$global:CMAKE_COMPILER_PARAM="Visual Studio 16 2019"
		$global:MAKE_BUILD_TYPE="Debug"
		if (-not $compiler_major_version) {
			$global:MY_CXX_COMPILER_MAJOR_VERSION="19"
		}
	} elseif ($compiler_name -eq "GNU") {
		$global:CMAKE_COMPILER_PARAM="MinGW Makefiles"
		$global:MAKE_BUILD_TYPE="."
		if (-not $compiler_major_version) {
			$global:MY_CXX_COMPILER_MAJOR_VERSION="8"
		}
	}
}

function CompileProject {
	param (
		$compiler_name,
		$project_dir
	)
	if ($compiler_name -eq "MSVC") {
		cd $project_dir
        Invoke-Expression "msbuild ALL_BUILD.vcxproj"
        cd ..\..  # Assuming two level directory
	} elseif ($compiler_name -eq "GNU") {
		Invoke-Expression "make -C $project_dir"
	}
}

InitEnviroment $args[0] $args[1]

$BUILD_DIR="build_$global:MY_CXX_COMPILER_NAME"

$OS_COMPILER="$global:MY_OS_NAME\$global:MY_CXX_COMPILER_NAME\$global:MY_CXX_COMPILER_MAJOR_VERSION"

echo "OS_COMPILER: $OS_COMPILER"

cmake -G $global:CMAKE_COMPILER_PARAM -S . -B $BUILD_DIR/mockcpp
cmake -G $global:CMAKE_COMPILER_PARAM -S tests/3rdparty/testngpp -B $BUILD_DIR/mockcpp_testngpp
cmake -G $global:CMAKE_COMPILER_PARAM -S tests -B $BUILD_DIR/mockcpp_tests
CompileProject $global:MY_CXX_COMPILER_NAME $BUILD_DIR/mockcpp
CompileProject $global:MY_CXX_COMPILER_NAME $BUILD_DIR/mockcpp_testngpp
CompileProject $global:MY_CXX_COMPILER_NAME $BUILD_DIR/mockcpp_tests

function RunTests {
	param (
		$build_dir,
		$tested_project,
		$build_type,
		$testing_tool
	)
	cd $build_dir/$tested_project/ut/$build_type
	if ($build_type -eq ".") {
		$BUILD_TYPE_BACK="."
	} else {
		$BUILD_TYPE_BACK=".."
	}
	$LISTENER_PATH="..\..\$BUILD_TYPE_BACK\$testing_tool\src\listeners\$build_type"
	$RUNNER_PATH="..\..\$BUILD_TYPE_BACK\$testing_tool\src\runner\$build_type"
	$ALL_DLL=(ls *.dll -name)-replace ".dll"
	Invoke-Expression "$RUNNER_PATH\testngpp-runner.exe  $ALL_DLL -L`"$LISTENER_PATH`" -l`"testngppstdoutlistener -c -v`" -m"
	cd ..\..\..\$BUILD_TYPE_BACK
}

RunTests $BUILD_DIR mockcpp_tests $global:MAKE_BUILD_TYPE mockcpp_testngpp
