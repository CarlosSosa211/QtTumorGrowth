#ifndef INANWINDOW_H
#define INANWINDOW_H

#include <QCheckBox>
#include <QComboBox>
#include <QDoubleSpinBox>
#include <QGroupBox>
#include <QProgressBar>
#include <QPushButton>
#include <QSpinBox>
#include <QWidget>

class InAnWindow : public QWidget{
    Q_OBJECT
public:
    InAnWindow();

private:
    QComboBox *m_method;
    QGroupBox *m_param, *m_sel;
    QCheckBox *m_initNa, *m_initNq;
    QCheckBox *m_alpha, *m_p, *m_beta;
    QCheckBox *m_GammaA, *m_GammaQ;
    QSpinBox *m_initNaS, *m_initNqS;
    QDoubleSpinBox *m_alphaS, *m_pS, *m_betaS;
    QDoubleSpinBox *m_GammaAS, *m_GammaQS;
    QPushButton *m_back, *m_cancel, *m_start;
    QProgressBar *m_progress;

private slots:
    void back();
    void start();
    void disable(int state);
};

#endif
