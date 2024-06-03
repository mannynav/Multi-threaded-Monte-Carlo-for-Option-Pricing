
#include "SABRModel.h"
#include "rv.h"

SABRModel::SABRModel(PseudoFactory& factory) : S0_(factory.GetS0()), 
											   r_(factory.GetRiskFreeRate()),
											   alpha_(factory.GetAlphaSABR()),
											   beta_(factory.GetBetaSABR()),
											   rho_(factory.GetRhoSABR()),
											   nu_(factory.GetNuSABR()),
											   M_(factory.GetNumberOfPaths()),
											   N_(factory.GetNumberTotalSteps()),
											   T_(factory.GetExpiry()),
											   dt_(factory.GetExpiry() / factory.GetNumberTotalSteps()),
	                                           sqrtdt_(std::sqrt(dt_)),
											   path_(factory.CreateBrownianMotionPath()),
											   generator_(factory.CreateRandomBase())

{}


void SABRModel::simulate_paths(int start_idx, int end_idx, Eigen::MatrixXd& paths) const
{
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	generator_->SeedGenerator(seed);
	boost::mt19937 rng = generator_->GetGenerator();

	paths.col(0).setConstant(S0_); //Spot price

	for (int i = start_idx; i < end_idx; ++i)
	{

		std::vector<double> variates1(N_), variates2(N_), sigmaVec_(N_);

		path_->GeneratePath(variates1, rng);
		path_->GeneratePath(variates2, rng);

		sigmaVec_[0] = alpha_; // Spot volatility

		for (int j = 0; j < N_; ++j)
		{
			double Z = rho_ * variates1[j] + std::sqrt(1 - rho_ * rho_) * variates2[j];

			double F_pred = paths(i, j) + sigmaVec_[j] * std::pow(paths(i, j), beta_) * sqrtdt_ * variates1[j];
			double sigma_pred = sigmaVec_[j] + nu_ * sigmaVec_[j] * sqrtdt_ * Z;

			paths(i, j + 1) = paths(i, j) + 0.5 * sigmaVec_[j] * std::pow(paths(i, j), beta_) * sqrtdt_ * variates1[j] + 0.5 * sigma_pred * std::pow(F_pred, beta_) * sqrtdt_ * variates1[j];
			sigmaVec_[j + 1] = sigmaVec_[j] + 0.5 * nu_ * sigmaVec_[j] * sqrtdt_ * Z + 0.5 * nu_ * sigma_pred * sqrtdt_ * Z;

		}

		if ((i + 1) % 200000 == 0)
		{
			std::cout << "Paths simulated: " << i + 1 << std::endl;
		}
	}
}
