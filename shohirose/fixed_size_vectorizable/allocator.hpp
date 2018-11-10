//
// Copyright (c) 2018 Sho Hirose
//
// Distributed under the MIT License. (See accompanying file LICENSE.txt or copy
// at https://opensource.org/licenses/MIT)
//
#ifndef ALLOCATOR_HPP
#define ALLOCATOR_HPP

#include <Eigen/StdVector>
#include <memory>
#include "is_fixed_size_vectorizable.hpp"

namespace foo {

/// Determines allocator for STL vector. If T is a fixed-size vectorizable Eigen
/// object, the aligned allocator provided by Eigen must be used. Please refer
/// to <a href=http://eigen.tuxfamily.org/dox/group__TopicStlContainers.html>
/// Using STL Containers with Eigen </a>
template <typename T>
using allocator =
    std::conditional_t<is_fixed_size_vectorizable<T>::value,
                       Eigen::aligned_allocator<T>, std::allocator<T>>;

}  // end namespace foo

#endif
