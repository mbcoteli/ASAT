#ifndef LEBEDEVPOINTS_H
#define LEBEDEVPOINTS_H

#include <math.h>
#include <stdio.h>
#include <iostream>

#define PI 3.141592653589793238462643383279502884197169399375105820974944592307816406286208998628034825342117068



class LebedevPoints
{
public:
    LebedevPoints();
    void ComputeLebedevPoints(int type,int w,double* we,double* x,double * y,double * z,int* size);
};

#endif // LEBEDEVPOINTS_H
