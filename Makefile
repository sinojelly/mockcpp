BUILD_MOCKCPP_DIR  = ../../build_mockcpp
BUILD_TESTNGPP_DIR = ../../build_testngpp
BUILD_TESTS_DIR    = ../../build_tests

.PHONY : all mockcpp testngpp tests test install clean clean_mockcpp clean_testngpp clean_tests

cmake_build = mkdir $(1) 2>/dev/null ; echo "$(1) exists!" && cd $(1) && cmake $(2) && make

all : test

mockcpp :
	@$(call cmake_build,$(BUILD_MOCKCPP_DIR), ../mockcpp/mockcpp)

install : mockcpp
	@cd $(BUILD_MOCKCPP_DIR) && make install

testngpp :   
	@$(call cmake_build,$(BUILD_TESTNGPP_DIR), ../mockcpp/mockcpp/tests/3rdparty/testngpp)

tests : mockcpp testngpp
	@$(call cmake_build,$(BUILD_TESTS_DIR), ../mockcpp/mockcpp/tests)

test : tests
	@cd $(BUILD_TESTS_DIR)/ut && ../../build_testngpp/src/runner/testngpp-runner $(shell echo *.so) -L"../../build_testngpp/src/listeners" -l"testngppstdoutlistener -c -f"

clean_mockcpp :
	@$(shell cd $(BUILD_MOCKCPP_DIR) && make clean) >/dev/null

clean_testngpp :
	@$(shell cd $(BUILD_TESTNGPP_DIR) && make clean) >/dev/null

clean_tests :
	@$(shell cd $(BUILD_TESTS_DIR) && make clean) >/dev/null

clean : clean_mockcpp clean_testngpp clean_tests

cmake_codeblocks = cd $(1) && cmake -G "CodeBlocks - Unix Makefiles" $(2)

codeblocks :
	@$(call cmake_codeblocks,$(BUILD_MOCKCPP_DIR), ../mockcpp/mockcpp)
	@$(call cmake_codeblocks,$(BUILD_TESTNGPP_DIR), ../mockcpp/mockcpp/tests/3rdparty/testngpp)
	@$(call cmake_codeblocks,$(BUILD_TESTS_DIR), ../mockcpp/mockcpp/tests)
