#ifndef WORKER_H
#define WORKER_H

#include <QObject>
#include "complex"
#include "vector"
#include <boost/math/special_functions/bessel.hpp>
#include <boost/math/special_functions/bessel_prime.hpp>
#include <boost/math/special_functions/legendre.hpp>
#include <boost/math/special_functions/hankel.hpp>
#include <boost/math/special_functions/spherical_harmonic.hpp>

#ifndef Q_MOC_RUN
#include <boost/geometry.hpp>
#endif

#include <iostream>

#define PI 3.141592653589793238462643383279502884197169399375105820974944592307816406286208998628034825342117068


class Worker : public QObject {
     Q_OBJECT
public:
    Worker();
    ~Worker();
public slots:
    void process(int MicPoints, double soundvelocity,double SourceFreq,double SphereRadius,double SourceAngleTheta, double SourceAnglePhi );
signals:
    void finished();
    void error(QString err);
private:

};

#endif // WORKER_H


