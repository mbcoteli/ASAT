#ifndef AUDIOCAPTURE_H
#define AUDIOCAPTURE_H

#include <iostream>
#include <string>
#include <fstream>
#include <QString>

#include <QFile>
#include <QCoreApplication>
#include <QTextStream>

#include "complex"


using namespace std;
using std::string;
using std::fstream;

class AudioCapture
{

typedef struct  WAV_HEADER{
    char                RIFF[4];        // RIFF Header      Magic header
    unsigned long       ChunkSize;      // RIFF Chunk Size
    char                WAVE[4];        // WAVE Header
    char                fmt[4];         // FMT header
    unsigned long       Subchunk1Size;  // Size of the fmt chunk
    unsigned short      AudioFormat;    // Audio format 1=PCM,6=mulaw,7=alaw, 257=IBM Mu-Law, 258=IBM A-Law, 259=ADPCM
    unsigned short      NumOfChan;      // Number of channels 1=Mono 2=Sterio
    unsigned long       SamplesPerSec;  // Sampling Frequency in Hz
    unsigned long       bytesPerSec;    // bytes per second
    unsigned short      blockAlign;     // 2=16-bit mono, 4=16-bit stereo
    unsigned short      bitsPerSample;  // Number of bits per sample
    char                Subchunk2ID[4]; // "data"  string
    unsigned long       Subchunk2Size;  // Sampled data length

    }wav_hdr;
public:
    FILE *wavFile;
    wav_hdr wavHeader;
    AudioCapture();
    AudioCapture(string path, int seconds);
    int filelength;
    QString filename;
    char * wavdata;
    double  * wav_value_ch1;
    double  * wav_value_ch2;
    double  * sampleno;
    complex<double> * wav_stft_ch1;
    complex<double>  * wav_stft_ch2;
    int samplesize;
    int fftsize;
    // Function prototypes
    int getFileSize(FILE *inFile);
};

#endif // AUDIOCAPTURE_H
