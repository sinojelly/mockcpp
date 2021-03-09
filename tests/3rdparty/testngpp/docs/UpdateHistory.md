#这是testngpp的更新历史

# 更新历史 #

## testngpp在2010.7~11月的改进 ##

1、支持内存泄露检查。
（监控测试用例运行中的内存申请释放，如果有内存未释放在报错）

2、错误信息输出改进，尽可能把有价值的信息打印出来。
（避免只报告给用户一个SEH异常，因为它很可能是在异常捕获后又抛出了异常，这种时候非常需要原始的异常信息）

3、支持统计并显示Fixture初始化出错的问题。
（有时在Fixture构造时失败，原来testngpp在这种情况下不输出任何信息，现在会打印Fixture初始化失败原因和统计信息）

4、Generator支持-d参数指定生成辅助.cpp文件的目录，这种模式下会给每个测试文件生成一个对应的.cpp文件，并且把多个这样的.cpp链接为一个测试.dll。
（同时在generator中判断是否需要重新生成.cpp文件，这样就可以良好的支持增量编译了）

5、测试辅助.cpp文件包含对应测试文件.h时，使用相对路径。
（避免路径存在中文时，写辅助.cpp文件时会出错）

6、支持在命令行使用TestModule或者TestModule.dll加载测试dll文件。
（原来只支持不带dll的情况）

7、支持Visual Studio 2010。

8、增加自动化编译脚本build.sh和build\_install.sh（Linux&cygwin）以及它们的Windows版本(PowerShell脚本）。
（build.sh用于编译和运行测试用例，build\_install.sh用于编译并安装，详细用法参见代码根目录的BuildGuide）


## 2011.3.17 ##

1、内存泄露改为两次运行检查，避免误报。

背景：
> 如果用到全局的vector变量（或其它STL类型的变量），由于STL考虑到性能优化，容器申请的内存在容器元素删除时并不会释放，而是在vector析构时才释放。
> 这就会导致testngpp误报了一些内存泄露。
> 一般来讲，一个用例运行完应该把所有更改的数据恢复原样，所以一个用例第一次运行有泄露，如果再运行一次，没有了泄露，那么第一次运行的泄露应该也不是用户代码引起的，很可能是前面描述的那种情况。这种情况下，应该不报告内存泄露。所以有了下面策略。

策略：
  1. 如果一个用例运行第一遍有内存泄露，并不立即报告，而是运行第二次。
  1. 如果第二次没有内存泄露则该用例不报告内存泄露；如果第二次有泄露则报告内存泄露。

注意：
> 本次修改后，内存泄露检查在fixture析构之前进行的，暂时没有想到fixture析构之后检查的简单办法，而且由于有了两次检查机制，正常使用情况下，误报基本不会出现。所以暂时未处理此问题。

## 2011.3.20 ##

1、增加ASSERT\_DBL\_EQ/NE用于判断float/double/long double是否相等。

注意：判断时使用的fabs(a-b)<FLT\_EPSILON，不能用DBL\_EPSILON，否则有float参与运算时，精度达不到，就会出现0.7 != 0.7的情况。


## 2011.3.25 ##

1、内存泄露检查开关完善。

  1. 如果命令行加了-m选项，则该次执行不再检查内存泄露（即使在Fixture/TestCase级别打开也没用）。
  1. 如果命令行没有-m选项，默认是会进行内存泄露检查的，具体的Fixture/TestCase的内存泄露是否检查由它们的tags确定。
  1. Fixture/TestCase的Annotation中增加memcheck开关，用于控制是否进行内存泄露检查：memcheck = on 表示检查，off表示不检查，两者都没有也表示检查。
  1. Fixture设置的memcheck开关，会影响到它的每一个用例，但Fixture的设置优先级比TestCase的要低。（可以在Fixture级别关闭，再在TestCase级别打开）

> 使用示例如下：

```
//@fixture(memcheck=on)
FIXTURE(TestFixtureMemCheckOnAnnotation)
{
   TEST(fixture has been set to memcheck on, its tests all memcheck on)
   {
       char *p = new char; // should fail       
   }

   //@test(memcheck=off)
   TEST(fixture has been set to memcheck on, its test can use memcheck off to close mem leak check)
   {
       char *p = new char; // should success
   }
};
```

注意：
  1. 去掉了STOP/OPEN\_MEM\_CHECKER两个接口。

## 2011.3.26 ##
> Release 1.1