#pragma once


#ifndef GREEKBASE_H
#define GREEKBASE_H

#include "PseudoFactory.h"
#include "ModelBase.h"
#include <map>

class GreekBase
{
public:

	virtual ~GreekBase() = default;

	virtual std::map<std::string, double> ComputeGreeks(const Eigen::MatrixXd& prices, const ModelBase& model) const = 0;
	virtual double ComputeDelta(const Eigen::MatrixXd& prices, const ModelBase& model) const = 0;
	virtual double ComputeVega(const Eigen::MatrixXd& prices, const ModelBase& model) const = 0;
	virtual double ComputeGamma(const Eigen::MatrixXd& prices, const ModelBase& model) const = 0;


private:

};


#endif