testngpp使用简明指导

# 基本原理 #
testngpp的用例写在.h文件中，

编译前，自动根据.h生成用例辅助文件.cpp/.cxx，（调用testngppgen.exe或者python脚本完成）

编译后，生成.dll/.so文件，

运行时，由testngpp-runner.exe加载并执行。（如果用了sandbox，则是由testngpp-win32-testcase-runner.exe加载执行）

# 命令行 #
### testngpp-runner 命令行 ###
```
usage: testngpp-runner [options] testsuites ...

   -l listener       register test listener
   -L path           listener searching path
   -f pattern        filter patterns
   -t pattern        tags filter pattern
   -c number         maximum # of concurrent sandboxes
   -s                using sandbox runner
   -m                not use memory leak checker
```

### stdoutlistener 命令行参数 ###
```
   -c                colourful
   -s                show suite name
   -f                show suite name and fixture name
   -t                show tags
   -v                show verbose info
   -l level          set output level (0 ~ 3)  
```

其中level的具体含义
```
error/failure   -    always output
info            -    level 0   (output when level <= 0)
warning         -    level 1   (output when level <= 1)
skipped         -    level 2   (output when level <= 2)
```

### 典型应用 ###
```
testngpp-runner.exe 用例Suite名称.dll -L"listener_path" -l"testngppstdoutlistener -c -v"
```
其中：listener的-v 参数表示输出最详细的信息，包括用例名称。

```
testngpp-runner.exe 用例Suite名称.dll -L"listener_path" -l"testngppstdoutlistener -c -f"
```
其中：listener的-f 参数表示输出Fixture名字，用例简化为一个点。

# 样例 #

### 简单样例 ###
```
    TEST(测试: 1+1 = 2)
    {
        ASSERT_EQ(2, 1+1);
    }
```
常用的判断执行结果的宏有：
```
ASSERT_TRUE(expr) 
ASSERT_FALSE(expr) 
ASSERT_EQ(expected, value)
ASSERT_NE(expected, value)
ASSERT_DBL_EQ(expected, value)
ASSERT_DBL_NE(expected, value)
ASSERT_THROWS(expr, except)
ASSERT_THROWS_ANYTHING(expr)
ASSERT_THROWS_NOTHING(expr)
ASSERT_THROWS_EQ(expr, except, expected, value) // 执行expr后应该抛出except异常，并且expected与value相等
ASSERT_SAME_DATA(addr1, addr2, size) 
ASSERT_DELTA(x, y, d) // x与y的差小于d
```
这些宏都有对应的EXPECT版本（把ASSERT改为EXPECT即可），它与ASSERT版本的差异是：判断失败，该用例仍然继续执行。

### 使用Do-Cleanup避免资源泄漏 ###
把资源清理代码写在Cleanup中。
```
    TEST(__DO__/__CLEANUP__/__DONE__)
    {
        __DO__
            FAIL("I'm gonna fail");
            WARN("I should not be shown");
        __CLEANUP__
            INFO("I should be shown always");
        __DONE__
    }
```

### 使用Annotation ###
##### 使用id给用例起名字 #####
```
    // @test(id=face-to-south)
    TEST(robot should face to south after turn right)
    {
       robot.turnRight();
       ASSERT_TRUE(robot.faceToSouth());
    }
```

##### 使用depends设置用例的依赖关系 #####
```
    // @test(id=face-to-west, depends=face-to-south)
    TEST(robot should face to west after another turn right)
    {
       robot.turnRight();
       ASSERT_TRUE(robot.faceToWest());
    }
```

##### 使用tags设置Fixture/TestCase的标签 #####
> 标签的作用：在testngpp-runner.exe运行命令行中，通过-f pattern来指定运行哪些用例。
> 多个标签用空格隔开。
```
    // @fixture(tags="ft something")
    FIXTURE(RobotTest)
    {
        // @test(tags="ut slow")
        TEST(robot should face to west after another turn right)
        {
             robot.turnRight();
             ASSERT_TRUE(robot.faceToWest());
        }
    };
```

##### 使用memcheck设置Fixture/TestCase是否进行内存泄漏检查 #####
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

##### 使用data进行参数化测试 #####
参数化测试，是通过DATA\_PROVIDER提供多组参数，每一组参数传入用例，就成了一个可运行的用例。

下面这个简单的用例，因为有三组数据，所以它执行时会运行三个用例。

这种测试方法非常适合于 一个测试方法，有多组输入时，可以构成多个用例的情况。

```
FIXTURE(DataDrivenTest)
{
    DATA_PROVIDER( names, 1
                 , DATA_GROUP((const char*)"darwin") 
                 , DATA_GROUP((const char*)"arthur") 
                 , DATA_GROUP((const char*)"steven"));

    // @test(data="names")
    PTEST( (const char* name), this is a parametered() test)
    {
       INFO(name);
    }
};
```