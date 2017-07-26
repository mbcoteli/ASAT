#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QCoreApplication>

#include "fftw3.h"






#define PI 3.141592653589793238462643383279502884197169399375105820974944592307816406286208998628034825342117068
#define NofMics 32

using namespace std;

int samplesize,MicSize,Nharm;

QString folder = "D:\\Spatial_Audio\\Eigenmike_Beamforming\\Eigenmike_Beamforming";

MicrophoneQuadrature* microphonearray;

complex<double> * STFT(double *signal, int signalLength, int windowSize, int hopSize);


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);



    connect(ui->harmonic_button,SIGNAL(released()),this,SLOT(handlebutton()));

    connect(ui->STFT_Signal,SIGNAL(released()),this,SLOT(Get_STFT()));

    connect(ui->generate_quad,SIGNAL(released()),this,SLOT(GenerateMicArray()));

    connect(ui->add_file_btn,SIGNAL(released()),this,SLOT(AddFile()));

    connect(ui->match_wav,SIGNAL(released()),this,SLOT(MatchWav()));

    connect(ui->Selected_STFT,SIGNAL(released()),this,SLOT(STFTSelected()));

    m_thread = new AlgorithmThreadLebedev();

    connect(m_thread,SIGNAL(Calculated(double,double,double)),this,SLOT(CalculatedAngle(double,double,double)));

    m_healpix = new algorithmthreadhealpix();

    connect(m_healpix,SIGNAL(Calculated(int,double*,bool*,double*,double*)),this,SLOT(PressurevRI(int,double*,bool*,double*,double*)));


    ui->array_param->clear();
    ui->array_param->insertColumn(0);
    ui->array_param->setHorizontalHeaderItem(0, new QTableWidgetItem("Azimuth (phi)"));
    ui->array_param->insertColumn(1);
    ui->array_param->setHorizontalHeaderItem(1, new QTableWidgetItem("Elevation (theta)"));
    ui->array_param->insertColumn(2);
    ui->array_param->setHorizontalHeaderItem(2, new QTableWidgetItem("Weight"));
    ui->array_param->insertColumn(3);
    ui->array_param->setHorizontalHeaderItem(3, new QTableWidgetItem("File Name"));





   // sockthread->start();

      // create graph and assign data to it:


}

MainWindow::~MainWindow()
{
    delete ui;
}

complex<double>* harmonic_coeff;

complex<double>* maxvalueofcoeff;


void MainWindow::plotgraph()
{

    ui->phaseplot->addGraph();

    ui->magnitudeplot->addGraph();

    double *x_values = (double *)malloc(16 * sizeof(double));
    double *y_values = (double *)malloc(16 * sizeof(double));
    double *y_ph_values = (double *)malloc(16 * sizeof(double));


    for(int smp=0; smp < 16; smp++)

    {

        *(y_values+smp) = abs(*(maxvalueofcoeff+smp));
        *(y_ph_values+smp) = arg(*(maxvalueofcoeff+smp));

        *(x_values+smp) = smp;


    }

    makeplot(0,x_values,y_values,16);

    makeplot(1,x_values,y_ph_values,16);





}


void MainWindow::STFTSelected()
{

    QModelIndexList indexes_mic = ui->array_param->selectionModel()->selectedIndexes();
    if(indexes_mic.empty())
        return;

    AudioCapture* wavread;

    if(indexes_mic.size()>0)
         wavread  = microphonearray->wavFilelist.at(indexes_mic[0].row());

    int selectedval = ui->select_channel->currentIndex();


    if(selectedval == 0)
    {
        makeplot(0,wavread->sampleno,wavread->wav_value_ch1,wavread->samplesize);
    }
    else
    {

        makeplot(0,wavread->sampleno,wavread->wav_value_ch2,wavread->samplesize);
    }


    if(wavread!= NULL)
    {
    ui->phaseplot->addGraph();

    ui->phaseplot->setInteractions(QCP::iRangeDrag|QCP::iRangeZoom);

    ui->phaseplot->axisRect()->setupFullAxesBox(true);

    ui->phaseplot->xAxis->setLabel("Theta");

    ui->phaseplot->yAxis->setLabel("Phi");

    QCPColorMap *colormap = new QCPColorMap(ui->phaseplot->xAxis,ui->phaseplot->yAxis);

    int nx =256;

    int ny= wavread->fftsize /nx;

    colormap->data()->setSize(nx,ny);

    if(selectedval == 0)
    {

        for(int vi=0;vi<ny;vi++)
           {
             for(int ki=0;ki<nx;ki++)
                 {
                 complex<double> realval =   *(wavread->wav_stft_ch1+nx*vi+ki);
                 colormap->data()->setCell(ki,vi,abs(realval));

             }
         }

    }
    else
    {

        for(int vi=0;vi<ny;vi++)
           {
             for(int ki=0;ki<nx;ki++)
                 {
                 complex<double> realval =   *(wavread->wav_stft_ch2+nx*vi+ki);
                 colormap->data()->setCell(ki,vi,abs(realval));

             }
         }

    }




   QCPColorScale *colorscale = new QCPColorScale(ui->phaseplot);

   ui->phaseplot->plotLayout()->addElement(0,1,colorscale);
   colorscale->setType(QCPAxis::atRight);
   colormap->setColorScale(colorscale);
   //colorscale->axis()->setLabel("Source Localization");

   colormap->setGradient(QCPColorGradient::gpPolar);

   colormap->rescaleDataRange();

   QCPMarginGroup *margingroup = new QCPMarginGroup(ui->phaseplot);

   ui->phaseplot->axisRect()->setMarginGroup(QCP::msBottom|QCP::msTop,margingroup);

   colorscale->setMarginGroup(QCP::msBottom|QCP::msTop,margingroup);

       colormap->data()->setRange(QCPRange(0,nx),QCPRange(0,ny));

   ui->phaseplot->xAxis->setRange(0,nx);

   ui->phaseplot->yAxis->setRange(0,ny);

   ui->phaseplot->rescaleAxes();


   ui->phaseplot->replot();

}



   // makeplot(1,wavread->sampleno,(double*)wavread->wav_stft_ch2,wavread->samplesize);

}

