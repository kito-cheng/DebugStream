CXX=g++
CXXFLAGS=-Wall -O0 -g3
OBJS= DebugStream.o DebugStreamManager.o DebugStreamTest.o
all: DebugStreamTest

DebugStreamTest: $(OBJS)
	$(CXX) -o DebugStreamTest $(LDFLAGS) $(OBJS)

DebugStreamTest.o: DebugStreamTest.cpp DebugStream.hpp DebugStreamManager.hpp
	$(CXX) -o DebugStreamTest.o $(CXXFLAGS) DebugStreamTest.cpp -c

DebugStream.o: DebugStream.cpp DebugStream.hpp
	$(CXX) -o DebugStream.o $(CXXFLAGS) DebugStream.cpp -c

DebugStreamManager.o: DebugStreamManager.cpp DebugStreamManager.hpp
	$(CXX) -o DebugStreamManager.o $(CXXFLAGS) DebugStreamManager.cpp -c

clean:
	@rm -f *.o DebugStream
