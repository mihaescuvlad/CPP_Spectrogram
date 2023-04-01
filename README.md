# :books: C++ Spectrogram :books:

This repository contains a C++ implementation of a spectrogram, which is a visualization of the frequency content of a signal over time. The spectrogram is computed using the Fast Fourier Transform (FFT) algorithm, which is a widely used technique for analyzing and processing digital signals.

## Features
To use the spectrogram implementation, you will first need to compile the program. The following dependencies are required:

  + [libsndfile library](https://github.com/libsndfile/libsndfile/releases)

To install these dependencies, follow the instructions provided by your operating system or package manager.

## Motivation

This project was created as part of a university project in computer graphics. The goal of the project was to implement a spectrogram algorithm in C++, which would allow us to analyze and visualize the frequency content of different audio signals. The spectrogram is a useful tool for many applications, including speech analysis, music analysis, and sound effects design.

We chose to use the FFT algorithm to compute the spectrogram because of its efficiency and accuracy. The FFT algorithm is a fast and efficient way to compute the frequency content of a signal, and it is widely used in many applications, including audio processing, image processing, and scientific computing. By using the FFT algorithm, we were able to compute the spectrogram in real-time, which allowed us to analyze and visualize the frequency content of the signal as it was being played.

Our implementation of the spectrogram is based on the following steps:

<ol>
    <li>Read in an audio file and convert it to a mono signal.</li>
    <li>Apply a windowing function to the signal to reduce spectral leakage.</li>
    <li>Compute the FFT of each window of the signal to obtain the frequency content.</li>
    <li>Compute the magnitude spectrum of each FFT to obtain the power spectral density.</li>
    <li>Map the power spectral density onto a logarithmic scale to obtain the spectrogram.</li>
</ol>

The spectrogram is visualized using a 2D colormap, where the x-axis represents time, the y-axis represents frequency, and the color represents the power spectral density. By analyzing the spectrogram, we can identify the frequency content of the signal over time, which can be useful for many applications.

## Requirements

[[TODO: Add Project Requirements/Dependencies]]