void MainWindow::MatchWav()
{


    QModelIndexList indexes = ui->filelist->selectionModel()->selectedIndexes();

    //QModelIndexList indexes_mic = ui->array_param->selectionModel()->selectedIndexes();

    if(indexes.size()>0 && MicSize >= indexes.size())
    {


for(int selectind = 0; selectind<indexes.size();selectind++)
{

    AudioCapture* wavread = new AudioCapture(m_list_dir.at(indexes[selectind].row()).toUtf8().constData(),1);

    int fftsize = 256 * ((wavread->samplesize/(512-256)));

    complex<double> * stft_ch1 =  STFT(wavread->wav_value_ch1, wavread->samplesize, 512, 256);
    complex<double> * stft_ch2 =  STFT(wavread->wav_value_ch2, wavread->samplesize, 512, 256);


     wavread->wav_stft_ch1 = stft_ch1;
    wavread->wav_stft_ch2 = stft_ch2;

    wavread->fftsize = fftsize;

    makeplot(0,wavread->sampleno,wavread->wav_value_ch1,wavread->samplesize);

    //makeplot(1,wavread->sampleno,abs(*wavread->wav_stft_ch1),wavread->samplesize);

    microphonearray->wavFilelist.remove(selectind);

    microphonearray->wavFilelist.insert(selectind,wavread);

    }

    while (ui->array_param->rowCount() > 0)
    {
        ui->array_param->removeRow(0);
    }

   for(int kl=0;kl <MicSize;kl++)
   {
        ui->array_param->insertRow(kl);

        ui->array_param->setItem(kl, 0, new QTableWidgetItem(QString::number(*(microphonearray->MicAnglesPhi+kl))));
        ui->array_param->setItem(kl, 1, new QTableWidgetItem(QString::number(*(microphonearray->MicAnglesTheta+kl))));
        ui->array_param->setItem(kl, 2, new QTableWidgetItem(QString::number(*(microphonearray->SurfaceCoeff+kl))));

        if(microphonearray->wavFilelist.at(kl) != NULL)
            ui->array_param->setItem(kl, 3, new QTableWidgetItem(microphonearray->wavFilelist.at(kl)->filename));


   }

}
    ui->array_param->repaint();


    //makeplot(0,x_values,wavread->wav_value_ch2,wavread->);


   // wavread.


}

void MainWindow::AddFile()
{




    QStringList fileName = QFileDialog::getOpenFileNames(this,tr("Select Audio"),"D:\\Mert\\AudioFiles",tr("Audio files (*.wav)"));

    QString file;

    for(int kl=0;kl <fileName.size();kl++)
    {

        file = fileName[kl].section("/",-1,-1);

        m_list.push_back(file);

        m_list_dir.push_back(fileName[kl]);

    }


    //QString dir = fileName.section("/",0,-2);

    ui->filelist->clear();

    ui->filelist->addItems(m_list);

}

void MainWindow::plotgraphintime()
{

    ui->phaseplot->addGraph();

    ui->magnitudeplot->addGraph();

    double *x_values = (double *)malloc(samplesize * sizeof(double));
    double *y_values = (double *)malloc(samplesize * sizeof(double));
    double *y_ph_values = (double *)malloc(samplesize * sizeof(double));

    int val = ui->lineEdit_3->text().toInt();

    for(int smp=0; smp < samplesize; smp++)

    {

        *(y_values+smp) = abs(*(harmonic_coeff+smp*16+val));
        *(y_ph_values+smp) = arg(*(harmonic_coeff+smp*16+val));

        *(x_values+smp) = smp;


    }

    makeplot(0,x_values,y_values,samplesize);

    makeplot(1,x_values,y_ph_values,samplesize);


}

void MainWindow::GenerateMicArray()
{
   // 2 *(N+1)^2
       QString str =  ui->comboBox_quadrature->currentText();
       int order = ui->sphere_order->text().toInt();

            if(str == "Gaussian Quadrature")
            {
                MicSize = 2* ((order+1)*(order+1));
                microphonearray = new MicrophoneQuadrature(MicSize);
                microphonearray->SetArrayGaussian(order);

            }
            else if(str == "Eigenmike Quadrature")
            {
                MicSize = 32;
                microphonearray = new MicrophoneQuadrature(MicSize);
                microphonearray->SetArrayEigenmike();
            }



            while (ui->array_param->rowCount() > 0)
            {
                ui->array_param->removeRow(0);
            }

           for(int kl=0;kl <MicSize;kl++)
           {
                ui->array_param->insertRow(kl);

                ui->array_param->setItem(kl, 0, new QTableWidgetItem(QString::number(*(microphonearray->MicAnglesPhi+kl))));
                ui->array_param->setItem(kl, 1, new QTableWidgetItem(QString::number(*(microphonearray->MicAnglesTheta+kl))));
                ui->array_param->setItem(kl, 2, new QTableWidgetItem(QString::number(*(microphonearray->SurfaceCoeff+kl))));


           }
            ui->array_param->repaint();
            ui->array_param->update();
}

