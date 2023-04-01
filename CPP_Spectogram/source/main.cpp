#include <iostream>
#include <vector>
#include <string>
#include "AudioFacade.h"
#include "Constants.h"

int main()
{
    AudioFacade audioFacade;
    audioFacade.openFile(Constants::ac_buzz);

    std::vector<double> frequencies = audioFacade.readDouble();

    for (const auto& frequency : frequencies)
        std::cout << frequency << ' ';

    

	return 0;
}