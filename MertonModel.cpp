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

		std::vector<double> variates(N_);


		//Variates will be filled with sqrt(dt)*Z, Z is standard normal
		path_->GeneratePath(variates, rng);
		

		for (int j = 0; j < N_; ++j)
		{
			double pj = rv::poisson_jumps(lambdaJ_*dt_);
			double jump_ = uJ_ * pj + sigmaJ * std::sqrt(pj);

			//std::cout << "Variates: " << variates[j] << std::endl;
			paths(i, j + 1) = paths(i, j) * std::exp(nu_ * dt_ + sigma_ * sqrtdt * variates[j] + jump_);

		}

		if ((i + 1) % 200000 == 0)
		{
			std::cout << "Paths simulated: " << i + 1 << std::endl;
		}
	}

	return paths;
}

