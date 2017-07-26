#ifndef ALGORITHMTHREADHEALPIX_H
#define ALGORITHMTHREADHEALPIX_H

#include <QThread>
#include <QtCore>
#include "microphonequadrature.h"
#include <math.h>

class algorithmthreadhealpix :public QThread
{
    Q_OBJECT
public:
    explicit algorithmthreadhealpix(QObject *parent=0);
    void run();
    bool Stop;
    MicrophoneQuadrature *m_mic;
    int samplenumber;
    int ResolutionIndex;
    double* ReadAzimuthAngles(int RI);
    double* ReadElevationAngles(int RI);
    int GetLocationSizes(int RI);
    double* MeasuredPowerValues(int locsize,double* AnglesTheta,double* AnglesPhi,int maxharmonic);
    void Compute(complex<double> * sph_harmonics);
    bool RealorSimulation;

signals:
    void Calculated(int locsize, double* Pressure,bool* putvalue,double* Az,double* El);
};

#endif // ALGORITHMTHREADHEALPIX_H
