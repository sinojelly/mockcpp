
#include <testcpp/AssertionFailure.h>

TESTCPP_NS_START

//////////////////////////////////////////////////////////
AssertionFailure::AssertionFailure(const std::string& file
   , unsigned int line, const std::string& msg)
	: fileName(file), lineNumber(line), errMsg(msg)
{}

//////////////////////////////////////////////////////////
AssertionFailure::~AssertionFailure()
{}

//////////////////////////////////////////////////////////
bool operator==(const AssertionFailure& lhs, const AssertionFailure& rhs) 
{
   return lhs.getFileName() == rhs.getFileName() &&
          lhs.getLineOfFile() == rhs.getLineOfFile() &&
          lhs.what() == rhs.what();
}
//////////////////////////////////////////////////////////
const std::string& AssertionFailure::getFileName() const
{
   return fileName;
}

//////////////////////////////////////////////////////////
unsigned int AssertionFailure::getLineOfFile() const
{
   return lineNumber;
}

//////////////////////////////////////////////////////////
const std::string& AssertionFailure::what() const
{
	return errMsg;
}

//////////////////////////////////////////////////////////

TESTCPP_NS_END

