#include "lebedevpoints.h"

using namespace std;
LebedevPoints::LebedevPoints()
{

}



void LebedevPoints::ComputeLebedevPoints(int type,int w,double* we,double* x,double * y,double * z,int* size)
{
    double a = 0.0;
    double b = 0.0;

    if(type == 1)
    {
        x = (double*)malloc(6*sizeof(double));
        y = (double*)malloc(6*sizeof(double));
        z = (double*)malloc(6*sizeof(double));
        we = (double*)malloc(6*sizeof(double));
        *size = 6;
    }
    else if(type == 2)
    {
        x = (double*)malloc(12*sizeof(double));
        y = (double*)malloc(12*sizeof(double));
        z = (double*)malloc(12*sizeof(double));
        we = (double*)malloc(12*sizeof(double));
        *size = 12;
    }
    else
    {
        x = (double*)malloc(8*sizeof(double));
        y = (double*)malloc(8*sizeof(double));
        z = (double*)malloc(8*sizeof(double));
        we = (double*)malloc(8*sizeof(double));
        *size = 8;
    }

    switch ( type ) {
      case 1:
        a = 1.0;
        x[0] = a;
        y[0] = 0.0;
        z[0] = 0.0;
        we[0] = 4.0*PI*w;

        x[1] = (-1) * a;
        y[1] = 0.0;
        z[1] = 0.0;
        we[1] = 4.0*PI*w;

        x[2] = 0.0;
        y[2] = a;
        z[2] = 0.0;
        we[2] = 4.0*PI*w;

        x[3] = 0.0;
        y[3] = (-1) * a;
        z[3] = 0.0;
        we[3] = 4.0*PI*w;

        x[4] = 0.0;
        y[4] = 0.0;
        z[4] = a;
        we[4] = 4.0*PI*w;

        x[5] = 0.0;
        y[5] = 0.0;
        z[5] = (-1) *a;
        we[5] = 4.0*PI*w;

        break;
      case 2:

        a = sqrt(0.5);
        x[0] = 0.0;
        y[0] = a;
        z[0] = a;
        we[0] = 4.0*PI*w;

        x[1] = 0.0;
        y[1] = (-1)*a;
        z[1] = a;
        we[1] = 4.0*PI*w;

        x[2] = 0.0;
        y[2] = a;
        z[2] = (-1)*a;
        we[2] = 4.0*PI*w;

        x[3] = 0.0;
        y[3] = (-1) * a;
        z[3] = (-1)*a;
        we[3] = 4.0*PI*w;

        x[4] = a;
        y[4] = 0.0;
        z[4] = a;
        we[4] = 4.0*PI*w;

        x[5] = a;
        y[5] = 0.0;
        z[5] = (-1) *a;
        we[5] = 4.0*PI*w;

        x[6] = (-1)*a;
        y[6] = 0.0;
        z[6] = a;
        we[6] = 4.0*PI*w;

        x[7] = (-1)*a;
        y[7] = 0.0;
        z[7] = (-1)*a;
        we[7] = 4.0*PI*w;

        x[8] = a;
        y[8] = a;
        z[8] = 0.0;
        we[8] = 4.0*PI*w;

        x[9] = (-1)*a;
        y[9] = a;
        z[9] = 0.0;
        we[9] = 4.0*PI*w;

        x[10] = a;
        y[10] = (-1)*a;
        z[10] = 0.0;
        we[10] = 4.0*PI*w;

        x[11] = (-1)*a;
        y[11] = (-1)*a;
        z[11] = 0.0;
        we[11] = 4.0*PI*w;

        break;
      case 3:
        a = sqrt(1.0/3.0);
        x[0] = a;
        y[0] = a;
        z[0] = a;
        we[0] = 4.0*PI*w;

        x[1] = (-1)*a;
        y[1] = a;
        z[1] = a;
        we[1] = 4.0*PI*w;

        x[2] = a;
        y[2] = (-1)*a;
        z[2] = a;
        we[2] = 4.0*PI*w;

        x[3] = a;
        y[3] = a;
        z[3] = (-1)*a;
        we[3] = 4.0*PI*w;

        x[4] = (-1)*a;
        y[4] = (-1)*a;
        z[4] = a;
        we[4] = 4.0*PI*w;

        x[5] = a;
        y[5] = (-1)*a;
        z[5] = (-1) *a;
        we[5] = 4.0*PI*w;

        x[6] = (-1)*a;
        y[6] = a;
        z[6] = (-1)*a;
        we[6] = 4.0*PI*w;

        x[7] = (-1)*a;
        y[7] = (-1)*a;
        z[7] = (-1)*a;
        we[7] = 4.0*PI*w;

        break;
      }


}
