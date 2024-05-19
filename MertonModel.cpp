#include "MertonModel.h"
#include "rv.h"

MertonModel::MertonModel(PseudoFactory& factory) : S0_(factory.GetS0()), r_(factory.Getr()), sigma_(factory.Getsig()), N_(factory.GetN()), T_(factory.GetT()), M_(factory.GetM()), uJ_(factory.GetUJ()), sigmaJ(factory.GetSigmaJ()), lambdaJ_(factory.GetLambdaJ())

{
	nu_ = r_ - lambdaJ_ * (std::exp(uJ_ + 0.5 * sigmaJ * sigmaJ) - 1) - 0.5 * sigma_ * sigma_;	//Martingale adjustment

	dt_ = factory.GetT() / factory.GetN();

	generator_ = factory.CreateRandomBase();
	path_ = factory.CreateBrownianMotionPath();
}


Eigen::MatrixXd MertonModel::simulate_paths(int start_idx, int end_idx, Eigen::MatrixXd& paths) const
{

	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	generator_->SeedGenerator(seed);
	boost::mt19937 rng = generator_->GetGenerator();

	double sqrtdt = std::sqrt(dt_);

	// Simulate paths within the designated range
	for (int i = start_idx; i < end_idx; ++i)
	{
		paths(i, 0) = S0_; // Set initial price

		//std::vector<double> variates(N_);
		std::vector<double> variatesPoisson(N_);

		//Variates will be filled with sqrt(dt)*Z, Z is standard normal
		//path_->GeneratePath(variates, rng);
		std::generate(variatesPoisson.begin(), variatesPoisson.end(), [&]() {return rv::Poisson_jumps(lambdaJ_ * dt_); });
		

		for (int j = 0; j < N_; ++j)
		{
			double jump_ = uJ_ * variatesPoisson[j] + sigmaJ * std::sqrt(variatesPoisson[j]) * rv::GetNormalVariate();

			paths(i, j + 1) = paths(i, j) * std::exp(nu_ * dt_ + sigma_ * sqrtdt * rv::GetNormalVariate() + jump_);

		}

		if ((i + 1) % 200000 == 0)
		{
			std::cout << "Paths simulated: " << i + 1 << std::endl;
		}
	}

	return paths;
}

