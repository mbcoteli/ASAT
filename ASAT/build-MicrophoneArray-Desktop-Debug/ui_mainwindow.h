/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>
#include <qcustomplot.h>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QCustomPlot *magnitudeplot;
    QCustomPlot *phaseplot;
    QLabel *label;
    QLabel *label_2;
    QGroupBox *groupBox;
    QLabel *theta_lbl;
    QLabel *philbl;
    QLineEdit *theta_edit;
    QLineEdit *phi_edit;
    QLabel *Source_freq_lbl;
    QLineEdit *freq_edit;
    QLabel *Sound_spd_lbl;
    QLineEdit *snd_speed_edit;
    QGroupBox *groupBox_2;
    QLineEdit *radius_edit;
    QLabel *label_13;
    QLabel *label_14;
    QComboBox *comboBox_quadrature;
    QLabel *label_15;
    QComboBox *sphere_type;
    QLabel *label_16;
    QLineEdit *sphere_order;
    QPushButton *generate_quad;
    QPushButton *harmonic_button;
    QLineEdit *lineEdit_3;
    QPushButton *maxcoeff;
    QPushButton *geometry;
    QPushButton *plotintime;
    QPushButton *Beamform_button;
    QPushButton *LocalizeBins;
    QPushButton *STFT_Signal;
    QPushButton *Coefficients;
    QPushButton *pushButton_2;
    QListWidget *filelist;
    QPushButton *add_file_btn;
    QLabel *audiofile_list;
    QLabel *audiofile_list_2;
    QPushButton *match_wav;
    QTableWidget *array_param;
    QPushButton *Selected_STFT;
    QComboBox *select_channel;
    QPushButton *play_button;
    QCustomPlot *algorithmplot;
    QLabel *label_3;
    QLabel *Label_PSE;
    QPushButton *pushButton_3;
    QPushButton *pushButton_4;
    QPushButton *pushButton_5;
    QLineEdit *lineEdit;
    QLabel *label_5;
    QCheckBox *checkBox;
    QComboBox *RI;
    QLabel *label_6;
    QPushButton *pushButton_6;
    QPushButton *pushButton_7;
    QListWidget *sourcelist;
    QCheckBox *SimulationData;
    QLabel *label_4;
    QLabel *pressure_avg;
    QPushButton *pushButton_8;
    QListWidget *sourcelocations;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1400, 913);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        magnitudeplot = new QCustomPlot(centralWidget);
        magnitudeplot->setObjectName(QStringLiteral("magnitudeplot"));
        magnitudeplot->setGeometry(QRect(600, 50, 731, 231));
        phaseplot = new QCustomPlot(centralWidget);
        phaseplot->setObjectName(QStringLiteral("phaseplot"));
        phaseplot->setGeometry(QRect(600, 290, 741, 231));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(600, 20, 121, 20));
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(480, 110, 151, 20));
        groupBox = new QGroupBox(centralWidget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(20, 50, 251, 161));
        theta_lbl = new QLabel(groupBox);
        theta_lbl->setObjectName(QStringLiteral("theta_lbl"));
        theta_lbl->setGeometry(QRect(10, 40, 81, 16));
        philbl = new QLabel(groupBox);
        philbl->setObjectName(QStringLiteral("philbl"));
        philbl->setGeometry(QRect(10, 70, 71, 20));
        theta_edit = new QLineEdit(groupBox);
        theta_edit->setObjectName(QStringLiteral("theta_edit"));
        theta_edit->setGeometry(QRect(110, 40, 113, 20));
        phi_edit = new QLineEdit(groupBox);
        phi_edit->setObjectName(QStringLiteral("phi_edit"));
        phi_edit->setGeometry(QRect(110, 70, 113, 20));
        Source_freq_lbl = new QLabel(groupBox);
        Source_freq_lbl->setObjectName(QStringLiteral("Source_freq_lbl"));
        Source_freq_lbl->setGeometry(QRect(10, 100, 81, 20));
        freq_edit = new QLineEdit(groupBox);
        freq_edit->setObjectName(QStringLiteral("freq_edit"));
        freq_edit->setGeometry(QRect(110, 100, 113, 20));
        Sound_spd_lbl = new QLabel(groupBox);
        Sound_spd_lbl->setObjectName(QStringLiteral("Sound_spd_lbl"));
        Sound_spd_lbl->setGeometry(QRect(10, 130, 91, 20));
        snd_speed_edit = new QLineEdit(groupBox);
        snd_speed_edit->setObjectName(QStringLiteral("snd_speed_edit"));
        snd_speed_edit->setGeometry(QRect(110, 130, 113, 20));
        groupBox_2 = new QGroupBox(centralWidget);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        groupBox_2->setGeometry(QRect(20, 220, 341, 151));
        radius_edit = new QLineEdit(groupBox_2);
        radius_edit->setObjectName(QStringLiteral("radius_edit"));
        radius_edit->setGeometry(QRect(110, 30, 113, 20));
        label_13 = new QLabel(groupBox_2);
        label_13->setObjectName(QStringLiteral("label_13"));
        label_13->setGeometry(QRect(15, 30, 71, 20));
        label_14 = new QLabel(groupBox_2);
        label_14->setObjectName(QStringLiteral("label_14"));
        label_14->setGeometry(QRect(10, 60, 81, 20));
        comboBox_quadrature = new QComboBox(groupBox_2);
        comboBox_quadrature->setObjectName(QStringLiteral("comboBox_quadrature"));
        comboBox_quadrature->setGeometry(QRect(110, 60, 131, 22));
        label_15 = new QLabel(groupBox_2);
        label_15->setObjectName(QStringLiteral("label_15"));
        label_15->setGeometry(QRect(10, 90, 81, 20));
        sphere_type = new QComboBox(groupBox_2);
        sphere_type->setObjectName(QStringLiteral("sphere_type"));
        sphere_type->setGeometry(QRect(110, 90, 131, 22));
        label_16 = new QLabel(groupBox_2);
        label_16->setObjectName(QStringLiteral("label_16"));
        label_16->setGeometry(QRect(10, 120, 91, 16));
        sphere_order = new QLineEdit(groupBox_2);
        sphere_order->setObjectName(QStringLiteral("sphere_order"));
        sphere_order->setGeometry(QRect(110, 120, 113, 20));
        generate_quad = new QPushButton(groupBox_2);
        generate_quad->setObjectName(QStringLiteral("generate_quad"));
        generate_quad->setGeometry(QRect(260, 30, 50, 50));
        QIcon icon;
        icon.addFile(QStringLiteral("icon/open_icon.png"), QSize(), QIcon::Normal, QIcon::Off);
        generate_quad->setIcon(icon);
        generate_quad->setIconSize(QSize(32, 32));
        harmonic_button = new QPushButton(centralWidget);
        harmonic_button->setObjectName(QStringLiteral("harmonic_button"));
        harmonic_button->setGeometry(QRect(20, 10, 161, 23));
        lineEdit_3 = new QLineEdit(centralWidget);
        lineEdit_3->setObjectName(QStringLiteral("lineEdit_3"));
        lineEdit_3->setGeometry(QRect(120, 710, 41, 20));
        maxcoeff = new QPushButton(centralWidget);
        maxcoeff->setObjectName(QStringLiteral("maxcoeff"));
        maxcoeff->setGeometry(QRect(460, 860, 111, 23));
        geometry = new QPushButton(centralWidget);
        geometry->setObjectName(QStringLiteral("geometry"));
        geometry->setGeometry(QRect(460, 890, 111, 23));
        plotintime = new QPushButton(centralWidget);
        plotintime->setObjectName(QStringLiteral("plotintime"));
        plotintime->setGeometry(QRect(170, 710, 75, 23));
        Beamform_button = new QPushButton(centralWidget);
        Beamform_button->setObjectName(QStringLiteral("Beamform_button"));
        Beamform_button->setGeometry(QRect(460, 770, 111, 23));
        LocalizeBins = new QPushButton(centralWidget);
        LocalizeBins->setObjectName(QStringLiteral("LocalizeBins"));
        LocalizeBins->setGeometry(QRect(460, 740, 111, 23));
        STFT_Signal = new QPushButton(centralWidget);
        STFT_Signal->setObjectName(QStringLiteral("STFT_Signal"));
        STFT_Signal->setGeometry(QRect(460, 710, 111, 23));
        Coefficients = new QPushButton(centralWidget);
        Coefficients->setObjectName(QStringLiteral("Coefficients"));
        Coefficients->setGeometry(QRect(460, 800, 111, 23));
        pushButton_2 = new QPushButton(centralWidget);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setGeometry(QRect(460, 830, 111, 23));
        filelist = new QListWidget(centralWidget);
        filelist->setObjectName(QStringLiteral("filelist"));
        filelist->setGeometry(QRect(20, 490, 91, 271));
        filelist->setSelectionMode(QAbstractItemView::MultiSelection);
        add_file_btn = new QPushButton(centralWidget);
        add_file_btn->setObjectName(QStringLiteral("add_file_btn"));
        add_file_btn->setGeometry(QRect(20, 380, 91, 50));
        QIcon icon1;
        icon1.addFile(QStringLiteral("icon/add_icon.png"), QSize(), QIcon::Normal, QIcon::Off);
        add_file_btn->setIcon(icon1);
        add_file_btn->setIconSize(QSize(32, 32));
        audiofile_list = new QLabel(centralWidget);
        audiofile_list->setObjectName(QStringLiteral("audiofile_list"));
        audiofile_list->setGeometry(QRect(20, 440, 91, 16));
        audiofile_list_2 = new QLabel(centralWidget);
        audiofile_list_2->setObjectName(QStringLiteral("audiofile_list_2"));
        audiofile_list_2->setGeometry(QRect(120, 440, 201, 16));
        match_wav = new QPushButton(centralWidget);
        match_wav->setObjectName(QStringLiteral("match_wav"));
        match_wav->setGeometry(QRect(120, 660, 161, 41));
        QIcon icon2;
        icon2.addFile(QStringLiteral("icon/next_icon.png"), QSize(), QIcon::Normal, QIcon::Off);
        match_wav->setIcon(icon2);
        match_wav->setIconSize(QSize(24, 24));
        array_param = new QTableWidget(centralWidget);
        array_param->setObjectName(QStringLiteral("array_param"));
        array_param->setGeometry(QRect(120, 460, 451, 192));
        Selected_STFT = new QPushButton(centralWidget);
        Selected_STFT->setObjectName(QStringLiteral("Selected_STFT"));
        Selected_STFT->setGeometry(QRect(520, 40, 71, 41));
        select_channel = new QComboBox(centralWidget);
        select_channel->setObjectName(QStringLiteral("select_channel"));
        select_channel->setGeometry(QRect(520, 80, 71, 22));
        play_button = new QPushButton(centralWidget);
        play_button->setObjectName(QStringLiteral("play_button"));
        play_button->setGeometry(QRect(410, 660, 75, 41));
        algorithmplot = new QCustomPlot(centralWidget);
        algorithmplot->setObjectName(QStringLiteral("algorithmplot"));
        algorithmplot->setGeometry(QRect(600, 530, 741, 231));
        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(590, 510, 151, 20));
        Label_PSE = new QLabel(centralWidget);
        Label_PSE->setObjectName(QStringLiteral("Label_PSE"));
        Label_PSE->setGeometry(QRect(330, 370, 91, 16));
        pushButton_3 = new QPushButton(centralWidget);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));
        pushButton_3->setGeometry(QRect(290, 660, 51, 41));
        pushButton_4 = new QPushButton(centralWidget);
        pushButton_4->setObjectName(QStringLiteral("pushButton_4"));
        pushButton_4->setGeometry(QRect(350, 660, 51, 41));
        pushButton_5 = new QPushButton(centralWidget);
        pushButton_5->setObjectName(QStringLiteral("pushButton_5"));
        pushButton_5->setGeometry(QRect(500, 660, 81, 41));
        lineEdit = new QLineEdit(centralWidget);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setGeometry(QRect(460, 430, 113, 20));
        label_5 = new QLabel(centralWidget);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(326, 430, 111, 20));
        checkBox = new QCheckBox(centralWidget);
        checkBox->setObjectName(QStringLiteral("checkBox"));
        checkBox->setGeometry(QRect(20, 460, 70, 17));
        RI = new QComboBox(centralWidget);
        RI->setObjectName(QStringLiteral("RI"));
        RI->setGeometry(QRect(460, 400, 69, 22));
        label_6 = new QLabel(centralWidget);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(330, 400, 111, 20));
        pushButton_6 = new QPushButton(centralWidget);
        pushButton_6->setObjectName(QStringLiteral("pushButton_6"));
        pushButton_6->setGeometry(QRect(460, 370, 75, 23));
        pushButton_7 = new QPushButton(centralWidget);
        pushButton_7->setObjectName(QStringLiteral("pushButton_7"));
        pushButton_7->setGeometry(QRect(280, 50, 41, 23));
        sourcelist = new QListWidget(centralWidget);
        sourcelist->setObjectName(QStringLiteral("sourcelist"));
        sourcelist->setGeometry(QRect(340, 50, 91, 161));
        sourcelist->setSelectionMode(QAbstractItemView::MultiSelection);
        SimulationData = new QCheckBox(centralWidget);
        SimulationData->setObjectName(QStringLiteral("SimulationData"));
        SimulationData->setGeometry(QRect(610, 770, 131, 17));
        label_4 = new QLabel(centralWidget);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(750, 770, 101, 16));
        pressure_avg = new QLabel(centralWidget);
        pressure_avg->setObjectName(QStringLiteral("pressure_avg"));
        pressure_avg->setGeometry(QRect(870, 770, 47, 13));
        pushButton_8 = new QPushButton(centralWidget);
        pushButton_8->setObjectName(QStringLiteral("pushButton_8"));
        pushButton_8->setGeometry(QRect(20, 770, 75, 23));
        sourcelocations = new QListWidget(centralWidget);
        sourcelocations->setObjectName(QStringLiteral("sourcelocations"));
        sourcelocations->setGeometry(QRect(120, 740, 256, 81));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1400, 21));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        label->setText(QApplication::translate("MainWindow", "Graph 1  -Time Domain", 0));
        label_2->setText(QApplication::translate("MainWindow", "Graph 2  - Frequency Domain", 0));
        groupBox->setTitle(QApplication::translate("MainWindow", "Plane Wave Parameters - Simulation", 0));
        theta_lbl->setText(QApplication::translate("MainWindow", "Theta (degree)", 0));
        philbl->setText(QApplication::translate("MainWindow", "Phi (degree)", 0));
        theta_edit->setText(QApplication::translate("MainWindow", "30", 0));
        phi_edit->setText(QApplication::translate("MainWindow", "30", 0));
        Source_freq_lbl->setText(QApplication::translate("MainWindow", "Source Freq.", 0));
        freq_edit->setText(QApplication::translate("MainWindow", "4000", 0));
        Sound_spd_lbl->setText(QApplication::translate("MainWindow", "Sound Speed", 0));
        snd_speed_edit->setText(QApplication::translate("MainWindow", "343", 0));
        groupBox_2->setTitle(QApplication::translate("MainWindow", "Microphone Array Params", 0));
        radius_edit->setText(QApplication::translate("MainWindow", "10", 0));
        label_13->setText(QApplication::translate("MainWindow", "Radius : (cm)", 0));
        label_14->setText(QApplication::translate("MainWindow", "Quadrature Type", 0));
        comboBox_quadrature->clear();
        comboBox_quadrature->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "Equal Angle (Az., El. )", 0)
         << QApplication::translate("MainWindow", "Gaussian Quadrature", 0)
         << QApplication::translate("MainWindow", "Eigenmike Quadrature", 0)
         << QApplication::translate("MainWindow", "Lebedev Quadrature", 0)
        );
        comboBox_quadrature->setCurrentText(QApplication::translate("MainWindow", "Equal Angle (Az., El. )", 0));
        label_15->setText(QApplication::translate("MainWindow", "Sphere Type", 0));
        sphere_type->clear();
        sphere_type->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "Rigid", 0)
         << QApplication::translate("MainWindow", "Open", 0)
        );
        label_16->setText(QApplication::translate("MainWindow", "# of Microphones", 0));
        sphere_order->setText(QApplication::translate("MainWindow", "32", 0));
        generate_quad->setText(QString());
        harmonic_button->setText(QApplication::translate("MainWindow", "Calculate Spherical Harmonics", 0));
        lineEdit_3->setText(QApplication::translate("MainWindow", "0", 0));
        maxcoeff->setText(QApplication::translate("MainWindow", "Max Coefficients", 0));
        geometry->setText(QApplication::translate("MainWindow", "Geometry", 0));
        plotintime->setText(QApplication::translate("MainWindow", "Plot in Time", 0));
        Beamform_button->setText(QApplication::translate("MainWindow", "Beamform", 0));
        LocalizeBins->setText(QApplication::translate("MainWindow", "Localize Freq Bins", 0));
        STFT_Signal->setText(QApplication::translate("MainWindow", "STFT Signal", 0));
        Coefficients->setText(QApplication::translate("MainWindow", "Coefficients", 0));
        pushButton_2->setText(QApplication::translate("MainWindow", "OpenWav", 0));
        add_file_btn->setText(QApplication::translate("MainWindow", "Add Wav", 0));
        audiofile_list->setText(QApplication::translate("MainWindow", "Audio File List", 0));
        audiofile_list_2->setText(QApplication::translate("MainWindow", "Microphone Array Parameters", 0));
        match_wav->setText(QApplication::translate("MainWindow", "Match Wav with Mic.", 0));
        Selected_STFT->setText(QApplication::translate("MainWindow", "Show Signal", 0));
        select_channel->clear();
        select_channel->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "Channel 1", 0)
         << QApplication::translate("MainWindow", "Channel 2", 0)
        );
        play_button->setText(QApplication::translate("MainWindow", "PLAY", 0));
        label_3->setText(QApplication::translate("MainWindow", "Graph 3  - Algorithm Results", 0));
        Label_PSE->setText(QApplication::translate("MainWindow", "PSE", 0));
        pushButton_3->setText(QApplication::translate("MainWindow", "NN", 0));
        pushButton_4->setText(QApplication::translate("MainWindow", "Load", 0));
        pushButton_5->setText(QApplication::translate("MainWindow", "PLAY_2", 0));
        label_5->setText(QApplication::translate("MainWindow", "Frequency Bin no :", 0));
        checkBox->setText(QApplication::translate("MainWindow", "Select All", 0));
        RI->clear();
        RI->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "1", 0)
         << QApplication::translate("MainWindow", "2", 0)
         << QApplication::translate("MainWindow", "4", 0)
         << QApplication::translate("MainWindow", "8", 0)
         << QApplication::translate("MainWindow", "16", 0)
        );
        label_6->setText(QApplication::translate("MainWindow", "Resolution Index", 0));
        pushButton_6->setText(QApplication::translate("MainWindow", "PowerMap", 0));
        pushButton_7->setText(QApplication::translate("MainWindow", "Add", 0));
        SimulationData->setText(QApplication::translate("MainWindow", "Simulation Data", 0));
        label_4->setText(QApplication::translate("MainWindow", "Pressure Average :", 0));
        pressure_avg->setText(QApplication::translate("MainWindow", "0", 0));
        pushButton_8->setText(QApplication::translate("MainWindow", "Clear", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
