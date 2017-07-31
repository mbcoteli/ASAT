#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <math.h>
#include <string>



#include "microphonequadrature.h"
#include "audiocapture.h"
#include "algorithmthreadlebedev.h"
#include "algorithmthreadhealpix.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void makeplot(int graphid, double* x,double* y,int size);
    void decorate();
    void PowerMapPlot(double *values);
    void PowerMapPlotRI(double *values,bool* PutArea,double* Az,double* El,int locsize);
    float* SourceAngles;
    float* MicPositions;
    float* MicAngles;
    QThread sockthread;
    QStringList m_list;
    QStringList m_list_dir;
    AlgorithmThreadLebedev *m_thread;
    algorithmthreadhealpix *m_healpix;
    QVector<double> sourceAzimuth;
    QVector<double> sourceElevation;
    QStringList sourcelocations;


private:


public slots:
    void handlebutton();
    void plotgraph();
    void plotgraphintime();
    void geometry();
    void GenerateMicArray();
    void AddFile();
    void MatchWav();
    void STFTSelected();   
    void CalculatedAngle(double horang,double verang,double sampleno);
    void PressurevRI(int RI,double *Pressure,bool* PutArea,double *Az,double * Elevation);


private slots:
    void on_play_button_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_5_clicked();

    void on_checkBox_clicked(bool checked);

    void on_pushButton_6_clicked();

    void on_pushButton_7_clicked();

    void on_harmonic_button_clicked();

    void on_pushButton_8_clicked();

    void on_match_wav_clicked();

private:
    Ui::MainWindow *ui;





};

#endif // MAINWINDOW_H
