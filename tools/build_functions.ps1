# Use the following content to make a CMakeLists.txt to get compiler name and major_ver, run : cmake -S . -B build
# CMAKE_MINIMUM_REQUIRED(VERSION 3.12...3.19)
# PROJECT(cmake-test)
# MESSAGE("CMAKE_CXX_COMPILER_ID - compiler name:")
# MESSAGE(${CMAKE_CXX_COMPILER_ID})
# MESSAGE("CMAKE_CXX_COMPILER_VERSION - compiler major version:")
# MESSAGE(${CMAKE_CXX_COMPILER_VERSION})
#
# cmake_param also can be: "-G `"Visual Studio 16 2019`" -A Win32"  etc.
$global:SUPPORTED_COMPILER = @(
           @{ name="GNU"; major_ver="7"; cmake_param="-G `"MinGW Makefiles`""; desc="MinGW GNU 7.x"},
           @{ name="GNU"; major_ver="8"; cmake_param="-G `"MinGW Makefiles`""; desc="MinGW GNU 8.x"},
           @{ name="MSVC"; major_ver="19"; cmake_param="-G `"Visual Studio 16 2019`""; desc="Visual Studio 2019" }
          )

function ReadUserChoice {
	param ()
	$count = $global:SUPPORTED_COMPILER.Count - 1
	Write-Host "Please choose your compiler's name and major version : (input the index)"
	foreach($index in 0..$count)
	{
		Write-Host $index, ". ", $global:SUPPORTED_COMPILER[$index].name, $global:SUPPORTED_COMPILER[$index].major_ver, " -- such as ",$global:SUPPORTED_COMPILER[$index].desc 
	}
	
	do {
		$global:USER_CHOICE=Read-Host "Enter your chooice ( 0 ~", $count, ")" 
	} while (-not $global:USER_CHOICE -or $global:USER_CHOICE -lt 0 -or $global:USER_CHOICE -gt 2)
}

function InitEnviroment {
	param (
		$compiler_name,
		$compiler_major_version,
		$cmake_param
	)
	# Running Powershell must be Windows
    $global:MY_OS_NAME="Windows"

	$global:MY_CXX_COMPILER_NAME=$compiler_name
	$global:MY_CXX_COMPILER_MAJOR_VERSION=$compiler_major_version
	$global:CMAKE_COMPILER_PARAM=$cmake_param

	if ($compiler_name -eq "MSVC") {
		$global:MAKE_BUILD_TYPE="Debug"
	} elseif ($compiler_name -eq "GNU") {
		$global:MAKE_BUILD_TYPE="."
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
        cd ..\..  # Assuming two levels directory
	} elseif ($compiler_name -eq "GNU") {
		Invoke-Expression "make -C $project_dir"
	}
}

function CompileProjectInstall {
	param (
		$compiler_name,
		$project_dir
	)
	if ($compiler_name -eq "MSVC") {
		cd $project_dir
        Invoke-Expression "msbuild INSTALL.vcxproj"
        cd ..\..  # Assuming two levels directory
	} elseif ($compiler_name -eq "GNU") {
		Invoke-Expression "make -C $project_dir install"
	}
}

function RunTests {
	param (
		$build_dir,
		$tested_project,
		$build_type,
		$testing_tool,
		$st_suffix
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
	Invoke-Expression "$RUNNER_PATH\testngpp${st_suffix}-runner.exe  $ALL_DLL -L`"$LISTENER_PATH`" -l`"testngpp${st_suffix}stdoutlistener -c -v`" -m"
	cd ..\..\..\$BUILD_TYPE_BACK
}

function RunTestsFromPrebuiltTools {
    param (
        $build_dir,
		$tested_project,
		$build_type,
        $os_compiler,
		$prebuilt_tools
    )
    cd $build_dir/$tested_project/$build_type
    if ($build_type -eq ".") {
		$BUILD_TYPE_BACK="."
	} else {
		$BUILD_TYPE_BACK=".."
	}
	if (-not $prebuilt_tools) { # not specify the prebuilt tools
		$TESTNGPP_PATH="..\..\$BUILD_TYPE_BACK\tests\testngpp"      # default choose the tools in project
	} else {
		$TESTNGPP_PATH=$prebuilt_tools
	}
    $LISTENER_PATH="$TESTNGPP_PATH\binary\$os_compiler\testngpp\listener"
    $RUNNER_PATH="$TESTNGPP_PATH\binary\$os_compiler\testngpp\bin"
    $ALL_DLL=(ls *.dll -name)-replace ".dll"
    Invoke-Expression "$RUNNER_PATH\testngpp-runner.exe  $ALL_DLL -L`"$LISTENER_PATH`" -l`"testngppstdoutlistener -c -v`" -m"
    cd ..\..\$BUILD_TYPE_BACK
}