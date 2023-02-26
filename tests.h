#ifndef TESTS_H
#define TESTS_H

#include <QObject>
#include <QTest>

#include "mainwindow.h"

class Tests : public QObject
{
    Q_OBJECT

public:

    explicit Tests(QObject *parent = 0);

private slots:
void check_timeT();
};

#endif // TESTS_H
