#include <string>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <time.h>

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>

#include "inwindow.h"

InWindow::InWindow(int initNa, int initNq, double p, double alpha, double beta,
                   double GammaA, double GammaQ, int nIter) : QWidget(){
    m_param = new QGroupBox("Enter the value of the parameters", this);
    m_initNa = new QSpinBox(m_param);
    m_initNq = new QSpinBox(m_param);
    m_alpha = new QDoubleSpinBox(m_param);
    m_p = new QDoubleSpinBox(m_param);
    m_beta = new QDoubleSpinBox(m_param);
    m_GammaA = new QDoubleSpinBox(m_param);
    m_GammaQ = new QDoubleSpinBox(m_param);
    m_nIter = new QSpinBox(m_param);
    m_back = new QPushButton("Back", this);
    m_cancel = new QPushButton("Cancel", this);
    m_loadInData = new QPushButton("Load input data", this);
    m_simulate = new QPushButton("Simulate", this);
    m_progress = new QProgressBar(this);

    m_initNa->setMaximum(9999);
    m_initNq->setMaximum(9999);
    m_nIter->setMinimum(1);
    m_nIter->setMaximum(99);
    m_alpha->setMaximum(1.0);
    m_alpha->setSingleStep(0.01);
    m_p->setMaximum(1.0);
    m_p->setSingleStep(0.01);
    m_beta->setMaximum(1.0);
    m_beta->setSingleStep(0.01);
    m_GammaA->setMaximum(1.0);
    m_GammaA->setSingleStep(0.01);
    m_GammaQ->setMaximum(1.0);
    m_GammaQ->setSingleStep(0.01);
    m_progress->setMinimum(0);

    m_initNa->setValue(initNa);
    m_initNq->setValue(initNq);
    m_p->setValue(p);
    m_alpha->setValue(alpha);
    m_beta->setValue(beta);
    m_GammaA->setValue(GammaA);
    m_GammaQ->setValue(GammaQ);
    m_nIter->setValue(nIter);

    QFormLayout *formLayout = new QFormLayout;
    formLayout->addRow("Initial number of active cells", m_initNa);
    formLayout->addRow("Initial number of quiescent cells", m_initNq);
    formLayout->addRow("Proliferation rate", m_alpha);
    formLayout->addRow("Probability of being born active", m_p);
    formLayout->addRow("Quiescent to active rate", m_beta);
    formLayout->addRow("Death rate of active cells", m_GammaA);
    formLayout->addRow("Death rate of quiescent cells", m_GammaQ);
    formLayout->addRow("Number of iterations", m_nIter);

    QVBoxLayout *boxLayout = new QVBoxLayout;
    boxLayout->addLayout(formLayout);
    m_param->setLayout(boxLayout);

    QHBoxLayout *hLayout = new QHBoxLayout;
    hLayout->addWidget(m_back);
    hLayout->addWidget(m_cancel);
    hLayout->addWidget(m_loadInData);
    hLayout->addWidget(m_simulate);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(m_param);
    mainLayout->addLayout(hLayout);
    mainLayout->addWidget(m_progress);

    setLayout(mainLayout);

    setWindowTitle("Tumor Growth Simulator");
    setWindowIcon(QIcon("logo.png"));
    /*setGeometry(QStyle::alignedRect(Qt::LeftToRight, Qt::AlignCenter, size(),
                                    qApp->desktop()->availableGeometry()));*/

    QObject::connect(m_loadInData, SIGNAL(clicked()), this, SLOT(loadInData()));
    QObject::connect(m_back, SIGNAL(clicked()), this, SLOT(back()));
    QObject::connect(m_cancel, SIGNAL(clicked()), qApp, SLOT(quit()));
    QObject::connect(m_simulate, SIGNAL(clicked()), this, SLOT(simulate()));
}


void InWindow::back(){
    StartWindow *startWindow = new StartWindow;
    close();
    startWindow->show();
}


void InWindow::loadInData(){
    QString QInFile = QFileDialog::getOpenFileName(this,
                                                  "Select input data file");
    std::string inFile = QInFile.toUtf8().constData();

    int initNa, initNq, nIter;
    double p, alpha, beta, GammaA, GammaQ;
    std::ifstream stream(inFile.c_str());

    stream >> initNa >> initNq >> p >> alpha >> beta >>
            GammaA >> GammaQ >> nIter;
    stream.close();

    m_initNa->setValue(initNa);
    m_initNq->setValue(initNq);
    m_p->setValue(p);
    m_alpha->setValue(alpha);
    m_beta->setValue(beta);
    m_GammaA->setValue(GammaA);
    m_GammaQ->setValue(GammaQ);
    m_nIter->setValue(nIter);
}

void InWindow::simulate(){
    std::vector<int> Na, Nq;
    std::string outFile("out.res");

    Tissue tissue(m_initNa->value(), m_initNq->value(), m_p->value(),
                  m_alpha->value(), m_beta->value(), m_GammaA->value(),
                  m_GammaQ->value());

    Na.push_back(tissue.getNumAct());
    Nq.push_back(tissue.getNumQuie());

    std::ofstream stream(outFile.c_str());
    stream << 0 << " " << tissue.getNumCells() << " " << tissue.getNumAct() <<
      " " << tissue.getNumQuie() << std::endl;

    srand(time(NULL));
    m_progress->reset();
    m_progress->setMaximum(m_nIter->value());
    int k;
    for(k = 1; k < m_nIter->value() + 1; k++){
        tissue.updateTissue();
        Na.push_back(tissue.getNumAct());
        Nq.push_back(tissue.getNumQuie());
        stream << k << " " << tissue.getNumCells() << " " << tissue.getNumAct() <<
            " " << tissue.getNumQuie() << std::endl;
        m_progress->setValue(k);
    }
    m_progress->setValue(k);
    stream.close();

    OutWindow *outWindow = new OutWindow(Na, Nq, m_p->value(), m_alpha->value(), m_beta->value(),
                                         m_GammaA->value(), m_GammaQ->value());
    close();
    outWindow->show();
    outWindow->resize(800, 600);
}

