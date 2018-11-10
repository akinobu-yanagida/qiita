//
// Copyright (c) 2018 Sho Hirose
//
// Distributed under the MIT License. (See accompanying file LICENSE.txt or copy
// at https://opensource.org/licenses/MIT)
//
#ifndef DENSE_SOLVER_HPP
#define DENSE_SOLVER_HPP

#include <memory>
#include <string>
#include "dense_solver_interface.hpp"

/// A templated class for Eigen dense solvers. Users should not use this class.
/// Instead, use make_dense_solver() function to create a dense solver.
///
/// Example:
/// @code{.cpp}
/// Eigen::MatrixXd A = /* ... */
/// Eigen::VectorXd b = /* ... */
/// auto solver = make_dense_solver("SparseQR");
/// solver->decompose(A);
/// const auto x = solver->solve(b);
/// @endcode
template <class SolverType>
class dense_solver : public dense_solver_interface {
 public:
  dense_solver()           = default;
  ~dense_solver() override = default;
  void decompose(const Eigen::Ref<const Eigen::MatrixXd>& A) override {
    solver_.compute(A);
  }
  Eigen::VectorXd solve(const Eigen::Ref<const Eigen::VectorXd>& b) override {
    return solver_.solve(b);
  }

 private:
  SolverType solver_;
};

/// Make a dense solver from a given type as a string.
///
/// Available types are:
///  - PartialPivLU
///  - FullPivLU
///  - HouseholderQR
///  - ColPivHouseholderQR
///  - FullPivHouseholderQR
///  - CompleteOrthogonalDecomposition
///  - BDCSVD
///  - JacobiSVD
///  - LLT
///  - LDLT
///
/// If an unknown solver type is passed , an exception of type
/// std::invalid_argument is thrown.
std::unique_ptr<dense_solver_interface> make_dense_solver(
    const std::string& type);

#endif
