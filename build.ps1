# This is a Windows PowerShell script
# On windows 7, open cmd.exe, input powershell, hit enter, then you can run this script.
# If you use powershell the first time, excute this cmd first: set-executionpolicy remotesigned
# Build mockcpp and it's tests, and at last run all tests.

# $args[0]  --- compiler name  (GNU, MSVC)
# $args[1]  --- [optional] compiler major version  (The first part of cxx compiler version)

$PARAM_COMPILER_NAME=$args[0]
$PARAM_COMPILER_MAJOR_VERSION=$args[1]

# Assuming MSVC is VS2019 and GNU is MinGW GCC 8
if ($PARAM_COMPILER_NAME -eq "MSVC") {
    $CMAKE_COMPILER_PARAM="Visual Studio 16 2019"
	$COMPILER_SCRIPT={ Param($project_dir) 
        cd $project_dir
        Invoke-Expression "msbuild ALL_BUILD.vcxproj"
        cd ..\..  # Assuming two level directory
    }
	$MAKE_BUILD_TYPE="Debug"
    if (-not $PARAM_COMPILER_MAJOR_VERSION) {
	    $PARAM_COMPILER_MAJOR_VERSION="19"
	}
} elseif ($PARAM_COMPILER_NAME -eq "GNU") {
    $CMAKE_COMPILER_PARAM="MinGW Makefiles"
    $COMPILER_SCRIPT={ Param($project_dir) 
        Invoke-Expression "make -C $project_dir"
    }
	$MAKE_BUILD_TYPE="."
    if (-not $PARAM_COMPILER_MAJOR_VERSION) {
	    $PARAM_COMPILER_MAJOR_VERSION="8"
	}
}

$BUILD_DIR="build_$PARAM_COMPILER_NAME"

# Running Powershell must be Windows
$MY_OS_NAME="Windows"
$MY_CXX_COMPILER_NAME=$PARAM_COMPILER_NAME
$MY_CXX_COMPILER_MAJOR_VERSION=$PARAM_COMPILER_MAJOR_VERSION

$OS_COMPILER="$MY_OS_NAME\$MY_CXX_COMPILER_NAME\$MY_CXX_COMPILER_MAJOR_VERSION"

echo "OS_COMPILER: $OS_COMPILER"

cmake -G $CMAKE_COMPILER_PARAM -S . -B $BUILD_DIR/mockcpp
cmake -G $CMAKE_COMPILER_PARAM -S tests/3rdparty/testngpp -B $BUILD_DIR/mockcpp_testngpp
cmake -G $CMAKE_COMPILER_PARAM -S tests -B $BUILD_DIR/mockcpp_tests
$COMPILER_SCRIPT.Invoke("$BUILD_DIR/mockcpp")
$COMPILER_SCRIPT.Invoke("$BUILD_DIR/mockcpp_testngpp")
$COMPILER_SCRIPT.Invoke("$BUILD_DIR/mockcpp_tests")

function RunTests {
	param (
		$build_type
	)
	cd $BUILD_DIR/mockcpp_tests/ut/$build_type
	if ($build_type -eq ".") {
		$BUILD_TYPE_BACK="."
	} else {
		$BUILD_TYPE_BACK=".."
	}
	$LISTENER_PATH="..\..\$BUILD_TYPE_BACK\mockcpp_testngpp\src\listeners\$build_type"
	$RUNNER_PATH="..\..\$BUILD_TYPE_BACK\mockcpp_testngpp\src\runner\$build_type"
	$ALL_DLL=(ls *.dll -name)-replace ".dll"
	Invoke-Expression "$RUNNER_PATH\testngpp-runner.exe  $ALL_DLL -L`"$LISTENER_PATH`" -l`"testngppstdoutlistener -c -v`" -m"
	cd ..\..\..\$BUILD_TYPE_BACK
}

RunTests $MAKE_BUILD_TYPE
