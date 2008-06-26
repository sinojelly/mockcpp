
INCLUDE= -I. -I../include -I/usr/local/include

CXX=g++

#GCCXML = gccxml

RM = rm -f
TARGET = ft

INCLUDE= -I. -I../include -I/usr/local/include
CXXFLAGS = -g
DEFS = -DMOCKPP_ENABLE_DEFAULT_FORMATTER -DMOCKCPP_USING_CPPUNIT
LIBS = -L/usr/local/lib -lcppunit -ldl 
TEST_OBJS = $(patsubst %.cpp, %.o, $(shell ls *.cpp))
PRODUCT_OBJS = $(patsubst %.cpp, %.o, $(shell ls ../src/*.cpp))
OBJS = $(TEST_OBJS) $(PRODUCT_OBJS)
XMLS = $(patsubst %.cpp, %.xml, $(shell ls *.cpp))

all: $(TARGET)

clean:
	$(RM) $(TARGET) $(TEST_OBJS)

clean-all:
	$(RM) $(TARGET) $(TEST_OBJS) $(PRODUCT_OBJS)

$(TARGET) : $(OBJS) #$(XMLS)
	$(CXX) -o $@ $(OBJS) $(LIBS)

%.o : %.cpp
	$(CXX) $(CXXFLAGS) $(DEFS) $(INCLUDE) -o $@ -c $<

%.xml : %.cpp
	$(CXX) -fdump-tree-dom $(CXXFLAGS) $(DEFS) $(INCLUDE) $< 

%.original : %
	$(CXX) -fdump-tree-original $(CXXFLAGS) $(DEFS) $(INCLUDE) $<
