#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>


#include<QCalendarWidget>

#include<QTime>
#include<QDate>

#include<QTimer>
#include<QVector>

#include<QMessageBox>

#include<fstream>

#include <Windows.h>

#include<plog/Log.h>
#include "plog/Initializers/RollingFileInitializer.h"






using namespace std;

/*!
    \brief Класс, що є основою.
    Він зберігає дані про час,в який повинен спрацювати таймер або ж Будильник.

    Також він зберігає тип(будильник або таймер) та дію яку він має зробити
    (відкрити файл,вивести напис чи просто звуковий та візуальний ефект)
*/

class timeT{
public:
    QTime time;
    QDate date;
    QString info;
    QString type;

    timeT(QTime time, QDate date, QString info, QString type){
        this->date = date;
        this->time = time;
        this->info = info;
        this->type = type;
    }

    timeT(){

    }

};

class DataList{
public:

    vector<timeT> myList;

    bool is_empty(){
        if(myList.empty()){
            return 1;
        }else{
            return 0;
        }
    }

    void addEndTimeT(QTime Time,QDate Date,QString Info,QString Type){
        timeT newNode(Time,Date,Info,Type);

        myList.push_back(newNode);

        PLOG_DEBUG << "created class timeT, added to list mainList";
    }

    void deleteTimeT(int pos){

        myList.erase(myList.begin() + pos);

        PLOG_DEBUG << "erase timeT with this time";
    }

};

class change{
public:
    void timerToTimeT(int h,int m,int s, QDate &Day,QTime &Time){
        QDate resD = QDate::currentDate();

        int resSecond = QTime::currentTime().second();
        int resMinute = QTime::currentTime().minute();
        int resHour =  QTime::currentTime().hour();

        while(h != 0 || m != 0 || s != 0){

            if(resSecond + s >= 60){
                resSecond = resSecond + s - 60;
                resMinute = resMinute + 1;
                s = 0;
            }else{
                resSecond = resSecond + s;
                s = 0;
            }

            if(resMinute + m >= 60){
                resMinute = resMinute + m - 60;
                resHour = resHour + 1;
                m = 0;
            }else{
                resMinute = resMinute + m;
                m = 0;
            }

            if(resHour + h >= 24){
                resHour = resHour + h - 24;
                h = 0;
                resD = resD.addDays(1);
            }else{
                resHour = resHour + h;
                h = 0;
            }


        }
        Day = resD;
        Time = QTime(resHour,resMinute,resSecond);

        PLOG_DEBUG << "changed sec,m,h to good format";
    }

};

class checks{
public:
    void checkTimeT(DataList &CurrList,QDate date,QTime time,bool &yn){
        if(!CurrList.is_empty()){

        int pos = 0;

        for(const timeT &child: CurrList.myList){

            if((child.date <= date && child.time == time) || (child.date <= date && child.time <= time)){
            PLOG_DEBUG << "time and date = timeT";

                //2 variants timer and alarm
                if(child.type == "budilnik"){

                    PLOG_DEBUG << "timeT budilnik time";
                    if(child.info != ""){

                      PLOG_DEBUG << "alarm budilnik with info,QMessageBox";

                      MessageBeep(MB_ICONEXCLAMATION);
                      QMessageBox::about(NULL,"Спрацював будильник!",child.info);


                    }else{

                        PLOG_DEBUG << "alarm budilnik without info,QMessageBox";
                        MessageBeep(MB_ICONEXCLAMATION);
                        QMessageBox::about(NULL,"Спрацював будильник!","Спрацював будильник без опису");

                    }
                }else if(child.type == "timer"){

                    PLOG_DEBUG << "timeT timer time";
                    if(child.info != ""){

                      PLOG_DEBUG << "alarm timer with info,QMessageBox,tried to open file " + child.info;
                      MessageBeep(MB_ICONEXCLAMATION);

                      const char* STRopen = (child.info.toStdString()).c_str();

                      system(STRopen);

                      QMessageBox::about(NULL,"Спрацював таймер!","Відкрито файл: " + child.info);



                    }else{

                      PLOG_DEBUG << "alarm timer with info,QMessageBox";
                      MessageBeep(MB_ICONEXCLAMATION);
                      QMessageBox::about(NULL,"Спрацював таймер!","Час вичерпано!");


                    }

                }else{
                    PLOG_WARNING << "error type";
                    QMessageBox::warning(NULL,"Помилка типу","Помилка типу");

                }

                CurrList.deleteTimeT(pos);
                yn = true;

            }
            pos++;
        }
      }
    }


    bool checkEnteredTime(int h,int m,int s){
        if(( h <= 0 && m <= 0 && s <= 0 ) || h >= 24 || m >= 60 || s >= 60){

            PLOG_ERROR << "wrong enter, time = 0 or more then can be";

            QMessageBox::warning(NULL,"Помилка","Некоректні дані!");

            return 1;

        }else if(h <= 0 && m <= 0 && s <= 4){

            PLOG_ERROR << "wrong enter, time less then 4 seconds";

            QMessageBox::warning(NULL,"Помилка","Мінімальний час таймера - 5 секунд!");

            return 1;

            }else{

                return 0;
            }

        }



};


/*
class workWithListWidget : MainWindow{
public:
    void rewriteWidget(DataList currList){

        PLOG_DEBUG << "rewrite listWidget";

        QString outString;

        for(const timeT &print: currList.myList){
            if(print.type == "budilnik"){
                outString = print.date.toString(typeDate) + " " + print.time.toString(typeTime) + " " + " " + "Будильник " + print.info;

            }else if(print.type == "timer"){
                if(print.info == ""){

                outString = print.date.toString(typeDate) + " " + print.time.toString(typeTime) + " " + "Таймер";

                }else{

                outString = print.date.toString(typeDate) + " " + print.time.toString(typeTime) + " "
                        + "Таймер, відкриває файл: " + print.info;

                }
            }else{
                QMessageBox::warning(this,"Помилка типу","Помилка типу");
            }

        }
    }




};*/


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();






private:

    Ui::MainWindow *ui;
    QTimer *timer;

    QTime time;
    QDate date;

    QString typeDate;
    QString typeTime;

private slots:
    void TimerSlot();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_radioButton_3_clicked();
    void on_radioButton_4_clicked();
    void on_radioButton_5_clicked();
};




#endif // MAINWINDOW_H
