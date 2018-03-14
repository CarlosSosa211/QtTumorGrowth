#ifndef INWINDOW_H
#define INWINDOW_H

#include <QApplication>
#include <QLabel>
#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QGroupBox>
#include <QMessageBox>
#include <QPushButton>
#include <QProgressBar>
#include <QFileDialog>
#include <QWidget>
#include <QStyle>
#include <QDesktopWidget>

#include "tissue.hpp"
#include "outwindow.h"
#include "startwindow.h"

class InWindow : public QWidget{
    Q_OBJECT
public:
    InWindow();

private:
    QGroupBox *m_param;
    QSpinBox *m_initNa, *m_initNq, *m_nIter;
    QDoubleSpinBox *m_alpha, *m_p, *m_beta;
    QDoubleSpinBox *m_GammaA, *m_GammaQ;
    QPushButton *m_loadInData;
    QPushButton *m_back, *m_cancel, *m_simulate;
    QProgressBar *m_progress;

private slots:
    void back();
    void simulate();
    void loadInData();
};

#endif
