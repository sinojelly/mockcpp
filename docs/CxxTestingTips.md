# C++ testing tips

## mockcpp

#### 1. Only the classes that have virtual method table can use MOCKER.
We can make the class have a virtual desturctor.

#### 2. Only the class method that is virtual can be mocked.
If the method is virtual, no problem.

If you don't want it to be virtual in production, but you want to mock it in testing, you can follow this instruction:
##### 1) use a header file not_test.h in product code.
the content is:
``` c++
#ifndef CAN_MOCK
#define CAN_MOCK
#endif

#ifndef FOR_TEST
#define FOR_TEST private
#endif
```
the FOR_TEST macro is used to expose more methods.

##### 2) In the class that should be tested.
``` c++
#include "not_test.h"

class ToBeTested {
    CAN_MOCK void ThisMethodCanBeMockedButNotVirtualInProduction();
FOR_TEST:
    char* GetInputParamOnlyForTesting();
}
```

##### 3) In the test file TestToBeTested.h
``` c++
#include <test_helper.h>  // include this header before the ToBeTested.h
#include "ToBeTested.h"

FIXTURE(TestToBeTested) {
}
```

##### 4) The content in test_helper.h
``` c++
#define CAN_MOCK virtual
#define FOR_TEST public
```

## testngpp

#### 1. Be care that the "{" after FIXTURE(xxx) should be in the new line.
The test code below in TestXXX.h cause failure in generating TestXXX.cpp file.
``` c++
FIXTURE(TestXXX) {
    TEST(something is wrong) {
    }
};
```
It should be:
``` c++
FIXTURE(TestXXX)
{ // Must like this, or else generate TestXXX.cpp fail.
    TEST(something is wrong) 
    {  // Must be this, or else no testcase
    }
};
```