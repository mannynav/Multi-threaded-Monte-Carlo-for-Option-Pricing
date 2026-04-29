#include "BasisFunction.h"
#include <vector>
#include <stdexcept>

namespace Finance {

    std::vector<double> LaguerreBasis::evaluate(double x, int num_functions) const {
        std::vector<double> result(num_functions);
        result[0] = 1.0;
        if (num_functions > 1) result[1] = 1.0 - x;
        for (int i = 2; i < num_functions; ++i) {
            result[i] = ((2.0 * i - 1.0 - x) * result[i - 1] - (i - 1.0) * result[i - 2]) / i;
        }
        return result;
    }

    std::vector<double> HermiteBasis::evaluate(double x, int num_functions) const {
        std::vector<double> result(num_functions);
        result[0] = 1.0;
        if (num_functions > 1) result[1] = 2.0 * x;
        for (int i = 2; i < num_functions; ++i) {
            result[i] = 2.0 * x * result[i - 1] - 2.0 * (i - 1) * result[i - 2];
        }
        return result;
    }

    std::vector<double> PolynomialBasis::evaluate(double x, int num_functions) const {
        std::vector<double> result(num_functions);
        result[0] = 1.0;
        for (int i = 1; i < num_functions; ++i) {
            result[i] = result[i - 1] * x;
        }
        return result;
    }

    std::vector<double> ChebyshevBasis::evaluate(double x, int num_functions) const {
        std::vector<double> result(num_functions);
        double scaled_x = 2.0 * (x - x_min_) / (x_max_ - x_min_) - 1.0;
        result[0] = 1.0;
        if (num_functions > 1) result[1] = scaled_x;
        for (int i = 2; i < num_functions; ++i) {
            result[i] = 2.0 * scaled_x * result[i - 1] - result[i - 2];
        }
        return result;
    }

    std::vector<double> LegendreBasis::evaluate(double x, int num_functions) const {
        std::vector<double> result(num_functions);
        double scaled_x = 2.0 * (x - x_min_) / (x_max_ - x_min_) - 1.0;
        result[0] = 1.0;
        if (num_functions > 1) result[1] = scaled_x;
        for (int i = 2; i < num_functions; ++i) {
            result[i] = ((2.0 * i - 1.0) * scaled_x * result[i - 1] - (i - 1.0) * result[i - 2]) / i;
        }
        return result;
    }

    std::unique_ptr<BasisFunction> BasisFactory::create(const std::string& type, double x_min, double x_max) {
        if (type == "Laguerre") return std::make_unique<LaguerreBasis>();
        if (type == "Hermite") return std::make_unique<HermiteBasis>();
        if (type == "Polynomial") return std::make_unique<PolynomialBasis>();
        if (type == "Chebyshev") return std::make_unique<ChebyshevBasis>(x_min, x_max);
        if (type == "Legendre") return std::make_unique<LegendreBasis>(x_min, x_max);
        throw std::invalid_argument("Unknown basis type: " + type);
    }

} // namespace Finance