void MainWindow::geometry()
{

    ui->magnitudeplot->setInteractions(QCP::iRangeDrag|QCP::iRangeZoom);

    ui->magnitudeplot->axisRect()->setupFullAxesBox(true);

    ui->magnitudeplot->xAxis->setLabel("Theta");

    ui->magnitudeplot->yAxis->setLabel("Phi");

    QCPColorMap *colormap = new QCPColorMap(ui->magnitudeplot->xAxis,ui->magnitudeplot->yAxis);

    int nx =181;

    int ny= 360;

    colormap->data()->setSize(nx,ny);

    complex<double> *values = (complex<double> *)malloc(360 * 181 * sizeof(complex<double>));

    complex<float> zeroval(0,0);

    for(int km =0;km < 360 *181 ; km++)
    {

        *(values+km) = zeroval;

    }

    int thetamax =0;
    int phimax = 0;

    double maxvalue = 0;

    QFile file("D:\\Spatial_Audio\\APPLICATION_EXAMPLES_R11-1220\\APPLICATION_EXAMPLES\\geometryh0v0.txt");

    file.open(QIODevice::WriteOnly | QIODevice::Text);

    QTextStream out(&file);

for(int phicnt =0; phicnt < 360;phicnt++)
{

 for(int cnt =0; cnt < 181;cnt++)
 {


    model::point<long double, 2, cs::spherical<radian> > p2(((double)cnt)*PI/180,((double)phicnt)*PI/180);

    int counter =0;

    for(int sph_n=0;sph_n < 4;sph_n ++)
           {

               for(int sph_m= -sph_n ; sph_m <= sph_n ;sph_m++)
                   {

                       complex<double> harmonic = (complex<double>)spherical_harmonic(sph_n,sph_m,get<0>(p2),get<1>(p2));

                       *(values+phicnt*181+cnt) += (*(maxvalueofcoeff+counter)) * harmonic  ;

                      counter++;

                  }
         }

    complex<double> realval =   abs(*(values+phicnt*181+cnt));
    colormap->data()->setCell(cnt,phicnt,abs(realval));


 }

}

QCPColorScale *colorscale = new QCPColorScale(ui->magnitudeplot);

ui->magnitudeplot->plotLayout()->addElement(0,1,colorscale);
colorscale->setType(QCPAxis::atRight);
colormap->setColorScale(colorscale);
//colorscale->axis()->setLabel("Source Localization");

colormap->setGradient(QCPColorGradient::gpPolar);

colormap->rescaleDataRange();

QCPMarginGroup *margingroup = new QCPMarginGroup(ui->magnitudeplot);

ui->magnitudeplot->axisRect()->setMarginGroup(QCP::msBottom|QCP::msTop,margingroup);

colorscale->setMarginGroup(QCP::msBottom|QCP::msTop,margingroup);

    colormap->data()->setRange(QCPRange(0,181),QCPRange(0,360));

ui->magnitudeplot->xAxis->setRange(0,181);

ui->magnitudeplot->yAxis->setRange(0,360);

ui->magnitudeplot->rescaleAxes();


ui->magnitudeplot->replot();


 //makeplot(0,x_values,y_values,180*360);

 //makeplot(1,x_values,y_ph_values,180*360);





}

// Create a hamming window of windowLength samples in buffer
void hamming(int windowLength, double *buffer) {

 for(int i = 0; i < windowLength; i++) {

   buffer[i] = 0.54 - (0.46 * cos( 2 * PI * (i / ((windowLength - 1) * 1.0))));

 }

}


complex<double> * STFT(double *signal, int signalLength, int windowSize, int hopSize) {


    fftw_complex    *data, *fft_result, *ifft_result;
    fftw_plan       plan_forward, plan_backward;
    int             i;
    std::complex <double> *outputsignal;


    data        = ( fftw_complex* ) fftw_malloc( sizeof( fftw_complex ) * windowSize );
    fft_result  = ( fftw_complex* ) fftw_malloc( sizeof( fftw_complex ) * windowSize );
    ifft_result = ( fftw_complex* ) fftw_malloc( sizeof( fftw_complex ) * windowSize );

    outputsignal = (std::complex <double> *) malloc(sizeof( std::complex <double> ) * (windowSize/2+1) * (signalLength/(hopSize)));

    plan_forward  = fftw_plan_dft_1d( windowSize, data, fft_result, FFTW_FORWARD, FFTW_ESTIMATE );

    // Create a hamming window of appropriate length
    double *window = (double *) malloc(sizeof( double ) * windowSize);

    hamming(windowSize, window);

    int chunkPosition = 0;

    int readIndex;

    // Should we stop reading in chunks?
    int bStop = 0;

    int numChunks = 0;

    // Process each chunk of the signal

    int outputcounter=0;

    while(chunkPosition < signalLength && !bStop) {

      // Copy the chunk into our buffer
      for(i = 0; i < windowSize; i++) {


          readIndex = chunkPosition + i;

          if(readIndex < signalLength) {

              // Note the windowing!
              data[i][0] = signal[readIndex] * window[i];
              data[i][1] = 0.0;

          } else {

             // we have read beyond the signal, so zero-pad it!

             data[i][0] = 0.0;
             data[i][1] = 0.0;

             bStop = 1;

         }
      }


  // Perform the FFT on our chunk
  fftw_execute( plan_forward );




  /* Uncomment to see the raw-data output from the FFT calculation
  std::cout << "Column: " << chunkPosition << std::endl;
  for(i = 0 ; i < windowSize ; i++ ) {
   fprintf( stdout, "fft_result[%d] = { %2.2f, %2.2f }\n",
     i, fft_result[i][0], fft_result[i][1] );
  }
   */


  // Copy the first (windowSize/2 + 1) data points into your spectrogram.
  // We do this because the FFT output is mirrored about the nyquist
  // frequency, so the second half of the data is redundant. This is how
  // Matlab's spectrogram routine works.


    for (i = 0; i < windowSize/2 ; i++) {

        complex<double> resultvalue(fft_result[i][0],fft_result[i][1]);
        *(outputsignal+outputcounter) = resultvalue;
        outputcounter++;
    }

  chunkPosition += hopSize;
  numChunks++;

  } // Excuse the formatting, the while ends here.

fftw_destroy_plan( plan_forward );

fftw_free( data );
fftw_free( fft_result );
fftw_free( ifft_result );

return outputsignal;

}

    complex<double> * frequencybinvals;

