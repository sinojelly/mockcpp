# mockcpp使用方法简明指导 #

## mock工具介绍 ##
mock工具的作用是指定函数的行为（模拟函数的行为）。可以对入参进行校验，对出参进行设定，还可以指定函数的返回值。

## 几个相关概念 ##
(1)mock规范：每个MOCKER(function)开始，跟一系列的.stubs、.with、.will等的内容的整体，称为一个mock规范。

(2)核心关键字：指stubs/defaults/expects/before/with/after/will/then/id等这些直接跟在点后面的关键字。

(3)扩展关键字：指once()/eq()/check()/returnValue()/repeat()等这些作为核心关键字参数的关键字。

下面，请看两段mockcpp的使用规范示例代码，其中带“/”或者“|”的表示在该位置可能有多种选择；带中括号的表示是可选的。

## mockcpp的特点 ##

(1) 开源。

(2) mockcpp支持C函数的mock和虚接口的mock。

(3) VC下，mockcpp支持cdecl和stdcall调用约定的函数。（socket/bind/ftp等函数就是stdcall调用约定的）

(4) mockcpp的语法清晰、简单，容易理解（参见下面两个sample）。

(5) mockcpp的错误信息提示非常友好，包含完整的mock规范定义和实际运行情况（参见下面的样例）。

```
Unexpected invocation: the invocation cannot be found in allowed invoking list.
Invoked: add((int)0x1/1, (int)0x2/2)
Allowed:
method(add)
  .stubs()
  .invoked(0)
  .with(eq((int)0xa/10), eq((int)0x14/20))
  .will(returnValue((int)0xc8/200));
```

(9) mockcpp是强类型检查的，强类型检查也是C/C＋＋的一个优势，比如eq(3)，如果调用函数时用的参数是_UL，那么就应该用eq((_UL)3)，对于函数返回值也是一样，声明的返回值类型应该跟mock中定义的一致。mock中支持类型检查，可能会发现更多代码BUG的。

C＋＋强类型检查，也是为了提高程序安全性，有些问题通过类型检查在编译期可以发现的，就不需要在运行时再痛苦的定位了。C/C＋＋的强类型检查是优势，我们不用把它抛弃了。

## mockcpp的sample代码 ##

下面，请看两段mockcpp的使用规范示例代码，其中带“/”或者“|”的表示在该位置可能有多种选择；带中括号的表示是可选的。

### 一段简单的mockcpp使用sample代码：（带有完整核心关键字） ###
```
TEST(mockcpp simple sample)
{
    MOCKER(function) / MOCK_METHOD(mocker, method)
        .stubs() / defaults() / expects(once())
        [.before("some-mocker-id")]
        [.with(eq(3))]
        [.after("some-mocker-id")]
        .will(returnValue(1)) / .will(repeat(1, 20))
        [.then(returnValue(2))]
        [.id("some-mocker-id")]
}
```


### 下面是一段比较详细的mockcpp使用sample代码：（带有完整扩展关键字） ###
```
TEST(mockcpp detail sample)
{
    MOCKER(function) / MOCK_METHOD(mocker, method)
        .stubs() / defaults() / expects(never() | once() | exactly(3) | atLeast(3) | atMost(3) )
        [.before("some-mocker-id")]
        [.with( any() | eq(3) | neq(3) | gt(3) | lt(3) | spy(var_out) | check(check_func)
                | outBound(var_out) | outBoundP(var_out_addr, var_size) | mirror(var_in_addr, var_size)
                | smirror(string) | contains(string) | startWith(string) | endWith(string) )]
        [.after("some-mocker-id")]
        .will( returnValue(1) | repeat(1, 20) | returnObjectList(r1, r2)
                | invoke(func_stub) | ignoreReturnValue()
                | increase(from, to) | increase(from) | throws(exception) | die(3))
        [.then(returnValue(2))]
        [.id("some-mocker-id")]
}
```


#### 注 ####
1、扩展关键字分类：
expects里面的叫匹配关键字（Matcher）；
with里面的叫约束关键字（Constraint）；
will/then里面的叫桩关键字（Stub）。

