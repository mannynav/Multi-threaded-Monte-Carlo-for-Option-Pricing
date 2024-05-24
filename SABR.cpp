
#include "SABRModel.h"
#include "rv.h"

SABRModel::SABRModel(PseudoFactory& factory) : S0_(factory.GetS0()), 
											   r_(factory.GetRiskFreeRate()),
											   alpha_(factory.GetAlphaSABR()),
											   beta_(factory.GetBetaSABR()),
											   rho_(factory.GetRhoSABR()),
											   nu_(factory.GetNuSABR()),
											   N_(factory.GetNumberTotalSteps()), 
											   T_(factory.GetExpiry()), 
											   M_(factory.GetNumberOfPaths()),
	                                           dt_(factory.GetExpiry() / factory.GetNumberTotalSteps()),
											   sqrtdt_(std::sqrt(dt_)),
											   generator_(factory.CreateRandomBase()),
											   path_(factory.CreateBrownianMotionPath())

{}


void SABRModel::simulate_paths(int start_idx, int end_idx, Eigen::MatrixXd& paths) const
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
			
			double Z = rho_ * variates[j] + std::sqrt(1 - rho_ * rho_) * rv::GetNormalVariate();
		
			double F_pred = paths(i, j) + sigmaVec_[j] * std::pow(paths(i, j), beta_) * sqrtdt_ * variates[j];
			double sigma_pred = sigmaVec_[j] + nu_ * sigmaVec_[j] * sqrtdt_ * Z;

			paths(i, j + 1) = paths(i, j) + 0.5 * sigmaVec_[j] * std::pow(paths(i, j), beta_) * sqrtdt_ * variates[j] + 0.5 * sigma_pred * std::pow(F_pred, beta_) * sqrtdt_ * variates[j];
			sigmaVec_[j + 1] = sigmaVec_[j] + 0.5 * nu_ * sigmaVec_[j] * sqrtdt_ * Z + 0.5 * nu_ * sigma_pred * sqrtdt_ * Z;

		}

		if ((i + 1) % 100000 == 0)
		{
			std::cout << "Paths simulated: " << i + 1 << std::endl;
		}
	}
}
