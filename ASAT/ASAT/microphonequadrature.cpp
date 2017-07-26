#include "microphonequadrature.h"

#define harmonicsize 25
#define Nharm 5
#define PI 3.141592653589793238462643383279502884197169399375105820974944592307816406286208998628034825342117068
#define BOOST_TT_HAS_OPERATOR_HPP_INCLUDED


using namespace std;
MicrophoneQuadrature::MicrophoneQuadrature(int Size)
{
    MicSize = Size;


    MicAnglesTheta = (double*) malloc(MicSize * sizeof(double));
    MicAnglesPhi = (double*) malloc(MicSize * sizeof(double));
    SurfaceCoeff = (double*) malloc(MicSize * sizeof(double));

    harmonic_size =harmonicsize;

    sph_harmonics = (complex<double>*) malloc(harmonicsize * sizeof(complex<double>));

    havesphericalharmonics = false;

    QString fileName = "results.txt";
    QFile file(fileName);

        if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
            return;

    out= new QTextStream(&file);

}



void MicrophoneQuadrature::SetArrayEigenmike()
{

    //Eigenmike Microphone Array


        QFile filemic("C:\\Spatial_audio\\angles.txt");

        filemic.open(QIODevice::ReadOnly | QIODevice::Text);

        QTextStream inmic(&filemic);

        this->MicSize = 32;

        this->MicAnglesTheta = (double*) malloc(this->MicSize * sizeof(double));
        this->MicAnglesPhi = (double*) malloc(this->MicSize * sizeof(double));
        this->SurfaceCoeff = (double*) malloc(this->MicSize * sizeof(double));

        QVector<AudioCapture*> wavFile = (QVector<AudioCapture*>(this->MicSize));

        wavFilelist = wavFile;

        for(int i = 0; i < MicSize; ++i)
                {
              QString line = inmic.readLine();

              QVector<QString> var = line.split(" ").toVector();

              int count = 0;

              for(int kl=0; kl< var.size();kl++)
                    {
                    if(var.at(kl)!="")
                        {

                            if(count==0)
                            {
                                *(this->MicAnglesTheta+i)= var.at(kl).toDouble();
                            }
                            else if(count==1)
                            {
                                *(this->MicAnglesPhi+i)= var.at(kl).toDouble();
                            }
                            else
                            {
                                *(this->SurfaceCoeff+i)= var.at(kl).toDouble();
                            }
                            count++;
                        }
                    }
                }


}

// Total number of 2 *(N+1)^2 microphones
// (N+1) in elevation, 2*(N+1) in azimuth
void MicrophoneQuadrature::SetArrayGaussian(int N)
{

    //Gaussian Quadrature
    int Theta_nofMic = N+1;
    int Phi_nofMic = 2 * (N+1);
    this->MicSize = Theta_nofMic *Phi_nofMic;

    this->MicAnglesTheta = (double*) malloc(this->MicSize * sizeof(double));
    this->MicAnglesPhi = (double*) malloc(this->MicSize * sizeof(double));
    this->SurfaceCoeff = (double*) malloc(this->MicSize * sizeof(double));

     QVector<AudioCapture*> wavFile = (QVector<AudioCapture*>(this->MicSize));

     wavFilelist = wavFile;


        for(int i = 0; i < Theta_nofMic; ++i)
                {
             for(int kl = 0; kl < Phi_nofMic; ++kl)
                    {
                   *(this->MicAnglesTheta+i*Phi_nofMic+kl) = (PI / ((double)N+1)) *(double)i;

                   double cos_theta_q = cos(*(this->MicAnglesTheta+i*Phi_nofMic+kl));

                   *(this->MicAnglesPhi+i*Phi_nofMic+kl)= (PI / ((double)N+1)) *(double)kl;

                   double coef1 = (PI / ((double)N+1));

                   double coef2 = (2* (1-pow(cos_theta_q,2)));

                   double coef3 =(((double)pow((double)N+2,2))*legendre_p(((double)N+2),2,cos_theta_q));

                   *(this->SurfaceCoeff+i*Phi_nofMic+kl)= (double)( coef1* coef2 / coef3);
                    }
                }
}


void WriteToFile()
{



}

void MicrophoneQuadrature::calcsphericalharmonics_c(complex<double> * pressurevalues)
{


    complex<double> zeroval(0,0);

    for(int km =0;km < harmonicsize ; km++)
    {

        *(sph_harmonics+km) = zeroval;

    }

    for(int ml=0;ml < MicSize;ml++)
    {

         model::point<long double, 2, cs::spherical<degree> > p1((*(this->MicAnglesTheta+ml)*PI/180),(*(this->MicAnglesPhi+ml)*PI/180));

         int counter = 0;

         for(int sph_n=0;sph_n < Nharm;sph_n++)
           {

                    for(int sph_m= ((-1)*sph_n) ; sph_m <= sph_n ;sph_m++)
                        {

                            complex<double> calcharmonic =  (complex<double>)boost::math::spherical_harmonic(sph_n,sph_m,get<0>(p1),get<1>(p1));


                            complex<double> harmonic = conj(calcharmonic);

                            *(sph_harmonics+counter) += ((complex<double>)(pressurevalues[ml].real())) * harmonic  * ((complex<double>)*(this->SurfaceCoeff+ml));

                            counter++;

                        }
          }


    }
    havesphericalharmonics =true;

    return;

}

