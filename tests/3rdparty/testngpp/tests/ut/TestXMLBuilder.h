
#include <string>
#include <sstream>
#include <string>

#include <listeners/XMLBuilder.h>

#include <cxxtest/TestSuite.h>


USING_TESTNGPP_NS

class TestXMLBuilder: public CxxTest::TestSuite
{
private:

public:
	void testXMLBuilder()
	{
		#if 0
		//def __GNUC__
		// TODO: there is a 15 bytes mem leak on linux, but it runs ok on windows. the reason is unknown.
		//STOP_MEM_CHECKER();
		extern void pauseCheckStatus();
		pauseCheckStatus();
		#endif
		std::string expected =
"<?xml version=\"1.0\"?>\n\
<books>\n\
  <book id=\"101\" genre=\"fiction\">\n\
    <description>Katherine</description>\n\
  </book>\n\
  <book id=\"102\" genre=\"novel\">\n\
  </book>\n\
</books>\n";

		std::stringstream ss;

		XMLBuilder* builder = XMLBuilder::create("books");
		builder->element("book")
					.attribute("id", "101")
					.attribute("genre", "fiction")
					.element("description")
						.text("Katherine")
						.up()
					.up()
				.element("book")
					.attribute("id", "102")
					.attribute("genre", "novel")
				.write(ss);

		TS_ASSERT_EQUALS(expected, ss.str());

		delete builder;
	}

	void testEscapeXMLCharacters()
	{
		std::stringstream ss;
		XMLBuilder* builder = XMLBuilder::create("books");
		builder->attribute("name", "<>&'\"")
				.text("<>&'\"")
				.write(ss);

		std::string expected =
"<?xml version=\"1.0\"?>\n\
<books name=\"&lt;&gt;&amp;&apos;&quot;\">&lt;&gt;&amp;&apos;&quot;</books>\n";

		TS_ASSERT_EQUALS(expected, ss.str());

		delete builder;
	}
};
