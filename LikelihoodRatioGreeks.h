//
//#pragma once
//
//#include "GreekBase.h"
//
//
//
//#ifndef LIKELIHOODRATIOGREEKS_H
//#define LIKELIHOODRATIOGREEKS_H
//
//class Pseudofactory;
//
//class LikelihoodRatioGreeks : public GreekBase
//{
//public:
//
//	explicit LikelihoodRatioGreeks(const PseudoFactory& factory);
//	std::map<std::string, double> ComputeGreeks(const Eigen::VectorXd& prices, const ModelBase& model) const override;
//
//
//private:
//
//	double ComputeDelta(const Eigen::VectorXd& prices, const ModelBase& model) const override;
//	double ComputeVega(const Eigen::VectorXd& prices, const ModelBase& model) const override;
//	double ComputeGamma(const Eigen::VectorXd& prices, const ModelBase& model) const override;
//
//	//might delegate to mixedGreek class for gamma
//
//
//
//};
//
//
//
//
//#endif