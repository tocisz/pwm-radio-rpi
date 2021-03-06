
CXX=g++

TARGET=send

INCLUDEDIR = ./

INCDIR  = $(patsubst %,-I%,$(INCLUDEDIR))

OPT = -O0
DEBUG = -g -DDEBUG
WARN= -Wall

CXXFLAGS= $(OPT) $(DEBUG) $(WARN) $(INCDIR)

INC = rpiPWM1.h
SRC = rpiPWM1.cpp send.cpp

OBJ = $(SRC:.cpp=.o)

all: $(OBJ)
	    $(CXX)  $(OBJ) -o $(TARGET)

%.o:%.cpp
	    $(CXX) $(CXXFLAGS)  -c $<

clean:
	    -rm *.o
		-rm $(TARGET)
