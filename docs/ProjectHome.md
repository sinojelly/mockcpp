mock++ is a jmock-like generic easy-of-use C++ Mock Framework, creating a mock object by mock++ is virtually as easy as using jMock.

IMPORTANT: The repository has been move to [bitbucket](https://bitbucket.org/godsme/mockcpp), in case you need to checkout the latest change.

## Current Release ##

mock++ 2.6 is avaliable for downloading now, the main changes of this release are:

  * supported both IA32 & IA64 platform (MSVC & GCC)
  * supported using parameter directly while setting an eq() constraint.

## Previous Releases ##


### mock++ 2.4 ###

mock++ 2.4 is avaliable for downloading now, the main changes of this release are:

  * Added support for mocking free functions & static class methods without using macro MOCKABLE (only for MSVC);
  * Fully switched the building system to [cmake](http://www.cmake.org);
  * Changed some implementation to work with [TestNG++](http://code.google.com/p/test-ng-pp)。

### mock++ 2.3 ###

  * Automatic type inference of integer types (`long`/`unsigned long`, `int`/`unsigned int`, `short`/`unsigned short`, `char`/`unsigned char`) is supported;
  * Using [CMake](http://www.cmake.org/) as the building system, rather than putting MSVC project files into repository directly.

### mock++ 2.2 ###

  * MSVC 2008 is supported, except for the RTTI capabilities (which means  dynamic\_cast does not work correctly, basically, it always returns 0).
  * Supported cygwin (tested under cygwin 1.5.25-15 with g++ 3.4.4)
  * [Advanced Guide](http://code.google.com/p/mockcpp/wiki/AdvancedGuideOfMockcpp) (English Version)

### mock++ 2.1 ###

  * down cast by dynamic\_cast is supported;
  * Able to specifing the life cycle of a mock object, and a mock object could be performed `delete` operation(not "::operator delete") safely.
  * const reference type of return value of a mocked method is fully supported.
  * ignoreReturnValue() is deprecated. Actually it's not allowed to use it any longer. Instead, you should always specify the return behavior in a mock specification.
  * Added some configure parameters to change the default settings
  * Some minor bugs were fixed

### mock++ 2.0 ###

  * Define mock classes for interfaces is not required any longer (Only working with g++ so far)
  * Refactored some concepts to make them more clear and easy to understand
  * Supporting mocking C function easily (g++ > 3 / MSVC > 6)
  * Added ._then_(stub) after ._will_(stub) to make specifying complex invocation behavior much easier
  * Allow specifying more order-related constraints by using multiple _before_()/_after_()
  * Added some useful extensions (_repeat_(), _increase_(), _throws_(), _startWith_(), _endWith_(), _contains_(), etc.)
  * [Chinese User Manual](http://code.google.com/p/mockcpp/wiki/ChineseVersionManual)

## Get The Source ##

You can download the latest version from [download page](http://code.google.com/p/mockcpp/downloads/list), or you can go to [source page](http://code.google.com/p/mockcpp/source/checkout) to checkout from svn to get the lastest change, in which some bugs might have been fixed.

Should you have any suggestions or questions, please [mailto:dev.mockcpp@gmail.com](mailto:dev.mockcpp@gmail.com)