void MainWindow::Get_STFT()
{

    int sampleinfile = 441000;

    double * pressureval = (double *) malloc(sizeof(double)*sampleinfile*32);

    QString filename = "womanh180manh60.txt";


    QString folderm = "C:\\Spatial_audio\\Testdata\\" + filename;


    //Get pressure values from txt file
    QFile file(folderm);

    file.open(QIODevice::ReadOnly | QIODevice::Text);

    QTextStream in(&file);

    int count = 0;

    for(int i = 0; i < sampleinfile; ++i)
            {
          QString line = in.readLine();

          QVector<QString> var = line.split(" ").toVector();

          for(int kl=0; kl< var.size();kl++)
                {
                if(var.at(kl)!="")
                    {

                        pressureval[i+sampleinfile*count]= var.at(kl).toDouble();
                        count++;
                        if(count==32)
                            break;

                    }
                }
          count=0;
            }

    int windows = 2048;
    int hopsize =1024;
    int fftsize = 1025 * ((sampleinfile/(windows-hopsize)));

    frequencybinvals = (complex<double> *)malloc(fftsize*32*sizeof(complex<double>) );

    QFile filemicfft("C:\\Spatial_audio\\Eigenmike_Beamforming\\fftresultsmic0real.txt");

    filemicfft.open(QIODevice::WriteOnly | QIODevice::Text);

    QTextStream inmicfft(&filemicfft);

    QFile filemicfftcomplex("C:\\Spatial_audio\\Eigenmike_Beamforming\\fftresultsmic0comp.txt");

    filemicfftcomplex.open(QIODevice::WriteOnly | QIODevice::Text);

    QTextStream inmicfftcomp(&filemicfftcomplex);

    for(int kl =0;kl < 32;kl++)
    {

        complex<double> * fftvalues = STFT(pressureval+kl*sampleinfile, sampleinfile, 2048, 1024);
        memcpy(frequencybinvals+kl*fftsize,fftvalues,fftsize* sizeof(complex<double>));
    }

    for(int ff =0;ff < fftsize;ff++)
    {

        if(ff%1025 ==0&&ff!=0)
                {
                    inmicfft << "\n" ;
                    inmicfftcomp << "\n" ;
                }
            complex<double> resultvalue = *(frequencybinvals+ff);
            inmicfft << resultvalue.real() << " "  ;
            inmicfftcomp << resultvalue.imag() << " "  ;



    }



      filemicfft.close();
      filemicfftcomplex.close();

}


void MainWindow::decorate()
{



    connect(ui->Coefficients,SIGNAL(released()),this,SLOT(calculatecoeff()));

    connect(ui->maxcoeff,SIGNAL(released()),this,SLOT(plotgraph()));

    connect(ui->plotintime,SIGNAL(released()),this,SLOT(plotgraphintime()));

    connect(ui->geometry,SIGNAL(released()),this,SLOT(geometry()));




}

