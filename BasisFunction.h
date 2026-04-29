#pragma once

#ifndef BASISFUNCTION_H
#define BASISFUNCTION_H

#include <vector>
#include <memory>
#include <string>

namespace Finance {

    class BasisFunction {
    public:
        virtual ~BasisFunction() = default;
        virtual std::vector<double> evaluate(double x, int num_functions) const = 0;
        virtual std::string getName() const = 0;
        virtual std::unique_ptr<BasisFunction> clone() const = 0;
    };

    class LaguerreBasis : public BasisFunction {
    public:
        std::vector<double> evaluate(double x, int num_functions) const override;
        std::string getName() const override { return "Laguerre"; }
        std::unique_ptr<BasisFunction> clone() const override { return std::make_unique<LaguerreBasis>(); }
    };

    class HermiteBasis : public BasisFunction {
    public:
        std::vector<double> evaluate(double x, int num_functions) const override;
        std::string getName() const override { return "Hermite"; }
        std::unique_ptr<BasisFunction> clone() const override { return std::make_unique<HermiteBasis>(); }
    };

    class PolynomialBasis : public BasisFunction {
    public:
        std::vector<double> evaluate(double x, int num_functions) const override;
        std::string getName() const override { return "Polynomial"; }
        std::unique_ptr<BasisFunction> clone() const override { return std::make_unique<PolynomialBasis>(); }
    };

    class ChebyshevBasis : public BasisFunction {
    public:
        ChebyshevBasis(double x_min, double x_max) : x_min_(x_min), x_max_(x_max) {}
        std::vector<double> evaluate(double x, int num_functions) const override;
        std::string getName() const override { return "Chebyshev"; }
        std::unique_ptr<BasisFunction> clone() const override { return std::make_unique<ChebyshevBasis>(x_min_, x_max_); }
    private:
        double x_min_, x_max_;
    };

    class LegendreBasis : public BasisFunction {
    public:
        LegendreBasis(double x_min, double x_max) : x_min_(x_min), x_max_(x_max) {}
        std::vector<double> evaluate(double x, int num_functions) const override;
        std::string getName() const override { return "Legendre"; }
        std::unique_ptr<BasisFunction> clone() const override { return std::make_unique<LegendreBasis>(x_min_, x_max_); }
    private:
        double x_min_, x_max_;
    };

    class BasisFactory {
    public:
        static std::unique_ptr<BasisFunction> create(const std::string& type, double x_min = 0.0, double x_max = 2.0);
    };

}

#endif // BASISFUNCTION_H