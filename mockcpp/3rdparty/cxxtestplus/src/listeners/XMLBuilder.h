
#ifndef __TESTCPP_XML_BUILDER_H
#define __TESTCPP_XML_BUILDER_H

#include <testcpp/testcpp.h>

#include <string>
#include <ostream>

TESTCPP_NS_START

class XMLBuilder {
public:
	static XMLBuilder* create(const std::string& root);

	virtual ~XMLBuilder(){};

	virtual XMLBuilder& element(const std::string& name) = 0;
	virtual XMLBuilder& attribute(const std::string& name, const std::string& value) = 0;
	virtual XMLBuilder& text(const std::string& text) = 0;
	virtual XMLBuilder& up() const = 0;
	virtual void write(std::ostream& stream) const = 0;
};

TESTCPP_NS_END

#endif