void MainWindow::calculatecoeff()
{
    //file = "D:\Spatial_audio\Records\irsh0v0.mat";

    MicSize =32;

    samplesize =10001;

    Nharm =5;

    int harmonicsize =25;

    double* pressurevalues = (double*) malloc(MicSize * sizeof(double));

    double* pressurevalues_def = (double*) malloc(MicSize * sizeof(double));

    double* angles_fnm = (double*) malloc((2)* MicSize * sizeof(double));

    double* surface_coeff = (double*) malloc( MicSize * sizeof(double));

    maxvalueofcoeff = ( complex<double>*) malloc( harmonicsize * sizeof(complex<double>));

    harmonic_coeff = (complex<double>*) malloc( (samplesize) * (harmonicsize) * sizeof(complex<double>));

    QString filename;  // =ui->comboBox_4->currentText();

    QString folderm = "C:\\Spatial_audio\\Eigenmike_Beamforming\\Eigenmike_Beamforming\\" + filename;


    //Get pressure values from txt file
    QFile file(folderm);

    file.open(QIODevice::ReadOnly | QIODevice::Text);

    QTextStream in(&file);





    for(int kml=0;kml < MicSize;kml++ )
        *(pressurevalues+kml) = 0;

    double val =0;

    for(int i = 0; i < samplesize; ++i)
            {
          QString line = in.readLine();

          QVector<QString> var = line.split(" ").toVector();

          int count = 0;

          bool canenter = false;

          for(int kl=0; kl< var.size();kl++)
                {
                if(var.at(kl)!="")
                    {

                        if((var.at(kl).toDouble() > val))
                           {

                                canenter = true;
                                val= var.at(kl).toDouble();

                            }
                            *(pressurevalues_def+count)= var.at(kl).toDouble();
                           count++;

                    }
                }
                if(canenter)
                    memcpy(pressurevalues,pressurevalues_def,MicSize*sizeof(double));
            }

    //Get Microphone values and Coefficients

    QFile filemic("C:\\Spatial_audio\\angles.txt");

    filemic.open(QIODevice::ReadOnly | QIODevice::Text);

    QTextStream inmic(&filemic);

    for(int i = 0; i < MicSize; ++i)
            {
          QString line = inmic.readLine();

          QVector<QString> var = line.split(" ").toVector();

          int count = 0;

          for(int kl=0; kl< var.size();kl++)
                {
                if(var.at(kl)!="")
                    {

                        if(count!=2)
                            *(angles_fnm+count+i*2)= var.at(kl).toDouble();
                        else
                            *(surface_coeff+i)= var.at(kl).toDouble();
                        count++;
                    }
                }
            }


    //Get Coefficients

complex<float> zeroval(0,0);

for(int km =0;km < 25 ; km++)
{

    *(maxvalueofcoeff+km) = zeroval;

}



        for(int ml=0;ml < MicSize;ml++)
        {


     model::point<long double, 2, cs::spherical<radian> > p2((*(angles_fnm+(ml*2))*PI/180),(*(angles_fnm+(ml*2)+1)*PI/180));

     int counter = 0;

     for(int sph_n=0;sph_n < Nharm;sph_n ++)
            {

                for(int sph_m= -sph_n ; sph_m <= sph_n ;sph_m++)
                    {

                        complex<double> calcharmonic =  (complex<double>)spherical_harmonic(sph_n,sph_m,get<0>(p2),get<1>(p2));

                        complex<double> harmonic = conj(calcharmonic);

                        *(maxvalueofcoeff+counter) += ((complex<double>)pressurevalues[ml]) * harmonic  * (*(surface_coeff+ml));

                        counter++;

                    }
           }
        }



}

complex<double>* pressure;

void MainWindow::convolvesignals()
{

    //Get 2 seconds of each signal
    int getsamplesize = 88200;

    //First RIR
    QString filename; //= ui->comboBox_4->currentText();
    QString folderm = "C:\\Spatial_audio\\Eigenmike_Beamforming\\Eigenmike_Beamforming\\" + filename;
    //Get pressure values from txt file
    QFile file(folderm);
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream in(&file);

    double * RIR_32        = (double*) malloc(32 *getsamplesize* sizeof(double));

    //First Sound
    QString recfilename; //= ui->comboBox_5->currentText();
    QString recfolderm = "C:\\Spatial_audio\\Kayitlar\\" + recfilename;
    //Get pressure values from txt file
    QFile recfile(recfolderm);
    recfile.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream recin(&recfile);

    double * RecSound        = (double*) malloc(getsamplesize* sizeof(double));

    for(int i = 0; i < getsamplesize; ++i)
            {
          QString line = in.readLine();
          QString recline = recin.readLine();

          QVector<QString> var = line.split(" ").toVector();
            int count =0;
          for(int kl=0; kl< var.size();kl++)
                {
                if(var.at(kl)!="")
                    {
                        *(RIR_32+i*32+count)= var.at(kl).toDouble();
                        count++;
                    }
                }
          QVector<QString> recvar = recline.split(" ").toVector();

          for(int kl=0; kl< recvar.size();kl++)
                {
                if(recvar.at(kl)!="")
                    {
                        *(RecSound+i)= recvar.at(kl).toDouble();
                    }
                }


            }

    int nconv = getsamplesize+getsamplesize-1;

   // double *   C = (double*) calloc(32 *nconv, sizeof(double));

    int i, j, i1;
    double tmp;

    QFile writefile("out.txt");
    writefile.open(QIODevice::WriteOnly | QIODevice::Text);
       QTextStream outfile(&writefile);


    for (i=0; i<nconv; i++)
        {

          for(int micno=0;micno < 32;micno++)
          {
            i1 = i;
            tmp = 0.0;
            for (j=0; j<getsamplesize; j++)
            {
                if(i1>=0 && i1<getsamplesize)
                    tmp = tmp + (RIR_32[i1*32+micno]*RecSound[j]);

                i1 = i1-1;
               // C[i] = tmp;
            }

            outfile << tmp << " ";
          }
            outfile <<  "\n";
        }

    writefile.close();


}




