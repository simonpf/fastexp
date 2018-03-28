#include <chrono>
#include <iomanip>
#include <iostream>
#include <memory>
#include <fstream>
#include "math.h"
#include "fastexp.h"

template<typename Real>
void benchmark_function(void (*f)(Real *, size_t),
                        std::string name,
                        size_t array_size,
                        size_t n_trials,
                        std::ofstream &file)
{
    std::unique_ptr<Real> x(new Real[array_size]);
    long time(0), time2(0);

    f(x.get(), array_size);

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


    std::cout << std::left << std::setw(10) << name;
    std::cout << std::setprecision(7) << mean << " ";
    std::cout << std::setprecision(7) << sigma << std::end;;

    file << name << " " << mean << " " << sigma << std::endl;
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

using fastexp::IEEE;
using fastexp::Product;

template<typename Real, size_t i>
void benchmark_ieee(std::ofstream &file)
{
    std::string name("IEEE ");
    name += std::to_string(i) + " ";
    benchmark_function(&fastexp::exp<float, IEEE, i>,
                       name, 100000000, 10, file);
}

template<typename Real, size_t i>
void benchmark_product(std::ofstream &file)
{
    std::string name("Product ");
    name += std::to_string(i) + " ";
    benchmark_function(&fastexp::exp<float, Product, i>,
                       name, 100000000, 10, file);
}

int main() {

    std::string filename("results/${CMAKE_CXX_COMPILER_ID}_${CMAKE_CXX_COMPILER_VERSION}.dat");
    std::ofstream file;
    file.open(filename);

    std::cout << std::left << std::setw(10) << "Method";
    std::cout << std::setw(8) << "Mean";
    std::cout << std::setw(8) << "Sigma" << std::endl;

    benchmark_ieee<float, 0>(file);
    benchmark_ieee<float, 1>(file);
    benchmark_ieee<float, 2>(file);
    benchmark_ieee<float, 3>(file);
    benchmark_ieee<float, 4>(file);
    benchmark_ieee<float, 5>(file);
    benchmark_ieee<float, 6>(file);

    benchmark_product<float, 4>(file);
    benchmark_product<float, 6>(file);
    benchmark_product<float, 8>(file);
    benchmark_product<float, 10>(file);
    benchmark_product<float, 12>(file);
    benchmark_product<float, 14>(file);
    benchmark_product<float, 16>(file);
}
