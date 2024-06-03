#include "VarianceGammaModel.h"
#include "rv.h"

VarianceGammaModel::VarianceGammaModel(PseudoFactory& factory) : s0_(factory.GetS0()),
                                                                 r_(factory.GetRiskFreeRate()),
                                                                 C_(factory.GetCVG()),
                                                                 G_(factory.GetGVG()),
                                                                 M_(factory.GetMVG()), 
																 N_(factory.GetNumberTotalSteps()),
                                                                 T_(factory.GetExpiry()),
																 dt_(T_ / N_)
{
	//convert CGM parameters to normal representation
	nu_ = 1 / C_;
	theta_ = (1 / M_ - 1 / G_) / nu_;
	sigma_ = std::sqrt((std::pow(1 / G_ + 0.5 * theta_ * nu_, 2) - 0.25 * std::pow(theta_, 2) * std::pow(nu_, 2)) * 2 / nu_);

	gamma_distr_ = boost::gamma_distribution<>(dt_ / nu_, nu_);

	omega_ = (1 / nu_) * std::log(1 - theta_ * nu_ - nu_ * sigma_ * sigma_ / 2);
	mu_ = omega_ + r_;

	generator_ = factory.CreateRandomBase();
	path_ = factory.CreateBrownianMotionPath();
	
}


void VarianceGammaModel::simulate_paths(int start_idx, int end_idx, Eigen::MatrixXd& paths) const
{
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	generator_->SeedGenerator(seed);
	boost::mt19937 rng = generator_->GetGenerator();

	boost::variate_generator<boost::mt19937&, boost::gamma_distribution<>> rgamma(rng, gamma_distr_);

	paths.col(0).setConstant(s0_);

	// Simulate paths within the designated range
	for (int i = start_idx; i < end_idx; ++i)
	{

		std::vector<double> variates(N_);
		path_->GeneratePath(variates, rng);

		std::vector<double> gamma_variates(N_);
		std::ranges::generate(gamma_variates, rgamma);


		for (int j = 0; j < N_; ++j)
		{
			double X_bar = theta_* gamma_variates[j] + sigma_ * std::sqrt(gamma_variates[j]) * variates[j];
			paths(i, j + 1) = paths(i, j) * std::exp(mu_ * dt_ + X_bar);
		}


		if ((i + 1) % 200000 == 0)
		{
			std::cout << "Paths simulated: " << i + 1 << '\n';
		}
	}
}