void MainWindow::handlebutton()
{
       int MicPoints = ui->sphere_order->text().toInt();

       //Memory Allocations for source and microphones
       double * SourceAngles        = (double*) malloc(2 * sizeof(double));
       double * MicAngles           = (double*) malloc(MicPoints * 2 * sizeof(double));

       double * Surface           = (double*) malloc(MicPoints *  sizeof(double));

       double * x           = (double*) malloc(MicPoints * sizeof(double));
       double * y           = (double*) malloc(MicPoints * sizeof(double));

       //Source Angles in Degree
       *SourceAngles       = ui->theta_edit->text().toDouble() ;
       *(SourceAngles+1)   = ui->phi_edit->text().toDouble() ;


       double soundvelocity =  ui->snd_speed_edit->text().toDouble();
       double SourceFreq =  ui->freq_edit->text().toDouble();
       double SphereRadius =  ui->radius_edit->text().toDouble();

       double kr = 2 * PI * SourceFreq * SphereRadius * 0.01 / soundvelocity;


      // ui->phaseplot->addGraph();

       QFile filemic("C:\\Spatial_audio\\angles.txt");

       filemic.open(QIODevice::ReadOnly | QIODevice::Text);

       QTextStream inmic(&filemic);

       int count = 0;

       for(int i = 0; i < MicPoints; ++i)
               {
             QString line = inmic.readLine();

             QVector<QString> var = line.split(" ").toVector();

             int count = 0;

             for(int kl=0; kl< var.size();kl++)
                   {
                   if(var.at(kl)!="")
                       {

                           if(count!=2)
                               *(MicAngles+count+i*2)= var.at(kl).toDouble();
                           else
                               *(Surface+i)= var.at(kl).toDouble();

                           count++;
                       }
                   }
               }


        pressure = (complex<double>*) calloc(MicPoints , sizeof(complex<double>));

       //complex<double>* pressure


       //m_alg->CalculatePressureValues(pressure,MicPoints,SourceAngles,MicAngles,kr);

       Nharm =5;


for(int NOfSource=0;sourceAzimuth.size()>NOfSource ;NOfSource++)

{
    *(SourceAngles+1) = sourceElevation.at(NOfSource);
    *(SourceAngles) = sourceAzimuth.at(NOfSource);


       model::point<long double, 2, cs::spherical<radian> > p1((*(SourceAngles)*PI/180),(*(SourceAngles+1)*PI/180));

       complex<double> comple(0,1);

       complex<double> zeroval(0,0);

       for(int ml=0;ml < MicPoints;ml++)
       {



    model::point<long double, 2, cs::spherical<radian> > p2((*(MicAngles+(ml*2))*PI/180),(*(MicAngles+(ml*2)+1)*PI/180));

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


                       *(pressure+ml) += (complex<double>)( calcharmonicsource * bnm * micsph_harmonic);

                   }
          }
       }

}


       microphonearray->calcsphericalharmonics_c(pressure);

      double *samp = microphonearray->GeneratePowerMap();

      PowerMapPlot(samp);

}








void MainWindow::makeplot(int graphid, double* x,double* y,int size)
{


    QVector<double> x_values;
    QVector<double> y_values;

    for(int i=0;i < size ;i++)
        x_values.insert(i,x[i]);

    for(int i=0;i < size ;i++)
        y_values.insert(i,y[i]);

    if(graphid == 0)
    {

    ui->magnitudeplot->addGraph();

    ui->magnitudeplot->setInteractions(QCP::iRangeDrag|QCP::iRangeZoom);

    ui->magnitudeplot->graph(0)->setPen(QPen(Qt::blue)); // line color blue for first graph

    ui->magnitudeplot->graph(0)->setBrush(QBrush(QColor(0, 0, 255, 20))); // first graph will be filled with translucent blue

    ui->magnitudeplot->graph(0)->setLineStyle(QCPGraph::lsImpulse); // first graph will be filled with translucent blue

    ui->magnitudeplot->graph(0)->setData(x_values, y_values);

    ui->magnitudeplot->yAxis->setRange(-10,10);

    ui->magnitudeplot->graph(0)->rescaleAxes();


    ui->magnitudeplot->replot();

    }

    else if(graphid == 1)
    {

        ui->phaseplot->addGraph();

        ui->phaseplot->setInteractions(QCP::iRangeDrag|QCP::iRangeZoom);

        ui->phaseplot->graph(0)->setPen(QPen(Qt::red)); // line color blue for first graph

        ui->phaseplot->graph(0)->setBrush(QBrush(QColor(0, 0, 255, 20))); // first graph will be filled with translucent blue

        ui->phaseplot->graph(0)->setLineStyle(QCPGraph::lsImpulse); // first graph will be filled with translucent blue

        ui->phaseplot->graph(0)->setData(x_values, y_values);

        ui->phaseplot->xAxis->setRange(0,size+1);


        ui->phaseplot->graph(0)->rescaleAxes();

        ui->phaseplot->replot();


    }






}

QVector<double> alg_x_values;
QVector<double> alg_y_values;


void MainWindow::PressurevRI(int RI,double *Pressure,bool* PutArea,double *Az,double * Elevation)
{

        PowerMapPlotRI(Pressure,PutArea,Az,Elevation,RI);



}


void MainWindow::CalculatedAngle(double horang,double verang,double sampleno)
{
    alg_x_values.insert(sampleno,sampleno);
    alg_y_values.insert(sampleno,horang);

    ui->algorithmplot->graph(0)->setData(alg_x_values, alg_y_values);

    ui->algorithmplot->graph(0)->rescaleAxes();

    ui->algorithmplot->replot();



}


void MainWindow::on_play_button_clicked()
{

    int totalnumberofmic = microphonearray->MicSize;

    int samplesize ;

    for(int km=0;km <totalnumberofmic;km++)
    {
        if(microphonearray->wavFilelist[km]==NULL)
            return;

        if(microphonearray->wavFilelist[km]->filename=="")
            return;

        samplesize = microphonearray->wavFilelist[0]->samplesize;

        if(microphonearray->wavFilelist[km]->samplesize!=samplesize)
            return;

    }

    alg_x_values.clear();
    alg_y_values.clear();


        ui->algorithmplot->addGraph();

    ui->algorithmplot->setInteractions(QCP::iRangeDrag|QCP::iRangeZoom);

    ui->algorithmplot->graph(0)->setPen(QPen(Qt::blue)); // line color blue for first graph

    ui->algorithmplot->graph(0)->setBrush(QBrush(QColor(0, 0, 255, 20))); // first graph will be filled with translucent blue

    ui->algorithmplot->graph(0)->setLineStyle(QCPGraph::lsImpulse); // first graph will be filled with translucent blue

    m_thread->m_mic = microphonearray;

    m_thread->start();


}


