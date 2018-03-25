#ifndef INWINDOW_H
#define INWINDOW_H

#include <QApplication>
#include <QDesktopWidget>
#include <QDoubleSpinBox>
#include <QFileDialog>
#include <QGroupBox>
#include <QLabel>
#include <QMessageBox>
#include <QProgressBar>
#include <QPushButton>
#include <QSpinBox>
#include <QStyle>
#include <QWidget>

#include <vector>

#include "outwindow.h"
#include "startwindow.h"
#include "tissue.hpp"

class InWindow : public QWidget{
    Q_OBJECT
public:
    InWindow(RInside &m_R, int initNa = 0, int initNq = 0, double p = 0.0,
             double alpha = 0.0, double beta = 0.0, double GammaA = 0.0,
             double GammaQ = 0.0, int nIter = 1);

public slots:
    void simulate();
private:
    RInside &m_R;
    QGroupBox *m_param;
    QSpinBox *m_initNa, *m_initNq, *m_nIter;
    QDoubleSpinBox *m_alpha, *m_p, *m_beta;
    QDoubleSpinBox *m_GammaA, *m_GammaQ;
    QPushButton *m_loadInData;
    QPushButton *m_back, *m_cancel, *m_simulate;
    QProgressBar *m_progress;

private slots:
    void back();
    void loadInData();
};

#endif
