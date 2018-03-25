#include <QHBoxLayout>
#include <QVBoxLayout>

#include "outwindow.h"

OutWindow::OutWindow(RInside &R, std::vector<int> Na, std::vector<int> Nq, double p, double alpha, double beta,
                     double GammaA, double GammaQ) : QWidget(), m_R(R){
    m_initNa = Na.at(0);
    m_initNq = Nq.at(0);
    m_nIter = Na.size() - 1;
    m_p = p;
    m_alpha = alpha;
    m_beta = beta;
    m_GammaA = GammaA;
    m_GammaQ = GammaQ;

    m_paramGroup = new QGroupBox("Results for a simulation considering", this);
    m_paramL = new QLabel("Initial number of active cells: " + QString::number(m_initNa) + "\n" +
                          "Initial number of quiescent cells: " + QString::number(m_initNq) + "\n" +
                          "Proliferation rate: " + QString::number(m_alpha) + "\n" +
                          "Probability of being born active: " + QString::number(m_p), m_paramGroup);
    m_paramR = new QLabel("Quiescent to active rate: " + QString::number(m_beta) + "\n" +
                          "Death rate of active cells: " + QString::number(m_GammaA) + "\n" +
                          "Death rate of quiescent cells: " +  QString::number(m_GammaQ) + "\n" +
                          "Number of iterations: " + QString:: number(m_nIter), m_paramGroup);
    m_resGroup = new QGroupBox("Fnal number of cells", this);
    m_resL = new QLabel("Total: " + QString::number(Na.at(m_nIter - 1) + Nq.at(m_nIter - 1)), m_resGroup);
    m_resC = new QLabel("Active cells: " + QString::number(Na.at(m_nIter - 1)), m_resGroup);
    m_resR = new QLabel("Quiescent cells: " + QString::number(Nq.at(m_nIter - 1)), m_resGroup);
    m_sel = new QPushButton("Select a new mode", this);
    m_change = new QPushButton("Change input and parameters", this);
    m_save = new QPushButton("Save chart", this);
    m_newSim = new QPushButton("New simulation", this);

    QtCharts::QLineSeries *seriesN = new QtCharts::QLineSeries();
    QtCharts::QLineSeries *seriesNa = new QtCharts::QLineSeries();
    QtCharts::QLineSeries *seriesNq = new QtCharts::QLineSeries();
    seriesN->setName("Total");
    seriesNa->setName("Active cells");
    seriesNq->setName("Quiescent cells");
    for(int i(0); i < m_nIter + 1; i++){
        seriesN->append(i, Na.at(i) + Nq.at(i));
        seriesNa->append(i, Na.at(i));
        seriesNq->append(i, Nq.at(i));
    }

    QtCharts::QChart *chart = new QtCharts::QChart();
    chart->addSeries(seriesN);
    chart->addSeries(seriesNa);
    chart->addSeries(seriesNq);
    chart->setTitle("Evolution of the number of tumor cells");

    QtCharts::QValueAxis *axisX = new QtCharts::QValueAxis;
    axisX->setTitleText("Iteration");
    axisX->setLabelFormat("%i");
    axisX->setTickCount(seriesN->count());
    chart->addAxis(axisX, Qt::AlignBottom);
    seriesN->attachAxis(axisX);
    seriesNa->attachAxis(axisX);
    seriesNq->attachAxis(axisX);
    axisX->applyNiceNumbers();

    QtCharts::QValueAxis *axisY = new QtCharts::QValueAxis;
    axisY->setTitleText("Number of cells");
    axisY->setLabelFormat("%i");
    chart->addAxis(axisY, Qt::AlignLeft);
    seriesN->attachAxis(axisY);
    seriesNa->attachAxis(axisY);
    seriesNq->attachAxis(axisY);
    axisY->setMin(0.0);
    axisY->applyNiceNumbers();

    m_chartView = new QtCharts::QChartView(chart);
    m_chartView->setRenderHint(QPainter::Antialiasing);

    QHBoxLayout *paramLayout = new QHBoxLayout;
    paramLayout->addWidget(m_paramL);
    paramLayout->addWidget(m_paramR);
    m_paramGroup->setLayout(paramLayout);

    QHBoxLayout *resLayout = new QHBoxLayout;
    resLayout->addWidget(m_resL);
    resLayout->addWidget(m_resC);
    resLayout->addWidget(m_resR);
    m_resGroup->setLayout(resLayout);

    QHBoxLayout *hLayout = new QHBoxLayout;
    hLayout->addWidget(m_sel);
    hLayout->addWidget(m_change);
    hLayout->addWidget(m_save);
    hLayout->addWidget(m_newSim);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(m_paramGroup);
    layout->addWidget(m_resGroup);
    layout->addWidget(m_chartView);
    layout->addLayout(hLayout);
    setLayout(layout);

    setWindowTitle("Tumor Growth Simulator");
    setWindowIcon(QIcon("logo.png"));
    /*setGeometry(QStyle::alignedRect(Qt::LeftToRight, Qt::AlignCenter, size(),
                                    qApp->desktop()->availableGeometry()));*/

    QObject::connect(m_sel, SIGNAL(clicked()), this, SLOT(sel()));
    QObject::connect(m_change, SIGNAL(clicked()), this, SLOT(change()));
    QObject::connect(m_newSim, SIGNAL(clicked()),this, SLOT(newSim()));
    QObject::connect(m_save, SIGNAL(clicked()), this, SLOT(save()));
}


void OutWindow::change(){
    InWindow *inWindow = new InWindow(m_R);
    close();
    inWindow->show();
}


void OutWindow::newSim(){
    InWindow *inWindow = new InWindow(m_R, m_initNa, m_initNq, m_p, m_alpha,
                                      m_beta, m_GammaA, m_GammaQ, m_nIter);
    inWindow->simulate();
    close();
}


void OutWindow::sel(){
    StartWindow *startWindow = new StartWindow(m_R);
    close();
    startWindow->show();
}

void OutWindow::save(){
    QString fileName = QFileDialog::getSaveFileName(this, "Save image", QString(),
                                                    "Images(*.png *.gif *.jpg *.jpeg)");
    if(!fileName.isEmpty()){
        QPixmap picture;
        picture = QPixmap::grabWidget(m_chartView);
        picture.save(fileName);
    }
}


