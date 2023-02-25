#include "mainwindow.h"
#include "ui_mainwindow.h"

using namespace std;



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->timeEdit->setTime(QTime::currentTime());

    timer = new QTimer(this);

    connect(timer, SIGNAL(timeout()) ,this ,SLOT(TimerSlot()) );

    timer->start(1000);

    typeDate = "dd.MM.yyyy";
    typeTime = "hh:mm";

    plog::init(plog::verbose,"C:\\Users\\user\\Documents\\GitHub\\OOP2.1a\\plogBase.txt");

    PLOG_VERBOSE << "PROGRAM OPENED";

}

MainWindow::~MainWindow()
{
    PLOG_VERBOSE << "PROGRAM CLOSED";
    delete ui;
}

DataList GlobalList;


void MainWindow::TimerSlot()
{

date = QDate::currentDate();

time = QTime::currentTime();

time.setHMS(time.hour(),time.minute(),time.second(),0);



bool yn = false;

checks check;

check.checkTimeT(GlobalList,date,time,yn);

if(yn){

        ui->listWidget->clear();

        PLOG_DEBUG << "rewrite listWidget";

        QString outString;

        for(const timeT &print: GlobalList.myList){

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
            ui->listWidget->addItem(outString);
        }

        yn = false;

}

}






//add budilik
void MainWindow::on_pushButton_clicked()
{
PLOG_INFO << "pressed button <add budilnik>";

QDate Date = ui->calendarWidget->selectedDate();

QTime Time = ui->timeEdit->time();

Time.setHMS(Time.hour(),Time.minute(),0,0);

QString Info = ui->textEdit->toPlainText();

QString Type = "budilnik";


if(( Date == QDate::currentDate() && Time > QTime::currentTime() ) || ( Date > QDate::currentDate()) ){

    for(const timeT &child: GlobalList.myList){

        if(child.date == Date && child.time == Time){

            PLOG_ERROR << "Budilnik with same time alredy exist";

            QMessageBox::warning(this,"Помилка","Будильник з таким часом вже є");

            return void();

        }


    }

    GlobalList.addEndTimeT(Time,Date,Info,Type);




    PLOG_NONE << "QMessageBox that budilnik added";
    QMessageBox::about(this,"Додано успішно",Date.toString(typeDate) + " " + Time.toString(typeTime) + " " + Info + " " + "Будильник");


    PLOG_NONE << "widget timeEdit set time curr, info line set void";
    ui->timeEdit->setTime(QTime::currentTime());
    ui->textEdit->setText("");



    PLOG_NONE << "add budilnik string to listWidget";
    QString outString = Date.toString(typeDate) + " " + Time.toString(typeTime) + " " + " " + "Будильник " + Info;

    ui->listWidget->addItem(outString);

}else{

    PLOG_ERROR << "wrong enter,QMessageBox";
    PLOG_NONE << "widget timeEdit set time curr, info line set void";

    ui->timeEdit->setTime(QTime::currentTime());

    ui->textEdit->setText("");

    QMessageBox::warning(this,"Помилка вводу","Некоректні дані,перевірте ввід");
}




}


//add timer
void MainWindow::on_pushButton_2_clicked()
{
    PLOG_INFO << "pressed button <add timer>";

    const QString fileway = ui->lineEdit_4->text();

    checks check;

    if(check.checkEnteredTime(ui->lineEdit->text().toInt(),ui->lineEdit_2->text().toInt(),ui->lineEdit_3->text().toInt())){
         return void();
    }


    QDate EnteredDate;
    QTime EnteredTime;
    change a;
    a.timerToTimeT(ui->lineEdit->text().toInt(),ui->lineEdit_2->text().toInt(),ui->lineEdit_3->text().toInt(),EnteredDate,EnteredTime);

    GlobalList.addEndTimeT(EnteredTime,EnteredDate,fileway,"timer");






     PLOG_NONE << "add timer string to listWidget 2 variants - with path to open or without";
      QString outString;
     if(fileway != "" || fileway != nullptr){
         PLOG_NONE << "QMessageBox that timer added";
         QMessageBox::about(this,"Додано успішно",EnteredDate.toString(typeDate) + " " + EnteredTime.toString(typeTime) + " "
                            + "Таймер \nЯкщо шлях вірний,то по закінченню часу відкриється файл: " + fileway);

         outString = EnteredDate.toString(typeDate) + " " + EnteredTime.toString(typeTime) + " "
                 + "Таймер, відкриває файл: " + fileway;
     }else{
         PLOG_NONE << "QMessageBox that timer added";
         QMessageBox::about(this,"Додано успішно",EnteredDate.toString(typeDate) + " " + EnteredTime.toString(typeTime) + " " + "Таймер");
         outString = EnteredDate.toString(typeDate) + " " + EnteredTime.toString(typeTime) + " " + "Таймер";

     }

    ui->listWidget->addItem(outString);

    PLOG_NONE << "set timer widgets to basic";
    ui->lineEdit_4->setText("");
    ui->lineEdit->setText("0");
    ui->lineEdit_2->setText("0");
    ui->lineEdit_3->setText("0");





}


void MainWindow::on_radioButton_3_clicked()
{
    PLOG_INFO << "Pressed radiobutton hh:mm:ss";
    typeTime = "hh:mm:ss";

    ui->listWidget->clear();

    PLOG_DEBUG << "rewrite listWidget";

    QString outString;

    for(const timeT &print: GlobalList.myList){

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
        ui->listWidget->addItem(outString);
    }
}



void MainWindow::on_radioButton_4_clicked()
{
    PLOG_INFO << "Pressed radiobutton hh:mm";
    typeTime = "hh:mm";

    ui->listWidget->clear();

    PLOG_DEBUG << "rewrite listWidget";

    QString outString;

    for(const timeT &print: GlobalList.myList){

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
        ui->listWidget->addItem(outString);
    }
}


void MainWindow::on_radioButton_5_clicked()
{
    PLOG_INFO << "Pressed radiobutton HH.m.s";
    typeTime = "HH.m.s";

    ui->listWidget->clear();

    PLOG_DEBUG << "rewrite listWidget";

    QString outString;

    for(const timeT &print: GlobalList.myList){

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
        ui->listWidget->addItem(outString);
    }

}




