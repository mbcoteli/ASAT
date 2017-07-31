#include "algorithmthreadhealpix.h"

algorithmthreadhealpix::algorithmthreadhealpix(QObject *parent):QThread(parent)
{


}

void algorithmthreadhealpix::Compute(complex<double> * sph_harmonics)
{
    int locsizeRI1 = GetLocationSizes(16);
    double* AnglesThetaRI1 = ReadElevationAngles(16);
    double* AnglesPhiRI1 = ReadAzimuthAngles(16);


    memcpy(m_mic->sph_harmonics,sph_harmonics,25 * sizeof(complex<double>));

    m_mic->havesphericalharmonics =true;

    double* measuredpressuresRI1 =  MeasuredPowerValues(locsizeRI1,AnglesThetaRI1,AnglesPhiRI1,5);


    QFile file("HealpixComputation.txt");
    file.open(QIODevice::ReadWrite);
    QTextStream stream(&file);

    for(int km =0;km < 3072;km++)
    {
        stream << (double)*(measuredpressuresRI1+km) << endl;
    }

    file.close();

}

bool* ComputePSEHealpix(double* currlevel, int currlevind,double* lowerlev,bool* prevmask)
{
    bool* resultPSE = (bool *)calloc(currlevind , sizeof(bool));
    double* PSE = (double *)calloc(currlevind , sizeof(double));
    double* useval = (double *)calloc(currlevind , sizeof(double));
    double PSEvalue = 0;
    double PSESum = 0;
    double* PressureSum = (double *)calloc(12 , sizeof(double));



    // PSESum is summation of all pixel values
    // Psum = p1+p2+p3....+pN
    for(int sm=0;sm <currlevind;sm++)
    {
        if(currlevel[sm]!=0)
        PSESum += (currlevel[sm]);

    }

    //PSE is calculated using the formula
    // PSEbefore = (p1/Psum) * log(p1/Psum) + (p2/Psum) * log(p2/Psum) +...
    //               (pN/Psum) * log(pN/Psum)

    for(int sm=0;sm <currlevind;sm++)
    {
        if(currlevel[sm]!=0)
        PSEvalue += (currlevel[sm] /PSESum) * log((currlevel[sm]/PSESum ));

    }

    // Compute if a pixel is divided into 4 equal area.
    // get higher RI values and average
    // p = (p1 + p2 + p3+ p4) / 4
    for(int iter =0; iter <currlevind;iter++)
    {
        for(int kml =0;kml <4;kml++)
        {
               useval[iter] = useval[iter] + lowerlev[kml+(iter)*4];
        }
        double comp = useval[iter] /4;
        useval[iter] =comp;
    }

    double differenceval;

    for(int iterin =0; iterin < currlevind;iterin++)
    {
        PSESum = 0;

        // Get summation if a pixel is divided.
        // If pixel 0 is divided what will happen,
        // If pixel 1 is divided what will happen
        for(int sm=0;sm <currlevind;sm++)
        {
            if(iterin == sm)
                PSESum += useval[sm];
            else
                PSESum += (currlevel[sm]);
        }

        // Compute the PSE value if the pixel is divided into 4 equal areas.
        // PSEafter_division = (p1/Psum) * log(p1/Psum) + (p2/Psum) * log(p2/Psum)
        //    +...+(pN/Psum) * log(pN/Psum)

        for(int kml =0;kml <currlevind;kml++)
        {

            if(iterin==kml && useval[kml]!=0)
                PSE[kml] += (useval[kml]/PSESum) * log((useval[kml]/PSESum));
            else if(iterin!=kml && currlevel[kml]!=0)
                PSE[kml] += (currlevel[kml]/PSESum) * log((currlevel[kml]/PSESum));
        }



    }

    for(int iterin =0; iterin < currlevind;iterin++)
    {
    differenceval = PSE[iterin] -PSEvalue;
    if(differenceval  < 0)
    {
      resultPSE[iterin] =true;
    }
    else
    {
      resultPSE[iterin] =false;
    }

    if((!prevmask[iterin/4]))
       resultPSE[iterin] =false;

    }


   /* int workingpixel =  currlevind/12;
    for(int km=0;km < 12;km++)
    {
    int count = 0;
    for(int sm=km*workingpixel;sm <(km+1)*workingpixel;sm++)
    {
        if((PressureSum[km] <currlevel[sm]))
        {
            PressureSum[km] = (currlevel[sm]);
        }

    }
    PressureSum[km] /= 1.41;
    }



    for(int kml =0;kml <currlevind;kml++)
    {
    if((currlevel[kml] < (PressureSum[kml/workingpixel])) && resultPSE[kml])
       resultPSE[kml] =false;
    }*/
    return resultPSE;


}

