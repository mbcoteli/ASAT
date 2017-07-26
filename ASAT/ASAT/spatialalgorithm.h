#ifndef SPATIALALGORITHM_H
#define SPATIALALGORITHM_H

#include <math.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include "complex"
#include "vector"
#include <boost/math/special_functions/bessel.hpp>
#include <boost/math/special_functions/bessel_prime.hpp>
#include <boost/math/special_functions/legendre.hpp>
#include <boost/math/special_functions/hankel.hpp>
#include <boost/math/special_functions/spherical_harmonic.hpp>
#include <boost/geometry.hpp>

#define PI 3.141592653589793238462643383279502884197169399375105820974944592307816406286208998628034825342117068

using namespace boost::math;
using namespace std;
using namespace boost::geometry;


class SpatialAlgorithm
{
public:
    SpatialAlgorithm(int Harmonic);
    void CalculatePressureValues(complex<double>* pressure,int MicSize,double* SourceLoc,double* MicLoc,double kr);
private:
    int Nharm;


};

SpatialAlgorithm::SpatialAlgorithm(int Harmonic)
{
    Nharm = Harmonic;


}

void SpatialAlgorithm::CalculatePressureValues(complex<double>* pressure,int MicPoint,double* SourceLoc,double* MicLoc,double kr) // initialize with entries 0..100)
{



    model::point<long double, 2, cs::spherical<radian> > p1((*(SourceLoc)*PI/180),(*(SourceLoc+1)*PI/180));

    complex<double> comple(0,1);

    complex<double> zeroval(0,0);

    for(int ml=0;ml < MicPoint;ml++)
    {

        *(pressure+ml) = zeroval;

 model::point<long double, 2, cs::spherical<radian> > p2((*(MicLoc+(ml*2))*PI/180),(*(MicLoc+(ml*2)+1)*PI/180));

 int counter = 0;

 for(int sph_n=0;sph_n < Nharm;sph_n ++)
        {

            for(int sph_m= -sph_n ; sph_m <= sph_n ;sph_m++)
                {

                    complex<double> calcharmonicsource =  conj((complex<double>)spherical_harmonic(sph_n,sph_m,get<0>(p1),get<1>(p1)));
                    complex<double> besselfunc = sph_bessel(sph_n,kr);
                    complex<double> besselfuncprime = sph_bessel_prime(sph_n,kr);
                    complex<double> hankelfunc = sph_hankel_2(sph_n,kr);
                    complex<double> hankelfuncprime;
                    if(sph_n==0)
                    {

                        hankelfuncprime = 0.5 * (-1) * (sph_hankel_2(sph_n,kr) + kr * sph_hankel_2(sph_n+1,kr)) / kr;
                    }
                    else
                    {

                        hankelfuncprime = 0.5 *  (sph_hankel_2(sph_n-1,kr) - (sph_hankel_2(sph_n,kr) + kr * sph_hankel_2(sph_n+1,kr))/kr);

                    }


                    complex<double> bnm = 4* PI *pow(comple, sph_n) * (besselfunc - (besselfuncprime/hankelfuncprime) *hankelfunc );

                    complex<double> micsph_harmonic = (complex<double>)spherical_harmonic(sph_n,sph_m,get<0>(p2),get<1>(p2));


                    *(pressure+ml) += ((complex<double>) calcharmonicsource * bnm * micsph_harmonic);

                }
       }
    }


}

#endif // SPATIALALGORITHM_H
