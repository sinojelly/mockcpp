CompilerArray=("1st item" 
               "2nd item" 
			   "3rd item" 
			   "4th item")


function ReadUserChoice() {
	printf 'Word -> %s\n' "${CompilerArray[@]}"
}


function InitEnviroment() {
        MY_OS_NAME="Linux"
	MY_CXX_COMPILER_NAME=$1
	MY_CXX_COMPILER_MAJOR_VERSION=$2
	CMAKE_COMPILER_PARAM=""
	MAKE_BUILD_TYPE="."
}

function CompileProject() {
  make -C $2
}

function CompileProjectInstall() {
  make -C $2 install
}

function RunTests() {
	cd $1/$2/ut/$3
	BUILD_TYPE_BACK="."
	LISTENER_PATH="../../$BUILD_TYPE_BACK/$4/src/listeners/$3"
	RUNNER_PATH="../../$BUILD_TYPE_BACK/$4/src/runner/$3"
	$RUNNER_PATH/testngpp$5-runner $(ls *.so) -L"$LISTENER_PATH" -l"testngpp$5stdoutlistener -c -v" -m
	cd ../../../$BUILD_TYPE_BACK
}

function RunTestsFromPrebuiltTools() {
    cd $1/$2/$3
    BUILD_TYPE_BACK="."
	if [ -z "$5" ]; then # not specify the prebuilt tools
		TESTNGPP_PATH="../../$BUILD_TYPE_BACK/tests/testngpp"      # default choose the tools in project
	else
		TESTNGPP_PATH=$5
	fi
    LISTENER_PATH="$TESTNGPP_PATH/binary/$4/testngpp/listener"
    RUNNER_PATH="$TESTNGPP_PATH/binary/$4/testngpp/bin"
    $RUNNER_PATH/testngpp-runner $(ls *.so) -L"$LISTENER_PATH" -l"testngppstdoutlistener -c -v" -m
    cd ../../$BUILD_TYPE_BACK
}
