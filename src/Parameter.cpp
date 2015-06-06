/*
 * Parameter.cpp
 *
 *  Created on: Apr 22, 2015
 *  Author: young
 */

#include <cstdlib>
#include <iostream>
#include "Parameter.hpp"
#include "SpecModel.hpp"

using namespace std;

Parameter::Parameter(int argc, char **argv) :
		quiet(0), bootstrap(1), lower(0), upper(kInfinity), alpha(0.05), sampleProp(1.0)
{
	if (argc < 2)
	{
		cerr << "More arguments required, please use -h/--help to get help!" << endl;
		exit(1);
	}
	//process command arguments
	for (int i = 1; i < argc; ++i)
	{
		string agv(argv[i]);
		if (agv == "-h" || agv == "--help")
		{
			help();
			exit(0);
		}
		else if (agv == "-q" || agv == "--quiet")
		{
			quiet = true;
		}
		else if (agv == "-i" || agv == "--input")
		{
			fname = string(argv[++i]);
		}
		else if (agv == "-l" || agv == "--lower")
		{
			lower = atof(argv[++i]);
		}
		else if (agv == "-u" || agv == "--upper")
		{
			upper = atof(argv[++i]);
		}
		else if (agv == "-b" || agv == "--bootstrap")
		{
			bootstrap = atoi(argv[++i]);
		}
		else if (agv == "-a" || agv == "--alpha")
		{
			alpha = atof(argv[++i]);
		}
		else if (agv == "-p" || agv == "--proportion")
		{
			sampleProp = atof(argv[++i]);
		}
	}
	if (!check())
	{
		exit(1);
	}
}

Parameter::~Parameter()
{
	// TODO Auto-generated destructor stub
}

bool Parameter::isQuiet() const
{
	return quiet;
}

double Parameter::getLower() const
{
	return lower;
}

string Parameter::getFname() const
{
	return fname;
}

int Parameter::getBootstrap() const
{
	return bootstrap;
}

double Parameter::getUpper() const
{
	return upper;
}

double Parameter::getAlpha() const
{
	return alpha;
}

double Parameter::getSampleProp() const
{
	return sampleProp;
}

//perform check, validate the inputs
bool Parameter::check()
{
	if (lower < 0)
	{
		cerr << "Lower bound to discard short tracks should be positive, reset to default 0!" << endl;
		lower = 0;
	}
	if (upper < lower)
	{
		cerr << "Upper bound should larger than lower bound, otherwise all data will be filtered out!" << endl;
		return 0;
	}
	if (alpha > 1 || alpha < 0)
	{
		cerr << "Alpha should between 0-1, reset to default 0.05" << endl;
		alpha = 0.05;
	}
	if (fname.length() == 0)
	{
		cerr << "Input filename is empty!" << endl;
		return 0;
	}
	if (bootstrap < 1)
	{
		cerr << "Number of bootstrapping repeats should be positive, reset to default 1" << endl;
		bootstrap = 1;
	}
	if (sampleProp <= 0)
	{
		cerr << "Proportion of bootstrapping resampling should be positive, reset to default 1.0" << endl;
		sampleProp = 1.0;
	}
	return 1;
}

void Parameter::help() const
{
	cout << kProgramName << " v" << kVersion << endl;
	cout << kProgramName << " is designed to optimize the parameters of admixture model via maximum likelihood estimation and figure out the model which best fit the data. The optimization is under assumption of HI, GA and CGF model" << endl;
	cout << "General usage: " << kProgramName << " <arguments> [options]" << endl;
	cout << "Arguments:" << endl;
	cout << "\t-i/--input\t<string>\tInput of the ancestral tracks [required]" << endl;
	cout << "\t-l/--lower\t[double]\tLower bound to discard short tracks [optional, default 0]" << endl;
	cout << "\t-u/--upper\t[double]\tUpper bound to discard long tracks [optional, default Infinity]" << endl;
	cout << "\t-a/--alpha\t[double]\tSignificance level to compute confidence intervals [optional, default 0.05]" << endl;
	cout << "\t-b/--bootstrap\t[integer]\tNumber of bootstrapping repeats [optional, default 1, do not perform bootstrapping]" << endl;
	cout << "\t-p/--proportion\t[double]\tProportion of tracks in bootstrapping sampled [optional, default 1.0, sample equal size]" << endl;
	cout << "Options:" << endl;
	cout << "\t-h/--help\tPrint help messages" << endl;
	cout << "\t-q/--quiet\tRunning in quiet mode" << endl;
}