void algorithmthreadhealpix::run()
{

    if(RealorSimulation==1)
    {
    int totalnumberofmic = m_mic->MicSize;
    int samplesize = m_mic->wavFilelist[0]->samplesize;

    complex<double>* values = (complex<double>*)malloc(totalnumberofmic*sizeof(complex<double>));


        for(int kl =0;kl < totalnumberofmic ; kl++)
        {

            *(values+kl) = *(m_mic->wavFilelist[kl]->wav_stft_ch1+samplenumber);

        }

    m_mic->calcsphericalharmonics_c(values);
}
   double sumRI1 = 0;
   double avr =0;

   int locsizeRI1 = GetLocationSizes(1);
   double* AnglesThetaRI1 = ReadElevationAngles(1);
   double* AnglesPhiRI1 = ReadAzimuthAngles(1);

   double* measuredpressuresRI1 =  MeasuredPowerValues(locsizeRI1,AnglesThetaRI1,AnglesPhiRI1,2);

   int locsizeRI2 = GetLocationSizes(2);
   double* AnglesThetaRI2 = ReadElevationAngles(2);
   double* AnglesPhiRI2 = ReadAzimuthAngles(2);

   double* measuredpressuresRI2 =  MeasuredPowerValues(locsizeRI2,AnglesThetaRI2,AnglesPhiRI2,3);

   int locsizeRI3 = GetLocationSizes(4);
   double* AnglesThetaRI3 = ReadElevationAngles(4);
   double* AnglesPhiRI3 = ReadAzimuthAngles(4);

   double* measuredpressuresRI3 =  MeasuredPowerValues(locsizeRI3,AnglesThetaRI3,AnglesPhiRI3,4);

   int locsizeRI4 = GetLocationSizes(8);
   double* AnglesThetaRI4 = ReadElevationAngles(8);
   double* AnglesPhiRI4 = ReadAzimuthAngles(8);

   double* measuredpressuresRI4 =  MeasuredPowerValues(locsizeRI4,AnglesThetaRI4,AnglesPhiRI4,5);

   int locsizeRI5 = GetLocationSizes(16);
   double* AnglesThetaRI5 = ReadElevationAngles(16);
   double* AnglesPhiRI5 = ReadAzimuthAngles(16);

   double* measuredpressuresRI5 =  MeasuredPowerValues(locsizeRI5,AnglesThetaRI5,AnglesPhiRI5,5);

   int locsizeRI6 = GetLocationSizes(32);
   double* AnglesThetaRI6 = ReadElevationAngles(32);
   double* AnglesPhiRI6 = ReadAzimuthAngles(32);

   double* measuredpressuresRI6 =  MeasuredPowerValues(locsizeRI6,AnglesThetaRI6,AnglesPhiRI6,5);
   bool* result = (bool*)malloc(3*sizeof(bool));

   result[0] = true;
   result[1] = true;
   result[2] = true;


   result = ComputePSEHealpix(measuredpressuresRI1,locsizeRI1,measuredpressuresRI2,result);

   emit Calculated(locsizeRI1,measuredpressuresRI1,result,AnglesPhiRI1,AnglesThetaRI1);
   //this->msleep(1000);

   result = ComputePSEHealpix(measuredpressuresRI2,locsizeRI2,measuredpressuresRI3,result);

   emit Calculated(locsizeRI2,measuredpressuresRI2,result,AnglesPhiRI2,AnglesThetaRI2);
   //this->msleep(1000);

   result = ComputePSEHealpix(measuredpressuresRI3,locsizeRI3,measuredpressuresRI4,result);

   emit Calculated(locsizeRI3,measuredpressuresRI3,result,AnglesPhiRI3,AnglesThetaRI3);
  // this->msleep(1000);

   result = ComputePSEHealpix(measuredpressuresRI4,locsizeRI4,measuredpressuresRI5,result);

   emit Calculated(locsizeRI4,measuredpressuresRI4,result,AnglesPhiRI4,AnglesThetaRI4);
   //this->msleep(1000);

   result = ComputePSEHealpix(measuredpressuresRI5,locsizeRI5,measuredpressuresRI6,result);

   emit Calculated(locsizeRI5,measuredpressuresRI5,result,AnglesPhiRI5,AnglesThetaRI5);
   //this->msleep(1000);
}