void MainWindow::on_pushButton_3_clicked()
{

    m_healpix->m_mic = microphonearray;
    m_healpix->Compute(harmonic_coeff);



}

QCPColorMap *colormap ;

void MainWindow::on_pushButton_5_clicked()
{
    if(!this->ui->SimulationData->isChecked())
    {
    int totalnumberofmic = microphonearray->MicSize;

    int samplesize ;

    for(int km=0;km <totalnumberofmic;km++)
    {
        if(microphonearray->wavFilelist[km]==NULL)
            return;

        if(microphonearray->wavFilelist[km]->filename=="")
            return;

        samplesize = microphonearray->wavFilelist[0]->samplesize;

        if(microphonearray->wavFilelist[km]->samplesize!=samplesize)
            return;

    }

    alg_x_values.clear();
    alg_y_values.clear();


        ui->algorithmplot->addGraph();

    ui->algorithmplot->setInteractions(QCP::iRangeDrag|QCP::iRangeZoom);

    ui->algorithmplot->graph(0)->setPen(QPen(Qt::blue)); // line color blue for first graph

    ui->algorithmplot->graph(0)->setBrush(QBrush(QColor(0, 0, 255, 20))); // first graph will be filled with translucent blue

    ui->algorithmplot->graph(0)->setLineStyle(QCPGraph::lsImpulse); // first graph will be filled with translucent blue

    m_healpix->samplenumber = ui->lineEdit->text().toInt();

    m_healpix->ResolutionIndex = ui->RI->currentText().toInt();


    m_healpix->RealorSimulation = 1;
    }
    else
    {
        m_healpix->RealorSimulation = 0;
    }

    m_healpix->m_mic = microphonearray;
    //ui->algorithmplot->clearGraphs();

    ui->algorithmplot->setInteractions(QCP::iRangeDrag|QCP::iRangeZoom);

    ui->algorithmplot->axisRect()->setupFullAxesBox(true);

    ui->algorithmplot->xAxis->setLabel("Theta");

    ui->algorithmplot->yAxis->setLabel("Phi");

   colormap  = new QCPColorMap(ui->algorithmplot->xAxis,ui->algorithmplot->yAxis);

   colormap->setGradient(QCPColorGradient::gpGrayscale);


    m_healpix->start();




}

void MainWindow::on_checkBox_clicked(bool checked)
{

    if(checked)
        ui->filelist->selectAll();
    else
        ui->filelist->clearSelection();

}

void MainWindow::on_pushButton_6_clicked()
{
    int totalnumberofmic = microphonearray->MicSize;
    int samplesize = microphonearray->wavFilelist[0]->samplesize;
    int samplenumber = ui->lineEdit->text().toInt();

    complex<double>* values = (complex<double>*)malloc(totalnumberofmic*sizeof(complex<double>));

    complex<double> average(0,0);

        for(int kl =0;kl < totalnumberofmic ; kl++)
        {

            *(values+kl) = (complex<double>)*(microphonearray->wavFilelist[kl]->wav_stft_ch1+samplenumber);

            average += (complex<double>)*(microphonearray->wavFilelist[kl]->wav_stft_ch1+samplenumber);

        }

    microphonearray->calcsphericalharmonics_c(values);

    double *samp = microphonearray->GeneratePowerMap();

    PowerMapPlot(samp);

    ui->pressure_avg->setText(QString::number( abs(average)));



}


