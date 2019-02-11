#pragma once

#include <cmath>

#include <ove/core/util/assert.hpp>
#include <ove/core/util/types.hpp>

namespace math {
using namespace core;

template <typename T, u8 S> struct vec_t;
template <typename T, u8 R, u8 C> struct mat_t;
template <typename T> struct quat_t;

/// Operators

/**
 * Operator +
 */
template <typename T, u8 S>
inline vec_t<T, S> operator+(const vec_t<T, S> &l, const vec_t<T, S> &r);

/**
 * Operator -
 */
template <typename T, u8 S>
inline vec_t<T, S> operator-(const vec_t<T, S> &l, const vec_t<T, S> &r);

template <typename T, u8 S> inline vec_t<T, S> operator-(const vec_t<T, S> &r);

/**
 * Operator *
 */

/// Vector
template <typename T, u8 S>
inline vec_t<T, S> operator*(const vec_t<T, S> &l, T r);

template <typename T, u8 S>
inline vec_t<T, S> operator*(T l, const vec_t<T, S> &r);

template <typename T, u8 S>
inline vec_t<T, S> operator*(const vec_t<T, S> &l, const vec_t<T, S> &r);

/// Quaternion
template <typename T>
inline quat_t<T> operator*(const quat_t<T> &l, const quat_t<T> &r);

/// Quaternion - Vector
template <typename T>
inline vec_t<T, 3u> operator*(const quat_t<T> &l, const vec_t<T, 3u> &r);

/// Matrix
template <typename T, u8 R, u8 C>
inline mat_t<T, R, C> operator*(const mat_t<T, R, C> &l,
                                const mat_t<T, R, C> &r);

template <typename T, u8 R, u8 C>
inline mat_t<T, R, C> operator*(const mat_t<T, R, C> &l, T &r);

/// Matrix - Vector
template <typename T, u8 R, u8 C>
inline vec_t<T, C> operator*(const mat_t<T, R, C> &l, const vec_t<T, C> &r);

/**
 * Operator /
 */
template <typename T, u8 S>
inline vec_t<T, S> operator/(const vec_t<T, S> &l, T r);

template <typename T, u8 S>
inline vec_t<T, S> operator/(T l, const vec_t<T, S> &r);

/**
 * Operator +=
 */
template <typename T, u8 S>
inline vec_t<T, S> &operator+=(vec_t<T, S> &l, const vec_t<T, S> &r);

/**
 * Operator -=
 */
template <typename T, u8 S>
inline vec_t<T, S> &operator-=(vec_t<T, S> &l, const vec_t<T, S> &r);

/**
 * Operator *=
 */

/// Vector
template <typename T, u8 S> inline vec_t<T, S> &operator*=(vec_t<T, S> &l, T r);

/// Quaternion
template <typename T> inline void operator*=(quat_t<T> &l, const quat_t<T> &r);

/// Matrix
template <typename T, u8 R, u8 C>
inline void operator*=(mat_t<T, R, C> &l, const mat_t<T, R, C> &r);

/**
 * Operator /=
 */
template <typename T, u8 S> inline vec_t<T, S> &operator/=(vec_t<T, S> &l, T r);

/**
 * Operator ==
 */
template <typename T, u8 S>
inline bool operator==(const vec_t<T, S> &l, const vec_t<T, S> &r);

/**
 * Operator !=
 */
template <typename T, u8 S>
inline bool operator!=(const vec_t<T, S> &l, const vec_t<T, S> &r);

/// Vector math

/**
 * Absolute values
 */
template <typename T, u8 S> inline vec_t<T, S> abs(const vec_t<T, S> &v);

/**
 * Length pow
 */
template <typename T, u8 S> inline T lengthPow(const vec_t<T, S> &v, T exp);

/**
 * Length squared
 */
template <typename T, u8 S> inline T lengthSq(const vec_t<T, S> &v);

/**
 * Length
 */
template <typename T, u8 S> inline T length(const vec_t<T, S> &v);

/**
 * Normalize
 */
template <typename T, u8 S> inline void normalize(vec_t<T, S> &v);

/**
 * Normalized
 */
template <typename T, u8 S> inline vec_t<T, S> normalized(const vec_t<T, S> &v);

/**
 * Dot
 */
template <typename T, u8 S>
inline T dot(const vec_t<T, S> &v1, const vec_t<T, S> &v2);

/**
 * Project
 */
template <typename T, u8 S>
inline vec_t<T, S> project(const vec_t<T, S> &v1, const vec_t<T, S> &v2);

/**
 * L.E.R.P
 */
template <typename T, typename R> inline T lerp(const T &v1, const T &v2, R t);

/**
 * Cross
 */
template <typename T>
inline vec_t<T, 3u> cross(const vec_t<T, 3u> &v1, const vec_t<T, 3u> &v2);

/**
 * Conjugate
 */
template <typename T> inline void conjugate(quat_t<T> &q);

/**
 * Conjugated
 */
template <typename T> inline quat_t<T> conjugated(const quat_t<T> &q);

/**
 * Euler Angles
 */
template <typename T> inline quat_t<T> eulerAngles(const vec_t<T, 3u> &v);

/**
 * Axis-Angle
 */
template <typename T> inline quat_t<T> axisAngle(const vec_t<T, 3u> &v, T a);

/**
 * Matrix transform
 */
template <typename T> inline mat_t<T, 4u, 4u> translate(const vec_t<T, 3u> &v);

template <typename T> inline mat_t<T, 4u, 4u> rotate(const vec_t<T, 3u> &v);

template <typename T>
inline mat_t<T, 4u, 4u> rotate(T a, const vec_t<T, 3u> &v);

template <typename T> inline mat_t<T, 4u, 4u> rotate(const quat_t<T> &q);

template <typename T> inline mat_t<T, 4u, 4u> scale(const vec_t<T, 3u> &v);

template <typename T> inline mat_t<T, 4u, 4u> scale(T s);

/**
 * Look At
 */
template <typename T>
inline mat_t<T, 4u, 4u> lookAt(const vec_t<T, 3u> &eye,
                               const vec_t<T, 3u> &center,
                               const vec_t<T, 3u> &up);

/**
 * Orthographic
 */
template <typename T>
inline mat_t<T, 4u, 4u> orthographic(T left, T right, T top, T bottom, T near,
                                     T far);

/**
 * Frustum
 */
template <typename T>
inline mat_t<T, 4u, 4u> frustum(T left, T right, T top, T bottom, T near,
                                T far);

/**
 * Perspective
 */
template <typename T>
inline mat_t<T, 4u, 4u> perspective(T aspect, T fov, T near, T far);

/**
 * Determinant
 */
template <typename T, u8 N> inline T determinant(const mat_t<T, N, N> &m);

/**
 * Invert
 */
template <typename T, u8 R, u8 C> inline void invert(mat_t<T, R, C> &m);

/**
 * Inverse
 */
template <typename T, u8 R, u8 C>
inline mat_t<T, R, C> inverse(const mat_t<T, R, C> &m);

/**
 * Transpose
 */
template <typename T, u8 R, u8 C> inline void transpose(mat_t<T, R, C> &m);

/**
 * Transposed
 */
template <typename T, u8 R, u8 C>
inline mat_t<T, R, C> transposed(const mat_t<T, R, C> &m);
}
