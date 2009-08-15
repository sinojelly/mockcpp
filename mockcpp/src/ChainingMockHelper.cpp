/***
    mockcpp is a generic C/C++ mock framework.
    Copyright (C) <2009>  <Darwin Yuan: darwin.yuan@gmail.com>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
***/

#include <mockcpp/mockcpp.h>

#include <mockcpp/Matcher.h>
#include <mockcpp/TypelessStubAdapter.h>
#include <mockcpp/InvokedOnce.h>
#include <mockcpp/InvokedAtLeast.h>
#include <mockcpp/InvokedAtMost.h>
#include <mockcpp/InvokedExactly.h>
#include <mockcpp/TestFailureMatcher.h>
#include <mockcpp/ReturnStub.h>
#include <mockcpp/ReturnObjectList.h>
#include <mockcpp/Constraint.h>
#include <mockcpp/OutBoundPointer.h>
#include <mockcpp/IsMirror.h>
#include <mockcpp/IgnoreReturnStub.h>
#include <mockcpp/RepeatStub.h>
#include <mockcpp/StringConstraint.h>
#include <mockcpp/IsStringStartWith.h>
#include <mockcpp/IsStringEndWith.h>
#include <mockcpp/IsStringContains.h>
#include <mockcpp/DieStub.h>

MOCKCPP_NS_START

//////////////////////////////////////////////////////////////////
Matcher* once()
{
	return new InvokedOnce;
}

//////////////////////////////////////////////////////////////////
Matcher* exactly(unsigned int times)
{
	return new InvokedExactly(times);
}

//////////////////////////////////////////////////////////////////
Matcher* atLeast(unsigned int times)
{
	return new InvokedAtLeast(times);
}

//////////////////////////////////////////////////////////////////
Matcher* atMost(unsigned int times)
{
	return new InvokedAtMost(times);
}

//////////////////////////////////////////////////////////////////
Matcher* atLeastOnce()
{
	return atLeast(1);
}

//////////////////////////////////////////////////////////////////
Matcher* atMostOnce()
{
	return atMost(1);
}

//////////////////////////////////////////////////////////////////
Matcher* never()
{
   return new TestFailureMatcher(
				"Invoking an invocation which should never be invoked",
            "never()");
}

//////////////////////////////////////////////////////////////////
Stub* returnValue(const Any& val)
{
   return new TypelessStubAdapter(new ReturnStub(val));
}

//////////////////////////////////////////////////////////////////
Stub* repeat(const Any& val, unsigned int repeatTimes)
{
   return new TypelessStubAdapter(new RepeatStub(val, repeatTimes));
}

//////////////////////////////////////////////////////////////////
Stub* ignoreReturnValue()
{
   return new TypelessStubAdapter(new IgnoreReturnStub());
}

Stub* die(int code)
{
   return new TypelessStubAdapter(new DieStub(code));
}
//////////////////////////////////////////////////////////////////
Stub* returnObjectList( const Any& o01
                      , const Any& o02 
                      , const Any& o03
                      , const Any& o04
                      , const Any& o05
                      , const Any& o06
                      , const Any& o07
                      , const Any& o08
                      , const Any& o09
                      , const Any& o10
                      , const Any& o11
                      , const Any& o12)
{
    return new TypelessStubAdapter(
                 new ReturnObjectList(
                       o01, o02, o03, o04, o05, o06,
                       o07, o08, o09, o10, o11, o12));
}

Constraint* outBoundP(void* p, size_t size, Constraint* constraint)
{
   return new OutBoundPointer<void*>(p, size, constraint);
}

Constraint* mirror(void* p, size_t size)
{
   return new IsMirror<void*>(p, size);
}

Constraint* smirror(char* s)
{
   return new IsMirror<char*>(s, strlen(s)+1);
}

Constraint* smirror(const char* s)
{
   return new IsMirror<const char*>(s, strlen(s)+1);
}

Constraint* smirror(unsigned char* s)
{
   return new IsMirror<unsigned char*>(s, strlen((char*)s)+1);
}

Constraint* smirror(const unsigned char* s)
{
   return new IsMirror<const unsigned char*>(s, strlen((const char*)s)+1);
}

Constraint* startWith(unsigned char* s)
{
    return new StringConstraint((char*)s, new IsStringStartWith());
}

Constraint* startWith(unsigned const char* s)
{
    return new StringConstraint((const char*)s, new IsStringStartWith());
}

Constraint* startWith(const std::string& s)
{
    return new StringConstraint(s, new IsStringStartWith());
}

Constraint* endWith(unsigned char* s)
{
    return new StringConstraint((char*)s, new IsStringEndWith());
}

Constraint* endWith(unsigned const char* s)
{
    return new StringConstraint((const char*)s, new IsStringEndWith());
}

Constraint* endWith(const std::string& s)
{
    return new StringConstraint(s, new IsStringEndWith());
}

Constraint* contains(unsigned char* s)
{
    return new StringConstraint((char*)s, new IsStringContains());
}

Constraint* contains(unsigned const char* s)
{
    return new StringConstraint((const char*)s, new IsStringContains());
}

Constraint* contains(const std::string& s)
{
    return new StringConstraint(s, new IsStringContains());
}

MOCKCPP_NS_END
