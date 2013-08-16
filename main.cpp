#include "IrisClassifier.hpp"
#include <ios>

using namespace std;

int main()
{
	ios_base::sync_with_stdio(0);

	BaseClassifier* classifier = new IrisClassifier(BaseClassifier::SVM_ERROR, IrisClassifier::IRIS_VERSICOLOR);
	classifier->setEpochs(100,1000000);
	classifier->run();
	return 0;
}

