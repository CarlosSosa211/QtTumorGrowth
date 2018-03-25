#include <QGridLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>

#include "inanwindow.h"

InAnWindow::InAnWindow(RInside &R) : QWidget(), m_R(R){

    m_sel = new QGroupBox("Select a method", this);
    m_method = new QComboBox(m_sel);
    m_param = new QGroupBox("Select the inputs and parameters to be analyzed and enter the value of the non-selected factors",
                            this);
    m_initNa = new QCheckBox("Initial number of active cells", m_param);
    m_initNq = new QCheckBox("Initial number of quiescent cells", m_param);
    m_alpha = new QCheckBox("Proliferation rate", m_param);
    m_p = new QCheckBox("Probability of being born acive", m_param);
    m_beta = new QCheckBox("Quiescent to active rate", m_param);
    m_GammaA = new QCheckBox("Death rate of active cells", m_param);
    m_GammaQ = new QCheckBox("Death rate of quiescent cells", m_param);
    m_initNaS = new QSpinBox(m_param);
    m_initNqS = new QSpinBox(m_param);
    m_alphaS = new QDoubleSpinBox(m_param);
    m_pS = new QDoubleSpinBox(m_param);
    m_betaS = new QDoubleSpinBox(m_param);
    m_GammaAS = new QDoubleSpinBox(m_param);
    m_GammaQS = new QDoubleSpinBox(m_param);
    m_back = new QPushButton("Back", this);
    m_cancel = new QPushButton("Cancel", this);
    m_start = new QPushButton("Start analysis", this);
    m_progress = new QProgressBar(this);

    m_method->addItem("Sobol");
    m_method->addItem("FAST");
    m_initNaS->setMaximum(9999);
    m_initNqS->setMaximum(9999);
    m_alphaS->setMaximum(1.0);
    m_alphaS->setSingleStep(0.01);
    m_pS->setMaximum(1.0);
    m_pS->setSingleStep(0.01);
    m_betaS->setMaximum(1.0);
    m_betaS->setSingleStep(0.01);
    m_GammaAS->setMaximum(1.0);
    m_GammaAS->setSingleStep(0.01);
    m_GammaQS->setMaximum(1.0);
    m_GammaQS->setSingleStep(0.01);
    m_progress->setMinimum(0);

    QVBoxLayout *boxLayout = new QVBoxLayout;
    boxLayout->addWidget(m_method);
    m_sel->setLayout(boxLayout);

    QGridLayout *gridLayout = new QGridLayout;
    gridLayout->addWidget(m_initNa, 0, 0);
    gridLayout->addWidget(m_initNaS, 0, 1);
    gridLayout->addWidget(m_initNq, 1, 0);
    gridLayout->addWidget(m_initNqS, 1, 1);
    gridLayout->addWidget(m_alpha, 2, 0);
    gridLayout->addWidget(m_alphaS, 2, 1);
    gridLayout->addWidget(m_p, 3, 0);
    gridLayout->addWidget(m_pS, 3, 1);
    gridLayout->addWidget(m_beta, 4, 0);
    gridLayout->addWidget(m_betaS, 4, 1);
    gridLayout->addWidget(m_GammaA, 5, 0);
    gridLayout->addWidget(m_GammaAS, 5, 1);
    gridLayout->addWidget(m_GammaQ, 6, 0);
    gridLayout->addWidget(m_GammaQS, 6, 1);
    m_param->setLayout(gridLayout);

    QHBoxLayout *hLayout = new QHBoxLayout;
    hLayout->addWidget(m_back);
    hLayout->addWidget(m_cancel);
    hLayout->addWidget(m_start);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(m_sel);
    mainLayout->addWidget(m_param);
    mainLayout->addLayout(hLayout);
    mainLayout->addWidget(m_progress);

    setLayout(mainLayout);

    setWindowTitle("Tumor Growth Simulator");
    setWindowIcon(QIcon("logo.png"));

    QObject::connect(m_back, SIGNAL(clicked()), this, SLOT(back()));
    QObject::connect(m_cancel, SIGNAL(clicked()), qApp, SLOT(quit()));
    QObject::connect(m_start, SIGNAL(clicked()), this, SLOT(start()));
    QObject::connect(m_initNa, SIGNAL(stateChanged(int)), this, SLOT(disable(int)));
    QObject::connect(m_initNq, SIGNAL(stateChanged(int)), this, SLOT(disable(int)));
    QObject::connect(m_alpha, SIGNAL(stateChanged(int)), this, SLOT(disable(int)));
    QObject::connect(m_p, SIGNAL(stateChanged(int)), this, SLOT(disable(int)));
    QObject::connect(m_beta, SIGNAL(stateChanged(int)), this, SLOT(disable(int)));
    QObject::connect(m_GammaA, SIGNAL(stateChanged(int)), this, SLOT(disable(int)));
    QObject::connect(m_GammaQ, SIGNAL(stateChanged(int)), this, SLOT(disable(int)));
}


void InAnWindow::back(){
    StartWindow *startWindow = new StartWindow(m_R);
    close();
    startWindow->show();
}


void InAnWindow::disable(int state){
    m_initNaS->setEnabled(!m_initNa->isChecked());
    m_initNqS->setEnabled(!m_initNq->isChecked());
    m_alphaS->setEnabled(!m_alpha->isChecked());
    m_pS->setEnabled(!m_p->isChecked());
    m_betaS->setEnabled(!m_beta->isChecked());
    m_GammaAS->setEnabled(!m_GammaA->isChecked());
    m_GammaQS->setEnabled(!m_GammaQ->isChecked());
}


void InAnWindow::start(){
    std::string cmd0 = "library(sensitivity);";
    std::string cmd1 = "library(boot);";
    std::string cmd2 = "n <- 1000;";
    std::string cmd3 = "X1 <- data.frame(matrix(runif(8 * n), nrow = n));";
    std::string cmd4 = "X2 <- data.frame(matrix(runif(8 * n), nrow = n));";
    std::string cmd5 = "x <- sobolmartinez(model = sobol.fun, X1, X2, nboot = 0);";
    std::string cmd6 = "png('test.png');";
    std::string cmd7 = "plot(x);";
    std::string cmd8 = "dev.off();";
    std::string cmd = cmd0 + cmd1 + cmd2 + cmd3 + cmd4 + cmd5 + cmd6 + cmd7 + cmd8;
    m_R.parseEvalQ(cmd);
}

