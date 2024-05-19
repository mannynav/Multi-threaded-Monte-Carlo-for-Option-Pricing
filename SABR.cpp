
#include "SABRModel.h"
#include "rv.h"

SABRModel::SABRModel(PseudoFactory& factory) : S0_(factory.GetS0()), 
											   r_(factory.Getr()),
											   alpha_(factory.GetAlphaSABR()),
											   beta_(factory.GetBetaSABR()),
											   rho_(factory.GetRhoSABR()),
											   nu_(factory.GetNuSABR()),
											   N_(factory.GetN()), 
											   T_(factory.GetT()), 
											   M_(factory.GetM()),
	                                           dt_(factory.GetT() / factory.GetN()),
											   sqrtdt_(std::sqrt(dt_)),
											   generator_(factory.CreateRandomBase()),
											   path_(factory.CreateBrownianMotionPath())

{}


Eigen::MatrixXd SABRModel::simulate_paths(int start_idx, int end_idx, Eigen::MatrixXd& paths) const
{

	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	generator_->SeedGenerator(seed);
	boost::mt19937 rng = generator_->GetGenerator();

	// Simulate paths within the designated range
	for (int i = start_idx; i < end_idx; ++i)
	{

		std::vector<double> variates(N_);
		std::vector<double> sigmaVec_(N_ + 1);

		paths(i, 0) = S0_; // Spot price
		sigmaVec_[0] = alpha_; // Spot volatility

		std::generate(variates.begin(), variates.end(), [&]() {return rv::GetNormalVariate(); });

		for (int j = 0; j < N_; ++j)
		{
			//paths(i, j + 1) = std::max(paths(i, j) + sigmaVec_[j] * std::pow(paths(i, j), beta_) * sqrtdt * variates[j] + 0.5 * beta_ * std::pow(sigmaVec_[j], 2) * std::pow(paths(i, j), 2 * beta_ - 1) * (std::pow(sqrtdt * variates[j], 2) - dt_), 0.0);
			double Z = rho_ * variates[j] + std::sqrt(1 - rho_ * rho_) * rv::GetNormalVariate();
			//sigmaVec_[j+1] = sigmaVec_[j] * std::exp(alpha_ * sqrtdt * Z - dt_ * alpha_ * alpha_ / 2.0);

			paths(i, j + 1) = paths(i, j) + r_ * dt_ + sigmaVec_[j] * std::pow(std::max(paths(i, j), 0.0), beta_) * sqrtdt_ * variates[j];
			sigmaVec_[j + 1] = sigmaVec_[j] +  nu_* sigmaVec_[j] * sqrtdt_ * Z;
		}

		if ((i + 1) % 100000 == 0)
		{
			std::cout << "Paths simulated: " << i + 1 << std::endl;
		}
	}

	return paths;
}
