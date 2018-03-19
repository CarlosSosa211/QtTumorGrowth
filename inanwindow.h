#ifndef INANWINDOW_H
#define INANWINDOW_H

#include <QCheckBox>
#include <QComboBox>
#include <QGroupBox>
#include <QProgressBar>
#include <QPushButton>
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
    QPushButton *m_back, *m_start;
    QProgressBar *m_progress;

private slots:
    void back();
    void start();
};

#endif
