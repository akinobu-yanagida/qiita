#include "dense_solver.hpp"
#include <Eigen/Dense>
#include <iostream>
#include <stdexcept>

std::unique_ptr<dense_solver_interface> make_dense_solver(
    const std::string& type) {
  using std::make_unique;
  using namespace Eigen;

  if (type == "PartialPivLU")
    return make_unique<dense_solver<PartialPivLU<MatrixXd>>>();
  else if (type == "FullPivLU")
    return make_unique<dense_solver<FullPivLU<MatrixXd>>>();
  else if (type == "HouseholderQR")
    return make_unique<dense_solver<HouseholderQR<MatrixXd>>>();
  else if (type == "ColPivHouseholderQR")
    return make_unique<dense_solver<ColPivHouseholderQR<MatrixXd>>>();
  else if (type == "FullPivHouseholderQR")
    return make_unique<dense_solver<FullPivHouseholderQR<MatrixXd>>>();
  else if (type == "CompleteOrthogonalDecomposition")
    return make_unique<
        dense_solver<CompleteOrthogonalDecomposition<MatrixXd>>>();
  else if (type == "BDCSVD")
    return make_unique<dense_solver<BDCSVD<MatrixXd>>>();
  else if (type == "JacobiSVD")
    return make_unique<dense_solver<JacobiSVD<MatrixXd>>>();
  else if (type == "LLT")
    return make_unique<dense_solver<LLT<MatrixXd>>>();
  else if (type == "LDLT")
    return make_unique<dense_solver<LDLT<MatrixXd>>>();
  else {
    std::stringstream ss;
    ss << "Error: " << __FILE__ << ": " << __LINE__
       << "\n  Invalid dense solver type found: " << type
       << "\n  Available types are:\n"
       << "    PartialPivLU,\n"
       << "    FullPivLU,\n"
       << "    HouseholderQR,\n"
       << "    ColPivHouseholderQR,\n"
       << "    FullPivHouseholderQR,\n"
       << "    CompleteOrthogonalDecomposition,\n"
       << "    BDCSVD,\n"
       << "    JacobiSVD,\n"
       << "    LLT,\n"
       << "    LDLT" << std::endl;
    throw std::invalid_argument(ss.str());
  }
}
