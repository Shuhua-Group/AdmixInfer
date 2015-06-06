/*
 * HIModel.cpp
 *
 *  Created on: Apr 22, 2015
 *  Author: young
 */

#include <cmath>
#include "HIModel.hpp"

HIModel::HIModel(int gen, double prop) :
		SpecModel(gen, prop)
{
}

HIModel::~HIModel()
{
}

double HIModel::distribution(int index, double x) const
{
	int gen = getGeneration(); // T
	double prop = 0;
	if (index == 0)
	{
		prop = 1 - getProportion(); // 1-m
	}
	else
	{
		prop = getProportion(); // m
	}
	double lambda = gen * prop;
	return (lambda * exp(-lambda * x));
}

double HIModel::getCorrector(int index, double lower, double upper) const
{
	int gen = getGeneration(); // T
	double prop = 0;
	if (index == 0)
	{
		prop = 1 - getProportion(); // 1-m
	}
	else
	{
		prop = getProportion(); // m
	}
	double lambda = gen * prop;
	return (exp(-lambda * lower) - exp(-lambda * upper));
}

