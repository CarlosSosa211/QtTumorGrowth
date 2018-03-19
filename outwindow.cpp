#include <QHBoxLayout>
#include <QVBoxLayout>

#include "outwindow.h"

OutWindow::OutWindow(int finN, int finNa, int finNq) : QWidget(){
    m_finN = new QLabel("Final number of cells: " + QString::number(finN),
                        this);
    m_finNa = new QLabel("Final number of active cells: " + QString::number(finNa),
                         this);
    m_finNq = new QLabel("Final number of quiescent cells: " + QString::number(finNq),
                         this);
    m_graph = new QLabel(this);
    m_sel = new QPushButton("Select a new mode", this);
    m_newSim = new QPushButton("New simulation", this);

    m_graph->setPixmap(QPixmap("logoUR1.jpg"));

    QVBoxLayout *vLayout = new QVBoxLayout;
    vLayout->addWidget(m_finN);
    vLayout->addWidget(m_finNa);
    vLayout->addWidget(m_finNq);

    QHBoxLayout *hLayout = new QHBoxLayout;
    hLayout->addWidget(m_sel);
    hLayout->addWidget(m_newSim);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addLayout(vLayout);
    layout->addWidget(m_graph);
    layout->addLayout(hLayout);
    setLayout(layout);

    setWindowTitle("Tumor Growth Simulator");
    /*setGeometry(QStyle::alignedRect(Qt::LeftToRight, Qt::AlignCenter, size(),
                                    qApp->desktop()->availableGeometry()));*/

    QObject::connect(m_sel, SIGNAL(clicked()), this, SLOT(sel()));
    QObject::connect(m_newSim, SIGNAL(clicked()), SLOT(newSim()));
}


void OutWindow::sel(){
    StartWindow *startWindow = new StartWindow;
    close();
    startWindow->show();
}


void OutWindow::newSim(){
    InWindow *inWindow = new InWindow;
    close();
    inWindow->show();
}
