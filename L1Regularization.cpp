#include "L1Regularization.hpp"
#include <queue>

L1Regularization::L1Regularization(double _radius)
{
	radius = _radius;
}

void L1Regularization::regularize(Hypothesis &hypotesis)
{
	double length = abs(hypotesis).sum();

	if (length > radius) {
		deque<pair<double, int>> values;
		for (unsigned i = 0; i < features; ++i) {
			values.push_back(make_pair(abs(hypotesis[i]), i));
		}
		sort(values.begin(), values.end());

		while (values.front().first < (length - radius) / values.size()) {
			length -= values.front().first;
			hypotesis[values.front().second] = 0.;
			values.pop_front();
		}

		//Length of translation in each direction
		double translation = (length - radius) / values.size();

		for (pair<double, int> &i: values) {
			if (hypotesis[i.second] > 0) {
				hypotesis[i.second] -= translation;
			} else {
				hypotesis[i.second] += translation;
			}
		}
	}
}
