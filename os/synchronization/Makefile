CXX = g++
CXXFLAGS = -std=c++11 -pthread
TARGETS = mutex deadlock rc

all: $(TARGETS)

mutex: mutex.cpp
	$(CXX) $(CXXFLAGS) -o mutex mutex.cpp

deadlock: deadlock.cpp
	$(CXX) $(CXXFLAGS) -o deadlock deadlock.cpp

rc: rc.cpp
	$(CXX) $(CXXFLAGS) -o rc rc.cpp

clean:
	rm -f $(TARGETS)