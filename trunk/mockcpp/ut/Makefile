
INCLUDE= -I. -I../include -I/usr/local/include

CXX=g++

RM = rm -f
TARGET = ut

INCLUDE= -I. -I../include -I/usr/local/include
CXXFLAGS = -g
DEFS = -DMOCKPP_ENABLE_DEFAULT_FORMATTER -DMOCKCPP_USING_CPPUNIT
LIBS = -L/usr/local/lib -lcppunit 
OBJS = $(patsubst %.cpp, %.o, $(shell ls Test*.cpp))
OBJS += $(patsubst %.cpp, %.o, $(shell ls ../src/*.cpp))

all: $(TARGET)

clean:
	$(RM) $(TARGET) $(OBJS)

$(TARGET) : $(OBJS)
	$(CXX) -o $@ $(OBJS) $(LIBS)

%.o : %.cpp
	$(CXX) $(CXXFLAGS) $(DEFS) $(INCLUDE) -o $@ -c $<

