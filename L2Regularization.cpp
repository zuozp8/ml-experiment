#include "L2Regularization.hpp"

L2Regularization::L2Regularization(double _radius)
{
	radius = _radius;
	radiusSquared = radius * radius;
	alphaCoefficient *= radius;
}

void L2Regularization::regularize(Hypothesis &hypotesis)
{
	double vectorLengthSquared = (hypotesis * hypotesis).sum();
	if (vectorLengthSquared > radiusSquared) {
		hypotesis /= sqrt(vectorLengthSquared / radiusSquared);
	}
}

void L2Regularization::tuneAlphaCoefficient()
{
	alphaCoefficient *= radius / sqrt(features);
}
