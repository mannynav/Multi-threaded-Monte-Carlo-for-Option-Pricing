#include "GBMModel.h"
#include "rv.h"
#include <mutex>
#include <immintrin.h> // AVX2

namespace {
	std::mutex cout_mutex; // For thread-safe std::cout
}

//Fast exp approximation(replace with SVML _mm256_exp_pd if available)
inline __m256d fast_exp_avx(__m256d x) {
	__m256d one = _mm256_set1_pd(1.0);
	__m256d half = _mm256_set1_pd(0.5);
	__m256d x2 = _mm256_mul_pd(x, x);
	__m256d result = _mm256_add_pd(one, x);
	result = _mm256_add_pd(result, _mm256_mul_pd(half, x2));
	return result;
}


GBMModel::GBMModel(PseudoFactory& factory) : S0_(factory.GetS0()),
                                             r_(factory.GetRiskFreeRate()),
                                             sigma_(factory.GetVolatility()),
                                             N_(factory.GetNumberTotalSteps()),
	                                         T_(factory.GetExpiry()),
	theta_(0.0),
									         dt_(factory.GetExpiry() / factory.GetNumberTotalSteps()),
											 sqrtdt_(std::sqrt(dt_)),
											 generator_(factory.CreateRandomBase()),
											 path_(factory.CreateBrownianMotionPath())
{
	//drift_ = (r_ - 0.5 * sigma_ * sigma_) * dt_;

	drift_ = (r_ - 0.5 * sigma_ * sigma_) * dt_;
	if (auto* importance = dynamic_cast<AdaptiveImportanceSampler*>(path_.get())) {
		theta_ = (std::log(factory.GetStrike() / S0_) - (r_ - 0.5 * sigma_ * sigma_) * T_) / (sigma_ * T_);
		drift_ = (r_ - 0.5 * sigma_ * sigma_ + theta_) * dt_;
	}
}


void GBMModel::simulate_paths(int start_idx, int end_idx, Eigen::MatrixXd& paths, unsigned seed) const
{

	//generator_->SeedGenerator(seed);
	boost::mt19937 rng(seed);

	auto local_path = paths;

	// Set initial column
	paths.col(0).segment(start_idx, end_idx - start_idx).setConstant(S0_);



	for (int i = start_idx; i < end_idx; ++i)
	{

		std::vector<double> variates(N_);
		path_->set_path_index(i);
		path_->fill_vector(variates,rng);


		for (int j = 0; j < N_; ++j)
		{
			paths(i, j + 1) = paths(i, j) * exp(drift_ + sigma_ * sqrtdt_ * variates[j]);

		}


	}
}
