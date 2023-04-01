#ifndef _AUDIO_FACADE_
#define _AUDIO_FACADE_

#include <vector>
#include <string>
#include <memory>
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

};

#endif
