
INCLUDE= -I. -I../include -I/usr/local/include

CXX=g++
AR = ar r

RM = rm -f

ifdef USING_CPPUNIT
TARGET = libmockcpp-cppunit.a
else
TARGET = libmockcpp.a 
endif

INCLUDE= -I. -I../include -I/usr/local/include
CXXFLAGS = -g

ifdef USING_CPPUNIT
DEFS += -DMOCKCPP_USING_CPPUNIT
endif

OBJS = $(patsubst %.cpp, %.o, $(shell ls *.cpp))

all: $(TARGET)

clean:
	$(RM) $(TARGET) $(OBJS)

$(TARGET) : $(OBJS)
	$(AR) $@ $^

%.o : %.cpp
	$(CXX) $(CXXFLAGS) $(DEFS) $(INCLUDE) -o $@ -c $<

