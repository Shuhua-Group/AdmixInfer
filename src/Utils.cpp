/*
 * Utils.cpp
 *
 *  Created on: Apr 22, 2015
 *  Author: young
 */
#include <iostream>
#include "Utils.hpp"
#include <boost/math/distributions/students_t.hpp>

//find the index of max
int indexOfMax(const double *data, int size)
{
	double maxVal = data[0];
	int index = 0;
	for (int i = 1; i < size; ++i)
	{
		if (data[i] > maxVal)
		{
			maxVal = data[i];
			index = i;
		}
	}
	return index;
}

//perform summation, i.e. return s=∑data
double sum(const vector<double> &data)
{
	double sum = 0;
	size_t size = data.size();
	for (size_t i = 0; i < size; ++i)
	{
		sum += data.at(i);
	}
	return sum;
}

//non-weighted mean, mean = ∑data(i) / n;
double mean(const vector<double> &data)
{
	return sum(data) / data.size();
}

//non-weighted variance, given data and mean
//var = ∑(data(i)-mean)^2/ (n-1)
double var(const vector<double> &data, double avg)
{
	double sum = 0;
	size_t size = data.size();
	for (size_t i = 0; i < size; ++i)
	{
		sum += (data.at(i) - avg) * (data.at(i) - avg);
	}
	return sum / (size - 1);
}

//weighted mean, mean = ∑data(i)*weight(i)
double mean(const vector<double> &data, const vector<double> &weights)
{
	double sum = 0;
	size_t size = data.size();
	for (size_t i = 0; i < size; ++i)
	{
		sum += data.at(i) * weights.at(i);
	}
	return sum;
}

//weighted variance, var = ∑weight(i)*(data(i)-mean)^2
double var(const vector<double> &data, const vector<double> &weights, double avg)
{
	double sum = 0;
	size_t size = data.size();
	for (size_t i = 0; i < size; ++i)
	{
		sum += (data.at(i) - avg) * (data.at(i) - avg) * weights.at(i);
	}
	return sum;
}

double t_confidence_interval(int size, double var, double alpha)
{
	boost::math::students_t dist(size - 1);
	double quant = boost::math::quantile(boost::math::complement(dist, alpha / 2));
	double ci = quant * sqrt(var / size);
	return ci;
}

double optimize(const vector<double> &segs1, const vector<double> &segs2, SpecModel *model, double lower, double upper)
{

	int leftBound = 1;
	int rightBound = 2;
	double llk1 = 0;
	double llk2 = 0;
	bool findBound = false;
	while (!findBound)
	{
		model->setGeneration(rightBound);
		llk1 = model->loglik(segs1, 0, lower, upper) + model->loglik(segs2, 1, lower, upper);
		model->setGeneration(rightBound - 1);
		llk2 = model->loglik(segs1, 0, lower, upper) + model->loglik(segs2, 1, lower, upper);
		if (llk1 > llk2)
		{
			leftBound = rightBound;
			rightBound *= 2;
		}
		else
		{
			rightBound = rightBound - 1;
			findBound = true;
		}
	}

	int left = leftBound;
	int right = rightBound;
	double optLik = 0;
	bool isOpt = false;
	while (!isOpt)
	{
		//if only two points lefted, just compare it
		if (right - left < 2)
		{
			model->setGeneration(right);
			llk1 = model->loglik(segs1, 0, lower, upper) + model->loglik(segs2, 1, lower, upper);
			model->setGeneration(left);
			llk2 = model->loglik(segs1, 0, lower, upper) + model->loglik(segs2, 1, lower, upper);
			if (llk1 > llk2)
			{
				optLik = llk1;
				model->setGeneration(right);
			}
			else
			{
				optLik = llk2;
			}
			isOpt = true;
		}
		else
		{
			int middle = (right + left) / 2;
			model->setGeneration(middle);
			llk1 = model->loglik(segs1, 0, lower, upper) + model->loglik(segs2, 1, lower, upper);
			model->setGeneration(middle - 1);
			llk2 = model->loglik(segs1, 0, lower, upper) + model->loglik(segs2, 1, lower, upper);
			if (llk1 < llk2)
			{
				right = middle - 1;
			}
			else
			{
				left = middle;
			}
		}
	}
	return optLik;
}

