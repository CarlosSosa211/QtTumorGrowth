#ifndef OUTWINDOW_H
#define OUTWINDOW_H

#include <QApplication>
#include <QLabel>
#include <QWidget>
#include <QPushButton>
#include <QStyle>
#include <QDesktopWidget>

#include "startwindow.h"
#include "inwindow.h"

class OutWindow : public QWidget{
    Q_OBJECT
public:
    OutWindow(int finN, int finNa, int finNq);

private:
    QLabel *m_finN, *m_finNa, *m_finNq;
    QLabel *m_graph;
    QPushButton *m_sel, *m_newSim;

private slots:
    void newSim();
    void sel();
};

#endif
