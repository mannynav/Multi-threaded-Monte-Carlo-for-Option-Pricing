#include "HestonModel.h"
#include <random>
#include "rv.h"
#include <boost/random.hpp>

HestonModel::HestonModel(PseudoFactory& factory) : S0_(factory.GetS0()), r_(factory.Getr()), sigma_(factory.Getsig()),
                                                   V_0_(factory.GetV0()), corr_(factory.GetCorrelation()),
                                                   volvol_(factory.GetVolVol()),
                                                   meanreversion_(factory.GetMeanReversion()),
                                                   ltmean_(factory.GetLtMean()), PsiC_(factory.GetPsiC()),
                                                   N_(factory.GetN()), T_(factory.GetT())
{
	cir_path_.resize(N_ + 1);

	dt_ = factory.GetT() / factory.GetN();
	expression_ = std::exp(-meanreversion_ * dt_);
	sqrt_expression_ = std::exp(1 - corr_ * corr_) * dt_;

	k0_ = (r_ - corr_ * meanreversion_ * ltmean_ / volvol_) * dt_;
	k1_ = (((corr_ * meanreversion_) / volvol_) - 0.5) * dt_ - corr_ / volvol_;
	k2_ = corr_ / volvol_;

	delta_ = 4.0 * meanreversion_ * ltmean_ / (volvol_ * volvol_);
	c_ = (1.0 / (4.0 * meanreversion_)) * volvol_ * volvol_ * (1 - expression_);

	generator_ = factory.CreateRandomBase();
}


std::vector<double> HestonModel::generate_CIR_path(boost::mt19937& rng) const
{
	cir_path_[0] = V_0_;

	for (int i = 0; i < N_; ++i)
	{
		double kappaBar = (4.0 * meanreversion_ * cir_path_[i] * expression_) / (volvol_ * volvol_ * (1.0 -
			expression_));
		kappaBar += 0.000000001;
		double sample = rv::NonCentral_CS_Sample(rng, delta_, kappaBar);
		cir_path_[i + 1] = c_ * sample;
	}

	return cir_path_;
}


void HestonModel::simulate_paths(int start_idx, int end_idx, Eigen::MatrixXd& paths) const
{
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	generator_->SeedGenerator(seed);
	boost::mt19937 rng = generator_->GetGenerator();

	boost::normal_distribution<> nd(0.0, 1.0);
	boost::variate_generator<boost::mt19937&, boost::normal_distribution<>> rnorm(rng, nd);

	// Simulate paths within the designated range
	for (int i = start_idx; i < end_idx; ++i)
	{
		paths(i, 0) = S0_;

		std::vector<double> variates(N_);
		std::ranges::generate(variates, rnorm);

		std::vector<double> variates_CIR{generate_CIR_path(rng)};


		for (int j = 0; j < N_; ++j)
		{
			paths(i, j + 1) = paths(i, j) * std::exp(
				k0_ + k1_ * variates_CIR[j] + k2_ * variates_CIR[j + 1] + std::sqrt(
					(1 - corr_ * corr_) * dt_ * variates_CIR[j]) * variates[j]);
		}


		if ((i + 1) % 200000 == 0)
		{
			std::cout << "Paths simulated: " << i + 1 << std::endl;
		}
	}
}
