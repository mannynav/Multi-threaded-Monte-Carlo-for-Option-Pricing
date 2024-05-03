#include "VarianceGammaModel.h"
#include "rv.h"

VarianceGammaModel::VarianceGammaModel(PseudoFactory& factory) : s0_(factory.GetS0()),
                                                                 r_(factory.Getr()),
                                                                 theta_(factory.GetThetaVG()),
                                                                 beta_(factory.GetBetaVG()),
                                                                 sigmaVg_(factory.GetSigmaVG()), N_(factory.GetN()),
                                                                 T_(factory.GetT())
{
	dt_ = factory.GetT() / factory.GetN();
	omega_ = (1 / beta_) * std::log(1 - theta_ * beta_ - beta_ * sigmaVg_ * sigmaVg_ / 2);
	mu_Vg_ = omega_ + r_;

	generator_ = factory.CreateRandomBase();
	path_ = factory.CreateBrownianMotionPath();
	
}


void VarianceGammaModel::simulate_paths(int start_idx, int end_idx, Eigen::MatrixXd& paths) const
{
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	generator_->SeedGenerator(seed);
	boost::mt19937 rng = generator_->GetGenerator();

	boost::gamma_distribution<> gamma_dist(dt_ / beta_, beta_);
	boost::variate_generator<boost::mt19937&, boost::gamma_distribution<>> rgamma(rng, gamma_dist);

	// Simulate paths within the designated range
	for (int i = start_idx; i < end_idx; ++i)
	{
		paths(i, 0) = s0_;

		std::vector<double> variates(N_);

		//generates standard normals
		path_->GeneratePath(variates, rng);

		std::vector<double> gamma_variates(N_);
		std::ranges::generate(gamma_variates, rgamma);

		for (int j = 0; j < N_; ++j)
		{
			std::cout << "Variates: " << variates[j] << std::endl;

			double X_bar = theta_ * gamma_variates[j] + sigmaVg_ * std::sqrt(gamma_variates[j]) * variates[j];

			paths(i, j + 1) = paths(i, j) * std::exp(mu_Vg_ * dt_ + X_bar);
		}

		if ((i + 1) % 200000 == 0)
		{
			std::cout << "Paths simulated: " << i + 1 << std::endl;
		}
	}
}
