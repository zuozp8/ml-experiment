#ifndef IRISCLASSIFIER_HPP
#define IRISCLASSIFIER_HPP

#include <string>

#include "BaseClassifier.hpp"

class IrisClassifier : public virtual BaseClassifier
{
public:
	enum PositiveClass {
		IRIS_SENTOSA, //fully linearly separable form the other 2
		IRIS_VERSICOLOR, //not linearly separable
		IRIS_VIRGINICA //not linearly separable
	};
	IrisClassifier(PositiveClass positiveClass);
private:
	void readData();
	string positiveClassName;
};

#endif // IRISCLASSIFIER_HPP
