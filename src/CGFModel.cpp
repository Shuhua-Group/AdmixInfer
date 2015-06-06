/*
 * CGFModel.cpp
 *
 *  Created on: Apr 22, 2015
 *  Author: young
 */

#include <cmath>
#include "CGFModel.hpp"

CGFModel::CGFModel(int gen, double prop) :
		SpecModel(gen, prop)
{
}

CGFModel::~CGFModel()
{
}

double CGFModel::distribution(int index, double x) const
{
	int gen = getGeneration();
	double prop = getProportion();
	double retVal = 0;
	if (index == 0)
	{ //using distribution of CGFR
		double lambda = pow(prop, 1.0 / gen);
		lambda = gen - (1 - prop) * lambda / (1 - lambda);
		retVal = lambda * exp(-lambda * x);
	}
	else
	{ //using distribution of CGFD
		double tmp1 = pow(prop, 1.0 / gen); //	m^(1/T)
		double tmp2 = 0;
		double tmp3 = 0;
		for (int t = 1; t <= gen; ++t)
		{
			tmp2 = pow(prop, 1.0 * t / gen); // m^(t/T)
			tmp3 = tmp2 - prop * tmp1; // m^(t/T)-m^(T+1)/T
			retVal += tmp3 * tmp3 * exp(-tmp3 * x / (1 - tmp1)) / tmp2;
		}
	}
	return retVal;
}

double CGFModel::getCorrector(int index, double lower, double upper) const
{
	int gen = getGeneration();
	double prop = getProportion();
	double retVal = 0;
	if (index == 0)
	{ //using distribution of CGFR
		double lambda = pow(prop, 1.0 / gen);
		lambda = gen - (1 - prop) * lambda / (1 - lambda);
		retVal = exp(-lambda * lower) - exp(-lambda * upper);
	}
	else
	{ //using distribution of CGFD
		double tmp1 = pow(prop, 1.0 / gen); //	m^(1/T)
		double tmp2 = 0;
		double tmp3 = 0;
		double lambda = 0;
		for (int t = 1; t <= gen; ++t)
		{
			tmp2 = pow(prop, 1.0 * t / gen); // m^(t/T)
			tmp3 = tmp2 - prop * tmp1; // m^(t/T)-m^(T+1)/T
			lambda = tmp3 / (1 - tmp1);
			retVal += tmp3 * (1 - tmp1) * (exp(-lambda * lower) - exp(-lambda * upper)) / tmp2;
		}
	}
	return retVal;
}

