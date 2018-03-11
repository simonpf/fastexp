#include <chrono>
#include <iomanip>
#include <iostream>
#include <memory>
#include "math.h"
#include "fastexp.h"

//template<typename Real>
//void benchmark_function(void (*f)(std::vector<Real> x),
//                        std::string name,
//                        size_t array_size,
//                        size_t n_trials)
//{
//    std::vector<Real> x(array_size, 1.0);
//    long time(0), time2(0);
//
//    for (size_t i = 0; i < n_trials; ++i) {
//        auto t1 = std::chrono::high_resolution_clock::now();
//        f(x);
//        auto t2 = std::chrono::high_resolution_clock::now();
//        long ms = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();
//
//        time += ms;
//        time2 += ms * ms;
//    }
//
//    double mean  = static_cast<double>(time) / static_cast<double>(n_trials);
//    double mean2 = static_cast<double>(time2) / static_cast<double>(n_trials);
//    double sigma = sqrt(mean2 - mean * mean);
//
//
//    std::cout << std::left << std::setw(25) << name;
//    std::cout << std::setprecision(2) << mean << " ± " << sigma << " ms" << std::endl;
//}

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
void exp(std::vector<Real> x) {
    for (size_t i = 0; i < x.size(); ++i) {
        Real e = exp(x[i]);
        x[i] = e;
    }
}

template<typename Real>
void exp(Real *x, size_t n) {
    for (size_t i = 0; i < n; ++i) {
        Real e = exp(x[i]);
        x[i] = e;
    }
}

using fastexp::Schraudolph;
using fastexp::Product;

int main() {
    std::cout << "Single Precistion:" << std::endl;
    benchmark_function(&fastexp::exp<float, Schraudolph, 0>,
                       "Schraudolph, 0", 10000000, 100);
    benchmark_function(&fastexp::exp<float, Schraudolph, 1>,
                       "Schraudolph, 1", 10000000, 100);
    benchmark_function(&fastexp::exp<float, Schraudolph, 2>,
                       "Schraudolph, 2", 10000000, 100);
    benchmark_function(&fastexp::exp<float, Product, 8>,
                       "Product, 8", 10000000, 100);
    benchmark_function(&fastexp::exp<float, Product, 10>,
                       "Product, 10", 10000000, 100);
    benchmark_function(&fastexp::exp<float, Product, 12>,
                       "Product, 12", 10000000, 100);
    benchmark_function(&exp<float>, "exp, math.h", 10000000, 100);
    std::cout << std::endl;

    std::cout << "Double Precistion:" << std::endl;
    benchmark_function(&fastexp::exp<double, Schraudolph, 0>,
                       "Schraudolph, 0", 10000000, 100);
    benchmark_function(&fastexp::exp<double, Schraudolph, 1>,
                       "Schraudolph, 1", 10000000, 100);
    benchmark_function(&fastexp::exp<double, Schraudolph, 2>,
                       "Schraudolph, 2", 10000000, 100);
    benchmark_function(&fastexp::exp<double, Product, 8>,
                       "Product, 8", 10000000, 100);
    benchmark_function(&fastexp::exp<double, Product, 10>,
                       "Product, 10", 10000000, 100);
    benchmark_function(&fastexp::exp<double, Product, 12>,
                       "Product, 12", 10000000, 100);
    benchmark_function(&exp<double>, "exp, math.h", 10000000, 100);
    std::cout << std::endl;
}
