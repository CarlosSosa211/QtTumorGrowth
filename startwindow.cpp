#include <QVBoxLayout>

#include "startwindow.h"
#include "inwindow.h"

StartWindow::StartWindow() : QWidget(){
    m_title = new QLabel("Tumor Growth");
    m_sel = new QGroupBox("Select mode", this);
    m_fixedVal = new QRadioButton("Simulation with fixed values");
    m_sensAn = new QRadioButton("Sensitivity analysis");
    m_ok = new QPushButton("Ok");

    m_title->setFont(QFont("Comic Sans MS", 20));
    m_fixedVal->setChecked(true);

    QVBoxLayout *boxLayout = new QVBoxLayout;
    QVBoxLayout *mainLayout = new QVBoxLayout;

    boxLayout->addWidget(m_fixedVal);
    boxLayout->addWidget(m_sensAn);
    m_sel->setLayout(boxLayout);

    mainLayout->addWidget(m_title);
    mainLayout->addWidget(m_sel);
    mainLayout->addWidget(m_ok);
    setLayout(mainLayout);

    setWindowTitle("Tumor Growth");
    /*setGeometry(QStyle::alignedRect(Qt::LeftToRight, Qt::AlignCenter, size(),
                                    qApp->desktop()->availableGeometry()));*/

    QObject::connect(m_ok, SIGNAL(clicked()), this, SLOT(advance()));
}

void StartWindow::advance(){
    if(m_fixedVal->isChecked()){
        InWindow *inWindow = new InWindow;
        inWindow->show();
        close();
    }
}

