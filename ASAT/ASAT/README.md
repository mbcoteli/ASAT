# Acoustic Scene Analysis Tool (ASAT)
Simulation software is for the analysis of Spatial Audio simulations and algorithms during my Phd thesis.
• Qt C++ coding environment Qt 5.8.0 - (MSVC 2015 - 32 bit)
• Boost libraries for mathematical functions Boost1_63_0 https://sourceforge.net/projects/boost/files/boost/1.63.0/
• FFTw for frequency domain analysis. http://www.fftw.org/install/windows.html
• QCustomPlot   http://www.qcustomplot.com/index.php/download

The features of this software will be:
• Audio Source Creator (A/S/C)
1. Plane Wave (P/W) Generator
2. Point Source (P/S) Generator

• Room Acoustics Simulator, Reflection and ISM for point sources (R/A/S)
• Spherical Microphone Array Quadrature Calculator (M/Q/C)

1. Rigid Microphone Array
2. Open Microphone Array

• Data Acquisition Tool - Connection between Audio Source Creator
(A/S/C), Room Acoustics Simulator (R/A/S) and Microphone Array
Quadrature Calculator (M/Q/C)

Setup :
1) FFTW libraries are downloaded.
2) .def file are converted into lib files using lib.exe
	 lib /def:libfftw3-3.def
     lib /def:libfftw3f-3.def
     lib /def:libfftw3l-3.def
3) Boost libraries are downloaded bootstrap.bat is executed, then b2.exe is executed.
4) Create a folder on project folder and give name of include to it. Put fftw and boost libraries inside that directory
5) Inside .pro file insert the following lines.
		INCLUDEPATH += $$PWD/include $$PWD/include/fftw
		LIBS += "-L$$PWD/include/fftw" -llibfftw3-3
6) Use the project

