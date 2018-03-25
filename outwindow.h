#ifndef OUTWINDOW_H
#define OUTWINDOW_H

#include <QApplication>
#include <QtCharts>
#include <QDesktopWidget>
#include <QGroupBox>
#include <QLabel>
#include <QPushButton>
#include <QStyle>
#include <QWidget>

#include<vector>

#include "inwindow.h"
#include "startwindow.h"

class OutWindow : public QWidget{
    Q_OBJECT
public:
    OutWindow(RInside &R, std::vector<int> Na, std::vector<int> Nq, double p, double alpha,
              double beta, double GammaA, double GammaQ);

private:
    RInside &m_R;
    int m_initNa, m_initNq, m_nIter;
    double m_p, m_alpha, m_beta, m_GammaA, m_GammaQ;
    QGroupBox *m_paramGroup, *m_resGroup;
    QLabel *m_paramL, *m_paramR, *m_resC, *m_resL, *m_resR;
    QtCharts::QChartView *m_chartView;
    QPushButton *m_sel, *m_change, *m_newSim, *m_save;

private slots:
    void change();
    void newSim();
    void sel();
    void save();
};

#endif
