#ifndef STARTWINDOW_H
#define STARTWINDOW_H

#include <QApplication>
#include <QLabel>
#include <QGroupBox>
#include <QRadioButton>
#include <QPushButton>
#include <QWidget>
#include <QStyle>
#include <QDesktopWidget>

class StartWindow : public QWidget{
    Q_OBJECT
public:
    StartWindow();

private:
    QLabel *m_title;
    QGroupBox *m_sel;
    QRadioButton *m_fixedVal, *m_sensAn;
    QPushButton *m_ok;

private slots:
    void advance();
};

#endif
