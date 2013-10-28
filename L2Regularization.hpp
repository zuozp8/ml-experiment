#ifndef L2REGULARIZATION_HPP
#define L2REGULARIZATION_HPP

#include "BaseClassifier.hpp"

class L2Regularization : public virtual BaseClassifier
{
public:
	L2Regularization(double radius);

protected:
	void regularize(Hypothesis &hypotesis);

	double radiusSquared;
};

#endif // L2REGULARIZATION_HPP
