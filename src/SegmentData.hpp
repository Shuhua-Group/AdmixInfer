/*
 * SegmentData.hpp
 *
 *  Created on: Apr 22, 2015
 *  Author: young
 */

#ifndef SEGMENTDATA_HPP_
#define SEGMENTDATA_HPP_

#include <string>
#include <map>
#include <vector>
#include <ctime>
#include <boost/random.hpp>

class SegmentData
{
public:
	SegmentData(const std::string &fname, double lower, double upper);
	virtual ~SegmentData();
	std::vector<std::string> getLabels() const;
	std::vector<double> getSegments(const std::string &label) const;
	std::map<std::string, double> getProportions() const;
	std::vector<double> sampleSeg(const std::string &label, boost::mt19937 &generator, double prop = 1) const;

private:
	std::vector<std::string> labels;
	std::map<std::string, double> proportions;
	std::map<std::string, std::vector<double> > segments;
};

#endif /* SEGMENTDATA_HPP_ */
