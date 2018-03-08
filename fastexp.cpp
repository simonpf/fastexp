#include "fastexp.h"

#define DLL_PUBLIC __attribute__ ((visibility ("default")))


extern "C" {

    float exp_s(float x) {
        return fast::exp(x);
    }

    double exp_d(double x) {
        return fast::exp(x);
    }

    void exp_v_s(float *x, size_t n) {
        fast::exp_v<float>(x, n);
    }

    void exp_v_d(double *x, size_t n) {
        fast::exp_v<double>(x, n);
    }

    void exp_nv_s(float *x, size_t n) {
        fast::exp<float>(x, n);
    }

    void exp_nv_d(double *x, size_t n) {
        fast::exp<double>(x, n);
    }
}


