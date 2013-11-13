#ifndef L2REGULARIZATION_HPP
#define L2REGULARIZATION_HPP

#include "BaseClassifier.hpp"

class L2Regularization : public virtual BaseClassifier
{
public:
	L2Regularization(double radius);

protected:
	void regularize(Hypothesis &hypotesis);
	void tuneAlphaCoefficient();

	double radius;
	double radiusSquared;
};

#endif // L2REGULARIZATION_HPP
