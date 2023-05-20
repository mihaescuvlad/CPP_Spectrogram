#include <iostream>

#include "AudioFacade.h"

AudioFacade::~AudioFacade()
{
	if (m_file)
	{
		this->closeFile();

		m_file = nullptr;
	}
}

void AudioFacade::openFile(const std::string& file_path)
{
	m_file = sf_open(file_path.c_str(), SFM_READ, &m_info);

	if (!m_file)
	{
		throw std::exception(sf_strerror(m_file));
	}
}

void AudioFacade::closeFile()
{
	try
	{
		if (const int errorNumber = sf_close(m_file))
		{
			throw std::exception(sf_error_number(errorNumber));
		}

		m_file = nullptr;
	}
	catch (const char* e)
	{
		std::cerr << e;

		m_file = nullptr;

		std::terminate();
	}
}

uint64_t AudioFacade::computeSize() const
{
	return static_cast<uint64_t>(m_info.frames * m_info.channels);
}

std::vector<short> AudioFacade::readShort() const
{
	std::vector<short> audioData(this->computeSize());
	sf_readf_short(m_file, audioData.data(), m_info.frames);

	return audioData;
}

std::vector<int> AudioFacade::readInt() const
{
	std::vector<int> audioData(this->computeSize());
	sf_readf_int(m_file, audioData.data(), m_info.frames);

	return audioData;
}

std::vector<float> AudioFacade::readFloat() const
{
	std::vector<float> audioData(this->computeSize());
	sf_readf_float(m_file, audioData.data(), m_info.frames);

	return audioData;
}

std::vector<std::complex<float>> AudioFacade::readComplexFloat()
{
	const std::vector<float> audioData = this->readFloat();
	std::vector<std::complex<float>> complexAudioData = makeComplex<float>(audioData);

	return complexAudioData;
}

std::vector<double> AudioFacade::readDouble() const
{
	std::vector<double> audioData(this->computeSize());
	sf_readf_double(m_file, audioData.data(), m_info.frames);

	return audioData;
}

std::vector<std::complex<double>> AudioFacade::readComplexDouble()
{
	const std::vector<double> audioData = this->readDouble();
	std::vector<std::complex<double>> complexAudioData = makeComplex<double>(audioData);

	return complexAudioData;
}
