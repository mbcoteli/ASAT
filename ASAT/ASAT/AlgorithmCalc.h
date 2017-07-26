#include <math.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include "complex"
#include "vector"


#define BOOST_TT_HAS_OPERATOR_HPP_INCLUDED

#ifndef Q_MOC_RUN  // See: https://bugreports.qt-project.org/browse/QTBUG-22829
#include <boost/geometry.hpp>
#endif

#include <boost/math/special_functions/bessel.hpp>
#include <boost/math/special_functions/bessel_prime.hpp>
#include <boost/math/special_functions/legendre.hpp>
#include <boost/math/special_functions/hankel.hpp>
#include <boost/math/special_functions/spherical_harmonic.hpp>



using namespace boost::math;
using namespace std;
using namespace boost::geometry;

class AlgorithmCalc
{


public:
double CalcMagnitude(std::complex<float> harmonic);
void CalculatePressureValues(complex<double>* pressure,int MicSize,double* SourceLoc,double* MicLoc,double kr);
float DotProduct(float * loc1, float *loc2);
float Distance3D(float *loc,float* loc2);
static void CalculateMicAnglesEqualPos(float* MicPos,float* MicAngles, float* SphereCenter, int NofMic,float radius);
float* CalculatePseudoIntensityVector(complex<float> * coefficients);



#define PI 3.141592653589793238462643383279502884197169399375105820974944592307816406286208998628034825342117068

float Vsound = 343;


//Sound speed in m/s


float SphereRadius,krs,kval,lambda_n,SamplingFreq,FFTBins;

int samplesize,MicSize,Nharm =3;

float angleval ;

float sampleval ;

complex<float> coefficients_fnm[25];
complex<float>* sphericalharmonic;
complex<float>* coefficients ;
complex<float>* pressurevalues;

float* MicPositions;

float* MicAng;

float* SourceCoordinates;



void SetCoordinates(float * Coordinates)
{

    SourceCoordinates = Coordinates;



}



double CalcMagnitude(complex<float> harmonic)
{

    return sqrt(harmonic.real() *harmonic.real() + harmonic.imag() *harmonic.imag());

}

void CalculateMicAnglesEqualPos(float* MicPos,float* MicAngles, int NofMic,float radius)
{
    //Define the microphone positions with the angles theta and phi in spherical coordinates
    float theta,phi;

    for(int ml=0;ml<NofMic;ml++)
    {
        //Theta angle with [-PI,PI]
        theta =	(-1) *PI + (PI /NofMic) *ml *2;
        //Theta angle with [-PI/2,PI/2]
        phi = (-1) * (PI /2) + (PI /NofMic) *ml;

        model::point<float, 3, cs::cartesian> point1;
        model::point<long double, 2, cs::spherical<radian> > p2(theta,phi);
        transform(p2,point1);

        *(MicPos+(ml*3)) = get<0>(point1)  *radius *0.01;
        *(MicPos+(ml*3)+1) = get<1>(point1) *radius *0.01;
        *(MicPos+(ml*3)+2) = get<2>(point1) *radius *0.01;

        *(MicAngles+(ml*2)) = theta;
        *(MicAngles+(ml*2)+1) = phi;

    }

    MicAng = MicAngles;
    MicPositions = MicPos;


}


void CalculatePressureValues(complex<double>* pressure,int MicPoint,double* SourceLoc,double* MicLoc,double kr) // initialize with entries 0..100)
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



complex<double>* SimulatePlanewave(int NFFT,double rm,double ds, double rs,int order,double t)
{

        double                 *r, *w, *k, *krm, *krs, *kds;
        double                 maxw, maxk, iteratew, iteratek,iteratem, iterates, iterated;
        complex<double>        **OutputArray, **rfArray;
        complex<double>        timeShift, SHresult,*result;

        w      = new double [NFFT];
        k      = new double [NFFT];
        krm    = new double [NFFT];
        krs    = new double [NFFT];
        kds    = new double [NFFT];


        maxw     = PI*SamplingFreq;
        maxk     = PI*SamplingFreq/Vsound;

        iteratew = maxw/(NFFT-1);
        iteratek = maxk/(NFFT-1);
        iteratem = maxk*rm/(NFFT-1);
        iterates = maxk*rs/(NFFT-1);
        iterated = maxk*ds/(NFFT-1);

        w[0]   = 0;
        k[0]   = 0;
        krm[0] = 0;
        krs[0] = 0;
        kds[0] = 0;

        for(int ctr=1; ctr<NFFT; ctr++)
        {
            w[ctr]      = w[ctr-1]+iteratew;
            k[ctr]      = k[ctr-1]+iteratek;
            krm[ctr]    = krm[ctr-1]+iteratem;
            krs[ctr]    = krs[ctr-1]+iterates;
            kds[ctr]    = kds[ctr-1]+iterated;
        }

        krm[0] = krm[1];
        krs[0] = krs[1];
        kds[0] = kds[1];

        int NMLocatorSize = (order+1) * (order+1);

        //Allocate Output Array Size [(N+1)^2]*[FFTBins]
        OutputArray = new complex<double>*[NMLocatorSize];

        for(int ctr = 0; ctr < NMLocatorSize; ctr++)
           {OutputArray[ctr] = new complex<double>[NFFT];}


        //Initializate Output Array
        for(int ctr = 0; ctr < NMLocatorSize; ctr++)
           {
            for(int ctrb = 0; ctrb < NFFT; ctrb++)
               {
                    OutputArray[ctr][ctrb] = complex<double>(0,0);
               }
           }

        //Allocate bn Array Size [N+1]*[NFFT]
         rfArray = new complex<double>*[order+1];

         for(int ctr = 0; ctr < (order+1); ctr++)
                  {rfArray[ctr] = new complex<double>[NFFT];}


               //Initializate bn Array
               for(int ctr = 0; ctr < (order+1); ctr++)
                  {
                   for(int ctrb = 0; ctrb < NFFT; ctrb++)
                      {
                           rfArray[ctr][ctrb] = complex<double>(0,0);
                      }
                  }


               for(int f = 0; f <= (NFFT-1); f++) //PLANE WAVE
                      {
                         timeShift = exp(complex<double>(0,-1)*complex<double>(w[f]*t,0));

                         for(int n = 0; n <= order; n++)
                         {
                          //  rfArray[n][f] = bn(n, krm[f], krs[f], ac)*timeShift;
                         }
                      }

return result;

}
float* CalculatePseudoIntensityVector(complex<float> * coefficients)
{

    float* degree = (float*)malloc(2 * sizeof(float));

    float minvalue = 0;

    complex<float> harmonic;



for(int ml=0; ml < 360 ;ml++)
{



    complex<float> value(0,0);

    float theta = -PI + (float)ml * PI / (float)180;

    float phi = -PI/2.0 + (float)90 * PI / (float)180;

    model::point<long double, 2, cs::spherical<radian> > p2(theta,phi);

    int counter =0;

    for(int sph_n=0;sph_n < Nharm;sph_n ++)
                {

                    for(int sph_m= -sph_n ; sph_m <= sph_n ;sph_m++)

                    {

                        harmonic  = (complex<float>)spherical_harmonic(sph_n,sph_m,get<0>(p2),get<1>(p2));

                        value +=  harmonic * coefficients[counter] * harmonic * coefficients[counter];

                        counter++;
                    }
                }


        if((float)abs(value) > minvalue)
        {
            minvalue = (float)abs(value);
            degree[0] = theta *180 /PI;
            degree[1] = phi *180 / PI;
        }


}



   return degree;


}

float DotProduct(float * loc1, float *loc2)
{

    return (float)((*loc1) * (*(loc2))+ (*(loc1+1)) * (*(loc2+1))+ (*(loc1+2)) * (*(loc2+2)));

}

float Distance3D(float *loc,float* loc2)
{


    float dist1 = sqrt( pow(*(loc)-*(loc2),2)+pow(*(loc+1)-*(loc2+1),2));

    float dist2 = sqrt( pow(dist1,2)+pow(*(loc+2)-*(loc2+2),2));

    return dist2;


}
}
