#ifndef FASTEXP_SCHRAUDOLPH_H
#define FASTEXP_SCHRAUDOLPH_H

namespace fastexp
{
    template<typename Real, size_t degree, size_t i = 0> struct PolynomialFit;
    template<typename Real> struct Info;

    template<typename Real, size_t degree>
    struct Schraudolph {
        static Real evaluate(Real x) {
            using unsigned_t = typename Info<Real>::unsigned_t;
            constexpr unsigned_t shift = static_cast<unsigned_t>(1) << Info<Real>::shift;

            x *= Info<Real>::log2e;
            Real xi = floor(x);
            Real xf = x - xi;

            Real k = PolynomialFit<Real, degree, 0>::evaluate(xf) + 1.0;
            unsigned_t e = reinterpret_cast<const unsigned_t &>(k);
            e += shift * static_cast<unsigned_t>(xi);
            return reinterpret_cast<Real &>(e);
        }
    };

    ////////////////////////////////////////////////////////////////////////////////
    // Polynomial coefficients for error function fit.
    ////////////////////////////////////////////////////////////////////////////////


    template<> struct Info<float> {
        using unsigned_t = uint32_t;
        static constexpr uint32_t shift = 23;
        static constexpr float  log2e = 1.442695040f;
    };

    template<> struct Info<double> {
        using unsigned_t = uint64_t;
        static constexpr uint64_t shift = 52;
        static constexpr double log2e = 1.442695040d;
    };

    template<typename Real, size_t degree>
        struct Data;

    template<typename Real>
    struct Data<Real, 1> {
        static constexpr Real coefficients[2] = {-0.05288671,
                                                 0.99232129};
    };

    template<typename Real>
    struct Data<Real, 2> {
        static constexpr Real coefficients[3] = {0.00365539,
                                                 0.64960693,
                                                 0.34271434};
    };

    template<typename Real>
    struct Data<Real, 3> {
        static constexpr Real coefficients[4] = {-1.77187919e-04,
                                                6.96787180e-01,
                                                2.24169036e-01,
                                                7.90302044e-02};
    };

    template<typename Real>
    struct Data<Real, 4> {
        static constexpr Real coefficients[5] = {7.90302044e-02,
                                                2.24169036e-01,
                                                6.96787180e-01,
                                                -1.77187919e-04};
    };

    template<typename Real>
    struct Data<Real, 5> {
        static constexpr Real coefficients[6] = {6.58721338e-06,
                                                6.92937406e-01,
                                                2.41696769e-01,
                                                5.16742848e-02,
                                                1.36779598e-02};
    };

    template<typename Real, size_t degree, size_t i>
        struct PolynomialFit {
            inline static Real evaluate(Real x) {
                Real p = PolynomialFit<Real, degree, i + 1>::evaluate(x) * x;
                p += Data<Real, degree>::coefficients[i];
                return p;
            }
        };

    template<typename Real, size_t degree>
        struct PolynomialFit<Real, degree, degree> {
        inline static Real evaluate(Real x) {
            return Data<Real, degree>::coefficients[degree];
        }
    };

    template<typename Real>
        struct PolynomialFit<Real, 0, 0> {
        inline static Real evaluate(Real x) {
            return x;
        }
    };

}      // fastexp
#endif // FASTEXP_SCHRAUDOLPH_H
