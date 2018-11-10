//
// Copyright (c) 2018 Sho Hirose
//
// Distributed under the MIT License. (See accompanying file LICENSE.txt or copy
// at https://opensource.org/licenses/MIT)
//
#ifndef SPARSE_SOLVER_INTERFACE_HPP
#define SPARSE_SOLVER_INTERFACE_HPP

#include <Eigen/SparseCore>
#include "solver_interface.hpp"

struct sparse_solver_interface : solver_interface<Eigen::SparseMatrix<double>> {
  using SparseMatrix = Eigen::SparseMatrix<double>;

  virtual ~sparse_solver_interface() override = default;
  virtual void analyze_pattern(const Eigen::Ref<const SparseMatrix>& A) = 0;
  virtual void factorize(const Eigen::Ref<const SparseMatrix>& A)       = 0;
  virtual bool fail() const                                             = 0;
};

#endif
