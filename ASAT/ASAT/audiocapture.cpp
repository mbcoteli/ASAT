#include "audiocapture.h"
typedef unsigned short int HALF;

AudioCapture::AudioCapture()
{


}

// WAVE PCM soundfile format (you can find more in https://ccrma.stanford.edu/courses/422/projects/WaveFormat/ )
typedef struct header_file
{
    char chunk_id[4];
    int chunk_size;
    char format[4];
    char subchunk1_id[4];
    int subchunk1_size;
    short int audio_format;
    short int num_channels;
    int sample_rate;			// sample_rate denotes the sampling rate.
    int byte_rate;
    short int block_align;
    short int bits_per_sample;
    char subchunk2_id[4];
    int subchunk2_size;			// subchunk2_size denotes the number of samples.
} header;

typedef struct header_file* header_p;


AudioCapture::AudioCapture(string path, int seconds)
{

    const char* filePath = path.c_str();

    FILE * infile = fopen(filePath,"rb");		// Open wave file in read mode

    filename = QString::fromStdString(filePath).section("/",-1,-1);

        int BUFSIZE = 2;					// BUFSIZE can be changed according to the frame size required (eg:512)
        int count = 0;						// For counting number of frames in wave file.
        unsigned char buff16[2];				// short int used for 16 bit as input data format is 16 bit PCM audio
        header_p meta = (header_p)malloc(sizeof(header));	// header_p points to a header struct that contains the wave file metadata fields
        int nb;

        // variable storing number of byes returned

        if (infile)
        {
            fread(meta, 1, sizeof(header), infile);
            samplesize = ((meta->subchunk2_size)/2)/meta->num_channels;
            wav_value_ch1 = (double*)malloc(sizeof(double)*(samplesize));
            wav_value_ch2 = (double*)malloc(sizeof(double)*(samplesize));
            sampleno = (double*)malloc(sizeof(double)*(samplesize));

               // optional, as QFile destructor will already do it:

            short c;
            double t;
            int counter =0;
            while (!feof(infile))
            {
                nb = fread(buff16,1,2,infile);		// Reading data in chunks of BUFSIZE

                c = (buff16[1] << 8) | buff16[0];
                    t = c/32768.0;
                *(wav_value_ch1+counter) = t;

                if(meta->num_channels==2)
                {

                nb = fread(buff16,1,2,infile);		// Reading data in chunks of BUFSIZE

                c = (buff16[1] << 8) | buff16[0];
                    t = c/32768.0;

                *(wav_value_ch2+counter) = t;

                }

                *(sampleno+counter) = (double)counter;



                counter++;

            }
        }

}


// find the file size
int AudioCapture::getFileSize(FILE *inFile){
    int fileSize = 0;
    fseek(inFile,0,SEEK_END);

    fileSize=ftell(inFile);

    fseek(inFile,0,SEEK_SET);
    return fileSize;
}
