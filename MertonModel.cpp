#include "MertonModel.h"
#include "rv.h"

MertonModel::MertonModel(PseudoFactory& factory) : S0_(factory.GetS0()),
												   r_(factory.GetRiskFreeRate()),
												   sigma_(factory.GetVolatility()),
												   uJ_(factory.GetJumpMean()),
												   sigmaJ(factory.GetJumpVol()),
												   lambdaJ_(factory.GetJumpIntensity()),
												   M_(factory.GetNumberOfPaths()),
												   N_(factory.GetNumberTotalSteps()),
												   T_(factory.GetExpiry()),
												   dt_(T_/N_),
                                                   sqrtdt_(std::sqrt(dt_)),
												   path_(factory.CreateBrownianMotionPath()),
											       generator_(factory.CreateRandomBase())

{
	nu_ = r_ - lambdaJ_ * (std::exp(uJ_ + 0.5 * sigmaJ * sigmaJ) - 1) - 0.5 * sigma_ * sigma_;	//Martingale adjustment
	poisson_ = boost::poisson_distribution<>(lambdaJ_ * dt_);
}


void MertonModel::simulate_paths(int start_idx, int end_idx, Eigen::MatrixXd& paths) const
{

	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	generator_->SeedGenerator(seed);
	boost::mt19937 rng = generator_->GetGenerator();

	boost::variate_generator<boost::mt19937&, boost::poisson_distribution<>> poisson_variate(rng, poisson_);

	paths.col(0).setConstant(S0_);

	for (int i = start_idx; i < end_idx; ++i)
	{
		std::vector<double> variates1(N_), variates2(N_), variatesPoisson(N_);

		path_->GeneratePath(variates1, rng);
		path_->GeneratePath(variates2, rng);

		std::ranges::generate(variatesPoisson,poisson_variate);

		for (int j = 0; j < N_; ++j)
		{
			double jump_ = uJ_ * variatesPoisson[j] + sigmaJ * std::sqrt(variatesPoisson[j]) * variates2[j];

			paths(i, j + 1) = paths(i, j) * std::exp(nu_ * dt_ + sigma_ * sqrtdt_ * variates1[j] + jump_);

		}

		if ((i + 1) % 200000 == 0)
		{
			std::cout << "Paths simulated: " << i + 1 << std::endl;
		}
	}
}

