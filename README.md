# Monte Carlo Pricing Engine

A multithreaded object-oriented C++ application for pricing derivatives under standard market models.

---

## Models

| Model | Dynamics | Discretization |
|---|---|---|
| Geometric Brownian Motion | Constant volatility | Exact |
| Displaced Diffusion | Skewed lognormal | Exact |
| Merton Jump Diffusion | GBM + compound Poisson jumps | Exact GBM + Poisson sampling |
| SABR | Stochastic alpha beta rho | Predictor-corrector |
| Heston | Stochastic volatility | Almost exact (non-central chi-squared) |
| Heston Hull-White | Stochastic volatility + stochastic rates | Quadratic exponential (QE) |
| Variance Gamma | Brownian motion time-changed by Gamma process | Gamma subordination |

---

## Options

| Option | Style |
|---|---|
| European Call | European |
| American Put | American (Longstaff-Schwartz LSM) |
| American Call | American (Longstaff-Schwartz LSM) |
| Asian Call | Path-dependent |
| Up-and-In Call | Barrier |
| Double Barrier Knock-In Call | Barrier |
| Floating Lookback Call | Path-dependent |
| Fixed Lookback Call | Path-dependent |

---

## Libraries

| Library | Usage |
|---|---|
| Eigen | Matrix storage and operations for path simulation |
| Boost | Random number generation, statistical distributions |
| STL threads | Multithreading across path simulation |

---

## Requirements

- C++17 or later
- Eigen 3.x
- Boost 1.70+

---

## Notes
- This project is no longer being edited. An improved version may be in the works in another repo.
