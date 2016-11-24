CXX=g++
BIN_DIR=../bin

HFILE=$(wildcard *.h)
SRC=$(wildcard *.cpp)

DIR_OBJ=../obj
OBJ=$(SRC:%.cpp=%.o)

CFLAGS=-g -O2 -fno-strict-aliasing -Wall -W -Wpointer-arith -Wcast-qual -pipe -fPIC
INC=-I./

TARGET=triangleService test

.PHONY:all
all:$(TARGET) $(OBJ)

#bulid middle obj
%.o:%.cpp $(HFILE)
	$(CXX) $(CFLAGS) $(INC) -o $@ -c $<

triangleService:triangle.o
	$(CXX) $(CFLAGS) -o $(BIN_DIR)/$@ $<

test:test.o
	$(CXX) $(CFLAGS) -o $(BIN_DIR)/$@ $< 


.PHONY:clean
clean:
	rm -f $(OBJ) ../bin/*

.PHONY:love
love:clean all
