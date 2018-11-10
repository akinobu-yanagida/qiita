#include "sparse_solver.hpp"
#include <Eigen/Sparse>
#include <iostream>
#include <stdexcept>

std::unique_ptr<sparse_solver_interface> make_sparse_solver(
    const std::string& type, const std::string& preconditioner) {
  using std::make_unique;
  using namespace Eigen;

  if (type == "BiCGSTAB") {
    if (preconditioner == "IncompleteLUT")
      return make_unique<sparse_solver<
          BiCGSTAB<SparseMatrix<double>, IncompleteLUT<double>>>>();
    else if (preconditioner == "Diagonal")
      return make_unique<sparse_solver<
          BiCGSTAB<SparseMatrix<double>, DiagonalPreconditioner<double>>>>();
    else if (preconditioner == "Identity")
      return make_unique<sparse_solver<
          BiCGSTAB<SparseMatrix<double>, IdentityPreconditioner>>>();
    else if (preconditioner == "SimplicialCholesky")
      return make_unique<sparse_solver<BiCGSTAB<
          SparseMatrix<double>, SimplicialCholesky<SparseMatrix<double>>>>>();
    else {
      std::stringstream ss;
      ss << "Error: " << __FILE__ << ": " << __LINE__;
      if (preconditioner.empty())
        ss << "\n  Empty preconditioner found\n";
      else
        ss << "\n  Invalid preconditioner found: " << preconditioner << "\n";
      ss << "  Valid preconditioners are:\n"
         << "    SimplicialCholesky,\n"
         << "    IncompleteLUT,\n"
         << "    Diagonal,\n"
         << "    Identity" << std::endl;
      throw std::invalid_argument(ss.str());
    }
  } else if (type == "SparseQR") {
    return make_unique<
        sparse_solver<SparseQR<SparseMatrix<double>, COLAMDOrdering<int>>>>();
  } else if (type == "SparseLU")
    return make_unique<sparse_solver<SparseLU<SparseMatrix<double>>>>();
  else {
    std::stringstream ss;
    ss << "Error: " << __FILE__ << ": " << __LINE__
       << "\n  Invalid sparse solver type found: " << type
       << "\n  Valid sparse solver types are:\n"
       << "    BiCGSTAB,\n"
       << "    SparseQR,\n"
       << "    SparseLU" << std::endl;
    throw std::invalid_argument(ss.str());
  }
}
