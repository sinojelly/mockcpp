

# Default Specification #

Default specification is defined by using _**defaults()**_, rather than _**expects()/stubs()**_. Relations between _**defaults()**_ and _**expects()/stubs()**_ could be thought as relations between **default** and **case** in C/C++ **switch** statements. If all specifications of a method of a mock object specified with _**expects()/stubs()**_ don't match one of your invocations to the method in question, the specification defined with _**defaults()**_ (if have any) will be used to perform the returned behavior.

This is a very useful feature, which helps you write your tests in a neater way.

```

struct TestCaseInfoReader
{
      virtual const std::string& getCaseName() const = 0;
      virtual const std::string& getFixtureName() const = 0;

      virtual ~TestCaseInfoReader() {}
};

class TestGeneralTestFilter: public TESTCPP_NS::TestFixture
{
      MockObject<TestCaseInfoReader> testcase;

      GeneralTestFilter* filter;

public:

      void setUp()
      {
            filter = new GeneralTestFilter("*TestFixture", "testcase?");

            MOCK_METHOD(testcase, getCaseName)
                      .defaults().will(returnValue("testcase1"));

            MOCK_METHOD(testcase, getFixtureName)
                      .defaults().will(returnValue("FooTestFixture"));
      }

     void tearDown()
     {
           testcase.reset();

           delete filter;
     }

     void test_should_be_able_to_recoginize_matched_fixture()
     {
          TS_ASSERT_TRUE(filter->matches(testcase));
     }

     void test_should_tell_unmatched_if_test_fixture_name_does_not_match()
     {
          MOCK_METHOD(fixture, getFixtureName)
             .stubs().will(returnValue("FooFixture"));

          TS_ASSERT_FALSE(filter->matches(testcase));
     }

     void test_should_tell_unmatched_if_testcase_name_does_not_match()
     {
          MOCK_METHOD(fixture, getCaseName)
             .stubs().will(returnValue("testcase10"));

          TS_ASSERT_FALSE(filter->matches(testcase));
     }
};

```

In this example, the default behaviors of methods **_getFixtureName()_** and **_getCaseName()_** return matched names. So the first test case is to test the happy path, which is pretty simple, you only need to write one assertion to test the class **`TestFilter`**. The latter 2 test cases test for the unmatched cases, so in each test case the _**stubs()**_ is used to "HIDE" the default behavior in order to do exceptional tests.

Furthermore, for one method, you can specify more than one default specification, distinguished by the _**with()**_ selectors. When falling in the default category, mockcpp will try to select a matching default specification. If multiple default specifications match your invocation, the first one will be selected. In the current implementation, the first matched default specification defined in a test would be the one chosen by mockcpp, but this might change in later version, so don't make your tests rely on this. Instead, you should make your default specification distinguishable.

```

struct TestFilter
{
      virtual bool matches(TestCaseInfoReader* ) const = 0;

      virtual ~TestFilter() {}
};

struct TestCase : public TestCaseInfoReader
{
      virtual void run() throw (AssertionFailure) = 0;

      virtual ~TestCase() {}
};

class TestTestCaseRunner : TESTCPP_NS::TestFixture
{
      MockObject<TestFilter> filter;
      MockObject<TestCase> testcase;

      TestRunner* runner;

public:
      void setUp()
      {
            runner = new SandboxTestRunner();

            MOCK_METHOD(filter, matches)
                    .defaults()
                    .with(eq((TestCase*)testcase)
                    .will(returnValue(true));

            MOCK_METHOD(filter, matches)
                    .defaults()
                    .with(neq((TestCase*)testcase)
                    .will(returnValue(false));
      }

     void tearDown()
     {
           filter.reset();
           testcase.reset();

           delete runner;
     }

     void test_should_run_matched_test_cases()
     {
           MOCK_METHOD(testcase, run).expects(once());

           runner->run(testcase, filter);

           testcase.verify();
     }

     void test_should_not_run_unmatched_test_cases()
     {
          MockObject<TestCase> unmatchedTestCase;
         
          MOCK_METHOD(unmatchedTestCase, run)
                  .expects(never());

           runner->run(unmatchedTestCase, filter);

           unmatchedTestCase.verify();
     }

     void test_should_throw_an_AsstionFailure_exception_if_the_test_case_did_that()
     {
           MOCK_METHOD(testcase, run)
                 .stubs().will(throws(AssertionFailure("AssertionFailure"));

           TS_ASSERT_THROWS(runner->run(testcase, filter), AssertionFailure);
     }

     void test_should_throw_a_CrashException_if_the_test_case_crashed()
     {
           MOCK_METHOD(testcase, run)
                 .stubs().will(die());

           TS_ASSERT_THROWS(runner->run(testcase, filter), CrashException);
     }
};

```

