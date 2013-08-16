#include "BaseClassifier.hpp"
#include <algorithm>
#include <iostream>

BaseClassifier::BaseClassifier(BaseClassifier::ErrorFunction _type) : type(_type)
{
}

void BaseClassifier::run()
{
	readData();
	instances = data.size();
	features = data[0].first.size();
	prepareData();
	performLearning(true);
	performLearning();
}

void BaseClassifier::performLearning(bool findBest)
{
	valarray<double>& hypothesis = findBest ? best : current;
	hypothesis.resize(features);

	unsigned epochsToDo = findBest ? epochsToFindBest : epochs;

	for (unsigned epoch = 1; epoch <= epochsToDo; epoch++) {
		for (unsigned i = 0; i < instances; i++) {
			//cout << best[0] << ' ' << best[1] << ' ' << best[2] << ' ' << best[3] << endl;
			double prediction = (hypothesis * data[i].first).sum();
			double desirablePrediction = 2 * data[i].second - 1; //always 1 or -1

			double differential = 0.;
			double cost = getCost(prediction * desirablePrediction, &differential);

			if (!findBest) {
				//output partial regret
				double predictionOfBest = (best * data[i].first).sum();
				double costOfBest = getCost(predictionOfBest * desirablePrediction);
				cout << cost - costOfBest << endl;
			}

			double alpha = sqrt(8 * log(epochsToDo * instances) / (i + epoch * instances));

			hypothesis -= alpha * differential * data[i].first * desirablePrediction;
		}
	}
}

double BaseClassifier::getCost(double prediction, double *differential) {
	if (type == LOGISTIC_ERROR) {
		if (differential) {
			*differential = -1. / (1 + exp(prediction));
		}
		return log(1 + exp(-prediction));
	} else if (type == SVM_ERROR) {
		if (differential) {
			*differential = prediction < 1. ? -1. : 0. ;
		}
		return max(1 - prediction, 0.);
	} else {
		return 0;
	}
}

void BaseClassifier::prepareData()
{
	//mean normalization
	valarray<double> sum(features);
	for (unsigned i = 0; i!= instances; i++) {
		sum += data[i].first;
	}
	valarray<double> mean = sum / double(instances);
	mean[0] = 0; // Bias feature
	for (unsigned i = 0; i!= instances; i++) {
		data[i].first -= mean;
	}

	//feature scaling
	valarray<double> quadraticSum(features);
	for (unsigned i = 0; i!= instances; i++) {
		quadraticSum += data[i].first * data[i].first;
	}
	valarray<double> deviation = sqrt(quadraticSum / double(instances));
	deviation[0] = 1; // Bias feature
	for (unsigned i = 0; i!= instances; i++) {
		data[i].first /= deviation;
	}

	random_shuffle(data.begin(), data.end());
}

void BaseClassifier::setEpochs(const unsigned &_epochs, const unsigned &_epochsToFindBest)
{
	epochs = _epochs;
	epochsToFindBest = _epochsToFindBest;
}
