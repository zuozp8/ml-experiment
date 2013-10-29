#ifndef BASECLASSIFIER_HPP
#define BASECLASSIFIER_HPP

#include <vector>
#include <valarray>

using namespace std;

class Hypothesis: public valarray<double> {
public:
	using valarray<double>::valarray;
};

class DataRow: public Hypothesis {
public:
	using Hypothesis::Hypothesis;
	bool y; // whether it is positive example
};


class BaseClassifier
{
public:
	enum ErrorFunction {
		LOGISTIC_ERROR,
		SVM_ERROR
	};
	BaseClassifier();

	void setEpochs(const unsigned &epochs);
	void setErrorType(const ErrorFunction &type);
	void run();
protected:
	//Fills data (must create bias feature)
	virtual void readData() = 0;

	//perform shuffling, scaling and mean normalization
	void prepareData();

	//returns hypoteses that has to be considered
	void performLearning();

	//prints errors for given hypoteses
	void performTesting(vector<Hypothesis> hypotheses);

	// Data is filled with instances described by vector of real values and boolean class
	vector<DataRow> data, testingData;

	//gives cost for certain prediction if positive class was desired
	//actual prediction should be multiplied by -1 before using this function if negative class was desired
	double getCost(double prediction);
	double getCostsDifferential(double prediction);

	//override this function to perform projection regularization
	//regularization may be performed by changing parameter passed by reference
	virtual void regularize(Hypothesis& hypotesis);

	//Amount of attributes and training examples
	unsigned features, instances;

private:
	unsigned epochs = 5; // number of epochs to do
	double split = 0.8;
	ErrorFunction type = LOGISTIC_ERROR;
};

#endif // BASECLASSIFIER_HPP
