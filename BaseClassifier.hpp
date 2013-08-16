#ifndef BASECLASSIFIER_HPP
#define BASECLASSIFIER_HPP

#include <vector>
#include <valarray>

using namespace std;

class BaseClassifier
{
public:
	enum ErrorFunction {
		LOGISTIC_ERROR,
		SVM_ERROR
	};
	BaseClassifier(ErrorFunction type);

	void setEpochs(const unsigned &epochs, const unsigned &epochsToFindBest = 20000);
	void run();

protected:
	//Fills data (must create bias feature)
	virtual void readData() = 0;

	//perform shuffling, scaling and mean normalization
	void prepareData();

	//call this function twice, firstly find best, then track regret
	void performLearning(bool findBest = false);

	// Data is filled with instances described by vector of real values and boolean class
	vector<pair<valarray<double>,bool> > data;

	//gives cost for certain prediction if positive class was desired
	//actual prediction should be multiplied by -1 before using this function if negative class was desired
	double getCost(double prediction, double* differential = nullptr);

private:
	//Amount of attributes and training examples
	unsigned features, instances;

	valarray<double> best, current; //hypotheses

	unsigned epochs = 5, epochsToFindBest = 20000; // number of epochs to do
	const ErrorFunction type;
};

#endif // BASECLASSIFIER_HPP
