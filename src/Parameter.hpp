/*
 * Parameter.hpp
 *
 *  Created on: Apr 22, 2015
 *  Author: young
 */

#ifndef PARAMETER_HPP_
#define PARAMETER_HPP_

#include <string>

const std::string kProgramName = "AdmixInfer";
const std::string kVersion = "1.0.4";
class Parameter
{
public:
	Parameter(int argc, char **argv);
	virtual ~Parameter();
	void help() const;
	bool check();
	bool isQuiet() const;
	int getBootstrap() const;
	double getLower() const;
	double getUpper() const;
	double getAlpha() const;
	double getSampleProp() const;
	std::string getFname() const;

private:
	bool quiet;
	int bootstrap;
	double lower;
	double upper;
	double alpha;
	double sampleProp;
	std::string fname;
};

#endif /* PARAMETER_HPP_ */
