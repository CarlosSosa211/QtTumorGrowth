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

#include "outwindow.h"
#include "startwindow.h"
#include "tissue.hpp"

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
