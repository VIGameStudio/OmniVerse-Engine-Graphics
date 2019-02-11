#pragma once

#include "../vmath.hpp"

#include <ove/math/utils.hpp>

namespace math {
/// Operators

/**
 * Operator +
 */
template <typename T, u8 S>
inline vec_t<T, S> operator+(const vec_t<T, S> &l, const vec_t<T, S> &r) {
  vec_t<T, S> res;
  for (u8 i = 0; i < S; ++i)
    res.data[i] = l.data[i] + r.data[i];
  return res;
}

/**
 * Operator -
 */
template <typename T, u8 S>
inline vec_t<T, S> operator-(const vec_t<T, S> &l, const vec_t<T, S> &r) {
  vec_t<T, S> res;
  for (u8 i = 0; i < S; ++i)
    res.data[i] = l.data[i] - r.data[i];
  return res;
}

template <typename T, u8 S> inline vec_t<T, S> operator-(const vec_t<T, S> &r) {
  return vec_t<T, S>(-r.x, -r.y, -r.z);
}

/**
 * Operator *
 */

/// Vector
template <typename T, u8 S>
inline vec_t<T, S> operator*(const vec_t<T, S> &l, T r) {
  vec_t<T, S> res;
  for (u8 i = 0; i < S; ++i)
    res.data[i] = l.data[i] * r;
  return res;
}

template <typename T, u8 S>
inline vec_t<T, S> operator*(T l, const vec_t<T, S> &r) {
  vec_t<T, S> res;
  for (u8 i = 0; i < S; ++i)
    res.data[i] = l * r.data[i];
  return res;
}

template <typename T, u8 S>
inline vec_t<T, S> operator*(const vec_t<T, S> &l, const vec_t<T, S> &r) {
  vec_t<T, S> res;
  for (u8 i = 0; i < S; ++i)
    res.data[i] = l.data[i] * r.data[i];
  return res;
}

/// Quaternion
template <typename T>
inline quat_t<T> operator*(const quat_t<T> &l, const quat_t<T> &r) {
  return quat_t<T>(l.w * r.x + l.x * r.w + l.y * r.z - l.z * r.y,
                   l.w * r.y + l.y * r.w + l.z * r.x - l.x * r.z,
                   l.w * r.z + l.z * r.w + l.x * r.y - l.y * r.x,
                   l.w * r.w - l.x * r.x - l.y * r.y - l.z * r.z);
}

/// Matrix
template <typename T, u8 N>
inline mat_t<T, N, N> operator*(const mat_t<T, N, N> &l,
                                const mat_t<T, N, N> &r) {
  mat_t<T, N, N> res(0.f);
  for (u8 i = 0; i < N; ++i)
    for (u8 j = 0; j < N; ++j)
      for (u8 k = 0; k < N; ++k)
        res.m[i][j] += l.m[i][k] * r.m[k][j];
  return res;
}

template <typename T, u8 N>
inline mat_t<T, N, N> operator*(mat_t<T, N, N> &l, T r) {
  mat_t<T, N, N> res(0.f);
  for (u8 i = 0; i < N; ++i)
    for (u8 j = 0; j < N; ++j)
      res.m[i][j] = l.m[i][j] * r;
  return res;
}

/// Matrix - Vector
template <typename T, u8 N>
inline vec_t<T, N> operator*(const mat_t<T, N, N> &l, const vec_t<T, N> &r) {
  vec_t<T, N> res(0.f);
  for (u8 i = 0; i < N; ++i)
    for (u8 j = 0; j < N; ++j)
      res.data[i] += l.m[i][j] * res.data[j];
  return res;
}

/// Quaternion - Vector
template <typename T>
inline vec_t<T, 3u> operator*(const quat_t<T> &l, const vec_t<T, 3u> &r) {
  const vec_t<T, 3u> q(l.x, l.y, l.z);
  const vec_t<T, 3u> t = (T)2 * cross(r, q);
  return r + l.w * t + cross(t, q);
}

/**
 * Operator /
 */
template <typename T, u8 S>
inline vec_t<T, S> operator/(const vec_t<T, S> &l, T r) {
  ASSERT(r != 0);

  const T ir = 1.0 / r;
  vec_t<T, S> res;
  for (u8 i = 0; i < S; ++i)
    res.data[i] = l.data[i] * ir;
  return res;
}

template <typename T, u8 S>
inline vec_t<T, S> operator/(T l, const vec_t<T, S> &r) {
  ASSERT(l != 0);

  vec_t<T, S> res;
  for (u8 i = 0; i < S; ++i)
    res.data[i] = l / r.data[i];
  return res;
}

/**
 * Operator +=
 */
template <typename T, u8 S>
inline vec_t<T, S> &operator+=(vec_t<T, S> &l, const vec_t<T, S> &r) {
  for (u8 i = 0; i < S; ++i)
    l.data[i] += r.data[i];
  return l;
}

/**
 * Operator -=
 */
template <typename T, u8 S>
inline vec_t<T, S> &operator-=(vec_t<T, S> &l, const vec_t<T, S> &r) {
  for (u8 i = 0; i < S; ++i)
    l.data[i] -= r.data[i];
  return l;
}

/**
 * Operator *=
 */

/// Vector
template <typename T, u8 S>
inline vec_t<T, S> &operator*=(vec_t<T, S> &l, T r) {
  for (u8 i = 0; i < S; ++i)
    l.data[i] *= r;
  return l;
}

/// Quaternion
template <typename T> inline void operator*=(quat_t<T> &l, const quat_t<T> &r) {
  l.x = l.w * r.x + l.x * r.w + l.y * r.z - l.z * r.y;
  l.y = l.w * r.y + l.y * r.w + l.z * r.x - l.x * r.z;
  l.z = l.w * r.z + l.z * r.w + l.x * r.y - l.y * r.x;
  l.w = l.w * r.w - l.x * r.x - l.y * r.y - l.z * r.z;
}

/// Matrix
template <typename T, u8 N> inline void operator*=(mat_t<T, N, N> &l, T r) {
  for (u8 i = 0; i < N; ++i)
    for (u8 j = 0; j < N; ++j)
      l.m[i][j] *= r;
}

/**
 * Operator /=
 */
template <typename T, u8 S>
inline vec_t<T, S> &operator/=(vec_t<T, S> &l, T r) {
  ASSERT(r != 0);

  const T ir = 1.0 / r;
  for (u8 i = 0; i < S; ++i)
    l.data[i] *= ir;
  return l;
}

/**
 * Operator ==
 */
template <typename T, u8 S>
inline bool operator==(const vec_t<T, S> &l, const vec_t<T, S> &r) {
  for (u8 i = 0; i < S; ++i)
    if (l.data[i] != r.data[i])
      return false;
  return true;
}

/**
 * Operator !=
 */
template <typename T, u8 S>
inline bool operator!=(const vec_t<T, S> &l, const vec_t<T, S> &r) {
  for (u8 i = 0; i < S; ++i)
    if (l.data[i] == r.data[i])
      return false;
  return true;
}

/// Vector math

/**
 * Absolute values
 */
template <typename T, u8 S> inline vec_t<T, S> abs(const vec_t<T, S> &v) {
  auto tmp = v;
  for (u8 i = 0; i < S; ++i)
    tmp.data[i] = std::abs(v.data[i]);
  return tmp;
}

/**
 * Length pow
 */
template <typename T, u8 S> inline T lengthPow(const vec_t<T, S> &v, T exp) {
  T lenSq = 0;
  for (u8 i = 0; i < S; ++i)
    lenSq += std::pow(v.data[i], exp);
  return lenSq;
}

/**
 * Length squared
 */
template <typename T, u8 S> inline T lengthSq(const vec_t<T, S> &v) {
  T lenSq = 0;
  for (u8 i = 0; i < S; ++i)
    lenSq += v.data[i] * v.data[i];
  return lenSq;
}

/**
 * Length
 */
template <typename T, u8 S> inline T length(const vec_t<T, S> &v) {
  return std::sqrt(lengthSq(v));
}

/**
 * Normalize
 */
template <typename T, u8 S> inline void normalize(vec_t<T, S> &v) {
  const auto len = length(v);
  ASSERT(len != 0 && "Division by zero!");
  v /= len;
}

/**
 * Normalized
 */
template <typename T, u8 S>
inline vec_t<T, S> normalized(const vec_t<T, S> &v) {
  auto tmp = v;
  normalize(tmp);
  return tmp;
}

/**
 * Dot
 */
template <typename T, u8 S>
inline T dot(const vec_t<T, S> &v1, const vec_t<T, S> &v2) {
  T tmp = 0;
  for (u8 i = 0; i < S; ++i)
    tmp += v1.data[i] * v2.data[i];
  return tmp;
}

/**
 * Project
 */
template <typename T, u8 S>
inline vec_t<T, S> project(const vec_t<T, S> &v1, const vec_t<T, S> &v2) {
  const auto pv = normalized(v2);
  return pv * dot(v1, pv);
}

/**
 * L.E.R.P
 */
template <typename T, typename R> inline T lerp(const T &v1, const T &v2, R t) {
  return v1 + (v2 - v1) * t;
}

/**
 * Cross
 */
template <typename T>
inline vec_t<T, 3u> cross(const vec_t<T, 3u> &v1, const vec_t<T, 3u> &v2) {
  auto tmp = vec_t<T, 3u>(v1.y * v2.z - v1.z * v2.y, v1.z * v2.x - v1.x * v2.z,
                          v1.x * v2.y - v1.y * v2.x);
  return tmp;
}

/**
 * Conjugate
 */
template <typename T> inline void conjugate(quat_t<T> &q) {
  q.x = -q.x;
  q.y = -q.y;
  q.z = -q.z;
}

/**
 * Conjugated
 */
template <typename T> inline quat_t<T> conjugated(const quat_t<T> &q) {
  auto tmp = q;
  conjugate(tmp);
  return tmp;
}

/**
 * Euler Angles
 */
template <typename T> inline quat_t<T> eulerAngles(const vec_t<T, 3u> &v) {
  const T hax = deg2rad(v.x * (T)0.5);
  const T hay = deg2rad(v.y * (T)0.5);
  const T haz = deg2rad(v.z * (T)0.5);

  const T c1 = std::cos(hax);
  const T s1 = std::sin(hax);
  const T c2 = std::cos(hay);
  const T s2 = std::sin(hay);
  const T c3 = std::cos(haz);
  const T s3 = std::sin(haz);

  const T c1c2 = c1 * c2;
  const T s1s2 = s1 * s2;

  quat_t<T> res;
  res.w = c1c2 * c3 - s1s2 * s3;
  res.z = c1c2 * s3 + s1s2 * c3;
  res.x = s1 * c2 * c3 + c1 * s2 * s3;
  res.y = c1 * s2 * c3 - s1 * c2 * s3;
  return res;
}

/**
 * Axis-Angle
 */
template <typename T> inline quat_t<T> axisAngle(const vec_t<T, 3u> &v, T a) {
  const T hrad = deg2rad(a) * (T)0.5;
  const T sa = std::sin(hrad * (T)2.0);

  quat_t<T> res;
  res.x = v.x * sa;
  res.y = v.y * sa;
  res.z = v.z * sa;
  res.w = std::cos(hrad);
  return res;
}

/**
 * Matrix transform
 */
template <typename T> inline mat_t<T, 4u, 4u> translate(const vec_t<T, 3u> &v) {
  mat_t<T, 4u, 4u> res;
  res.m[3][0] = v.x;
  res.m[3][1] = v.y;
  res.m[3][2] = v.z;
  return res;
}

template <typename T> inline mat_t<T, 4u, 4u> rotate(const vec_t<T, 3u> &v) {
  const T ax = deg2rad(v.x);
  const T ay = deg2rad(v.y);
  const T az = deg2rad(v.z);

  const T ch = std::cos(ax);
  const T sh = std::sin(ax);
  const T ca = std::cos(ay);
  const T sa = std::sin(ay);
  const T cb = std::cos(az);
  const T sb = std::sin(az);

  mat_t<T, 4u, 4u> res;
  res.m[0][0] = ch * ca;
  res.m[0][1] = sh * sb - ch * sa * cb;
  res.m[0][2] = ch * sa * sb + sh * cb;
  res.m[1][0] = sa;
  res.m[1][1] = ca * cb;
  res.m[1][2] = -ca * sb;
  res.m[2][0] = -sh * ca;
  res.m[2][1] = sh * sa * cb + ch * sb;
  res.m[2][2] = -sh * sa * sb + ch * cb;
  return res;
}

template <typename T>
inline mat_t<T, 4u, 4u> rotate(T a, const vec_t<T, 3u> &v) {
  const T rad = deg2rad(a);
  const T c = std::cos(rad);
  const T s = std::sin(rad);
  const T t = 1.0 - c;

  mat_t<T, 4u, 4u> res;
  res.m[0][0] = c + v.x * v.x * t;
  res.m[1][1] = c + v.y * v.y * t;
  res.m[2][2] = c + v.z * v.z * t;

  T tmp1 = v.x * v.y * t;
  T tmp2 = v.z * s;
  res.m[1][0] = tmp1 + tmp2;
  res.m[0][1] = tmp1 - tmp2;

  tmp1 = v.x * v.z * t;
  tmp2 = v.y * s;
  res.m[2][0] = tmp1 - tmp2;
  res.m[0][2] = tmp1 + tmp2;

  tmp1 = v.y * v.z * t;
  tmp2 = v.x * s;
  res.m[2][1] = tmp1 + tmp2;
  res.m[1][2] = tmp1 - tmp2;

  return res;
}

template <typename T> inline mat_t<T, 4u, 4u> rotate(const quat_t<T> &q) {
  const T sqw = q.w * q.w;
  const T sqx = q.x * q.x;
  const T sqy = q.y * q.y;
  const T sqz = q.z * q.z;

  // invs (inverse square length) is only required if quaternion is not already
  // normalized
  const T t = sqx + sqy + sqz + sqw;
  ASSERT(t != 0 && "Can't normalize quaternion of length 0!");
  const T invs = (T)1.0 / t;

  mat_t<T, 4u, 4u> res(0.0);
  res.m[0][0] = (sqx - sqy - sqz + sqw) * invs;
  res.m[1][1] = (-sqx + sqy - sqz + sqw) * invs;
  res.m[2][2] = (-sqx - sqy + sqz + sqw) * invs;

  T tmp1 = q.x * q.y;
  T tmp2 = q.z * q.w;
  res.m[1][0] = 2.0 * (tmp1 + tmp2) * invs;
  res.m[0][1] = 2.0 * (tmp1 - tmp2) * invs;

  tmp1 = q.x * q.z;
  tmp2 = q.y * q.w;
  res.m[2][0] = 2.0 * (tmp1 - tmp2) * invs;
  res.m[0][2] = 2.0 * (tmp1 + tmp2) * invs;

  tmp1 = q.y * q.z;
  tmp2 = q.x * q.w;
  res.m[2][1] = 2.0 * (tmp1 + tmp2) * invs;
  res.m[1][2] = 2.0 * (tmp1 - tmp2) * invs;

  return res;
}

template <typename T> inline mat_t<T, 4u, 4u> scale(const vec_t<T, 3u> &v) {
  mat_t<T, 4u, 4u> res;
  res.m[0][0] = v.x;
  res.m[1][1] = v.y;
  res.m[2][2] = v.z;
  return res;
}

template <typename T> inline mat_t<T, 4u, 4u> scale(T s) {
  mat_t<T, 4u, 4u> res;
  res.m[0][0] = s;
  res.m[1][1] = s;
  res.m[2][2] = s;
  return res;
}

/**
 * Look At
 */
template <typename T>
inline mat_t<T, 4u, 4u> lookAt(const vec_t<T, 3u> &eye,
                               const vec_t<T, 3u> &center,
                               const vec_t<T, 3u> &up) {
  const vec_t<T, 3u> k(normalized(center - eye));
  const vec_t<T, 3u> i(normalized(cross(k, up)));
  const vec_t<T, 3u> j(cross(i, k));

  mat_t<T, 4u, 4u> res;
  res.m[0][0] = i.x;
  res.m[1][0] = i.y;
  res.m[2][0] = i.z;

  res.m[0][1] = j.x;
  res.m[1][1] = j.y;
  res.m[2][1] = j.z;

  res.m[0][2] = -k.x;
  res.m[1][2] = -k.y;
  res.m[2][2] = -k.z;

  res.m[3][0] = -dot(i, eye);
  res.m[3][1] = -dot(j, eye);
  res.m[3][2] = dot(k, eye);
  return res;
}

/**
 * Orthographic
 */
template <typename T>
inline mat_t<T, 4u, 4u> orthographic(T left, T right, T top, T bottom, T near,
                                     T far) {
  const T sx = right - left;
  const T sy = top - bottom;
  const T sz = far - near;

  mat_t<T, 4u, 4u> res;
  res.m[0][0] = (T)2.0 / sx;
  res.m[1][1] = (T)2.0 / sy;
  res.m[2][2] = (T)-2.0 / sz;

  res.m[3][0] = -(right + left) / sx;
  res.m[3][1] = -(top + bottom) / sy;
  res.m[3][2] = -(far + near) / sz;
  return res;
}

/**
 * Frustum
 */
template <typename T>
inline mat_t<T, 4u, 4u> frustum(T left, T right, T top, T bottom, T near,
                                T far) {
  const auto zero = static_cast<T>(0.0);
  const auto one = static_cast<T>(1.0);
  const auto two = static_cast<T>(2.0);

  const T sx = right - left;
  const T sy = top - bottom;
  const T sz = far - near;

  mat_t<T, 4u, 4u> res(zero);
  res.m[0][0] = two * near / sx;
  res.m[1][1] = two * near / sy;
  res.m[2][0] = right + left / sx;
  res.m[2][1] = top + bottom / sy;
  res.m[2][2] = -(far + near) / sz;
  res.m[2][3] = -one;
  res.m[3][2] = -two * far * near / sz;
  return res;
}

/**
 * Perspective
 */
template <typename T>
inline mat_t<T, 4u, 4u> perspective(T aspect, T fov, T near, T far) {
  const auto one = static_cast<T>(1.0);
  const auto half = static_cast<T>(0.5);

  /*const T hrad = one / deg2rad(fov) * half;

  const T top = near * std::tan(hrad);
  const T right = top * aspect;
  return frustum(-right, right, top, -top, near, far);*/

  const auto htan = std::tan(deg2rad(fov) * half);

  mat_t<T, 4u, 4u> res(T(0));
  res.m[0][0] = one / (aspect * htan);
  res.m[1][1] = one / (htan);
  res.m[2][2] = far / (near - far);
  res.m[2][3] = -one;
  res.m[3][2] = -(far * near) / (far - near);
  return res;
}

/**
 * Determinant
 */
template <typename T> inline T determinant(const mat_t<T, 2u, 2u> &m) {
  return m[0] * m[3] - m[1] * m[2];
}

template <typename T, u8 N> inline T determinant(const mat_t<T, N, N> &m) {
  T res = 0;
  size_t z = 0;
  mat_t<T, N - 1, N - 1> tmp((T)0);

  for (u8 i = 0; i < N; ++i) {
    const T s = i % 2 == 0 ? m.m[0][i] : -m.m[0][i];

    z = 0;
    for (u8 j = 1; j < N; ++j) {
      for (u8 k = 0; k < N; ++k) {
        if (i == k)
          continue;
        tmp[z++] = m.m[j][k];
      }
    }

    res += s * determinant(tmp);
  }

  return res;
}

/**
 * Invert
 */
template <typename T, u8 N> inline void invert(mat_t<T, N, N> &m) {
  const T det = determinant(m);
  ASSERT(det != 0 && "No determinant for matrix!");
  const T idet = 1.0 / det;

  mat_t<T, N, N> minors((T)0);
  mat_t<T, N - 1, N - 1> tmp((T)0);
  T dtmp = 0;
  size_t z = 0;
  for (u8 x = 0; x < N; ++x) {
    for (u8 y = 0; y < N; ++y) {

      z = 0;
      for (u8 i = 0; i < N; ++i) {
        for (u8 j = 0; j < N; ++j) {
          if (i == x || j == y)
            continue;
          tmp[z++] = m.m[i][j];
        }
      }

      dtmp = determinant(tmp);
      minors.m[y][x] = (x + y) % 2 == 0 ? dtmp : -dtmp;
    }
  }

  m = minors * idet;
}

/**
 * Inverse
 */
template <typename T, u8 R, u8 C>
inline mat_t<T, R, C> inverse(const mat_t<T, R, C> &m) {
  mat_t<T, R, C> res = m;
  invert(res);
  return res;
}

/**
 * Transpose
 */
template <typename T, u8 R, u8 C> inline void transpose(mat_t<T, R, C> &m) {
  ASSERT(false && "TODO");
}

/**
 * Transposed
 */
template <typename T, u8 R, u8 C>
inline mat_t<T, R, C> transposed(const mat_t<T, R, C> &m) {
  mat_t<T, R, C> res = m;
  transpose(res);
  return res;
}
}
