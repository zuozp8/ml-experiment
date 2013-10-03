#ifndef COVERTYPECLASSIFIER_HPP
#define COVERTYPECLASSIFIER_HPP

#include "BaseClassifier.hpp"

class CovertypeClassifier: public virtual BaseClassifier
{
public:
	CovertypeClassifier(int positiveClass);
private:
	void readData();
	int positiveClass;
};

#endif // COVERTYPECLASSIFIER_HPP
