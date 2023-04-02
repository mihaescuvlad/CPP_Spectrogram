#ifndef _AUDIO_FACADE_
#define _AUDIO_FACADE_

#include <complex>
#include <string>
#include <unordered_map>
#include <vector>

#include <sndfile.h>

class AudioFacade
{
private:
	SNDFILE* m_file{ nullptr };
	SF_INFO m_info{};

	uint64_t computeSize();

public:
	~AudioFacade();

	void openFile(const std::string& file_path);
	void closeFile();

	std::vector<short> readShort();
	std::vector<int> readInt();
	std::vector<float> readFloat();
	std::vector<double> readDouble();

	std::vector<std::complex<float>> readComplexFloat();
	std::vector<std::complex<double>> readComplexDouble();

private:
	template<typename T>
	std::vector<std::complex<T>> makeComplex(std::vector<T> elements)
	{
		std::vector<std::complex<T>> complexElements;
		for_each(elements.begin(), elements.end(), [&complexElements](const auto& currentElement) {
			std::complex<T> temp = { currentElement, 0 };
			complexElements.emplace_back(temp);
			});

		return complexElements;
	}
};

#endif