double* algorithmthreadhealpix::MeasuredPowerValues(int locsize,double* AnglesTheta,double* AnglesPhi,int maxharmonic)
{
    double* measuredpressures = (double*)malloc(locsize * sizeof(double));
    double* pixelnum = (double*)malloc(locsize * sizeof(double));

    for(int kml =0;kml<locsize;kml++)
    {
        double cmptpress = m_mic->ComputePressure(*(AnglesPhi+kml),*(AnglesTheta+kml),maxharmonic);
        *(measuredpressures+kml) = cmptpress;
        *(pixelnum+kml) = kml;
    }

    return measuredpressures;
}

int algorithmthreadhealpix::GetLocationSizes(int RI)
{

    switch( RI)
    {
            case 1 :
                return 12;
            case 2 :
                return 48;
            case 4 :
                return 192;
            case 8 :
                return 768;
            case 16:
                return 3072;
            case 32:
                return 12288;
            case 64:
                return 49152;
            default :
        break;
    }


}

double* algorithmthreadhealpix::ReadAzimuthAngles(int RI)
{

    int locsize = 12;
    double * PSE;
    QString s;
    PSE = (double*)malloc(1*sizeof(double));
    if(RI==1)
    {
            s = "HealpixCoordinates\\RI1.txt";
            locsize = 12;

    }
    else if(RI==2)
    {
         s = "HealpixCoordinates\\RI2.txt";
        locsize = 48;

    }
    else if(RI==4)
    {
         s = "HealpixCoordinates\\RI4.txt";
        locsize = 192;

    }
    else if(RI==8)
    {
         s = "HealpixCoordinates\\RI8.txt";
        locsize = 768;

    }
    else if(RI==16)
    {
         s = "HealpixCoordinates\\RI16.txt";
        locsize = 3072;

    }
    else if(RI==32)
    {
         s = "HealpixCoordinates\\RI32.txt";
        locsize = 12288;

    }
    else if(RI==64)
    {
         s = "HealpixCoordinates\\RI64.txt";
        locsize = 49152;

    }
    QFile RIFile(s);

    RIFile.open(QIODevice::ReadOnly | QIODevice::Text);

    QTextStream inpos(&RIFile);


    double *AnglesPhi = (double*) malloc(locsize * sizeof(double));

    for(int i = 0; i < locsize; ++i)
            {
          QString line = inpos.readLine();

          QVector<QString> var = line.split(" ").toVector();

          int count = 0;

          for(int kl=0; kl< var.size();kl++)
                {
                if(var.at(kl)!="")
                    {

                        if(count==1)
                        {
                            *(AnglesPhi+i)= var.at(kl).toDouble();
                        }
                        count++;
                    }
                }
            }
    return AnglesPhi;

}

double* algorithmthreadhealpix::ReadElevationAngles(int RI)
{

    int locsize = 12;
    double * PSE;
    QString s;
    PSE = (double*)malloc(1*sizeof(double));
    if(RI==1)
    {
            s = "HealpixCoordinates\\RI1.txt";
            locsize = 12;

    }
    else if(RI==2)
    {
         s = "HealpixCoordinates\\RI2.txt";
        locsize = 48;

    }
    else if(RI==4)
    {
         s = "HealpixCoordinates\\RI4.txt";
        locsize = 192;

    }
    else if(RI==8)
    {
         s = "HealpixCoordinates\\RI8.txt";
        locsize = 768;

    }
    else if(RI==16)
    {
         s = "HealpixCoordinates\\RI16.txt";
        locsize = 3072;

    }
    else if(RI==32)
    {
         s = "HealpixCoordinates\\RI32.txt";
        locsize = 12288;

    }
    else if(RI==64)
    {
         s = "HealpixCoordinates\\RI64.txt";
        locsize = 49152;

    }
    QFile RIFile(s);

    RIFile.open(QIODevice::ReadOnly | QIODevice::Text);

    QTextStream inpos(&RIFile);


    double *AnglesTheta = (double*) malloc(locsize * sizeof(double));

    for(int i = 0; i < locsize; ++i)
            {
          QString line = inpos.readLine();

          QVector<QString> var = line.split(" ").toVector();

          int count = 0;

          for(int kl=0; kl< var.size();kl++)
                {
                if(var.at(kl)!="")
                    {

                        if(count==0)
                        {
                            *(AnglesTheta+i)= var.at(kl).toDouble();
                        }
                        count++;
                    }
                }
            }
    return AnglesTheta;

}





