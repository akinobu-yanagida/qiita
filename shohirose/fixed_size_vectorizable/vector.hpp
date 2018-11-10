//
// Copyright (c) 2018 Sho Hirose
//
// Distributed under the MIT License. (See accompanying file LICENSE.txt or copy
// at https://opensource.org/licenses/MIT)
//
#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <vector>
#include "allocator.hpp"

namespace foo {

/// A heap allocated array which is a wrapper of STL vector.
///  - select a proper allocator of T if T is a fixed-size vectorizable Eigen
///  object.
template <typename T, typename Allocator = allocator<T>>
using vector = std::vector<T, Allocator>;

}  // end namespace foo

#endif
