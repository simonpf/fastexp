#ifndef FASTEXP_H
#define FASTEXP_H

#include "math.h"
#include <cstdint>
#include <cstddef>

namespace fast
{

/** \brief Fast approximate exponential.
 *
 * This function implements a fast, vectorizable approximation
 * of the exponential function based on the following two articles:
 *
 * - Malossi, A. Cristiano I. & Ineichen, Yves & Bekas, Costas & Curioni,
 *   Alessandro. "Fast Exponential Computation on SIMD Architectures." (2015)
 *   10.13140/2.1.4362.3207.
 * - Schraudolph, Nicol N. "A fast, compact approximation of the exponential
 *   function." Neural Computation 11.4 (1999): 853-862.
 *
 * The approximation interpolates linearly between points on the curve of
 * the exponential function that can be expressed as 2^i where i is an
 * a signed integer. So yes, that is very approximate ...
 *
 * \tparam Real The floating point type of the arguments.
 * \param x The argument of the exponential function.
 * \return The approximated value of the exponential function.
 */
#pragma omp declare simd notinbranch
template<typename Real> inline Real exp(Real x);

template<> inline float exp(float x)
{
    constexpr uint32_t shift = static_cast<uint32_t>(1) << 23;

    x *= 1.442695040f;
    float xi = floor(x);
    float xf = x - xi + 1.0;

    uint32_t e = reinterpret_cast<const uint32_t &>(xf);
    e += shift * static_cast<uint32_t>(xi);
    return reinterpret_cast<float &>(e);
}

template<> inline double exp(double x)
{
    constexpr uint64_t shift = static_cast<uint64_t>(1) << 52;

    x *= 1.442695040d;
    double xi = floor(x);
    double xf = x - xi + 1.0;

    uint64_t e = reinterpret_cast<const uint64_t &>(xf);
    e += shift * static_cast<uint64_t>(xi);
    return reinterpret_cast<double &>(e);
}

#pragma omp declare simd notinbranch
template<typename Real> inline Real exp256(Real x)
{
    x = 1.0 + x / 256.0;
    x *= x;
    x *= x;
    x *= x;
    x *= x;
    x *= x;
    x *= x;
    x *= x;
    x *= x;
    return x;
}

#pragma omp declare simd notinbranch
template<typename Real> inline Real exp1024(Real x)
{
    x = 1.0 + x / 1024.0;
    x *= x;
    x *= x;
    x *= x;
    x *= x;
    x *= x;
    x *= x;
    x *= x;
    x *= x;
    x *= x;
    x *= x;
    return x;
}

/** \brief Fast approximate array exponential.
 *
 * Applies the fast exponential to an array of given length making
 * use of SIMD instructions if available. To enable vectorization
 * the code needs to be compiled with OpenMP support.
 *
 * \tparam Real The floating point type of the arguments.
 * \param x The array to which apply the exponential function.
 * \return n The number of elements in the array.
 */
template <typename Real>
inline void exp(Real *x, size_t n) {
    // Vectorized part.
    #pragma omp simd
    for (size_t i = 0; i < n; ++i) {
        Real e = fast::exp(x[i]);
        x[i] = e;
    }
}

template <typename Real>
    inline void exp256(Real *x, size_t n) {
    // Vectorized part.
    #pragma omp simd
    for (size_t i = 0; i < n; ++i) {
        Real e = fast::exp256(x[i]);
        x[i] = e;
    }
}

template <typename Real>
    inline void exp1024(Real *x, size_t n) {
    // Vectorized part.
#pragma omp simd
    for (size_t i = 0; i < n; ++i) {
        Real e = fast::exp1024(x[i]);
        x[i] = e;
    }
}

/** \brief Not-so-fast approximate array exponential.
 *
 * Applies the approximate exponential function to an array but
 * without enforcing vectorization using OpenMP. This function exists
 * mainly for purposes of comparison.
 *
 * \tparam Real The floating point type of the arguments.
 * \param x The array to which apply the exponential function.
 * \return n The number of elements in the array.
 */
template <typename Real>
inline void exp_nv(Real *x, size_t n) {
    for (size_t i = 0; i < n; ++i) {
        Real e = fast::exp(x[i]);
        x[i] = e;
    }
}

}      // fast
#endif // FASTEXP_H
