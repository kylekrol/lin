/** @file lin/core/queries/types.hpp
 *  @author Kyle Krol
 *  Defines types directly related to the queries module (essentially boolean
 *  matrices and vectors). */

#ifndef LIN_QUERIES_TYPES_HPP_
#define LIN_QUERIES_TYPES_HPP_

#include "../core.hpp"

namespace lin {

template <size_t R, size_t C, size_t MR = R, size_t MC = C>
using Matrixb = Matrix<bool, R, C, MR, MC>;

typedef Matrixb<2, 2> Matrix2x2b;
typedef Matrixb<3, 2> Matrix3x2b;
typedef Matrixb<4, 2> Matrix4x2b;
typedef Matrixb<2, 3> Matrix2x3b;
typedef Matrixb<3, 3> Matrix3x3b;
typedef Matrixb<4, 3> Matrix4x3b;
typedef Matrixb<2, 4> Matrix2x4b;
typedef Matrixb<3, 4> Matrix3x4b;
typedef Matrixb<4, 4> Matrix4x4b;

template <size_t N, size_t MN = N>
using RowVectorb = RowVector<bool, N, MN>;

typedef RowVectorb<2> RowVector2b;
typedef RowVectorb<3> RowVector3b;
typedef RowVectorb<4> RowVector4b;

template <size_t N, size_t MN = N>
using Vectorb = Vector<bool, N, MN>;

typedef Vectorb<2> Vector2b;
typedef Vectorb<3> Vector3b;
typedef Vectorb<4> Vector4b;

};

#endif
