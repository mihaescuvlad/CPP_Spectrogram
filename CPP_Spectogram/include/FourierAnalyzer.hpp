#ifndef FOURIER_ANALYZER_HPP
#define FOURIER_ANALYZER_HPP

#include <algorithm>
#include <complex>
#include <functional>
#include <future>
#include <numbers>
#include <numeric>
#include <queue>
#include <thread>
#include <vector>

namespace FourierAnalyzer
{
	template <typename T>
	void computeFft(std::vector<std::complex<T>>& result)
	{
		size_t containerSize = result.size();

		if (containerSize <= 1)
			return;

		std::vector<std::complex<T>> even(containerSize / 2), odd(containerSize / 2);
		for (size_t i = 0; i < containerSize / 2; ++i)
		{
			even[i] = result[2 * i];
			odd[i] = result[2 * i + 1];
		}

		computeFft(even);
		computeFft(odd);

		for (size_t i = 0; i < containerSize / 2; ++i)
		{
			std::complex<T> t = std::polar(
				1.0, -2.0 * std::numbers::pi_v<T> * static_cast<T>(i) / static_cast<T>(containerSize)) * odd[i];

			result[i] = even[i] + t;
			result[i + containerSize / 2] = even[i] - t;
		}
	}

	template <typename T>
	struct transform_data
	{
		T operator()(T result)
		{
			computeFft(result);

			return result;
		}
	};

	template <typename Iterator, typename T>
	struct apply_hanning_window
	{
		std::vector<std::complex<T>> operator()(Iterator first, Iterator last)
		{
			const auto length = static_cast<uint64_t>(std::distance(first, last));
			std::vector<std::complex<T>> windowedInput;

			for (auto [iter, position] = std::tuple(first, 0); iter != last; std::advance(iter, 1), ++position) 
			{
				T window = 0.54 - 0.46 * std::cos(2.0 * std::numbers::pi_v<T> * position / (static_cast<T>(length) - 1.0));

				windowedInput.emplace_back(*iter * window);
			}

			return windowedInput;
		}
	};

	template <typename Iterator, typename T>
	struct flatten_matrix
	{
		std::vector<T> operator()(Iterator first, Iterator last)
		{
			std::vector<T> flattened;

			std::for_each(first, last, [&flattened](std::vector<T>& inner)
			{
				std::copy(inner.begin(), inner.end(), std::back_inserter(flattened));
			});

			return flattened;
		}
	};

	template <typename T>
	struct normalize_signals
	{
		std::vector<std::complex<T>> operator()(const std::vector<std::complex<T>>& signals)
		{
			T normalizationFactor = 1.0 / std::sqrt(signals.size());

			std::vector<std::complex<T>> normalizedSignal;
			normalizedSignal.reserve(signals.size());

			for (const auto& signal : signals) 
			{
				normalizedSignal.emplace_back(signal * normalizationFactor);
			}

			return normalizedSignal;
		}
	};

	template <typename T>
	struct compute_power_spectrum_no_redundant
	{
		std::vector<T> operator()(const std::vector<std::complex<T>>& frequencies)
		{
			std::vector<T> powerSpectrum(frequencies.size() / 2);
			for (size_t i = 0; i < frequencies.size() / 2; ++i)
			{
				T magnitude = std::abs(frequencies[i]);
				powerSpectrum[i] = magnitude * magnitude;
			}

			return powerSpectrum;
		}
	};

	template <typename T>
	struct compute_power_spectrum
	{
		std::vector<T> operator()(const std::vector<std::complex<T>>& frequencies)
		{
			std::vector<T> powerSpectrum;
			powerSpectrum.reserve(frequencies.size());

			for (const auto& frequency : frequencies) 
			{
				powerSpectrum.emplace_back(std::pow(std::abs(frequency), 2));
			}

			return powerSpectrum;
		}
	};

	template <typename T>
	struct compute_power_spectral_density
	{
		std::vector<T> operator()(const std::vector<std::complex<T>>& frequencies)
		{
			const T frequency_resolution = 1.0 / static_cast<T>(frequencies.size());
			const std::vector<T> powerSpectrum = compute_power_spectrum<T>()(frequencies);

			std::vector<T> powerSpectralDensity;
			powerSpectralDensity.reserve(frequencies.size());

			for (std::size_t i = 0; i < frequencies.size(); ++i) 
			{
				powerSpectralDensity.emplace_back(powerSpectrum[i] / frequency_resolution);
			}

			return powerSpectralDensity;
		}
	};

	template <typename T>
	struct apply_log_filter
	{
		std::vector<T> operator()(const std::vector<T>& frequencies)
		{
			std::vector<T> logPowerSpectralDensity;
			logPowerSpectralDensity.reserve(logPowerSpectralDensity.size());

			for (const auto& frequency : frequencies) 
			{
				logPowerSpectralDensity.emplace_back(10.0 * std::log10(frequency));
			}

			return logPowerSpectralDensity;
		}
	};

	template <typename Iterator, typename T>
	std::vector<std::complex<T>> parallelStfft(Iterator first, Iterator last)
	{
		const auto length = static_cast<uint64_t>(std::distance(first, last));

		if (!length)
			return std::vector<std::complex<T>>();

		std::vector<std::complex<T>> windowedData = apply_hanning_window<
			typename std::vector<std::complex<T>>::iterator, T>()
			(first, last);

		std::queue<std::future<std::vector<std::complex<T>>>> threadQueue;

		const uint64_t numBlocks = std::thread::hardware_concurrency();
		const uint64_t blockSize = length / numBlocks;

		
		Iterator blockStart = windowedData.begin();
		for (uint64_t i = 0; i < numBlocks; ++i)
		{
			Iterator blockEnd = blockStart;
			std::advance(blockEnd, blockSize);

			std::vector<std::complex<T>> chunkData(blockStart, blockEnd);

			threadQueue.emplace(std::async(std::launch::async, transform_data<std::vector<std::complex<T>>>(), std::move(chunkData)));

			blockStart = blockEnd;
		}
		
		if(blockStart != windowedData.end())
		{
			std::vector<std::complex<T>> chunkData(blockStart, windowedData.end());

			threadQueue.emplace(std::async(std::launch::async, transform_data<std::vector<std::complex<T>>>(), std::move(chunkData)));
		}
		
		std::vector<std::complex<T>> results(length);
		blockStart = results.begin();
		while (!threadQueue.empty()) 
		{


			std::vector<std::complex<T>> threadResult = threadQueue.front().get();
			std::copy(threadResult.begin(), threadResult.end(), blockStart);

			advance(blockStart, threadResult.size());
			threadQueue.pop();
		}
		
		return results;
	}
};

#endif
