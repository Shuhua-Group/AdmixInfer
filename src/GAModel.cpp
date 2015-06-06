/*
 * GAModel.cpp
 *
 *  Created on: Apr 22, 2015
 *      Author: young
 */

#include <cmath>
#include "GAModel.hpp"

GAModel::GAModel(int gen, double prop) :
		SpecModel(gen, prop)
{
}

GAModel::~GAModel()
{
}

double GAModel::distribution(int index, double x) const
{
	int gen = getGeneration();
	double prop = 0;
	double retVal = 0;
	double tmp = 0;
	if (index == 0)
	{
		prop = 1 - getProportion();
	}
	else
	{
		prop = getProportion();
	}
	for (int t = 2; t <= gen; ++t)
	{
		tmp = (gen - t + 1);
		retVal += tmp * tmp * pow(1 - 1.0 / gen, 1.0 - t) * exp(-tmp * prop * x);
	}
	retVal = prop * (retVal / gen + gen * gen * exp(-gen * prop * x));
	return retVal;
}

double GAModel::getCorrector(int index, double lower, double upper) const
{
	int gen = getGeneration();
	double prop = 0;
	double retVal = 0;
	double tmp = 0;
	if (index == 0)
	{
		prop = 1 - getProportion();
	}
	else
	{
		prop = getProportion();
	}
	for (int t = 2; t <= gen; ++t)
	{
		tmp = (gen - t + 1);
		retVal += tmp * pow(1 - 1.0 / gen, 1.0 - t) * (exp(-tmp * prop * lower) - exp(-tmp * prop * upper));
	}
	retVal = retVal / gen + gen * (exp(-gen * prop * lower) - exp(-gen * prop * upper));
	return retVal;
}