In this example, we used the _**defaults()**_ to specify the matched test case and unmatched test cases, which helps us to focus on the aspects which we intent to test in later test cases.

# Multiple Inheritance #

In order to make mockcpp support multi-inheritance, you need to make sure the configured option **--disable-multi-inheritance** was not specified when you built mockcpp. Besides, you also need to be sure the interface you are trying to mock does not inherit from more than **N** other interfaces, and the **N** represents "allowed maximum number of inherited interfaces" of an interface. It was specified with the configured option **max\_inheritance=N** at the build time. Currently, the default value is 2, and maximum allowed value is 5. If your interface inherits from more than that, you should probably reconsider your design, or you will not be able to mock it. The reason we chose this number was not technical,  but, according to our experience, when an interface needs to inherit from many other interfaces, usually it implies a **bad smell**.

The similar constraint exists in the setting of allowed maximum number of methods in one interface, which is specified with the configured option **max\_vtbl\_size=N** (N cannot be specified as the number more than 50, and its default value is 20). Note that the method number includes all methods defined in an interface and all its parents, normal methods and destructors. If an interface contains more than 50 (still too many, in our opinion), it's probably too fat -- having too many responsibilities.

Yes, I lied. It has technical reasons of having these constraints. Due to the usage of C++ template (we have tried desperately to reduce it) in our implementation, the compiling time and generated binary size will increase with the growth of values of these settings. If you choose **max\_inheritance=5** and **max\_vtbl\_size=50**, the compiling time would be far slower than specifying them as 2 and 20.

Non-public and virtual inheritance are not supported, because they are pretty tricky and we haven't seen any use case from our experience. So we simply choose not to support them until they are proved usefully someday.


# Lifecycle Management #

A big difference between C++ and other more-modern languages is that C++ developers have to manage the lifecycle of objects on their own. The fact of an injected object being a real object or just a mocked one is totally transparent for CUTs (Class Under Test), so a mock object might be performed a deletion operation by the CUT in various design reasons.

Therefore, a useful mock framework should support that a mock object is able to be deleted safely, and more: afterwards, the deleted mock object should still be able to verify whether the deletion actually happens, since this operation is part of design, otherwise a memory leakage will occur.

mockcpp supports this in a easy way:
  * If an injected mock object should be deleted by CUT, **willBeDeleted()** method of **MockObject** should be called before it's deleted by CUT;
  * If it should not be deleted by CUT, **willKeepAlive()** should be invoked; and
  * If the deletion is not a concern, you don't need to do anything.

**willBeDeleted()** and **willKeepAlive()** are used for the purpose of verification. No matter they are called or not, the mock object could be deleted safely anyway.

Here is an example:

```

class TestGeneralTestFilter : public TESTCPP_NS::TestFixture
{
      MockObject<NameMatcher> testcaseMatcher;

public:

     
     void tearDown()
     {
            testcaseMatcher.reset();    
     }

     void test_should_delete_the_matcher_if_it_is_injected_as_composite_when_object_is_deleted()
     {
            GeneralTestFilter* filter = 
                  new GeneralTestFilter(testcaseMatcher, true);

            testcaseMatcher.willBeDeleted();

            delete filter;

            testcaseMatcher.verify();
     }

     void test_should_not_delete_the_matcher_if_it_is_injected_as_non_composite_when_object_is_deleted()
     {
            GeneralTestFilter* filter = 
                  new GeneralTestFilter(testcaseMatcher, false);

            testcaseMatcher.willKeepAlive();

            delete filter;

            testcaseMatcher.verify();
     }

     void test_should_be_able_to_tell_whether_a_test_case_matches_the pattern_hold_by_matcher()
     {
            GeneralTestFilter* filter = 
                  new GeneralTestFilter(testcaseMatcher, false);

            MockObject<TestCase> testcase0;
            MockObject<TestCase> testcase1;

            MOCK_METHOD(testcaseMatcher, matches)
                   .stubs().with(eq((TestCaseInfoReader*)testcase0))
                   .will(returnValue(false));

            MOCK_METHOD(testcaseMatcher, matches)
                   .stubs().with(eq((TestCaseInfoReader*)testcase1))
                   .will(returnValue(true));

            TS_ASSERT_FALSE(filter->matches(testcase0));
            TS_ASSERT_TRUE(filter->matches(testcase1));

            delete filter;
     }

};

class GeneralTestFilter
{
public:
     
     GeneralTestFilter(NameMatcher* matcher, bool isComposite)
           : m_isComposite(isComposite), m_testcaseMatcher(matcher)
     {}
     
     ~GeneralTestFilter()
     {
           if(isComposite)
           {
                 delete matcher;
           }
     }

     // other code

private:
     bool m_isComposite;
     NameMatcher* m_testcaseMatcher;
};

```

