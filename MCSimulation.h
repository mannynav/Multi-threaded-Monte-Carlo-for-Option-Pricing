


#include <Eigen/Dense>
#include <thread>
#include <vector>
#include <mutex>
#include <chrono>

#include "ModelBase.h"
#include "OptionBase.h"
#include "MCGatherer.h"
#include "TermStructureBase.h"
#include "ValuationMethodBase.h"

class PseudoFactory;
class GBMModel;


class MCSimulation : public ValuationMethodBase
{

public:

    explicit MCSimulation();
    MCSimulation(PseudoFactory& factory);
	void run(const OptionBase& option, const ModelBase& model, const TermStructureBase& ts) override;
	void OutputResults(const TermStructureBase& ts, const ModelBase& model) const;

private:

	std::unique_ptr<MCGatherer> gatherer_;
	int number_of_paths_{};
	int number_of_steps_{};
	int num_threads_{};

};