#include "BaseClassifier.hpp"
#include <algorithm>
#include <iostream>

BaseClassifier::BaseClassifier()
{
}

void BaseClassifier::run()
{
	readData();
	instances = data.size();
	features = data[0].size();

	prepareData();

	//TODO split into training and testing
	instances -= int(instances * split);
	auto beginingOfTestingData = data.begin() + instances;
	testingData.assign(beginingOfTestingData, data.end());
	data.resize(instances);

	performLearning();
}

void BaseClassifier::performLearning()
{
	Hypothesis hypothesis(features), hypothesesSum(features);
	vector<double> discountFactors{100., 1000., 10000., 100000., 1000000.};
	vector<Hypothesis> discountedHypotheses(discountFactors.size(), Hypothesis(features));

	for (unsigned epoch = 1; epoch <= epochs; epoch++) {
		for (unsigned i = 0; i < instances; i++) {
			double prediction = (hypothesis * data[i]).sum();
			double desirablePrediction = 2 * data[i].y - 1; //always 1 or -1

			double differential = getCostsDifferential(prediction * desirablePrediction);

			double alpha = 2 * sqrt(log(epochs * instances) / (i + epoch * instances));

			hypothesis -= alpha * differential * data[i] * desirablePrediction;
			regularize(hypothesis);

			hypothesesSum += hypothesis;
			for (unsigned i= 0; i<discountedHypotheses.size(); i++) {
				discountedHypotheses[i] = (discountedHypotheses[i] * discountFactors[i] + hypothesis)
									   / (1 + discountFactors[i]);
			}
		}
		vector<Hypothesis> hypothesesToTest(discountedHypotheses);
		hypothesesToTest.push_back(hypothesis);
		hypothesesToTest.push_back(hypothesesSum/double(epoch*instances));
		performTesting(hypothesesToTest);
	}
}

void BaseClassifier::performTesting(vector<Hypothesis> hypotheses)
{
	vector<unsigned> boolErrorSum(hypotheses.size());
	vector<double> learningErrorSum(hypotheses.size());
	for (unsigned i=0; i<hypotheses.size(); i++) {
		for (DataRow& row: testingData) {
			double prediction = (hypotheses[i] * row).sum();
			double desirablePrediction = 2 * row.y - 1; //always 1 or -1
			boolErrorSum[i] += (prediction * desirablePrediction < 0);
			learningErrorSum[i] += getCost(prediction * desirablePrediction);
		}
	}
	for (unsigned& sum: boolErrorSum) {
		cout << double(sum)/testingData.size() << '\t';
	}
	cout << endl;
	for (double& sum: learningErrorSum) {
		cout << sum << '\t';
	}
	cout << endl;
}

double BaseClassifier::getCost(double prediction) {
	if (type == LOGISTIC_ERROR) {
		return log(1 + exp(-prediction));
	} else if (type == SVM_ERROR) {
		return max(1 - prediction, 0.);
	} else {
		return 0;
	}
}

double BaseClassifier::getCostsDifferential(double prediction) {
	if (type == LOGISTIC_ERROR) {
		return -1. / (1 + exp(prediction));
	} else if (type == SVM_ERROR) {
		return prediction < 1. ? -1. : 0. ;
	} else {
		return 0;
	}
}

void BaseClassifier::regularize(Hypothesis &/*hypotesis*/)
{

}

void BaseClassifier::prepareData()
{
	//mean normalization
	Hypothesis sum(features);
	for (unsigned i = 0; i!= instances; i++) {
		sum += data[i];
	}
	Hypothesis mean = sum / double(instances);
	mean[0] = 0; // Bias feature
	for (unsigned i = 0; i!= instances; i++) {
		data[i] -= mean;
	}

	//feature scaling
	Hypothesis quadraticSum(features);
	for (unsigned i = 0; i!= instances; i++) {
		quadraticSum += data[i] * data[i];
	}
	Hypothesis deviation = sqrt(quadraticSum / double(instances));
	deviation[0] = 1; // Bias feature
	for (unsigned i = 0; i!= instances; i++) {
		data[i] /= deviation;
	}

	random_shuffle(data.begin(), data.end());
}

void BaseClassifier::setEpochs(const unsigned &_epochs)
{
	epochs = _epochs;
}

void BaseClassifier::setErrorType(const BaseClassifier::ErrorFunction &_type)
{
	type = _type;
}
