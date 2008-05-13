
INCLUDE= -I. -I../include -I/usr/local/include

CXX=g++

RM = rm -f
TARGET = ft

INCLUDE= -I. -I../include -I/usr/local/include
CXXFLAGS = -g
DEFS = -DMOCKPP_ENABLE_DEFAULT_FORMATTER -DMOCKCPP_USING_CPPUNIT
LIBS = -L/usr/local/lib -lcppunit -ldl 
TEST_OBJS = $(patsubst %.cpp, %.o, $(shell ls *.cpp))
PRODUCT_OBJS = $(patsubst %.cpp, %.o, $(shell ls ../src/*.cpp))
OBJS = $(TEST_OBJS) $(PRODUCT_OBJS)

all: $(TARGET)

clean:
	$(RM) $(TARGET) $(TEST_OBJS)

clean-all:
	$(RM) $(TARGET) $(TEST_OBJS) $(PRODUCT_OBJS)

$(TARGET) : $(OBJS)
	$(CXX) -o $@ $(OBJS) $(LIBS)

%.o : %.cpp
	$(CXX) $(CXXFLAGS) $(DEFS) $(INCLUDE) -o $@ -c $<

