/*
 * GAModel.hpp
 *
 *  Created on: Apr 22, 2015
 *  Author: young
 *  index={0,1} is used to distinguish the parental populations
 *  if index == 0, then use distribution of population with proportion 1-m,
 *  else use distribution of population with proportion m
 */

#ifndef GAMODEL_HPP_
#define GAMODEL_HPP_

#include "SpecModel.hpp"

class GAModel: public SpecModel
{
public:
	GAModel(int gen, double prop);
	virtual ~GAModel();
	double distribution(int index, double x) const;
	double getCorrector(int index, double lower = 0, double upper = kInfinity) const;
};

#endif /* GAMODEL_HPP_ */
