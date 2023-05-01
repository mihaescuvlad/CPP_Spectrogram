#include <complex>
#include <iostream>
#include <vector>

#include "AudioFacade.h"
#include "Constants.h"
#include "FourierAnalyzer.hpp"

int main()
{
	AudioFacade audioFacade;
	audioFacade.openFile(Constants::ac_buzz);

	const std::vector<std::complex<double>> audioFrames = audioFacade.readComplexDouble();

	std::vector<std::complex<double>> normalizedSignals = FourierAnalyzer::normalize_signals<double>()(audioFrames);

	const std::vector<std::complex<double>> frequencies = FourierAnalyzer::parallelStfft<
		std::vector<std::complex<double>>::iterator, double>(normalizedSignals.begin(), normalizedSignals.end());

	const std::vector<double> powerSpectralDensity = FourierAnalyzer::compute_power_spectral_density<double>()(frequencies);

	const std::vector<double> filteredPsd = FourierAnalyzer::apply_log_filter<double>()(powerSpectralDensity);

	for (const auto& result : filteredPsd)
	{
		std::cout << result << ' ';
	}

	return 0;
}
