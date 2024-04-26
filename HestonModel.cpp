
#include "HestonModel.h"
#include <random>
#include "rv.h"
#include <boost/random.hpp>
#include <boost/random/uniform_real_distribution.hpp>

#include <gsl/gsl_randist.h>
#include <gsl/gsl_rng.h>

const gsl_rng_type* rng_type = gsl_rng_mt19937; // Mersenne Twister generator



HestonModel::HestonModel(double S0, double r, double sigma) : S0_(S0), r_(r), sigma_(sigma)
{
}

HestonModel::HestonModel(PseudoFactory& factory) : S0_(factory.GetS0()), r_(factory.Getr()), sigma_(factory.Getsig()), N_(factory.GetN()), T_(factory.GetT()),
V_0_(factory.GetV0()), meanreversion_(factory.GetMeanReversion()), ltmean_(factory.GetLtMean()), volvol_(factory.GetVolVol()), corr_(factory.GetCorrelation()), PsiC_(factory.GetPsiC())
{

	std::cout << "S0: " << S0_ << std::endl;
	std::cout << "V0:" << V_0_ << std::endl;

	FillCirPath_.resize(N_+1);
	dt_ = factory.GetT() / factory.GetN();
	expression_ = std::exp(-meanreversion_ * dt_);

	k0_ = (r_ - corr_*meanreversion_*ltmean_/volvol_) * dt_;
	k1_ = ((meanreversion_ * corr_ / volvol_) - 0.5) * y2_ * dt_ + corr_ / volvol_;
	k2_ = ((meanreversion_*meanreversion_/volvol_) - 0.5) * y1_*dt_ - corr_/volvol_;
	k3_ = (1 - corr_ * corr_) * y2_ * dt_;
	k4_ = (1-corr_ * corr_) * y1_ * dt_;


	cbar_ = (volvol_*volvol_/(4*meanreversion_))*(1-std::exp(-meanreversion_*dt_));
	dof_ = 4*meanreversion_*ltmean_/(volvol_*volvol_);
	ncp_ = 4*meanreversion_*expression_/((volvol_*volvol_)*(1-expression_));


	generator_ = factory.CreateRandomBase();
}


HestonModel::~HestonModel()
{
	delete generator_;
}


double HestonModel::Next_V(double V) const
{

	double delta = 4 * meanreversion_ * ltmean_ / volvol_ / volvol_;
	double c = 1 / (4 * meanreversion_) * volvol_ * volvol_ * (1 - expression_);
	double kappa_bar = 4 * meanreversion_ * V * expression_ / (volvol_ * volvol_ * (1 - expression_));

	boost::random::non_central_chi_squared_distribution<> dist(delta, kappa_bar);
	boost::variate_generator<boost::mt19937&, boost::random::non_central_chi_squared_distribution<> > chrnorm(generator_->GetGenerator(), dist);
	

	double sample = c * chrnorm();


}

void HestonModel::simulate_paths(int start_idx, int end_idx, Eigen::MatrixXd& paths) const
{

	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	generator_->SeedGenerator(seed);
	boost::mt19937 rng = generator_->GetGenerator();
	boost::normal_distribution<> nd1(0.0, 1.0);
	boost::variate_generator<boost::mt19937&, boost::normal_distribution<> > rnorm(rng, nd1);

	double sqrtdt = std::sqrt(dt_);

	// Simulate paths within the designated range
	for (int i = start_idx; i < end_idx; ++i)
	{
		paths(i, 0) = S0_;
		FillCirPath_[0] = V_0_;

		std::vector<double> variates(N_);
		std::generate(variates.begin(), variates.end(), rnorm);

		for (int j = 0; j < N_; ++j)
		{

			//std::cout << "FillCirPath_[j-1]: " << FillCirPath_[j] << std::endl;

			FillCirPath_[j+1] = Next_V(FillCirPath_[j]);

			//std::cout << "Variates: " << variates[j] << std::endl;

			paths(i, j + 1) = paths(i, j) * std::exp(k0_ + k1_ * FillCirPath_[j] + k2_ * FillCirPath_[j + 1] + std::sqrt((1 - corr_ * corr_) * FillCirPath_[j])) * variates[j];
		}


		if ((i + 1) % 20000 == 0)
		{
			std::cout << "Paths simulated: " << i + 1 << std::endl;
		}
	}
}
