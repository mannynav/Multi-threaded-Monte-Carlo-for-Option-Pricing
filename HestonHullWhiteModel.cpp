#include "HestonHullWhiteModel.h"
#include "rv.h"
#include <random>
#include <boost/random.hpp>


HestonHullWhiteModel::HestonHullWhiteModel(PseudoFactory& factory) : S0_(factory.GetS0()), V_0_(factory.GetV0()),
                                                                     corrXR_(factory.GetCorrXR()),
                                                                     corrXV_(factory.GetCorrXV()),
                                                                     volvol_(factory.GetVolVol()),
                                                                     meanreversion_(factory.GetMeanReversion()),
                                                                     ltmean_(factory.GetLtMean()),
                                                                     PsiC_(factory.GetPsiC()), eta_(factory.GetEta()),
                                                                     lambda_(factory.GetLambda()), N_(factory.GetN()),
                                                                     T_(factory.GetT()),
                                                                     generator_(factory.CreateRandomBase())
{
	cir_path_.resize(N_ + 1);
	pathR_.resize(N_ + 1);
	Mt_.resize(N_ + 1);
	timeDt_.resize(N_ + 1);

	//pre-compute everything possible

	dt_ = T_ / N_;
	differentiationStep_ = 0.0001;
	expression_ = std::exp(-meanreversion_ * dt_);

	k0_ = -(meanreversion_ * corrXV_ * ltmean_ * dt_) / volvol_;

	k1_ = ((meanreversion_ * corrXV_ / volvol_) - 0.5) * dt_ - corrXV_ / volvol_;

	k2_ = corrXV_ / volvol_;

	k3_ = (1 - corrXV_ * corrXV_) * dt_;

	L1_ = (eta_ * std::sqrt(dt_) * corrXR_) / std::sqrt(1 - corrXV_ * corrXV_);

	L2_ = (eta_ * std::sqrt(dt_)) * std::sqrt(1 - ((corrXR_ * corrXR_) / (1 - corrXV_ * corrXV_)));
}


HestonHullWhiteModel::~HestonHullWhiteModel()
{
	delete generator_;
}


double HestonHullWhiteModel::f0(double t) const
{
	double fwdBond = ZCB(t + differentiationStep_);
	double backwardBond = ZCB(t - differentiationStep_);

	double result = -(std::log(fwdBond) - std::log(backwardBond)) / (2 * differentiationStep_);

	return result;
}

double HestonHullWhiteModel::theta(double t) const
{
	double result = (1 / lambda_) * (f0(t + dt_) - f0(t - dt_)) / (2 * dt_) +
		f0(t) + (eta_ * eta_) / (2 * lambda_ * lambda_) * (1 - std::exp(-2.0 * lambda_ * t));

	return result;
}

double HestonHullWhiteModel::next_v(boost::mt19937& rng, double V) const
{
	double m_ = ltmean_ + (V - ltmean_) * expression_;

	double s2_ = (V * volvol_ * volvol_ * expression_) * (1 - expression_) / meanreversion_
		+ ((ltmean_ * volvol_ * volvol_) * (1 - expression_) * (1 - expression_)) / (2 * meanreversion_);

	double psi_ = s2_ / (m_ * m_);

	if (psi_ <= PsiC_)
	{
		double b2_ = (2 / psi_) - 1 + std::sqrt((2 / psi_)) * std::sqrt((2 / psi_) - 1);
		double a_ = m_ / (1 + b2_);

		double z = rv::normVariate(rng);

		return a_ * (std::sqrt(b2_) + z) * (std::sqrt(b2_) + z);
	}
	double p_ = (psi_ - 1) / (psi_ + 1);
	double beta_ = (1 - p_) / m_;
	double u = rv::rand_uniform(rng);

	if (u <= p_)
	{
		return 0;
	}

	if (p_ < u <= 1)
	{
		double ret = (std::log((1 - p_) / (1 - u))) / beta_;

		return ret;
	}
	return 0.0;
}

std::vector<double> HestonHullWhiteModel::generate_CIR_path(boost::mt19937& rng) const
{
	cir_path_[0] = V_0_;
	for (int i = 0; i < N_; ++i)
	{
		cir_path_[i + 1] = next_v(rng, cir_path_[i]);
	}

	return cir_path_;
}


void HestonHullWhiteModel::simulate_paths(int start_idx, int end_idx, Eigen::MatrixXd& paths) const
{
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	generator_->SeedGenerator(seed);
	boost::mt19937 rng = generator_->GetGenerator();

	boost::normal_distribution<> normal_distribution(0.0, 1.0);
	boost::random::uniform_real_distribution<> uniform_real_distribution(0.0, 1.0);

	boost::variate_generator<boost::mt19937&, boost::normal_distribution<>> rnorm(rng, normal_distribution);
	boost::variate_generator<boost::mt19937&, boost::random::uniform_real_distribution<>> u(
		rng, uniform_real_distribution);


	// Each thread gets its own "chunk" of paths to simulate
	for (int i = start_idx; i < end_idx; ++i)
	{
		paths(i, 0) = S0_;
		pathR_[0] = f0(0.00001);
		timeDt_[0] = 0;
		Mt_[0] = 1;

		std::vector<double> variates(N_);
		std::vector<double> variatesL2(N_);

		std::ranges::generate(variates, rnorm);
		std::ranges::generate(variatesL2, rnorm);

		std::vector<double> variates_CIR{generate_CIR_path(rng)};


		for (int j = 0; j < N_; ++j)
		{
			pathR_[j + 1] = pathR_[j] + lambda_ * (theta(timeDt_[j]) - pathR_[j]) * dt_ + L1_ * variates[j] + L2_ *
				variatesL2[j];

			paths(i, j + 1) = paths(i, j) * std::exp(
				pathR_[j] * dt_ + k0_ + k1_ * variates_CIR[j] + k2_ * variates_CIR[j + 1] + std::sqrt(
					k3_ * cir_path_[j]) * variates[j]);

			Mt_[j + 1] = Mt_[j] * std::exp(0.5 * (pathR_[j + 1] + pathR_[j]) * dt_);

			timeDt_[j + 1] = timeDt_[j] + dt_;
		}


		if ((i + 1) % 200000 == 0)
		{
			std::cout << "Paths simulated: " << i + 1 << std::endl;
		}
	}
}
