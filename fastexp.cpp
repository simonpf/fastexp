#include "fastexp.h"
#include "math.h"

#define DLL_PUBLIC __attribute__ ((visibility ("default")))

using fastexp::IEEE;
using fastexp::Product;

extern "C" {

    float exp_s(float x) {
        return fastexp::exp(x);
    }

    double exp_d(double x) {
        return fastexp::exp(x);
    }

    void exp_v_s(float *x, size_t n) {
        fastexp::exp<float>(x, n);
    }

    void exp_v_d(double *x, size_t n) {
        fastexp::exp<double>(x, n);
    }

    void exp256_v_s(float *x, size_t n) {
        fastexp::exp<float, Product, 8>(x, n);
    }

    void exp256_v_d(double *x, size_t n) {
        fastexp::exp<double, Product, 8>(x, n);
    }

    void exp1024_v_s(float *x, size_t n) {
        fastexp::exp<float, Product, 10>(x, n);
    }

    void exp1024_v_d(double *x, size_t n) {
        fastexp::exp<double, Product, 10>(x, n);
    }

}
