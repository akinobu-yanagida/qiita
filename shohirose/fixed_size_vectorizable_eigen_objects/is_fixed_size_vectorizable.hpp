//
// Copyright (c) 2018 Sho Hirose
//
// Distributed under the MIT License. (See accompanying file LICENSE.txt or copy
// at https://opensource.org/licenses/MIT)
//
#ifndef IS_FIXED_SIZE_VECTORIZABLE_HPP
#define IS_FIXED_SIZE_VECTORIZABLE_HPP

#include <Eigen/Core>
#include <Eigen/Geometry>
#include <type_traits>

namespace foo {

/// Checks wether if T is an Eigen object of fixed-size vectorizable type.
/// Please refer to <a
/// href=http://eigen.tuxfamily.org/dox/group__TopicFixedSizeVectorizable.html>
/// Fixed-size vectorizable Eigen objects </a>
template <typename T>
struct is_fixed_size_vectorizable : std::false_type {};

template <>
struct is_fixed_size_vectorizable<Eigen::Vector2d> : std::true_type {};

template <>
struct is_fixed_size_vectorizable<Eigen::Vector4d> : std::true_type {};

template <>
struct is_fixed_size_vectorizable<Eigen::Matrix2d> : std::true_type {};

template <>
struct is_fixed_size_vectorizable<Eigen::Matrix2f> : std::true_type {};

template <>
struct is_fixed_size_vectorizable<Eigen::Matrix4d> : std::true_type {};

template <>
struct is_fixed_size_vectorizable<Eigen::Matrix4f> : std::true_type {};

template <>
struct is_fixed_size_vectorizable<Eigen::Affine3d> : std::true_type {};

template <>
struct is_fixed_size_vectorizable<Eigen::Affine3f> : std::true_type {};

template <>
struct is_fixed_size_vectorizable<Eigen::Quaterniond> : std::true_type {};

template <>
struct is_fixed_size_vectorizable<Eigen::Quaternionf> : std::true_type {};

}  // end namespace foo

#endif
