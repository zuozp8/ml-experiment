CXXFLAGS := $(CXXFLAGS) -O3 -Wall -std=c++11

all: experiment1

experiment1: main.o BaseClassifier.o IrisClassifier.o
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $@ $^

main.o: main.cpp IrisClassifier.hpp BaseClassifier.hpp
BaseClassifier.o: BaseClassifier.cpp BaseClassifier.hpp
IrisClassifier.o: IrisClassifier.cpp IrisClassifier.hpp BaseClassifier.hpp

clean:
	rm *.o experiment1
