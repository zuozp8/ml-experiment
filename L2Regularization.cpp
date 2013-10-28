#include "L2Regularization.hpp"

L2Regularization::L2Regularization(double radius)
{
	radiusSquared = radius * radius;
}

void L2Regularization::regularize(Hypothesis &hypotesis)
{
	double vectorLengthSquared = (hypotesis * hypotesis).sum();
	if (vectorLengthSquared > radiusSquared) {
		hypotesis /= sqrt(vectorLengthSquared / radiusSquared);
	}
}