void MainWindow::PowerMapPlotRI(double *values,bool* PutArea,double* Az,double* El,int locsize)
{
    QString filename;


    int nx =360;

    int ny= 180;

    colormap->data()->setSize(nx,ny);
    int iterationpx,iterationpy ;
    int region;

    if(locsize == 12)
    {
        filename ="12.txt";
        iterationpx = 45;
        iterationpy = 30;
        region = 1;
    }
    else if(locsize == 48)
    {
        filename ="48.txt";
        iterationpx = 22.5;
        iterationpy = 15;
        region = 4;
    }
    else if(locsize == 192)
    {
        filename ="192.txt";
        iterationpx = 11.250;
        iterationpy = 7.5;
        region = 16;
    }
    else if(locsize == 768)
    {
        filename ="768.txt";
        iterationpx = 5.625;
        iterationpy = 3.75;
        region = 64;
    }
    else if(locsize == 3072)
    {
        filename ="3072.txt";
        iterationpx = 2.8125;
        iterationpy = 1.875;
        region = 256;
    }
    else if(locsize == 12288)
    {
        filename ="12288.txt";
        iterationpx = 2.7;
        iterationpy = 1.8;
        region = 1024;
    }
    else if(locsize == 49152)
    {
        filename ="49152.txt";
        iterationpx = 0.23;
        iterationpy = 0.35;
        region = 4096;
    }

    QFile file(filename);
    file.open(QIODevice::ReadWrite);
    QTextStream stream(&file);



    int regionpixels[12];
    double regionsumelevation[12];
    double regionsumazimuth[12];
    for(int yk=0;yk< 12;yk++)
    {
        regionpixels[yk]=0;
        regionsumelevation[yk]=0;
        regionsumazimuth[yk]=0;
    }
    for(int id=0; id <locsize;id++)
    {
        int label = id/region;
        for(int kl=*(El+id) *180/PI -iterationpy;kl <*(El+id) *180/PI +iterationpy;kl++ )
            for(int ml=*(Az+id)*180/PI -iterationpx;ml <*(Az+id)*180/PI +iterationpx;ml++ )
               {
                    if(*(PutArea+id))
                    {
                        colormap->data()->setCell(ml,kl,255);

                    }
                    else
                    {
                        colormap->data()->setCell(ml,kl,0);
                        label = -1;
                    }

                }
        if(label!=-1)
        {
            regionpixels[label]++;
            regionsumelevation[label]+=*(El+id) *180/PI;
            regionsumazimuth[label]+=*(Az+id) *180/PI;
        }
        stream << (int)*(PutArea+id) << "   " << label <<endl;
    }
    file.close();

    for(int yk=0;yk< 12;yk++)
    {
        if(regionpixels[yk]!=0)
        {
            regionsumelevation[yk] =regionsumelevation[yk] /regionpixels[yk];
            regionsumazimuth[yk] =regionsumazimuth[yk] /regionpixels[yk];
        }
    }

    double resultazimuth[12];
    double resultelevation[12];
    QList<double> azimuth;
    if(region==256)
    {
    for(int yk=0;yk< 12;yk++)
    {

        if(regionpixels[yk]>10)
        {
        resultazimuth[yk] = regionsumazimuth[yk];
        resultelevation[yk] = regionsumelevation[yk];

        for(int ml=0;ml< 12;ml++)
        {
            if(regionpixels[ml]!=0 && ml!=yk)
            {

            if(pow(abs(resultazimuth[yk]-regionsumazimuth[ml]),2)+pow(abs(resultelevation[yk]-regionsumelevation[ml]),2)<2025)
            {
               resultazimuth[yk] = (resultazimuth[yk] * regionpixels[yk] + regionsumazimuth[ml] * regionpixels[ml]) / (regionpixels[yk]+ regionpixels[ml]);
               resultelevation[yk] = (resultelevation[yk] * regionpixels[yk] + regionsumelevation[ml] * regionpixels[ml]) / (regionpixels[yk]+ regionpixels[ml]);
            }
            }
        }
        }
        else
        {
            resultazimuth[yk] = -1;
            resultelevation[yk] = -1;

        }


    }
    ui->sourcelocations->clear();
    for(int jl=0;jl< 12;jl++)
    {
        if(regionpixels[jl] > 0)
        {
            bool issource = true;
            for(int ko=0;ko < azimuth.length();ko++)
            {
                if(abs(azimuth.at(ko)-resultazimuth[jl]) <25)
                {
                    issource = false;

                }

            }
            if(issource)
            {
                    ui->sourcelocations->insertItem(0,"Source : "+QString::number(resultelevation[jl])+" / " +QString::number(resultazimuth[jl]) + " / "+QString::number(regionpixels[jl]));
                    azimuth.insert(0,resultazimuth[jl]);
            }
        }

    }
    }




    QCPColorScale *colorscale = new QCPColorScale(ui->algorithmplot);

    ui->algorithmplot->plotLayout()->addElement(0,1,colorscale);
    colorscale->setType(QCPAxis::atRight);
    colormap->setColorScale(colorscale);


    colormap->rescaleDataRange(true);

    QCPMarginGroup *margingroup = new QCPMarginGroup(ui->phaseplot);

    ui->algorithmplot->axisRect()->setMarginGroup(QCP::msBottom|QCP::msTop,margingroup);

    colorscale->setMarginGroup(QCP::msBottom|QCP::msTop,margingroup);

    colormap->data()->setRange(QCPRange(0,360),QCPRange(0,180));

    ui->algorithmplot->xAxis->setRange(0,360);

    ui->algorithmplot->yAxis->setRange(0,180);

    ui->algorithmplot->rescaleAxes();


    ui->algorithmplot->replot();

}



void MainWindow::PowerMapPlot(double *values)
{
    ui->phaseplot->clearGraphs();

    ui->phaseplot->setInteractions(QCP::iRangeDrag|QCP::iRangeZoom);

    ui->phaseplot->axisRect()->setupFullAxesBox(true);

    ui->phaseplot->xAxis->setLabel("Azimuth (Phi)");

    ui->phaseplot->yAxis->setLabel("Elevation (Theta)");

    int nx =360;

    int ny= 180;

    QCPColorMap *colormap = new QCPColorMap(ui->phaseplot->xAxis,ui->phaseplot->yAxis);

    colormap->data()->setSize(nx, ny);
    colormap->data()->setRange(QCPRange(0, 359), QCPRange(0, 179));

    for(int cnt=0; cnt <180;cnt++)
        for(int phicnt=0; phicnt <360;phicnt++)
            colormap->data()->setCell(phicnt,cnt,*(values+cnt*360+phicnt));


    colormap->setGradient(QCPColorGradient::gpPolar);
    colormap->rescaleDataRange(true);
    colormap->setInterpolate(false);
    colormap->setDataScaleType(QCPAxis::ScaleType::stLinear);

    ui->phaseplot->xAxis->setRange(0,360);

    ui->phaseplot->yAxis->setRange(0,180);

     ui->phaseplot->rescaleAxes();
       ui->phaseplot->replot();

}

void MainWindow::on_pushButton_7_clicked()
{


    sourceAzimuth.push_back(ui->theta_edit->text().toDouble());
    sourceElevation.push_back(ui->phi_edit->text().toDouble());

    QString s = "El:"+ui->theta_edit->text() + " Az:" + ui->phi_edit->text();


    sourcelocations.push_back(s);

    ui->sourcelist->clear();

    ui->sourcelist->addItems(sourcelocations);


}



void MainWindow::on_harmonic_button_clicked()
{

}

void MainWindow::on_pushButton_8_clicked()
{
    qDeleteAll(ui->filelist->selectedItems());

}


void MainWindow::on_match_wav_clicked()
{

}
