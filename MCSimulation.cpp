#include "MCSimulation.h"

#include <map>

#include "PseudoFactory.h"

MCSimulation::MCSimulation()
{
}

MCSimulation::MCSimulation(PseudoFactory& factory) : gatherer_(std::make_unique<MCGatherer>()),
                                                     number_of_paths_(factory.GetM()),
                                                     number_of_steps_(factory.GetN()),
                                                     num_threads_(factory.GetNumThreads())
{
}

void MCSimulation::run(const OptionBase& option, const ModelBase& model, const TermStructureBase& ts)
{
	std::cout << "MCSimulation::run()" << std::endl;

	Eigen::MatrixXd stock_prices(number_of_paths_, number_of_steps_ + 1);

	// Vector to store threads
	std::vector<std::thread> threads;

	// Workload per thread
	int workload = number_of_paths_ / num_threads_;

	auto start_time = std::chrono::high_resolution_clock::now();


	// Launch threads (with a small adjustment if workload doesn't divide evenly)
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

	//std::cout << stock_prices << std::endl;

	Eigen::VectorXd payoffs = option.ComputePayoffs(stock_prices);

	const std::pair<double, double> accumulatedResults = gatherer_->accumulate(payoffs, model);

	std::map<std::string, double> GreekMap = option.ComputeGreeks(stock_prices);

	double discount = ts.Get_MT(model);

	std::cout << "Discount: " << discount << std::endl;

	std::cout << "MC price: " << discount * accumulatedResults.first << std::endl;
	std::cout << "MC delta: " << discount * GreekMap["Delta"] << std::endl;
	std::cout << "MC vega: " << discount * GreekMap["Vega"] << std::endl;
	std::cout << "MC gamma: " << discount * GreekMap["Gamma"] << std::endl;

	std::cout << "standard error: " << accumulatedResults.second << std::endl;


	auto end_time = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::seconds>(end_time - start_time);

	std::cout << "Simulation took: " << duration.count() << " s\n";
}
