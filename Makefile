CXX=clang++
CXXFLAGS=-Wall

all: DebugStream

DebugStream: DebugStream.o
	$(CXX) -o DebugStream $(CXXFLAGS) DebugStream.o

DebugStream.o: DebugStream.cpp DebugStream.hpp
	$(CXX) -o DebugStream.o $(CXXFLAGS) DebugStream.cpp -c

clean:
	@rm -f *.o DebugStream
