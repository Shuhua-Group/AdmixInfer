/*
 * SpecModel.cpp
 *
 *  Created on: Apr 22, 2015
 *  Author: young
 */

#include <cmath>
#include "SpecModel.hpp"

SpecModel::SpecModel(int gen, double prop) :
		generation(gen), proportion(prop)
{
}

SpecModel::~SpecModel()
{
}

int SpecModel::getGeneration() const
{
	return generation;
}

double SpecModel::getProportion() const
{
	return proportion;
}

void SpecModel::setGeneration(int gen)
{
	generation = gen;
}

void SpecModel::setProportion(double prop)
{
	proportion = prop;
}

double SpecModel::loglik(const std::vector<double> &observ, int index, double lower, double upper) const
{
	double llk = 0;
	for (unsigned long i = 0; i < observ.size(); ++i)
	{
		llk += log(distribution(index, observ.at(i)));
	}
	double corrector = getCorrector(index, lower, upper);
	llk -= observ.size() * log(corrector);
	return llk;
}
