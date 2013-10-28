#ifndef L1REGULARIZATION_HPP
#define L1REGULARIZATION_HPP

#include "BaseClassifier.hpp"

class L1Regularization : public virtual BaseClassifier
{
public:
	L1Regularization(double radius);

protected:
	void regularize(Hypothesis &hypotesis);

	double radius;
};

#endif // L1REGULARIZATION_HPP
