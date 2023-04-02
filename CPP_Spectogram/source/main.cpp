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
    std::vector<std::complex<double>> frequencies = FourierAnalyzer::parallelSTFFT<std::vector<std::complex<double>>::iterator, double>(audioFrames.begin(), audioFrames.end());

    std::vector<double> powerSpectrum = FourierAnalyzer::compute_power_spectrum<double>()(frequencies);

    for (const auto& power : powerSpectrum)
        std::cout << power << ' ';

	return 0;
}