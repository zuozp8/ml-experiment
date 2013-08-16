#include "IrisClassifier.hpp"
#include <fstream>
#include <sstream>
#include <algorithm>


IrisClassifier::IrisClassifier(BaseClassifier::ErrorFunction type, IrisClassifier::PositiveClass positiveClass) : BaseClassifier(type)
{
	switch (positiveClass) {
	case IRIS_SENTOSA:
		positiveClassName = "Iris-setosa";
		break;
	case IRIS_VERSICOLOR:
		positiveClassName = "Iris-versicolor";
		break;
	case IRIS_VIRGINICA:
		positiveClassName = "Iris-virginica";
		break;
	}

}

void IrisClassifier::readData()
{
	ifstream in("data/iris.data");
	string line;
	while (in >> line) {
		replace(line.begin(), line.end(), ',', ' ');
		istringstream iss(line);
		valarray<double> row(5);
		string yClass;
		bool y;
		row[0] = 1;
		iss >> row[1] >> row[2] >> row[3] >> row[4] >> yClass;

		y = (yClass == positiveClassName);
		data.push_back(make_pair(row, y));
	}
}
