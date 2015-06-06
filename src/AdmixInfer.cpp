/*
 * AdmixInfer.cpp
 *
 *  Created on: Apr 22, 2015
 *  Author: young
 */

#include <iostream>
#include <string>
#include <ctime>
#include <iomanip>
#include <boost/random.hpp>
#include "HIModel.hpp"
#include "GAModel.hpp"
#include "CGFModel.hpp"
#include "Parameter.hpp"
#include "SegmentData.hpp"
#include "Utils.hpp"

using namespace std;

int main(int argc, char ** argv)
{
	bool isQuiet;
	double lower;
	double upper;
	double prop1;
	double samProp;
	string fname;
	string pop1;
	string pop2;

	vector<string> pops;
	map<string, double> props;

	int *indexes;
	double *globalMax;
	Parameter *par;
	SegmentData *seg;
	HIModel *hi;
	GAModel *ga;
	CGFModel *cgfr;
	CGFModel *cgfd;

	//initialize random number generator
	boost::mt19937 generator(time(0));
	par = new Parameter(argc, argv);
	isQuiet = par->isQuiet();
	lower = par->getLower();
	upper = par->getUpper();
	fname = par->getFname();
	samProp = par->getSampleProp();
	//echo command
	if (!isQuiet)
	{
		cout << endl;
		cout << "//CMD: ";
		for (int i = 0; i < argc; ++i)
		{
			cout << argv[i] << " ";
		}
		cout << endl << endl;
		cout << "Reading ancestral tracks from " << fname << endl;
	}
	//reading tracks
	seg = new SegmentData(fname, lower, upper);
	pops = seg->getLabels();
	props = seg->getProportions();
	pop1 = pops.at(0);
	pop2 = pops.at(1);
	if (pop1 > pop2)
	{
		pop1 = pops.at(1);
		pop2 = pops.at(0);
	}
	prop1 = props[pop1];
	hi = new HIModel(1, prop1);
	ga = new GAModel(1, prop1);
	cgfr = new CGFModel(1, prop1);
	cgfd = new CGFModel(1, 1 - prop1);
	string models[4] =
	{ "HI", "GA", "CGF(" + pop1 + " as recipient)", "CGF(" + pop1 + " as donor)" };

	indexes = new int[4];
	globalMax = new double[4];

	//start optimize
	if (!isQuiet)
	{
		cout << "Start optimizing process... " << endl;
	}
	//no bootstrapping
	if (par->getBootstrap() == 1)
	{
		vector<double> segs1 = seg->getSegments(pop1);
		vector<double> segs2 = seg->getSegments(pop2);
		globalMax[0] = optimize(segs1, segs2, hi, lower, upper);
		indexes[0] = hi->getGeneration();
		globalMax[1] = optimize(segs1, segs2, ga, lower, upper);
		indexes[1] = ga->getGeneration();
		globalMax[2] = optimize(segs1, segs2, cgfr, lower, upper);
		indexes[2] = cgfr->getGeneration();
		globalMax[3] = optimize(segs2, segs1, cgfd, lower, upper);
		indexes[3] = cgfd->getGeneration();
		int index = indexOfMax(globalMax, 4);
		cout << endl;
		cout << "Results Summary" << endl;
		cout << "----------------------------------------------------------" << endl;
		cout << "Parental populations: " << pop1 << ", " << pop2 << endl;
		cout << "Admixture proportions: " << props[pop1] << ", " << props[pop2] << endl;
		cout << "Optimal-model: " << models[index] << ", generation: " << indexes[index] << ", likelihood: " << globalMax[index] << endl;
		cout << "----------------------------------------------------------" << endl;
	}
	else
	{
		int numBoot = par->getBootstrap();
		map<int, vector<double> > optGens;
		if (!isQuiet)
		{
			cout << "Start bootstrapping process... " << endl;
		}
		for (int k = 0; k < numBoot; ++k)
		{
			vector<double> segs1 = seg->sampleSeg(pop1, generator, samProp);
			vector<double> segs2 = seg->sampleSeg(pop2, generator, samProp);
			globalMax[0] = optimize(segs1, segs2, hi, lower, upper);
			indexes[0] = hi->getGeneration();
			globalMax[1] = optimize(segs1, segs2, ga, lower, upper);
			indexes[1] = ga->getGeneration();
			globalMax[2] = optimize(segs1, segs2, cgfr, lower, upper);
			indexes[2] = cgfr->getGeneration();
			globalMax[3] = optimize(segs2, segs1, cgfd, lower, upper);
			indexes[3] = cgfd->getGeneration();
			int index = indexOfMax(globalMax, 4);
			if (optGens.find(index) == optGens.end())
			{
				vector<double> tmp;
				optGens[index] = tmp;
			}
			optGens[index].push_back(indexes[index]);
			if (!isQuiet)
			{
				cout << "Bootstrap-" << k + 1 << "--> model: " << models[index] << ", generation: " << indexes[index] << ", likelihood: " << globalMax[index]
						<< endl;
			}
		}

		//finished bootstrapping, processing results
		if (!isQuiet)
		{
			cout << "Finish bootstrapping, processing results..." << endl;
		}
		unsigned int maxCounts = 0;
		int bestMod = 0;
		for (map<int, vector<double> >::iterator it = optGens.begin(); it != optGens.end(); ++it)
		{
			if (it->second.size() > maxCounts)
			{
				maxCounts = it->second.size();
				bestMod = it->first;
			}
		}
		double meanGen = mean(optGens[bestMod]);
		double varGen = var(optGens[bestMod], meanGen);
		double ci = t_confidence_interval(maxCounts, varGen, par->getAlpha());
		double right_per = 100.0 * maxCounts / par->getBootstrap();
		double conf_level = (1 - (par->getAlpha())) * 100;
		cout << endl;
		cout << "Results Summary" << endl;
		cout << "----------------------------------------------------------" << endl;
		cout << "Parental populations: " << pop1 << ", " << pop2 << endl;
		cout << "Admixture proportions: " << props[pop1] << ", " << props[pop2] << endl;
		cout << "Optimal-model: " << models[bestMod] << setprecision(4) << "(" << right_per << "%)" << endl;
		cout << "Generation: " << meanGen << ", " << conf_level << "% confidence interval: (" << meanGen - ci << ", " << meanGen + ci << ")" << endl;
		cout << "----------------------------------------------------------" << endl;
	}

	delete hi;
	delete ga;
	delete cgfr;
	delete cgfd;
	delete seg;
	delete par;
	delete[] globalMax;
	delete[] indexes;
	return 0;
}

