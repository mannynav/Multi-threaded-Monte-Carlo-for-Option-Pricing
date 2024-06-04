#include "MCSimulation.h"
#include "PseudoFactory.h"
#include <map>

MCSimulation::MCSimulation()
{
}

MCSimulation::MCSimulation(PseudoFactory& factory) : gatherer_(std::make_unique<MCGatherer>()),
                                                     number_of_paths_(factory.GetNumberOfPaths()),
                                                     number_of_steps_(factory.GetNumberTotalSteps()),
                                                     num_threads_(factory.GetNumThreads())
{
}

void MCSimulation::run(const OptionBase& option, const ModelBase& model, const TermStructureBase& ts)
{
	Eigen::MatrixXd stock_prices(number_of_paths_, number_of_steps_ + 1);

	std::vector<std::thread> threads;
	
	int workload = number_of_paths_ / num_threads_;

	auto start_time = std::chrono::high_resolution_clock::now();

	for (int i = 0; i < num_threads_; ++i)
	{
		int start = i * workload;
		int end = (i == num_threads_ - 1) ? number_of_paths_ : start + workload;

		threads.emplace_back([&model, start, end, &stock_prices]()
			{
				model.simulate_paths(start, end, stock_prices);
			});
	}


	for (auto& th : threads)
	{
		th.join();
	}

	//std::cout << stock_prices << '\n';

	Eigen::VectorXd payoffs = option.ComputePayoffs(stock_prices);

	//std::cout << payoffs << '\n';

	gatherer_->accumulate(payoffs, model);

	//std::map<std::string, double> GreekMap = option.ComputeGreeks(stock_prices, model);
	//std::cout << "MC delta: " << discount * GreekMap["Delta"] << std::endl;
	//std::cout << "MC vega: " << discount * GreekMap["Vega"] << std::endl;
	//std::cout << "MC gamma: " << discount * GreekMap["Gamma"] << std::endl;

	auto end_time = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::seconds>(end_time - start_time);

	std::cout << "Simulation took: " << duration.count() << " s\n";
}


void MCSimulation::OutputResults(const TermStructureBase& ts, const ModelBase& model) const
{
	std::pair<double, double> results = gatherer_->GetResults(ts, model);

	std::cout << "MC price: " << results.first << '\n';
	std::cout << "standard error: " << results.second << '\n';
}


