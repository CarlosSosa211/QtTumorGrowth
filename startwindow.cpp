#include <QVBoxLayout>

#include "inanwindow.h"
#include "inwindow.h"
#include "startwindow.h"

StartWindow::StartWindow(RInside &R) : QWidget(), m_R(R){
    m_title = new QLabel;
    m_sel = new QGroupBox("Select mode", this);
    m_fixedVal = new QRadioButton("Simulation with fixed values", m_sel);
    m_sensAn = new QRadioButton("Sensitivity analysis", m_sel);
    m_ok = new QPushButton("Ok", this);

    m_title->setPixmap(QPixmap("lLogo.png"));
    m_fixedVal->setChecked(true);

    QVBoxLayout *boxLayout = new QVBoxLayout;
    QVBoxLayout *mainLayout = new QVBoxLayout;

    boxLayout->addWidget(m_fixedVal);
    boxLayout->addWidget(m_sensAn);
    m_sel->setLayout(boxLayout);

    mainLayout->addWidget(m_title);
    mainLayout->setAlignment(m_title, Qt::AlignHCenter);
    mainLayout->addWidget(m_sel);
    mainLayout->addWidget(m_ok);
    setLayout(mainLayout);

    setWindowTitle("Tumor Growth Simulator");
    setWindowIcon(QIcon("logo.png"));
    /*setGeometry(QStyle::alignedRect(Qt::LeftToRight, Qt::AlignCenter, size(),
                                    qApp->desktop()->availableGeometry()));*/

    QObject::connect(m_ok, SIGNAL(clicked()), this, SLOT(advance()));
}

void StartWindow::advance(){
    if(m_fixedVal->isChecked()){
        InWindow *inWindow = new InWindow(m_R);
        inWindow->show();
        close();
    }
    if(m_sensAn->isChecked()){
        InAnWindow *inAnWindow = new InAnWindow(m_R);
        inAnWindow->show();
        close();
    }
}

