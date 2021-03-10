/***
   mockcpp is a C/C++ mock framework.
   Copyright [2020] [Chen Guodong <sinojelly@163.com>]

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

      http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
***/

#include <mockcpp/Asserter.h>
#include <catch2/catch_test_macros.hpp>

MOCKCPP_NS_START

void
reportFailure(unsigned srcline, const char* srcfile,
             const std::string& message)
{
   Catch::AssertionHandler catchAssertionHandler("MOCKCPP_FAIL", 
       ::Catch::SourceLineInfo(srcfile, static_cast<std::size_t>(srcline)), 
       Catch::StringRef(), Catch::ResultDisposition::Normal); 
   catchAssertionHandler.handleMessage( Catch::ResultWas::ExplicitFailure, message); 
   INTERNAL_CATCH_REACT( catchAssertionHandler );
   //FAIL(srcline, srcfile, message);
}


MOCKCPP_NS_END

