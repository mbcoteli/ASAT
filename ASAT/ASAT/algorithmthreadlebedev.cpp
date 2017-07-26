#include "algorithmthreadlebedev.h"


AlgorithmThreadLebedev::AlgorithmThreadLebedev(QObject *parent):QThread(parent)
{

}


void AlgorithmThreadLebedev::run()
{
    int hor_ang;
    int ver_ang;
    int sampleno;
    QMutex mutex;

    int totalnumberofmic = m_mic->MicSize;
    int samplesize = m_mic->wavFilelist[0]->samplesize;

    double* values = (double*)malloc(totalnumberofmic*sizeof(double));

    for(int ml=0;ml<samplesize;ml++)
    {
    mutex.lock();

        for(int kl =0;kl < totalnumberofmic ; kl++)
        {

            *(values+kl) = abs(*(m_mic->wavFilelist[kl]->wav_stft_ch1+ml));

        }

    m_mic->calcsphericalharmonics(values);

    int* result = m_mic->MeasureLocation();

    emit Calculated((double)result[0],(double)result[1],(double)ml);

   this->msleep(1);

    mutex.unlock();

    }




}
