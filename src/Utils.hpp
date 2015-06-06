/*
 * Utils.hpp
 *
 *  Created on: Apr 22, 2015
 *  Author: young
 */

#ifndef UTILS_HPP_
#define UTILS_HPP_

#include <vector>
#include "SpecModel.hpp"
#include "SegmentData.hpp"

using namespace std;

int indexOfMax(const double *data, int size);

double sum(const vector<double> &data);

double mean(const vector<double> &data);

double mean(const vector<double> &data, const vector<double> &weights);

double var(const vector<double> &data, double avg);

double var(const vector<double> &data, const vector<double> &weights, double avg);

double t_confidence_interval(int size, double var, double alpha = 0.05);

double optimize(const std::vector<double> &segs1, const std::vector<double> &segs2, SpecModel *model, double lower = 0, double upper = kInfinity);

#endif /* UTILS_HPP_ */