There are 3 test cases in this example, the first one tests that the injected matcher should be deleted with the destruction of the CUT object, because it was injected as composite; the second one tests the opposite; and the last one is used to test the other aspect of the CUT, it doesn't care about the lifecycle of the injected matcher.

If an interface inherits from more than one other interfaces, and it's expected to be deleted by the injecting CUT, you should explicitly points out that the injected mock object might be used as other interfaces. Because the CUT might delete it as a pointer of any interfaces it inherits, and it's better to keep the implementation of CUT black. mockcpp has no way to deduce its inherited interface type unless you tell them to mockcpp, due to the lack of reflection of C++ language.

Once again, this feature should only be used in multi-inheritance cases, although it does not harm at all in single-inheritance cases.

Here is an example:

```

struct Base0
{
    virtual void base00() = 0;
    virtual ~Base0() {}
};

struct Base1
{
    virtual void base01() = 0;
    virtual ~Base1() {}
};

struct Interface : public Base0, public Base1
{
   virtual void foo() = 0;
   virtual ~Interface() {}
};

class TestBar : public TESTCPP_NS::TestFixture
{
public:

    void test_should_do_something()
    {
          MockObject<Interface> iface;

          Bar * bar = new Bar(iface);

          iface.mightBeUsedAs<Base1>();

          iface.shouldBeDeleted();

          delete bar;

          iface.verify();
    }
};

```


# Dynamic Cast #

mockcpp supports **dynamic\_cast** quite well. The behavior of **dynamic\_cast**-ing a mock object is exactly the same as **dynamic cast**-ing a normal C++ object.

Take an example:

```
////////////////////////////////////////////////////////////////
struct BillingObject
{
      enum Type
      {
          UNKNOWN = 0;
          CALL,
          SMS,
          INET
      };

      virtual Type getType() const = 0; 

      virtual ~BillingObject() {}
};

////////////////////////////////////////////////////////////////
struct Call : public BillingObject
{
      virtual const std::string& getPhoneNumberOfOriginator() const = 0;
      virtual const std::string& getPhoneNumberOfTerminator() const = 0;
      virtual unsigned int getDurationInSeconds() const = 0;

      virtual ~ShortMessage() {}
};

////////////////////////////////////////////////////////////////
struct InternetAccess : public BillingObject
{
      virtual const std::string& getPhoneNumber() const = 0;
      virtual unsigned int getDurationInSeconds() const = 0;
      virtual unsigned int getTransferSize() const = 0;

      virtual ~InternetAccess() {}
};

////////////////////////////////////////////////////////////////
struct Bill
{
     unsigned char type;
     std::string originator;
     unsigned int originatorFee;
     std::string terminator;
     unsigned int terminatorFee;
     unsigned int duration;
     unsigned int size;

     Bill() 
           : type(BillingObject::UNKOWN)
           , originator("")
           , originatorFee(0)
           , teminator("")
           , terminatorFee(0)
           , duration(0)
           , size(0)
     {}
};

////////////////////////////////////////////////////////////////
class BillingManager
{
public:

      void billing(const BillingObject* billingObject, Bill& bill);

// Other methods and attributes
};

```

In this design, _**billing()**_ always accepts an object of type **`BillingObject`**. However, in its implementation, in order to generate bills correctly, **billingObject** will be downcast to a concrete type according to the returned value of the method _**getType()**_.

Here is the test fixture for testing **BillManager**:

```

class TestBillingManager : public TESTCPP_NS::TestFixture
{
public:
 
     void test_should_be_able_to_generate_bill_of_a_CALL_type_billing_object()
     {
           BillingManager manager;
           Bill bill;

           MockObject<Call> billingObject;

           MOCK_METHOD(billingObject, getType)
                     .stubs().will(returnValue(BillingObject::CALL));

           MOCK_METHOD(billingObject, getPhoneNumberOfOriginator)
                     .stubs().will(returnValue(std::string("123456789")));

           MOCK_METHOD(billingObject, getPhoneNumberOfTerminator)
                     .stubs().will(returnValue(std::string("987654321")));

           MOCK_METHOD(billingObject, getDurationInSeconds)
                     .stubs().will(returnValue((unsigned int)78));
           
           manager.billing(billingObject, bill);

           TS_ASSERT_EQUALS(BillingObject::CALL, bill.type);
           TS_ASSERT_EQUALS("123456789", bill.originator);      
           TS_ASSERT_EQUALS("987654321", bill.terminator);      
           TS_ASSERT_EQUALS(78, bill.duration); 
           TS_ASSERT_EQUALS(0, bill.size); 
           TS_ASSERT_EQUALS(80, bill.originatorFee); 
           TS_ASSERT_EQUALS(20, bill.terminatorFee); 
     }
};

```

