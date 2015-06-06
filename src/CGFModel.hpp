/*
 * CGFModel.hpp
 *
 *  Created on: Apr 22, 2015
 *  Author: young
 *  index={0,1} is used to distinguish the parental populations
 *  if index == 0, then use the distribution of population as gene flow recipient (CGFR),
 *  else use the distribution of population as gene flow donor(CGFD)
 */

#ifndef CGFMODEL_HPP_
#define CGFMODEL_HPP_

#include "SpecModel.hpp"

class CGFModel: public SpecModel
{
public:
	CGFModel(int gen, double prop);
	virtual ~CGFModel();
	double distribution(int index, double x) const;
	double getCorrector(int index, double lower = 0, double upper = kInfinity) const;
};

#endif /* CGFMODEL_HPP_ */
