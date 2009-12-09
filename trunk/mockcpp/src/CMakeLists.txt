
INCLUDE(FindPythonInterp)

IF(PYTHONINTERP_FOUND)
    SET(PYTHON ${PYTHON_EXECUTABLE})
ELSE()
    MESSAGE(FATAL_ERROR "No Python interpreter found")
ENDIF(PYTHONINTERP_FOUND)

SET(PACKAGE_NAME \"mockcpp\")
SET(PACKAGE_STRING \"mockcpp\")
SET(PACKAGE_BUGREPORT \"dev.mockcpp@gmail.com\")
SET(PACKAGE_URL \"http://code.google.com/p/mockcpp\")
SET(PACKAGE \"mockcpp\")
SET(VERSION \"2.2\")


# Set MOCKCPP_MAX_INHERITANCE
#
IF(MOCKCPP_ALLOW_MI)
    SET(MOCKCPP_ALLOW_MULTI_INHERITANCE 1)
    IF(NOT MOCKCPP_MAX_INHERITANCE)
        SET(MOCKCPP_MAX_INHERITANCE 2)
    ENDIF(NOT MOCKCPP_MAX_INHERITANCE)
ELSE(MOCKCPP_ALLOW_MI)
    SET(MOCKCPP_ALLOW_MULTI_INHERITANCE 0)
    SET(MOCKCPP_MAX_INHERITANCE 1)
ENDIF(MOCKCPP_ALLOW_MI)

IF(MOCKCPP_NO_NAMESPACE)
   SET(MOCKCPP_NO_NAMESPACE 1)
ELSE(MOCKCPP_NO_NAMESPACE)
   SET(MOCKCPP_NO_NAMESPACE 0)
ENDIF(MOCKCPP_NO_NAMESPACE)
#
# Set MOCKCPP_MAX_VTBL_SIZE
#
IF(NOT MOCKCPP_MAX_VTBL_SIZE)
    SET(MOCKCPP_MAX_VTBL_SIZE 20)
ENDIF(NOT MOCKCPP_MAX_VTBL_SIZE)

IF(NOT MOCKCPP_MAX_PARAMETERS)
    SET(MOCKCPP_MAX_PARAMETERS 12)
ENDIF(NOT MOCKCPP_MAX_PARAMETERS)

ADD_DEFINITIONS(
    -DPACKAGE_NAME=${DPACKAGE_NAME}
    -DPACKAGE_STRING=${DPACKAGE_STRING}
    -DPACKAGE_BUGREPORT=${PACKAGE_BUGREPORT}
    -DPACKAGE_URL=${PACKAGE_URL}
    -DPACKAGE=${PACKAGE}
    -DVERSION=${VERSION}
    -DMOCKCPP_NO_NAMESPACE=${MOCKCPP_NO_NAMESPACE}
    -DMOCKCPP_ALLOW_MULTI_INHERITANCE=${MOCKCPP_ALLOW_MULTI_INHERITANCE}
    -DMOCKCPP_MAX_INHERITANCE=${MOCKCPP_MAX_INHERITANCE}
    -DMOCKCPP_MAX_VTBL_SIZE=${MOCKCPP_MAX_VTBL_SIZE}
    -DMOCKCPP_MAX_PARAMETERS=${MOCKCPP_MAX_PARAMETERS}
)

SET(MOCKCPP_SRCS 
    AfterMatcher.cpp
    AnyBase.cpp
    AnyCast.cpp
    Any.cpp
    Asserter.cpp
    AssertionFailedError.cpp
    BeforeMatcher.cpp
    CallerMatcher.cpp
    ChainableMockMethodContainer.cpp
    ChainableMockMethodCore.cpp
    ChainableMockMethodIndexKey.cpp
    ChainableMockMethodNameKey.cpp
    ChainableMockObjectBase.cpp
    ChainableMockObject.cpp
    ChainingMockHelper.cpp
    ConstraintSet.cpp
    DecoratedConstraint.cpp
    DefaultMatcher.cpp
    DefaultStub.cpp
    DelegatedMethodGetter.cpp
    DestructorChecker.cpp
    DieStub.cpp
    Exception.cpp
    ExpectsMatcher.cpp
    Formatter.cpp
    GenericMethodIndicesChecker.cpp
    GlobalMockObject.cpp
    IdentityBuilder.cpp
    IgnoreResultHandler.cpp
    IgnoreResultHandlerFactory.cpp
    IgnoreReturnStub.cpp
    InterfaceInfo.cpp
    Invocation.cpp
    InvocationId.cpp
    InvocationMockBuilderGetter.cpp
    InvocationMocker.cpp
    InvocationMockerSet.cpp
    InvocationTimesMatcher.cpp
    InvokedAtLeast.cpp
    InvokedAtMost.cpp
    InvokedExactly.cpp
    InvokedOnce.cpp
    InvokedTimesMatcher.cpp
    IsAnythingHelper.cpp
    IsStringContains.cpp
    IsStringEndWith.cpp
    IsStringStartWith.cpp
    MismatchResultHandler.cpp
    MismatchResultHandlerFactory.cpp
    MockObjectBase.cpp
    NormalResultHandler.cpp
    NormalResultHandlerFactory.cpp
    OutBoundPointer.cpp
    PendingMatcher.cpp
    ProcStub.cpp
    RefAny.cpp
    RepeatStub.cpp
    Result.cpp
    ReturnObjectList.cpp
    ReturnStub.cpp
    SimpleInvocationRecorder.cpp
    StringConstraint.cpp
    StubContainer.cpp
    StubsMatcher.cpp
    TestFailureMatcher.cpp
    ThenStub.cpp
    TypelessConstraintAdapter.cpp
    TypelessStubAdapter.cpp
    TypeString.cpp
    VirtualTable.cpp
    VirtualTableUtils.cpp
    VoidResultHandler.cpp
    VoidResultHandlerFactory.cpp
    WillStub.cpp)

IF(WIN32)
   SET(MOCKCPP_SRCS ${MOCKCPP_SRCS} Win32Hook.cpp)
ENDIF(WIN32)
######################################################
SET(MOCKCPP_HEADERS_PATH ${CMAKE_SOURCE_DIR}/include/mockcpp)
SET(MOCKCPP_SOURCES_PATH ${CMAKE_SOURCE_DIR}/src)

SET(MOCKCPP_VTBL_RELATED_HEADERS 
    ${MOCKCPP_HEADERS_PATH}/DelegatedMethodGetDef.h 
    ${MOCKCPP_HEADERS_PATH}/DelegatedMethodGetByVptrDef.h 
    ${MOCKCPP_HEADERS_PATH}/GenericMethodCheckerDef.h 
    ${MOCKCPP_HEADERS_PATH}/DestructorAddrGetterDef.h 
    ${MOCKCPP_HEADERS_PATH}/DestructorCheckerDef.h
)

SET(MOCKCPP_ARG_RELATED_HEADER_FILES
    ${MOCKCPP_HEADERS_PATH}/DelegatedMethodDef.h 
    ${MOCKCPP_HEADERS_PATH}/ArgumentsListDef.h  
    ${MOCKCPP_HEADERS_PATH}/MethodTypeTraitsDef.h
)

IF(MOCKCPP_ALLOW_MI)
    SET(ALLOW_MI yes)
ELSE(MOCKCPP_ALLOW_MI)
    SET(ALLOW_MI no)
ENDIF(MOCKCPP_ALLOW_MI)

######################################################
SET(VTBL_GENERATOR ${CMAKE_SOURCE_DIR}/src/generate_vtbl_related_files.py)
SET(EXTRA_VTBL_HEADERS_DEFS
    --allow-mi=${ALLOW_MI}
    --max-inheritance=${MOCKCPP_MAX_INHERITANCE}
    --max-vtbl-size=${MOCKCPP_MAX_VTBL_SIZE}
    --include-path=${MOCKCPP_HEADERS_PATH}
)
FOREACH(HEADER ${MOCKCPP_VTBL_RELATED_HEADERS})
    GET_FILENAME_COMPONENT(HEADER_NAME ${HEADER} NAME)
    ADD_CUSTOM_COMMAND(
        OUTPUT ${HEADER}
        COMMAND ${PYTHON} ${VTBL_GENERATOR} ${EXTRA_VTBL_HEADERS_DEFS} ${HEADER_NAME}
    )
ENDFOREACH()

######################################################
SET(ARG_GENERATOR ${CMAKE_SOURCE_DIR}/src/generate_arg_related_files.py)
SET(EXTRA_ARG_HEADERS_DEFS
    --max-parameters=${MOCKCPP_MAX_PARAMETERS}
    --include-path=${MOCKCPP_HEADERS_PATH}
)
FOREACH(HEADER ${MOCKCPP_ARG_RELATED_HEADER_FILES})
    GET_FILENAME_COMPONENT(HEADER_NAME ${HEADER} NAME)
    ADD_CUSTOM_COMMAND(
        OUTPUT ${HEADER}
        COMMAND ${PYTHON} ${ARG_GENERATOR} ${EXTRA_ARG_HEADERS_DEFS} ${HEADER_NAME}
    )
ENDFOREACH()

######################################################
ADD_LIBRARY(mockcpp ${MOCKCPP_SRCS})

INCLUDE_DIRECTORIES(BEFORE ${CMAKE_SOURCE_DIR}/include ${CMAKE_SOURCE_DIR}/3rdparty)

ADD_CUSTOM_TARGET(vtbl_related_headers DEPENDS ${MOCKCPP_VTBL_RELATED_HEADERS})
ADD_CUSTOM_TARGET(arg_related_headers DEPENDS ${MOCKCPP_ARG_RELATED_HEADER_FILES})

ADD_DEPENDENCIES(mockcpp vtbl_related_headers arg_related_headers)
