#include <iostream>
#include <vector>
#include <string>
#include "AudioFacade.h"
#include "Constants.h"

int main()
{
    AudioFacade audioFacade;
    audioFacade.OpenFile(Constants::ac_buzz);

    std::vector<double> frequencies = audioFacade.ReadDouble();

    for (const auto& frequency : frequencies)
        std::cout << frequency << ' ';
    
	return 0;
}