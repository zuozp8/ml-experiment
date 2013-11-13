#include "IrisClassifier.hpp"
#include "CovertypeClassifier.hpp"
#include "L2Regularization.hpp"
#include <iostream> //for ios_base
#include <cstdlib> //for rand and atoi
#include <unistd.h> //for getopt

using namespace std;

#define GETOPT(nr, default) argc > nr ? atoi(argv[nr]) : default
#define GETOPTF(nr, default) argc > nr ? atof(argv[nr]) : default

int main(int argc, char** argv)
{
	ios_base::sync_with_stdio(0);
	cout.precision(15);

	int positiveClass = GETOPT(1,1);
	double radius = GETOPTF(2,10);
	int epochs = GETOPT(3,10);
	double learningSpeedCoefficient = GETOPTF(4,1);
	int randSeed = GETOPT(5,time(0));

	srand(randSeed);

	class ConcreteClassifier : public CovertypeClassifier, public L2Regularization {
	public:
		ConcreteClassifier(int _positiveClass, double _radius) :
			CovertypeClassifier(_positiveClass),
			L2Regularization(_radius)
		{
		}
	};

	BaseClassifier* classifier = new ConcreteClassifier(positiveClass, radius);
	classifier->setEpochs(epochs);
	classifier->setAlphaCoefficient(learningSpeedCoefficient);
	classifier->run();
	return 0;
}
