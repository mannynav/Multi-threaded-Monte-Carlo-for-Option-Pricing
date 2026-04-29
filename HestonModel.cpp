#include "HestonModel.h"
#include <random>
#include "rv.h"
#include <boost/random.hpp>

HestonModel::HestonModel(PseudoFactory& factory) : S0_(factory.GetS0()),
												   r_(factory.GetRiskFreeRate()),
												   sigma_(factory.GetVolatility()),
												   V_0_(factory.GetV0()),
												   corr_(factory.GetCorrelation()),
												   volvol_(factory.GetVolVol()),
												   meanreversion_(factory.GetMeanReversion()),
												   ltmean_(factory.GetLongTermMean()),
												   PsiC_(factory.GetPsiC()),
												   N_(factory.GetNumberTotalSteps()),
												   T_(factory.GetExpiry()),
												   dt_(T_ / N_),
                                                   path_(factory.CreateBrownianMotionPath()),
                                                   generator_(factory.CreateRandomBase())
{


	expression_ = std::exp(-meanreversion_ * dt_);

	k0_ = (r_ - corr_ * meanreversion_ * ltmean_ / volvol_) * dt_;
	k1_ = (((corr_ * meanreversion_) / volvol_) - 0.5) * dt_ - corr_ / volvol_;
	k2_ = corr_ / volvol_;

	delta_ = 4.0 * meanreversion_ * ltmean_ / (volvol_ * volvol_);
	c_ = (1.0 / (4.0 * meanreversion_)) * volvol_ * volvol_ * (1 - expression_);
}


void HestonModel::generate_CIR_path(std::vector<double>& vec, boost::mt19937& rng) const
{
	vec[0] = V_0_;

	for (int i = 0; i < N_; ++i)
	{
		double kappaBar = (4.0 * meanreversion_ * vec[i] * expression_) / (volvol_ * volvol_ * (1.0 - expression_));
		kappaBar += 0.00000001; // needed for stability in generating NonCentral_ChiSquared_Sample
		double sample = rv::NonCentral_CS_Sample(rng, delta_, kappaBar);
		vec[i + 1] = c_ * sample;
	}
}


void HestonModel::simulate_paths(int start_idx, int end_idx, Eigen::MatrixXd& paths, unsigned seed) const
{
	std::cout << "simulated paths" << std::endl; 


	std::vector<double> variates(N_ + 1);
	std::vector<double> variates_CIR(N_ + 1);

	boost::mt19937 rng(seed);

	boost::normal_distribution<> nd(0.0, 1.0);

	// Simulate paths within the designated range
	for (int i = start_idx; i < end_idx; ++i)
	{

		paths(i, 0) = S0_;

		path_->fill_vector(variates, rng);
		generate_CIR_path(variates_CIR,rng);

		for (int j = 0; j < N_; ++j)
		{
			paths(i, j + 1) = paths(i, j) * std::exp(
				k0_ + k1_ * variates_CIR[j] + k2_ * variates_CIR[j + 1] + std::sqrt((1 - corr_ * corr_) * dt_ * variates_CIR[j]) * variates[j]);
		}

	}

}