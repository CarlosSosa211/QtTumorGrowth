#ifndef STARTWINDOW_H
#define STARTWINDOW_H

#include <QApplication>
#include <QDesktopWidget>
#include <QGroupBox>
#include <QLabel>
#include <QPushButton>
#include <QRadioButton>
#include <QStyle>
#include <QWidget>

#include <RInside.h>

class StartWindow : public QWidget{
    Q_OBJECT
public:
    StartWindow(RInside &R);

private:
    RInside &m_R;
    QLabel *m_title;
    QGroupBox *m_sel;
    QRadioButton *m_fixedVal, *m_sensAn;
    QPushButton *m_ok;

private slots:
    void advance();
};

#endif
