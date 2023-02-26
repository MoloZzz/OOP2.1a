#include "mainwindow.h"

#include <QApplication>

#include <QTest>
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include "tests.h"




int main(int argc, char *argv[])
{

    freopen("testing.log", "w", stdout);

    QApplication a(argc, argv);

    QTest::qExec(new Tests, argc, argv);

    MainWindow w;
    w.show();
    return a.exec();


}