The CUT code:

```

void BillingManager::billing(const BillingObject* billingObject, Bill& bill)
{
      if(billingObject->getType() == BillingObject::CALL)
      {
            Call* call = dynamic_cast<Call*>(billingObject);
            // "call" should not be 0
            if(call == 0)
            {
                  throw Error("Invalid billing object");
            }

            bill.type = call->getType();
            bill.originator = call->getPhoneNumberOfOriginator();
            bill.terminator = call->getPhoneNumberOfTerminator();
            bill.duration = call->getDurationInSeconds();
            bill.size = 0;
            unsigned int minutes = (bill.duration/60 + (bill.duration%60>0?1:0));
            bill.originatorFee  = minutes* 40;
            bill.terminatorFee  = minutes* 10;
            return;
      }
      // Other code
};

```

Because the interface you mocked was **Call**, the parameter "pointer to billingObject" of _**billing()**_ could be successfully downcast to a pointer to **Call**. If you specify the mocked interface as any other type, the downcast operation will return 0.

In previous example, according to the implementation of the method _**billing()**_, the following test case will pass.

```
     void test_should_throw_an_Error_exception_if_the_object_type_mismatch()
     {
           BillingManager manager;
           Bill bill;

           MockObject<InternetAccess> billingObject;

           MOCK_METHOD(billingObject, getType)
                     .stubs().will(returnValue(BillingObject::CALL));
           
           TS_ASSERT_THROWS(manager.billing(billingObject, bill), Error);
     }
```

Please note that mock++ does not provide this capabities for MSVC, due to the evil ABI definition of type info.  ( it proves again that -- Micro$oft sucks, in terms of techniques. It should develop products only for non-developers).

# Object Assignment #

The assignment operation of a mock object is not allowed in mockcpp (the method **`MockOject& operator=(const MockObject&)`** is private). It has basically no value to provide this operation, and it will bring tricky issues and the complexity of implementation.

However, copy constructor is allowed, which means this operation is valid:

```

MockObject<Foo> foo1;
MockObject<Foo> foo2 = foo1;

```

But this is not:

```

MockObject<Foo> foo1, foo2;
foo2 = foo1;

```

Before we explain the reason why one is allowed but another is not, I'd like to take a few minutes to introduce the difference between the assignment operation and the copy constructor, in case you are not familiar with it.

For basic data types of C++, these two kinds of operations are basically identical, which means the effect of the following two ways are pretty much the same:

```
int a = 10;
```

and

```
int a;
a = 10;
```

However, for the abstract types of C++, the difference is bigger. In the example:

```
Foo foo1;
Foo foo2 = foo1;
```

The object _**foo1**_ is constructed with the default constructor _**Foo()**_. The object _**foo2**_ is constructed with the copy constructor _**Foo(const Foo&)**_.

However, in this example:
```
Foo foo1, foo2;
foo2 = foo1;
```

The object _**foo2**_ is firstly constructed with the default constructor and then it's performed an assignment operation (the method `Foo& operator=(const Foo&)` is invoked) in the second statement.

The implications of these two ways are utterly difference, the first way means object _**foo2**_ is initialized according to the value of the object _**foo1**_. The latter, however, means the object _**foo2**_ is changed to the value of _**foo1**_.

Back to the issue of mockcpp, the disability of the assignment operation of a mock object implies a fact: You can construct it both with default constructor and copy constructor. However, once a mock object is constructed, it's not allowed to be changed to another one any longer.

Besides, you must be aware of that, a mock object constructed with the default constructor is a freshly new object, but ones constructed with the copy constructor are merely references to the original mock object. For example:

```
MockObject<Foo> foo1;
MockObject<Foo> foo2 = foo1;
MOCK_METHOD(foo2, foo).stubs().will(returnValue(10));
```

When you set a specification of the method _**foo()**_ of object _**foo2**_, you are actually setting the specification to the method _**foo()**_ of object _**foo1**_.

Note that, the usage of constructing a mock object with copy constructor is not encouraged, mockcpp does not promise the safety of copy-constructed mock objects (no reference count is implemented), which means, once the referenced mock object is deleted, accessing the referencing mock object might cause crash.