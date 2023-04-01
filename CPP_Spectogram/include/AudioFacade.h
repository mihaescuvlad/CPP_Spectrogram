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
public:
	~AudioFacade();

	void OpenFile(const std::string& file_path);
	void CloseFile();
	std::vector<short> ReadShort();
	std::vector<int> ReadInt();
	std::vector<float> ReadFloat();
	std::vector<double> ReadDouble();

};

#endif
