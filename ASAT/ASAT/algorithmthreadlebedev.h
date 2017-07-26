#ifndef ALGORITHMTHREADLEBEDEV_H
#define ALGORITHMTHREADLEBEDEV_H

#include <QThread>
#include <QtCore>
#include "microphonequadrature.h"



class AlgorithmThreadLebedev :public QThread
{
    Q_OBJECT
public:
    explicit AlgorithmThreadLebedev(QObject *parent=0);
    void run();
    bool Stop;
    MicrophoneQuadrature *m_mic;

signals:
    void Calculated(double Pressure,double ver_ang,double sampleno);
};

#endif // ALGORITHMTHREAD_H
