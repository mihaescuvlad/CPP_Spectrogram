#ifndef AUDIO_FACADE_H
#define AUDIO_FACADE_H

#include <algorithm>
#include <complex>
#include <ranges>
#include <string>
#include <vector>

#include "sndfile.h"

class AudioFacade
{
private:
	SNDFILE* m_file{nullptr};
	SF_INFO m_info{};

	[[nodiscard]] uint64_t computeSize() const;

public:
	AudioFacade() = default;
	~AudioFacade();

	void openFile(const std::string& file_path);
	void closeFile();

	[[nodiscard]] std::vector<short> readShort() const;
	[[nodiscard]] std::vector<int> readInt() const;
	[[nodiscard]] std::vector<float> readFloat() const;
	[[nodiscard]] std::vector<double> readDouble() const;

	std::vector<std::complex<float>> readComplexFloat();
	std::vector<std::complex<double>> readComplexDouble();


	AudioFacade(const AudioFacade&) = delete;
	AudioFacade& operator=(const AudioFacade&) = delete;

	AudioFacade(AudioFacade&&) = delete;
	AudioFacade& operator=(AudioFacade&&) = delete;

private:
	template <typename T>
	std::vector<std::complex<T>> makeComplex(std::vector<T> elements)
	{
		std::vector<std::complex<T>> complexElements;
		std::ranges::for_each(elements, [&complexElements](const auto& currentElement)
		{
			std::complex<T> temp = {currentElement, 0};
			complexElements.emplace_back(temp);
		});

		return complexElements;
	}
};

#endif
