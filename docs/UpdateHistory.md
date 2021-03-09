# testngpp在2010.7~12月的改进 #

  1. 支持多种的xUnit测试框架。
（支持testngpp、gtest、CppUnit、CppUTest）

> 2 支持spy约束关键字。
（用于窥探给某个被mock函数传入的入参）

> 3 支持check约束关键字。
（以函数，或者仿函数对象来自定义参数检查规则）

> 4、支持Windows 7下的ApiHook功能。
（原来的ApiHook功能在Win7上使用有异常）

> 5、支持Linux下的ApiHook功能。
（之前只支持Windows，现在支持了Linux，在Linux下页可以不用MOCKABLE来进行C函数的mock ）

> 6、支持64位平台下的ApiHook功能。（增加限制：一个用例中打桩的函数不超过10个）
（在Windows XP 64bit + VS2008和Linux + GCC 下测试通过）

> 7、支持VC stdcall调用约定的函数的mock。
（stdcall调用约定的函数，清栈的方式与默认不同。VC下socket操作函数都是stdcall）

> 8、增加自动化编译脚本build.sh和build\_install.sh（Linux&cygwin）以及它们的Windows版本(PowerShell脚本）。
（build.sh用于编译和运行测试用例，build\_install.sh用于编译并安装，详细用法参见代码根目录的BuildGuide）

> 9、在verify之后，自动执行reset。
（无论是全局函数mock，还是对象mock，都支持这种方式，用户不用调用reset）

  1. 、[DEV](DEV.md) 梳理了Windows和Linux用例的差异，现在两种平台上都可以运行通过所有用例。

# 20110326 #

> Release 2.5

# 20111002 #

> Release 2.6

changes:
  1. reduce lib file size.
  1. fix compile error when compile for cppunit.
  1. add default mocker for mockable.