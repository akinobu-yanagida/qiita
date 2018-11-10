//
// Copyright (c) 2018 Sho Hirose
//
// Distributed under the MIT License. (See accompanying file LICENSE.txt or copy
// at https://opensource.org/licenses/MIT)
//
#ifndef SOLVER_INTERFACE_HPP
#define SOLVER_INTERFACE_HPP

#include <Eigen/Core>

/// Interface class to solve a system of linear equation, Ax = b, using Eigen
/// solvers.
template <class MatrixType>
class solver_interface {
 public:
  virtual ~solver_interface()                                   = default;
  virtual void decompose(const Eigen::Ref<const MatrixType>& A) = 0;
  virtual Eigen::VectorXd solve(const Eigen::Ref<const Eigen::VectorXd>& b) = 0;
};

#endif
