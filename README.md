
		mockcpp --- A C/C++ Mock Framework
		-------------------------------------
		https://github.com/sinojelly/mockcpp
		https://gitee.com/sinojelly/mockcpp


mockcpp is a jmock-like generic C/C++ Mock Framework, which doesn't use complex template technique which will result in very heavy compiling overhead.

## C/C++ test framework 
This project provided two tools for C/C++ testing.
| Name     | Description   |   Path       |         
| ----     | ----   | ----                 |
| mockcpp  | C/C++ mock framework | mockcpp|  
| testngpp | C/C++ test framework | mockcpp/tests/3rdparty/testngpp |

The sample project to use these tools is at :<br> 
https://gitee.com/sinojelly/testngpp-mockcpp-sample

You can use mockcpp with other C/C++ test framework, such as gtest, Catch2, CppUTest etc. The sample projects are at:<br>
https://gitee.com/sinojelly/gtest-with-mockcpp <br>
https://gitee.com/sinojelly/catch2-with-mockcpp

You can use mockcpp testngpp prebuilt libraries and header files, or use their source code.

If you use the prebuilt libraries, be sure they are built on the same os and compiler as the project that is being tested.

## mockcpp features
|  OS    | Compiler | Virtual method mock | Global function mock | Overloaded function mock |
|  ----  | ----     |         ----  |    ----  |   ----      |
|Linux   | GCC      |  Yes          | Yes      |   Yes       |
|Win10   | MinGW    |  Yes          | Yes      |   Yes       |
|Win10   | VS2019   |  Yes          | No       |   Yes       |

## testngpp features

|OS|Compiler|Base function| Memory leak check |Run in Sandbox| Parameterized test |
|----|----  |----         |----     |----     |----          |
|Linux|GCC  |Yes          |Yes      |Yes      | Yes          |
|Win10|MinGW|Yes          |No       |No       | Yes          |
|Win10|VS2019|Yes         |Yes      |Yes      | Yes          |

## Sample code
### Testngpp parameterized test sample
``` c++
FIXTURE(DataDrivenTest)
{
	DATA_PROVIDER( mydata, 3
		, DATA_GROUP(1, 2, 3) 
		, DATA_GROUP(77, 20, 97) 
		, DATA_GROUP(101, 503, 604));

	// @test(data="mydata")
	PTEST( (int a, int b, int c), this is a parameterized test)
	{
		ASSERT_EQ(c, add(a, b));
	}
};
```
## Documents for user
[New Build System Description](docs/BuildSystemDescription.md)(<font color=red>recommended for user and developers</font>)<br>
[Mockcpp manual english](docs/EnglishManual.md)<br>
[Mockcpp manual chinese](docs/ChineseVersionManual.md)<br>
[Mockcpp simple instruction](docs/SimpleUserInstruction_zh.md) (Chinese, recommended)<br>
[Testngpp simple instruction](tests/3rdparty/testngpp/docs/SimpleUserInstruction_zh.md) (Chinese, recommended)<br>
[Testngpp user manual](tests/3rdparty/testngpp/docs/ChineseUserManual.md) (Chinese)<br>

## Documents for developer
[Advanced Guide of Mockcpp](docs/AdvancedGuideOfMockcpp.md)<br>
[Mockcpp version history](docs/ProjectHome.md)<br>
[Software Architecture](docs/SoftwareArchitecture.md) (Chinese)<br>
[Mockcpp configure parameter](docs/Installation.md)<br>
[Mockcpp Build Guide](docs/BuildGuide) (a bit old)<br>
[Mockcpp Install Guide](docs/INSTALL) (old)


## Other documents for reference

[Testngpp MSVC Installation](tests/3rdparty/testngpp/docs/InstallationMSVC.md) (old)<br>
[Testngpp Introduction](tests/3rdparty/testngpp/docs/ProjectHome.md)


Email to the current maintainers may be sent to
<darwin.yuan@gmail.com>, <sinojelly@163.com>.

