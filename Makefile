ifeq "$(CXX)" "g++"
	GCCVERSION := $(shell $(CXX) -dumpversion)
	ifeq "$(GCCVERSION)" "4.7"
		CXX := g++-4.8
	endif
endif

CXXFLAGS := $(CXXFLAGS) -O3 -Wall -std=c++11

all: experiment1

experiment1: main.o BaseClassifier.o IrisClassifier.o CovertypeClassifier.o L1Regularization.o L2Regularization.o
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $@ $^

main.o: main.cpp IrisClassifier.hpp BaseClassifier.hpp L1Regularization.hpp L2Regularization.hpp CovertypeClassifier.hpp
BaseClassifier.o: BaseClassifier.cpp BaseClassifier.hpp
CovertypeClassifier.o: CovertypeClassifier.cpp CovertypeClassifier.hpp BaseClassifier.hpp
IrisClassifier.o: IrisClassifier.cpp IrisClassifier.hpp BaseClassifier.hpp
L1Regularization.o: L1Regularization.cpp L1Regularization.hpp BaseClassifier.hpp
L2Regularization.o: L2Regularization.cpp L2Regularization.hpp BaseClassifier.hpp

clean:
	rm *.o experiment1
