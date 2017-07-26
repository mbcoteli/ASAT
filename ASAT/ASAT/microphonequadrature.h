#ifndef MICROPHONEQUADRATURE_H
#define MICROPHONEQUADRATURE_H

#include <QFile>
#include <QTextStream>
#include <QVector>
#include "complex"
#include <math.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include "vector"
#include "audiocapture.h"
#include <QDataStream>

#ifndef Q_MOC_RUN
#include <boost/geometry.hpp>
#endif

#include <boost/math/special_functions/bessel.hpp>
#include <boost/math/special_functions/bessel_prime.hpp>
#include <boost/math/special_functions/legendre.hpp>
#include <boost/math/special_functions/hankel.hpp>
#include <boost/math/special_functions/spherical_harmonic.hpp>

#include "lebedevpoints.h"




using namespace boost::geometry;
using namespace boost::math;
using namespace std;

class MicrophoneQuadrature
{



public:
    MicrophoneQuadrature(int size);
    int MicSize;
    double* MicAnglesTheta;
    double* MicAnglesPhi;
    double* SurfaceCoeff;
    QVector<AudioCapture*> wavFilelist;
    void SetArrayEigenmike();
    void SetArrayGaussian(int N);
    void SetArrayEqualAngle(int N);
    complex<double>* sph_harmonics;
    void calcsphericalharmonics(double* pressurevalues);
    void calcsphericalharmonics_c(complex<double> * pressurevalues);
    int numberofsamples;
    int harmonic_size;
    int * MeasureLocation();
    bool havesphericalharmonics;
    void WriteToFile();
    QTextStream *out;
    LebedevPoints m_leb;
    double ComputePressure(double azimuth, double elevation,int maxharmonic);
    double* GeneratePowerMap();



};

#endif // MICROPHONEQUADRATURE_H