void MicrophoneQuadrature::calcsphericalharmonics(double* pressurevalues)
{


    complex<double> zeroval(0,0);

    for(int km =0;km < harmonicsize ; km++)
    {

        *(sph_harmonics+km) = zeroval;

    }

int counter = 0;


for(int ml=0;ml < MicSize;ml++)
{

         for(int sph_n=0;sph_n < Nharm;sph_n++)
           {

                    for(int sph_m= ((-1)*sph_n) ; sph_m <= sph_n ;sph_m++)
                        {


                             model::point<double, 2, cs::spherical<degree> > p1((*(this->MicAnglesTheta+ml)*PI/180),(*(this->MicAnglesPhi+ml)*PI/180));

                            complex<double> calcharmonic =  (complex<double>)boost::math::spherical_harmonic(sph_n,sph_m,get<0>(p1),get<1>(p1));


                            complex<double> harmonic = conj(calcharmonic);

                            *(sph_harmonics+counter) += ((complex<double>)(pressurevalues[ml])) * harmonic  * ((complex<double>)*(this->SurfaceCoeff+ml));

                            counter++;

                        }
          }


    }
    havesphericalharmonics =true;

    return;

}


double MicrophoneQuadrature::ComputePressure(double azimuth, double elevation,int maxharmonic)
{
    if(!havesphericalharmonics)
        return 0;

    model::point<long double, 2, cs::spherical<radian> > p2(elevation,azimuth);

    complex<double> zeroval(0,0);

    complex<double> valuecalc = zeroval;

    int counter = 0;

    for(int sph_n=0;sph_n < maxharmonic;sph_n ++)
           {

               for(int sph_m= -sph_n ; sph_m <= sph_n ;sph_m++)
                   {

                       complex<double> harmonic = (complex<double>)boost::math::spherical_harmonic(sph_n,sph_m,get<0>(p2),get<1>(p2));

                       valuecalc += (complex<double>)(*(this->sph_harmonics+counter)) * harmonic  ;

                       counter++;

                  }
         }

    if(valuecalc.real()>0)
        return valuecalc.real()*valuecalc.real();
    else
        return 0;



}

double* MicrophoneQuadrature::GeneratePowerMap()
{
    if(!havesphericalharmonics)
        return 0;

    double* computedval = (double*)calloc(360*180,sizeof(double));

    QFile file("out.txt");
        if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
            return 0;

        QTextStream out(&file);



     for(int cnt =0; cnt < 180;cnt++)
     {

         for(int phicnt =0; phicnt < 360;phicnt++)
         {

        complex<double> computation(0,0);

        model::point<double, 2, cs::spherical<radian> > p1(((double)cnt)*PI/180,((double)phicnt)*PI/180);

        int counter =0;

        for(int sph_n=0;sph_n < 5;sph_n ++)
               {

                   for(int sph_m= ((-1) *sph_n) ; sph_m <= sph_n ;sph_m++)
                       {

                           complex<double> harmonic = (complex<double>)boost::math::spherical_harmonic(sph_n,sph_m,get<0>(p1),get<1>(p1));

                           computation += (*(sph_harmonics+counter)) * harmonic  ;

                           counter++;

                      }
             }
    if(computation.real()>0  )
        *(computedval+cnt*360+phicnt) = computation.real()*computation.real();

        out << *(computedval+cnt*360+phicnt) << " ";

     }
        out << "\n";
    }


    return computedval;


}

int* MicrophoneQuadrature::MeasureLocation()
{
    if(!havesphericalharmonics)
        return 0;

    int * angles =(int*) malloc(6 * sizeof(int));
    double maxvalue[3];
    maxvalue[0] =0;
    maxvalue[1] =0;
    maxvalue[2] =0;

    complex<double> zeroval(0,0);

    double *we;
    double *x;
    double *y;
    double *z;
    int size;





    m_leb.ComputeLebedevPoints(1,0,we,x,y,z,&size);


    for(int k=0;k < size;k++)
    {

         model::point<long double, 3, cs::cartesian> p3(x[k],y[k],z[k]);
         model::point<long double, 2, cs::spherical<radian> > p2;
         transform(p3, p2);


         int counter =0;

         complex<double> valuecalc = zeroval;

         for(int sph_n=0;sph_n < 5;sph_n ++)
                {

                    for(int sph_m= -sph_n ; sph_m <= sph_n ;sph_m++)
                        {

                            complex<double> harmonic = (complex<double>)spherical_harmonic(sph_n,sph_m,get<0>(p2),get<1>(p2));

                            valuecalc += (complex<double>)(*(sph_harmonics+counter)) * harmonic  ;

                            counter++;

                       }
              }

         if(abs(valuecalc) > maxvalue[0])
         {

             maxvalue[0] = abs(valuecalc);
             angles[0] = get<1>(p2);
             angles[1] = get<0>(p2);

         }
         else if(abs(valuecalc) > maxvalue[1])
         {
             maxvalue[1] = abs(valuecalc);
             angles[2] = get<1>(p2);
             angles[3] = get<0>(p2);


         }
         else if(abs(valuecalc) > maxvalue[2])
         {

             maxvalue[2] = abs(valuecalc);
             angles[4] = get<1>(p2);
             angles[5] = get<0>(p2);

         }


     }



    return angles;



}
