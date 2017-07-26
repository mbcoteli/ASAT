#ifndef ALGORITHMTHREAD_H
#define ALGORITHMTHREAD_H

#include <QThread>
#include <QtCore>
#include "microphonequadrature.h"


class AlgorithmThread :public QThread
{
    Q_OBJECT
public:
    explicit AlgorithmThread(QObject *parent=0);
    void run();
    bool Stop;
    MicrophoneQuadrature *m_mic;

signals:
    void Calculated(double hor_ang,double ver_ang,double sampleno);
};

#endif // ALGORITHMTHREAD_H
