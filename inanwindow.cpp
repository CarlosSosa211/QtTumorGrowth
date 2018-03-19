#include <QHBoxLayout>
#include <QVBoxLayout>

#include "inanwindow.h"
#include "startwindow.h"

InAnWindow::InAnWindow() : QWidget(){
    m_sel = new QGroupBox("Select a method", this);
    m_method = new QComboBox(m_sel);
    m_param = new QGroupBox("Select the inputs and parameters to be analyzed",
                            this);
    m_initNa = new QCheckBox("Initial number of active cells", m_param);
    m_initNq = new QCheckBox("Initial number of quiescent cells", m_param);
    m_alpha = new QCheckBox("Proliferation rate", m_param);
    m_p = new QCheckBox("Probability of being born acive", m_param);
    m_beta = new QCheckBox("Quiescent to active rate", m_param);
    m_GammaA = new QCheckBox("Death rate of active cells", m_param);
    m_GammaQ = new QCheckBox("Death rate of quiescent cells", m_param);
    m_back = new QPushButton("Back", this);
    m_cancel = new QPushButton("Cancel", this);
    m_start = new QPushButton("Start analysis", this);
    m_progress = new QProgressBar(this);

    m_method->addItem("Sobol");
    m_method->addItem("FAST");
    m_progress->setMinimum(0);

    QVBoxLayout *boxLayout = new QVBoxLayout;
    boxLayout->addWidget(m_method);
    m_sel->setLayout(boxLayout);

    QVBoxLayout *box2Layout = new QVBoxLayout;
    box2Layout->addWidget(m_initNa);
    box2Layout->addWidget(m_initNq);
    box2Layout->addWidget(m_alpha);
    box2Layout->addWidget(m_p);
    box2Layout->addWidget(m_beta);

    box2Layout->addWidget(m_GammaA);
    box2Layout->addWidget(m_GammaQ);
    m_param->setLayout(box2Layout);

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

    QObject::connect(m_back, SIGNAL(clicked()), this, SLOT(back()));
    QObject::connect(m_cancel, SIGNAL(clicked()), qApp, SLOT(quit()));
    QObject::connect(m_start, SIGNAL(clicked()), this, SLOT(start()));
}


void InAnWindow::back(){
    StartWindow *startWindow = new StartWindow;
    close();
    startWindow->show();
}


void InAnWindow::start(){

}

