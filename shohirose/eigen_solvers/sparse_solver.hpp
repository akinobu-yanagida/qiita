//
// Copyright (c) 2018 Sho Hirose
//
// Distributed under the MIT License. (See accompanying file LICENSE.txt or copy
// at https://opensource.org/licenses/MIT)
//
#ifndef SPARSE_SOLVER_HPP
#define SPARSE_SOLVER_HPP

#include <memory>
#include <string>
#include "sparse_solver_interface.hpp"

/// A templated class for Eigen sparse solvers. Users should not use this class.
/// Instead, use make_sparse_solver() function to create a sparse solver.
///
/// Example:
/// @code{.cpp}
/// Eigen::SparseMatrix<double> A = /* ... */
/// Eigen::VectorXd b = /* ... */
/// auto solver = make_sparse_solver("BiCGSTAB", "IncompleteLUT");
/// solver->decompose(A);
/// // Note: calling decompose() function is equivalent with calling
/// // analyze_pattern() first and then calling factorize():
/// // solver->analyze_pattern(A);
/// // solver->factorize(A);
/// const auto x = solver->solve(b);
/// @endcode
template <class SolverType>
class sparse_solver : public sparse_solver_interface {
 public:
  using SparseMatrix = Eigen::SparseMatrix<double>;

  sparse_solver()           = default;
  ~sparse_solver() override = default;
  void decompose(const Eigen::Ref<const SparseMatrix>& A) override {
    solver_.compute(A);
  }
  Eigen::VectorXd solve(const Eigen::Ref<const Eigen::VectorXd>& b) override {
    return solver_.solve(b);
  }
  void analyze_pattern(const Eigen::Ref<const SparseMatrix>& A) override {
    solver_.analyzePattern(A);
  }
  void factorize(const Eigen::Ref<const SparseMatrix>& A) override {
    solver_.factorize(A);
  }
  bool fail() const override { return solver_.info() != Eigen::Success; }

 private:
  SolverType solver_;
};

/// Make a sparse solver from a given type as a string.
///
/// Available types are:
///  - BiCGSTAB
///  - SparseLU
///  - SparseQR
///
/// When the sparse solver type is "BiCGSTAB", preconditioner type must be
/// explicitly specified as well. Available preconditioners are:
///  - SimplicialCholesky
///  - IncompleteLUT
///  - Diagonal
///  - Identity
///
/// If an unknown solver or preconditioner type is passed, an exception of type
/// std::invalid_argument is thrown.
std::unique_ptr<sparse_solver_interface> make_sparse_solver(
    const std::string& type, const std::string& preconditioner = "");

#endif
