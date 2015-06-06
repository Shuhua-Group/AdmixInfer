/*
 * SpecModel.hpp
 *
 *  Created on: Apr 22, 2015
 *  Author: young
 *  A Specified model act as interface for HI, GA and CGF model;
 * 	it has two members:
 * 		generation: generation since admix events occurred
 * 		proportion: mix proportion
 *
 *	with the distribution of a model, likelihoods can be calculated
 *
 *	Accelerating calculation:
 *	In calculating the likelihood, because for given m and T, the denominator is always the same,
 *	in order to avoid repeatedly calculation, the denominator thus can be calculated and stored,
 *	as a corrector, to corrector the results at the end of calculation.
 */

#ifndef SPECMODEL_HPP_
#define SPECMODEL_HPP_

#include <vector>

const double kInfinity = 1.0e50;

class SpecModel
{
public:
	SpecModel(int gen, double prop);
	virtual ~SpecModel();
	int getGeneration() const;
	double getProportion() const;
	void setGeneration(int gen);
	void setProportion(double prop);
	double loglik(const std::vector<double> &observ, int index, double lower = 0, double upper = kInfinity) const;
	virtual double distribution(int index, double x) const = 0;
	virtual double getCorrector(int index, double lower = 0, double upper = kInfinity) const = 0;
private:
	int generation;
	double proportion;
};

#endif /* SPECMODEL_HPP_ */
