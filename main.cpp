#include "IrisClassifier.hpp"
#include "CovertypeClassifier.hpp"
#include "L2Regularization.hpp"
#include <iostream>
#include <cstdlib>

using namespace std;

int main()
{
	ios_base::sync_with_stdio(0);
	cout.precision(15);
	srand(173);

	class ConcreteClassifier : public CovertypeClassifier, public L2Regularization {
	public:
		ConcreteClassifier() :
			CovertypeClassifier(1),
			L2Regularization(10)
		{
		}
	};

	BaseClassifier* classifier = new ConcreteClassifier;
	//BaseClassifier* classifier = new IrisClassifier(IrisClassifier::IRIS_VERSICOLOR);
	classifier->setEpochs(10);
	classifier->run();
	return 0;
}

