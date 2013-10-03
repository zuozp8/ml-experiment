#include "CovertypeClassifier.hpp"
#include <fstream>
#include <sstream>
#include <algorithm>

CovertypeClassifier::CovertypeClassifier(int _positiveClass)
{
	if (positiveClass < 1 && positiveClass > 7)
		throw "CovertypeClassifier - Wymagana klasa z zakresu 1-7";
	positiveClass = _positiveClass;
}

void CovertypeClassifier::readData()
{
	ifstream in("data/covtype.data");
	string line;
	while (in >> line) {
		replace(line.begin(), line.end(), ',', ' ');
		istringstream iss(line);
		valarray<double> row(55);
		int yClass;
		bool y;
		row[0] = 1;
		for (int i=1; i<=54; i++)
			iss >> row[i];
		iss >> yClass;

		y = (yClass == positiveClass);
		data.push_back(make_pair(row, y));
	}
}
