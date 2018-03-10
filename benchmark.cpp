#include <chrono>
#include <iomanip>
#include <iostream>
#include <memory>
#include "math.h"
#include "fastexp.h"

template<typename Real>
void benchmark_function(void (*f)(Real *, size_t),
                        std::string name,
                        size_t array_size,
                        size_t n_trials)
{
    std::unique_ptr<Real> x(new Real[array_size]);
    long time(0), time2(0);

    for (size_t i = 0; i < n_trials; ++i) {
        auto t1 = std::chrono::high_resolution_clock::now();
        f(x.get(), array_size);
        auto t2 = std::chrono::high_resolution_clock::now();
        long ms = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();

        time += ms;
        time2 += ms * ms;
    }

    double mean  = static_cast<double>(time) / static_cast<double>(n_trials);
    double mean2 = static_cast<double>(time2) / static_cast<double>(n_trials);
    double sigma = sqrt(mean2 - mean * mean);


    std::cout << std::left << std::setw(25) << name;
    std::cout << std::setprecision(2) << mean << " ± " << sigma << " ms" << std::endl;
}

template<typename Real>
void exp(Real *x, size_t n) {
    for (size_t i = 0; i < n; ++i) {
        Real e = exp(x[i]);
        x[i] = e;
    }
}

int main() {
    benchmark_function(&fast::exp<float>, "exp, float (OpenMP)", 10000000, 100);
    benchmark_function(&fast::exp_nv<float>, "exp, float", 10000000, 100);
    benchmark_function(&fast::exp<double>, "exp_v, double (OpenMP)", 10000000, 100);
    benchmark_function(&fast::exp_nv<double>, "exp_v, double", 10000000, 100);
    benchmark_function(&exp<float>, "exp, float, math.h", 10000000, 100);
    benchmark_function(&exp<double>, "exp, double, math.h", 10000000, 100);
}