2、spy的作用是监视执行该被mock的函数function被调用时传入的值，会保存在var\_out中，供用例中其它地方使用。

3、outBound的作用是设置函数function的出参的值。多半是把该值作为后面部分被测代码的输入。（注意与spy区别）

4、outBoundP，与outBound作用相同，只是用于数组的情况。

5、mirror的作用是对数组类型的入参进行检查。（outBoundP是设置出参的值，两者是不同的）

6、check的作用是进行定制化的入参检查，比如只检查结构体的部分成员。可以通过函数指针或者仿函数的方式指定，用仿函数还能预先保存一些值，非常方便。（有些mock工具叫它follow）

7、check也能够用于设置出参的情况。

8、die表示程序退出，并且返回指定的值。它是异常退出，用于模拟一个函数调用崩溃的情况。

9、increase(from, to)，表示依次返回from到to的对象，任何重载了++运算符的对象都可以用。

10、outBound和outBoundP都可以带一个约束参数，用于对参数进行检查，因为有同时作为in和out的参数。（如：outBound(var\_out, eq(3))  ）


### 下面是结合上面sample的mockcpp使用说明 ###

1、mock C函数或者类的静态成员方法用MOCKER;
> mock 类的非静态成员方法需要先用`MockObject<MyClass> mocker;`声明一个mock对象，再用MOCK\_METHOD(mocker, method)来mock指定方法。

2、紧跟着MOCKER/MOCK\_METHOD之后的是stubs、或者defaults、或者expects，三个必须有一个。（这是与AMOCK不同的地方，在这个层次上确定这三个关键字必须有一个，可以让mock语法更清晰）
> stubs 表示指定函数的行为，不校验次数。
> expects 与stubs的区别就是校验次数。（.expects(once()) / .expects(never()) / .expects(exactly(123))）
> defaults 表示定义一个默认的mock规范，但它优先级很低；如果后面有stubs或者expects重新指定函数行为，就会按照新指定的来运行。（一般用在setup中）

3、用will指定函数的返回值；
> 如果要指定20次调用都返回1，则用.will(repeat(1, 20))；
> 要指定第一次返回1，第二次返回2，第三次返回3，就用
```
      .will(returnValue(1))
      .then(returnValue(2))
      .then(returnValue(3))
```
> 如果你指定了前三次的返回值依次为1、2、3，那么第四次、第五次调用，都是返回最后的返回值3。

4、用id给一个mock规范指定一个名字，然后可以用after、before来指定多个mock应该的调用顺序。
> 注意before在with前，after在with后，id在整个mock规范的最后。

5、使用mockcpp时，校验是否按照mock规范进行调用的，应该用：
GlobalMockObject::verify();
verify之后，会自动执行reset。（如果是对象的mock，应该用mocker.verify()，同样也会自动reset。）

如果单单只想reset，也可以：(这很少见，难道前面你定义的mock规范都不想要了，也不校验？那为何要定义呢？)
GlobalMockObject::reset();

> 一般是在teardown中调用verify。

6、如果要对某个函数（比如add）指定多个调用不同的行为（多个mock规范），比如调用入参为1，2时，返回30；调用入参为3、4时，返回700。那么可以这样写：
```
MOCKER(add)
  .stubs()
  .with(eq(1), eq(2))
  .will(returnValue(30));

MOCKER(add)
  .stubs()
  .with(eq(3), eq(4))
  .will(returnValue(700));
```

7、如果对于6的例子，还希望校验次数，则把stubs改为expects(once())这样的即可。

8、如果对于6的例子，还希望对调用顺序做严格要求，必须第一次调用参数是1、2，第二次是3、4，那么可以这样写：
```
MOCKER(add)
  .stubs()
  .with(eq(1), eq(2))
  .will(returnValue(30))
  .id("first");

MOCKER(add)
  .stubs()
  .with(eq(3), eq(4))
  .after("first")
  .will(returnValue(700));
```

9、指定出参的方法（例子中出参为指针类型，出参为引用的outBound(var)即可，更加简单）
```
void function(int *val)
{
}
```
应该用下面方式来指定出参：
```
int expect = 10;
MOCKER(function)
  .stubs()
  .with(outBoundP(&expect, sizeof(expect)));
```

