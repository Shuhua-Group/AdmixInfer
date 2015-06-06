/*
 * SegmentData.cpp
 *
 *  Created on: Apr 22, 2015
 *  Author: young
 */

#include <algorithm>
#include <fstream>
#include <sstream>
#include "SegmentData.hpp"

using namespace std;

SegmentData::SegmentData(const string &fname, double lower, double upper)
{
	ifstream fin(fname.c_str());
	if (!fin.good())
	{
		cerr << "Can't open file " << fname << endl;
		exit(1);
	}
	string line;
	string pop;
	double start, end;
	vector<string> labels;
	map<string, double> proportions;
	map<string, vector<double> > segments;

	while (getline(fin, line))
	{
		istringstream iss(line);
		iss >> start;
		iss >> end;
		iss >> pop;
		double len = end - start;
		//if no population label find, push back
		if (find(labels.begin(), labels.end(), pop) == labels.end())
		{
			labels.push_back(pop);
			proportions[pop] = 0;
			vector<double> newEntry;
			segments[pop] = newEntry;
		}
		//this added to calculate mixture proportions
		proportions.at(pop) += len;
		//if len between lower and upper, then add to the data
		if (len > lower && len < upper)
		{
			segments.at(pop).push_back(len);
		}
	}

	fin.close();
	if (labels.size() != 2)
	{
		cerr << "Tracks from either one population or more than two populations" << endl;
		exit(1);
	}
	pop = labels.at(0);
	string pop2 = labels.at(1);
	proportions.at(pop) = proportions.at(pop) / (proportions.at(pop) + proportions.at(pop2));
	proportions.at(pop2) = 1 - proportions.at(pop);
	this->proportions = proportions;
	this->labels = labels;
	this->segments = segments;
}

SegmentData::~SegmentData()
{
}

vector<string> SegmentData::getLabels() const
{
	return labels;
}

vector<double> SegmentData::getSegments(const string &label) const
{
	return segments.at(label);
}

map<string, double> SegmentData::getProportions() const
{
	return proportions;
}

vector<double> SegmentData::sampleSeg(const string &label, boost::mt19937 &generator, double prop) const
{
	int index = 0;
	int numSeg = segments.at(label).size();
	boost::uniform_int<> sample(0, numSeg - 1);
	int numSamp = int(prop * numSeg);
	vector<double> segment;
	for (int i = 0; i < numSamp; ++i)
	{
		index = sample(generator);
		segment.push_back(segments.at(label).at(index));
	}
	return segment;
}
