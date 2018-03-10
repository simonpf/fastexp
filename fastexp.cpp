#include "fastexp.h"
#include "math.h"

#define DLL_PUBLIC __attribute__ ((visibility ("default")))

extern "C" {

    float exp_s(float x) {
        return fast::exp(x);
    }

    double exp_d(double x) {
        return fast::exp(x);
    }

    void exp_v_s(float *x, size_t n) {
        fast::exp<float>(x, n);
    }

    void exp_v_d(double *x, size_t n) {
        fast::exp<double>(x, n);
    }

    void exp256_v_s(float *x, size_t n) {
        fast::exp256<float>(x, n);
    }

    void exp256_v_d(double *x, size_t n) {
        fast::exp256<double>(x, n);
    }

    void exp1024_v_s(float *x, size_t n) {
        fast::exp1024<float>(x, n);
    }

    void exp1024_v_d(double *x, size_t n) {
        fast::exp1024<double>(x, n);
    }

    void exp_nv_s(float *x, size_t n) {
        fast::exp_nv<float>(x, n);
    }

    void exp_nv_d(double *x, size_t n) {
        fast::exp_nv<double>(x, n);
    }

    void slow_exp_s(float *x, size_t n) {
        for (size_t i = 0; i < n; ++i) {
            float e = exp(x[i]);
            x[i] = e;
        }
    }

    void slow_exp_d(float *x, size_t n) {
        for (size_t i = 0; i < n; ++i) {
            double e = exp(x[i]);
            x[i] = e;
        }
    }
}
