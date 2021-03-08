/**
    TestNG++ is a practical, easy-to-use C/C++ xUnit framework.
    Copyright (C) <2011>  <Chen Guodong: sinojelly@gmail.com>

    TestNG++ is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    TestNG++ is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with TestNG++.  If not, see <http://www.gnu.org/licenses/>.
**/
#include <string.h>

#include <testngppst/internal/TestCase.h>
#include <testngppst/internal/MemChecker.h>

#include <testngppst/runner/loaders/ModuleLoader.h>

#include <mem_checker/interface_4xunit.h>


TESTNGPPST_NS_START

bool MemChecker::isGlobalOpen = true;

namespace
{

struct Reporter
{
    Reporter(TestFixture *_fixture)
        : fixture(_fixture)
    {
    }

protected:
    TestFixture *fixture;
};

struct InfoReporter : public Reporter
{
    InfoReporter(TestFixture *_fixture) : Reporter(_fixture) {}
    
    void operator ()(const char *file, unsigned int line, const char *message)
    {
        fixture->reportMemLeakInfo(file, line, message);
    }
};

struct FailureReporter : public Reporter
{
    FailureReporter(TestFixture *_fixture) : Reporter(_fixture) {}

    void operator ()(const char *file, unsigned int line, const char *message)
    {
        fixture->reportMemLeakFailure(file, line, message, false);
    }
};

}


namespace {
mem_checker::Reporter * info;
mem_checker::Reporter * failure;
}

bool MemChecker::isOpenInAnnotation()
{
	if (strcmp(testcase->getMemCheckSwitch(), "off") == 0)
	{
	    return false;
	}

	return true; // default is true
}

bool MemChecker::needMemCheck()
{
    return isGlobalOpen && isTestOpen;
}

MemChecker::MemChecker(TestCase *testcase) : testcase(testcase)
{ 
    isTestOpen = isOpenInAnnotation();
}

void MemChecker::start()
{
    if (!needMemCheck())
    {
        return;
    }

	ModuleLoader *loader = testcase->getLoader();

	typedef void (*start_t)(mem_checker::Reporter *, mem_checker::Reporter *);
    start_t starter = (start_t)loader->findSymbol("startMemChecker");

	TestFixture *fixture = testcase->getFixture();
	
	info = mem_checker::createReporter(InfoReporter(fixture));
	failure = mem_checker::createReporter(FailureReporter(fixture)); // Note: Reporter is new in runner.exe, and used in .dll. is this ok?
	starter(info, failure);
}

void MemChecker::verify()
{
    if (!needMemCheck())
    {
        return;
    }

	ModuleLoader *loader = testcase->getLoader();
	
	typedef void (*verify_t)(void);    
	verify_t verifier = (verify_t)loader->findSymbol("verifyMemChecker");    
	verifier(); 

	//delete info;  // Note: this will cause linux run exception
	//delete failure;
	//info = 0;
	//failure = 0;
}

void MemChecker::setGlobalOpen(bool globalOpen)
{
    isGlobalOpen = globalOpen;
}


TESTNGPPST_NS_END


