#ifndef _FOURIER_ANALYZER_
#define _FOURIER_ANALYZER_

#include <algorithm>
#include <complex>
#include <functional>
#include <numbers>
#include <numeric>
#include <thread>
#include <vector>

#include "Constants.h"

namespace FourierAnalyzer
{
    template<typename T>
    void computeFFT(std::vector<std::complex<T>>& result)
    {
        size_t containerSize = result.size();

        if (containerSize <= 1)
            return;

        std::vector<std::complex<T>> even(containerSize / 2), odd(containerSize / 2);
        for (size_t iter = 0; iter < containerSize / 2; ++iter)
        {
            even[iter] = result[2 * iter];
            odd[iter] = result[2 * iter + 1];
        }

        computeFFT(even);
        computeFFT(odd);

        for (size_t iter = 0; iter < containerSize / 2; ++iter) {
            std::complex<T> t = std::polar(1.0, -2 * std::numbers::pi_v<T> *iter / containerSize) * odd[iter];

            result[iter] = even[iter] + t;
            result[iter + containerSize / 2] = even[iter] - t;
        }
    }

    template<typename T>
    struct transform_window
    {
        void operator()(T& result)
        {
            computeFFT(result);
        }
    };

    template<typename Iterator, typename T>
    struct flatten_matrix
    {
        std::vector<T> operator()(Iterator first, Iterator last)
        {
            std::vector<T> flattened;

            std::for_each(first, last, [&flattened](std::vector<T>& inner) {
                std::copy(inner.begin(), inner.end(), std::back_inserter(flattened));
                });

            return flattened;
        }
    };

    template<typename T>
    struct compute_power_spectrum
    {
        std::vector<T> operator()(const std::vector<std::complex<T>>& frequencies)
        {
            std::vector<T> powerSpectrum(frequencies.size() / 2 + 1);
            for (size_t iter = 0; iter <= frequencies.size() / 2; ++iter)
            {
                T realPart = frequencies[iter].real();
                T imagPart = frequencies[iter].imag();

                powerSpectrum[iter] = (realPart * realPart) + (imagPart * imagPart);
            }

            return powerSpectrum;
        }
    };

    template<typename Iterator, typename T>
    std::vector<T> parallel_STFFT(Iterator first, Iterator last)
    {
        uint64_t const length = static_cast<uint64_t>(std::distance(first, last));

        if (!length)
            return std::vector<T>();

        const uint64_t minPerThread = Constants::min_window_size;
        const uint64_t maxThreads = (length + minPerThread - 1) / minPerThread;

        const uint64_t hardwareThreads = std::thread::hardware_concurrency();
        const uint64_t numThreads = std::min(hardwareThreads != 0 ? hardwareThreads : 2, maxThreads);

        const uint64_t blockSize = length / numThreads;

        std::vector<std::vector<std::complex<T>>> frequencies(numThreads);
        std::vector<std::thread> threads(numThreads - 1);
        
        Iterator blockStart = first;
        for (uint64_t i = 0; i < (numThreads - 1); ++i)
        {
            Iterator blockEnd = blockStart;
            std::advance(blockEnd, blockSize);

            std::copy(blockStart, blockEnd, std::back_inserter(frequencies[i]));
            threads[i] = std::thread(transform_window<std::vector<std::complex<T>>>(), std::ref(frequencies[i]));

            blockStart = blockEnd;
        }

        std::copy(blockStart, last, std::back_inserter(frequencies[numThreads - 1]));
        transform_window<std::vector<std::complex<T>>>()(frequencies[numThreads - 1]);

        std::for_each(threads.begin(), threads.end(), std::mem_fn(&std::thread::join));

        std::vector<std::complex<T>> results = flatten_matrix<typename std::vector<std::vector<std::complex<T>>>::iterator, std::complex<T>>()(frequencies.begin(), frequencies.end());

        return compute_power_spectrum<T>()(results);
    }
};

#endif