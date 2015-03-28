

# 1. 背景 #

mock++是一个C/C++语言的mock框架。它最初出现的原因并不是为了重新发明轮子，也不是为了做Yet Another C++ mock framework。

在mock++出现之前，在互联网上可以找到的C++ Mock框架只有[mockpp](http://mockpp.sourceforge.net/); 在我们最初的敏捷开发实践中，它也就是我们唯一的选择。虽然[mockpp](http://mockpp.sourceforge.net/) 是一个优秀的框架，但它的实现使用了非常复杂的模版技术，这带来了漫长的编译时间，和非常晦涩难懂的编译错误信息。这对于TDD的步伐有着非常负面的影响。另外，[mockpp](http://mockpp.sourceforge.net/)所提供的功能在某些程度下无法满足我们的需要，我们在一开始选择向[mockpp](http://mockpp.sourceforge.net/)增加这些功能，但它的复杂模版所带来的负面影响促使我们最终决定开发一个新的框架。

mock++致力于如下目标：

  * 尽量少的使用模版技术，以提高编译性能，降低错误信息的晦涩性；
  * 框架产生的错误信息格式应该简单直观，信息应该全面，以帮助程序员更加快速的了解和定位问题；
  * 生成一个mock对象应该尽可能的简单；
  * 框架应该具备良好的扩展性，以应对各种特殊的需要；
  * 能够支持针对静态函数的mock；

它的实现很大程度上受到了[mockpp](http://mockpp.sourceforge.net/), [jmock](http://www.jmock.org/)的启发。

# 2. 介绍 #

mock++当前的实现支持七种类型的约束/行为：
  1. 调用次数约束 —— expects()/stubs()
  1. 调用者选择器 —— caller()
  1. 先行调用约束 —— before()
  1. 调用参数约束 —— with()
  1. 后行调用约束 —— after()
  1. 函数调用行为 —— will()/then()
  1. 标识符指定     —— id()

除了调用次数约束之外，所有其它的调用约束或行为都可以任意。但一旦你使用其中的一部分或全部，则必须按照上面所列的顺序给出。比如：

```
MOCK_METHOD(mock, method)
      .expects(once())
      .before(anotherMock, "close")
      .with(eq(1), any(), neq(2.0))
      .after(anotherMock, "open")
      .will(returnValue(true))
      .then(throws(std::exception))
      .id("myMethod");
```

## 2.1函数调用行为 ##

### 作用 ###

函数调用行为是mock机制中最重要的部分。也是mock存在最基本的价值所在。通过指定函数调用行为，mock更好得实现了stub的功能。

### 行为类型 ###

  * 返回一个值：        returnValue (value)
  * 返回一系列的值：returnObjectList (o1, o2,…)
  * 抛出异常：            throws (exception)
  * 忽略返回值：        ignoreReturnValue ()
  * 转调一个stub函数：invoke(stubFunction)
  * 重复返回一个值： repeat(value, times)
  * 步增一个值：increase(from, to)/increase(from)

### 用法 ###

函数调用行为通过_will_(behavior)/_then_(behavior)来指定。_then_()必须在_will_()之后。_will_()只会出现一次，但_then_()可以出现任意多次。比如：

```
     MOCK_METHOD(mock, foo)
                .stubs()
                .will(returnValue(10))
                .then(repeat(20, 2))
                .then(throws(std::exception))
                .then(returnValue(5));
```

当你使用_will_()/_then()_来指定**_函数调用行为_**时，指定的**_函数调用行为_**将会按照指定的顺序依次发生作用，如果指定的最后一个**_函数调用行为_**发生了作用之后，仍然有进一步的调用发生，如果其它约束条件都满足，则最后一个**_函数调用行为_**将持续发生作用。比如上一个例子将会产生如下结果：

```
    TS_ASSERT_EQUALS(10, mock->foo());
    TS_ASSERT_EQUALS(20, mock->foo());
    TS_ASSERT_EQUALS(20, mock->foo()); 
    TS_ASSERT_THROWS(mock->foo(), std::exception); 
    TS_ASSERT_EQUALS(5, mock->foo()); 
    TS_ASSERT_EQUALS(5, mock->foo()); 
    TS_ASSERT_EQUALS(5, mock->foo()); 
```

_returnValue_()用来指定匹配的调用所返回的单个值。如果它是指定最后一个**_函数调用行为_**，那么无论这个调用发生了多少次，指定的值总是作为返回值返回。如果它不是指定的最后一个**_函数调用行为_**，那么它仅仅返回一次指定的值。

在约束相同的情况下，你可能会希望一个调用每次返回的值是不相同的，这个时候你可以使用_returnObjectList_()。 mock++会按照你在_returnObjectList_()中指定的返回值的顺序在匹配的调用中依次返回。如果它是指定最后一个**_函数调用行为_**，那么当最后一个对象返回后，如果匹配的调用再次发生，mock++将会宣告一个错误。如果它不是指定的最后一个**_函数调用行为_**，那么下一个指定的**_函数调用行为_**将会产生作用。

另外，在当前的实现中，_returnObjectList_()的所允许指定对象个数是有限制的，这或许在某些情况下无法直接的满足测试的需求。这种情况下，你可以利用_then_()的无数量限制的特点来workaround。

当希望一个匹配的调用抛出异常时，可以通过_throws_(exception)来指定，即便函数定义的返回值类型是void。

如果函数定义的返回值类型不是**void** ，则一定要指定函数调用行为。 即使不关心返回值，也要通过_ignoreReturnValue_()来指定。


### 使用时机 ###

N/A

### 最好不使用的场景 ###

N/A

### 例子 ###
```
// 被依赖接口
struct ITextFileReader
{
    virtual void open(const char* name) = 0;
    virtual bool close() = 0;
    virtual String readLine() = 0;

    virtual ~ITextFile() {}
};
```

```
// 被测单元
struct AwkProcessor
{
    AwkProcessor(ITextFileReader* fileReader);

    String process(const char* textFileName, String script); 
};
```

```
// 测试用例
void test_should_throw_exception_if_open_file_failed ()
{
   MockObject<ITextFileReader> textFile;

     MOCK_METHOD(textFile, open)
                 .stubs()
                 .will(throwException(Exception( "File Not Exist" )));

    ///////////////////////////////////////////////
    AwkProcessor awkProcessor(textFile);

    TS_ASSERT_THROWS( awkProcessor.process("myFile.txt", "{print $2}"), Exception);
}

```

## 2.2 调用参数约束 ##

### 作用 ###

调用参数事实上是一种选择器，而不是一种约束。因为你可以在一个用例中，针对一个函数，指定多个mock调用方式。当被测函数调用这个mock函数时，mock++会找到第一个匹配所有选择器的调用方式，然后返回这个调用方式指定的结果（返回值，抛出异常，等等）。

但如果mock++找不到任何匹配的调用方式，则会让这个用例失败，这就让调用参数约束间接的成为一种约束。

另外，由于C/C++都支持输出参数的功能（通过指针/引用），在这种情况下，调用参数约束同时具备了stub的作用。

### 约束的类型 ###

输入参数约束：

  * 相等：   eq (value)
  * 不等：   neq (value)
  * 大于 :    gt (value)
  * 小于 :    lt (vlaue)
  * 内存匹配
    * mirror (object)
    * mirror (address, size)
  * 对象内容监控
    * spy(address, size)
  * 引用传值 : outBound(object)
  * 指针传值 : outBoundP(address)
  * 字符串匹配：
    * smirror (str)
    * startWith (str)
    * endWith (str)
    * contains (str)
  * 占位符：any ()

输出参数约束：

  * 通过引用得到输出参数：outBound (reference, 输入参数约束)
  * 通过指针得到输出参数：outBoundP (pointer, 输入参数约束)

### 用法 ###
调用参数约束通过_with_(contraint1, contraint2, …)指定。

如果想指定任何一个参数约束，则必须使用_with_()。在_with_()里，参数约束必须按照函数定义的参数顺序指定。

对于不需要指定约束的参数，可以通过_any_() 来忽略约束；最后一个有效约束后面的_any_()可以省略。

对于_eq_()和_neq_()约束，如果参数类型不能够进行相等性比较，则会引起编译错误；这种情况下，你可以通过重载双等号（==）来让类型具备相等性判断的能力。

_mirror_()用来约束内存内容的严格相等性。如果用来约束对象内容，则可以忽略size参数；如果用来约束非单一对象的内容，则需要通过size参数以字节为单位来指定内存的大小。

需要注意的是，当约束单一对象内容时，由于对齐问题所造成的padding字节内容的随机性，这种约束可能会带来错误的结果。对于C程序员，可以通过memset函数来清零内存。对于C++程序员，则可以通过重载对象的双等(==)操作符，然后通过_eq_()来指定相应的约束。

_startWith_()，_endWith_(), _contains_()用来约束字符串的存在性，_startWith_()约束参数是否以指定的字符串开始，_endWith_()约束参数是否以指定的字符串结束；而_contains_()则不关心指定的字符串在参数的任何位置，只关心它的存在。

_smirror_()用来约束字符串的相等性。在实现上，它事实上是一个 _mirror_()的特殊情况，只不过
mock++可以自动的计算size参数，不需要程序员自己指定。另外，_smirror_()没有_mirror_()的对象padding问题。

如果一个参数是out类型，则可以使用_outBound_()/_outBoundP_()来设置输出参数，此时，它们的**_输入参数约束_**应该被忽略。如果一个参数是inout类型，则可以通过_outBound_()/_outBoundP_()的**_输入参数约束_**参数来指定输入参数约束，如果输入参数约束不被关注，则可以忽略此参数。

### 使用时机 ###

  * 当输入参数的正确与否决定了被测函数功能的正确与否时；即无论如何重构你的实现，只要被调函数的对外表现以及内在功能没有发生变化，这样的约束总是保持正确，而一旦将这个约束删除，则会导致被测函数功能上的错误实现；
  * 当你的被测函数多次调用了一个函数，而这个函数在不同的情况下，需要返回不同的结果时，则可以考虑利用调用参数选择器的功能。（如果mock函数调用返回的结果都是值类型，也可以利用_will_ (returnObjectList(…))；
  * 当你需要通过被调函数的传出参数来获取值的时候。

### 最好不使用的场景 ###
  * 参数的值与实现的正确性无关，只是一种实现上的选择；
  * 对于log或debug函数的调用；

## 2.3 调用次数约束 ##

### 作用 ###

调用次数在很多情况下都是非常重要的约束。在这些情况下，调用的次数决定了实现的正确性。调用次数约束正是为了帮助程序员进行这类目的的验证而存在的。

### 约束的类型 ###
  * 一次：once ()
  * 准确的次数：exactly (n)
  * 至少：
    * atLeast (n)
    * atLeastOnce()
  * 至多：
    * atMost (n)
    * atMostOnce()
  * 不调用：never ()

### 用法 ###

调用次数约束通过_expects_(times)指定。其中times是约束的类型，比如_once_()；如果不关心调用次数，则使用_stubs_()。

### 使用时机 ###
  * 如果被调用方法可以修改系统状态，其调用的次数决定了实现的正确与否。也就是说，无论你如何重构被测方法的实现，只要你还需要通过被调方法提供服务，调用次数的约束总是成立的，则需要通过调用次数约束来约束重构的正确性。

### 最好不使用的场景 ###
  * 即使一个函数可能修改系统状态，但它被调用的次数对于实现的正确与否无关紧要；
  * 对于debug，log等对于函数功能无关紧要的调用；
  * 如果被调函数是一个查询函数，我们最好不要指定精确的次数，而是通过_atLeast_()来判断是否它曾经被调用过。或者干脆不关心其是否被调用。

### 例子 ###

```
// 被依赖接口
struct ITextFileReader
{
   virtual void open(const char* name) = 0;
   virtual bool close() = 0;
   virtual String readLine() = 0;

   virtual ~ITextFile() {}
};
```

```
// 被测单元
struct AwkProcessor
{
   AwkProcessor(ITextFileReader* fileReader);

   String process(const char* textFileName, String script); 
};
```

```
// 测试用例
void test_should_be_able_to_process_a_text_file()
{
   MockObject<ITextFileReader> textFile;

   String line1("1  A");
   String line2("2  B");
   String line3("3  C");

   char * fileName = "testFile";

   ///////////////////////////////////////////////
     MOCK_METHOD(textFile, open)
                 .expects(atLeast(1))
                 .with(endWith(fileName));

     MOCK_METHOD(textFile, close)
                 .expects(atLeast(1))
                 .will(ignoreReturnValue());

     MOCK_METHOD(textFile, readLine)
                 .stubs()
                 .will(returnObjectList(line1, line2, line3))
                 .then(throws(EOFError));

   ///////////////////////////////////////////////
   AwkProcessor awkProcessor(textFile);

   String result = awkProcessor.process(fileName, "{print $2}");
    
    TS_ASSERT_EQUALS("A\nB\nC\n", result);
}

```

## 2.4 调用顺序约束 ##

### 作用 ###

调用顺序约束主要用做验证目的。当调用顺序关乎到实现上的正确性时，调用顺序约束就成为方便的测试手段。

### 约束的类型 ###

  * 之前：
    * before (id)
    * before (object, id)
  * 之后：
    * after (id)
    * after (object, id)

### 相关类型 ###

标识符：id (id)

### 用法 ###

_before_()/_after()可以在一个调用规范中指定多次，以满足复杂的调用序列要求。比如:_

```
      MockObject<Interface> mock;

     MOCK_METHOD(mock, foo)
                 .stubs()
                 .will(returnValue(10))
                 .id("foo");

     MOCK_METHOD(mock, bar)
                 .stubs()
                 .will(returnValue(true))
                 .id("bar");

     MOCK_METHOD(mock, fix)
                 .stubs()
                 .after("foo")
                 .after("bar")
                 .will(returnValue(true));
```

当_before_()/_after()_需要参照的调用发生在其它对象上时，你可以通过另外一个参数来指定对象。比如：


```
      MockObject<Interface> mock0;
      MockObject<Interface> mock1;
      MockObject<Interface> mock2;
      
     MOCK_METHOD(mock0, foo)
                 .stubs()
                 .will(returnValue(10))
                 .id("foo");

     MOCK_METHOD(mock1, foo)
                 .stubs()
                 .will(returnValue(1))
                 .id("foo");

     MOCK_METHOD(mock2, foo)
                 .stubs()
                 .after(mock0, "foo")
                 .after(mock1, "foo")
                 .will(returnValue(11));
```

### 使用时机 ###

  * 当调用顺序的正确与否决定了被测函数功能的正确与否时；即无论如何重构你的实现，只要被调函数的对外表现以及内在功能没有发生变化，这样的约束总是保持正确，而一旦将这个约束删除，则会导致被测函数功能上的错误实现；

### 最好不使用的场景 ###

  * 除非调用顺序是一种设计上的需求，是唯一正确的实现，否则不要使用调用顺序约束。

## 2.5 标识符指定 ##

### 作用 ###

当一个**_调用描述_**用到_before_()/_after_()等调用顺序约束时，需要给被参照的**_调用描述_**一个标识符。

### 用法 ###

标识符通过_id_(identity)指定。其中identity是一个字符串。

在一个对象范围内，identity必须唯一，否则mock++则可能会引用到错误的**_调用描述_**。

### 使用时机 ###
  * 当且仅当当前**_调用描述_**被其它调用描述通过_before_()/_after_()引用时。

### 例子 ###
```
// 被依赖接口
struct IUserValidator
{
   virtual bool validate(const User&) const = 0;   
   
   virtual ~IUserValidator() {}
};
```

```
// 被测单元
struct SequenceUserValidator : public IUserValidator
{
   typedef std::list<IUserValidator*> Validators;

   CompositeUserValidator(Validators*);

   bool validate(const User&) const;

 private:
   Validators* validators;
};
```

```
// 测试用例
void test_should_invoke_validators_in_order()
{
   MockObject<IUserValidate> validator0;

   MockObject<IUserValidate> validator1;

   MockObject<IUserValidate> validator2;
    
   ///////////////////////////////////////////////
   SequenceUserValidator::Validators validators;

   validators.push_back(validator0);
   validators.push_back(validator1);
   validators.push_back(validator2);
   ///////////////////////////////////////////////
   User user("darwin");
   ///////////////////////////////////////////////
   MOCK_METHOD(validator0, validate)
                       .expects(atLeast(1))
		       .before(validate1, "v")
                       .with(eq(user))
                       .will(returnValue(true));

   MOCK_METHOD(validator1, validate)
                       .expects(atLeast(1))
                       .with(eq(user))
                       .will(returnValue(true))
                       .id("v");

   MOCK_METHOD(validator2, validate)
                       .expects(atLeast(1))
                       .with(eq(user))
                       .after(validate1, "v")
                       .will(returnValue(true));    
   ///////////////////////////////////////////////
   SequenceUserValidator validator(&validators);

   TS_ASSERT(validator.validate(user)); 
}

```

## 2.6 调用者选择器 ##

### 作用 ###

这个功能当前主要用于C语言的单元测试/集成测试。当一个函数会被一个流程的多个函数调用时，当其它的选择器很难以进行描述时，可以使用调用者选择器来缩小定位范围。

### 用法 ###

调用者选择器通过_caller_(function)来指定。其中，function是一个字符串，应该等于调用函数的名字。


# 3. 错误定位 #

当出现与mock有关的错误时，能够提供给尽量直观，详实的信息，以帮助程序员进行快速的定位是mock++的一个重要目标。

mock++以一种一致而简洁的方式来完成这个目标。其错误信息的标准格式分为两种：
  1. 只有错误信息，以文字的方式告知相关错误；
  1. 除了错误信息，还提供对一个方法实际调用的详细信息；

错误信息是一句文字描述，比如：

**expected invoking exactly 0 times, but it's actually invoked 1 times.**

而实际调用的详细信息就像一条调用规范，其基本格式为：

```
method(方法名)
    .expects(在规范中所指定的调用次数约束)
    .invoked(实际调用次数)
    .before(参照对象的类型, "参照mock规范的ID")
    .with(带有实际参数值的参数约束)
    .after(参照对象的类型, "参照mock规范的ID")
    .will(带有实际的行为值的行为规范)
    .id("本规范的ID")
```

实际调用的详细信息会按照用户编写的mock规范所列出的约束进行输出。

例如：

```
   MOCK_METHOD(collector, startTestCase)
     .expects(exactly(0))
     .invoked(1)
     .before(testcpp::TestFixture, "setUp")
     .with(eq((testcpp::TestCaseInfoReader*)0x00304388))
     .id("startTestCase");
```

在测试代码中，有一条用户编写的mock规范与之对应：

```
   MOCK_METHOD(collector, startTestCase)
     .expects(exactly(0))
     .before(fixture, "setUp")
     .with(eq((TestCaseInfoReader*)testcase[0]))
     .id("startTestCase");
```

这条详细调用信息描述的是：

你期待的调用次数是精确的0次（通过**expects(once())**来指定），但你实际的调用次数却是1次（通过**invoked(1)**得知实际的调用次数）。

所以，结合之前的那条错误信息：

**expected invoking exactly 0 times, but it's actually invoked 1 times.**

你就可以更加准确的知道你的错误所在。