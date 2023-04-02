#include <complex>
#include <iostream>
#include <string>
#include <vector>

#include "AudioFacade.h"
#include "Constants.h"
#include "FourierAnalyzer.hpp"

int main()
{
    AudioFacade audioFacade;
    audioFacade.openFile(Constants::ac_buzz);

    std::vector<std::complex<double>> audioFrames = audioFacade.readComplexDouble();
    std::vector<double> frequencies = FourierAnalyzer::parallel_STFFT<std::vector<std::complex<double>>::iterator, double>(audioFrames.begin(), audioFrames.end());

    for (const auto& frequency : frequencies)
        std::cout << frequency << ' ';

	return 0;
}