10、对同一个函数指定多个mock规范，那么这些mock规范一般是应该在输入方面有差异的，否则没必要指定多个。而且，在输入方面无差异的两个mock规范，让mockcpp内部无法判断是否满足规范约束。
比如，测试函数 void function(int in, int &out)，前面一个是入参，后面一个是出参，希望in为1时，输出out为100，in为2时，输出out为3，那么应该这样写：

```
int out = 100;
MOCKER(function)
  .expects(once())
  .with(eq(1), outBound(out));

out = 3;
MOCKER(function)
  .expects(once())
  .with(eq(2), outBound(out));
```

假设你把eq(1)、eq(2)写为any()，那么mockcpp会判断你的两个调用function(1, out)和function(2, out)都符合第一个mock规范，从而报告与你定义的次数1不匹配。


11、有时候需要对同一个函数指定多个mock规范，并且它们是有规律的，那么可以借助循环来简化代码。
假设要mock的函数是void function(int in)，希望它依次以0、1、2...10为入参被调用，每次都调用一次，那么可以像这样写：

```
MOCKER(function)
  .expects(once())
  .with(eq(0))
  .id("0");

for (int i = 1; i <= 10; i＋＋)
{
  MOCKER(function)
    .expects(once())
    .with(eq(i))
    .after(string(i - 1))
    .id(string(i));   
}
```

12、spy约束关键字应用举例。
spy的作用是监视，下面例子，就是监视test在调用func时，传入的值是多少。有些时候，测试用例需要这样的值，这种方式是很有效的。
```
void func(int var)
{
}
void test()
{
    int var = 10;
    func(var);
}
TEST(sample test)
{
    int var;
    MOCKER(func)
        .stubs()
        .with(spy(var));
        .with(eq(10));

    test();
    ASSERT_EQ(var, 10);    
}
```

13、check约束关键字的用法。
约束关键字中，有很多都是对入参进行检查的，比如eq、neq、lt、gt等等，但它们都只实现了非常简单的检查。
如果用户想做一个定制化的检查，那么就可以用check。
例1：假设用户想检查入参p指向的结构的字段b是不是10，那么可以如下这样写：
```
struct AA 
{
    int a;
    int b;
};

void func(int in, AA *p)
{
}

// 实现一个检查函数，入参类型跟要检查的入参相同，返回值为bool，返回true表示检查通过。
bool check_func(AA *p)
{
    if ( p->b == 10)
    {
        return true;
    }
    return false;
}

TEST(sample test)
{
    MOCKER(func)
        .stubs()
        .with(any(), check(check_func));
    func(in, p);
}
```

例2：如果需要检查b是否小于某个给定的数，而且有多个用例，每个用例中与b比较的数不同，则可以使用仿函数的方式。
```
// 实现一个仿函数类，即重载“()”运算符的类。
struct CheckFunctor 
{
    CheckFunctor(int _base) : base(_base){}
    bool operator ()(AA *p)
    {
        if (p->b < base)
               return true;
        return false;
    }
    int base;
};

TEST(b should less than 100)
{
    MOCKER(func)
        .stubs()
        .with(any(), check(CheckFunctor(100)));
    func(in, p);
}

TEST(b should less than 200)
{
    MOCKER(func)
        .stubs()
        .with(any(), check(CheckFunctor(200)));
    func(in, p);
}
```

14、只要打桩了，那么就不会运行原函数，都是与mock规范匹配，运行桩。
下面例子中，对add的入参为1、2的情况打桩了，如果调用了入参为2、3的情况，则会报告调用在允许的mock规范列表中不存在的错误。
```
TEST(sample test)
{
    MOCKER(add)
        .expects(once())
        .with(eq(1), eq(2))
        .will(returnValue(100));

    ASSERT_EQ(100, add(1, 2));
    ASSERT_EQ(50, add(2, 3));
}
```

15、带有返回值的函数，MOCKER后面必须有will，否则mockcpp认为无返回值，校验时会发现返回类型不匹配。