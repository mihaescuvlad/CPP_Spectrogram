#include "AudioFacade.h"

#include <iostream>

AudioFacade::~AudioFacade()
{
    if (m_file) 
    {
        CloseFile();

        m_file = nullptr;

    }
}

void AudioFacade::OpenFile(const std::string& file_path) 
{
    m_file = sf_open(file_path.c_str(), SFM_READ, &m_info);

    if (!m_file)
    {
        throw sf_strerror(m_file);
    }
}

void AudioFacade::CloseFile()
{
    try
    {
        uint16_t errorNumber = sf_close(m_file);

        if (errorNumber)
        {
            throw sf_error_number(errorNumber);
        }

        m_file = nullptr;
    }
    catch (const char* e)
    {
        std::cerr << e;

        m_file = nullptr;

        std::terminate;
    }
}

std::vector<short> AudioFacade::ReadShort()
{
    std::vector<short> audioData(m_info.frames);
    sf_read_short(m_file, audioData.data(), m_info.frames);

    return audioData;
}

std::vector<int> AudioFacade::ReadInt()
{
    std::vector<int> audioData(m_info.frames);
    sf_read_int(m_file, audioData.data(), m_info.frames);

    return audioData;
}

std::vector<float> AudioFacade::ReadFloat()
{
    std::vector<float> audioData(m_info.frames);
    sf_read_float(m_file, audioData.data(), m_info.frames);

    return audioData;
}

std::vector<double> AudioFacade::ReadDouble()
{
    std::vector<double> audioData(m_info.frames);
    sf_read_double(m_file, audioData.data(), m_info.frames);

    return audioData;
}