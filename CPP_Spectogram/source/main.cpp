#include <iostream>
#include <vector>
#include <sndfile.hh>

const char* path = "input_data\\222677__unfa__ac-buzz-04.flac";

int main()
{
    SNDFILE* file = nullptr;
    SF_INFO info = {};

    file = sf_open(path, SFM_READ, &info);
    if (!file)
    {
        std::cerr << "Failed to open file " << path << std::endl;
        return 1;
    }

    if (info.channels != 1)
    {
        std::cerr << "Only mono audio files are supported" << std::endl;
        return 1;
    }

    std::vector<double> audio(info.frames);
    sf_read_double(file, audio.data(), info.frames);

    for (const auto& it : audio)
    {
        std::cout << it << ' ';
    }

	return 0;
}