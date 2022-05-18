#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "functiongenerator.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->Plot->addGraph();
    ui->MinSpin->setRange(-100000,100000);
    ui->MaxSpin->setRange(-100000,100000);

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_PlotBtn_clicked()
{
    QPen pen;
    QString function= ui->FunctionLine->text();
    qreal minLimit= ui->MinSpin->value();
    qreal maxLimit= ui->MaxSpin->value();
    if(minLimit>maxLimit){
        Error("Min Limit cannot be larger than Max Limit.");
        return;
    }
    if(function.length()==0){
        Error("Please write a fuction before plotting");
        return;
    }

    qreal step = (maxLimit-minLimit)/500;


    pen.setWidth(2);
    pen.setColor(Qt::red);
    ui->Plot->graph(0)->setPen(pen);
    QVector<double> x0(500), y0(500);
    for (int i=0; i<500; ++i)
    {
      x0[i] = minLimit+step*i;
      try{
      y0[i] = FunctionGenerator::FCalc(function,x0[i]);}
      catch(const std::runtime_error& re){
          Error( re.what());
          return;
      }
    }
    ui->Plot->graph(0)->setData(x0, y0);
    ui->Plot->rescaleAxes();
    ui->Plot->replot();
    ui->Plot->update();
    NoError();
}

void MainWindow::Error(QString errMsg)
{
    ui->ErrorLabel->setText(errMsg);
    ui->ErrorLabel->setStyleSheet("QLabel { background-color : red; color : white; }");

}

void MainWindow::NoError()
{
    ui->ErrorLabel->setText("");
    ui->ErrorLabel->setStyleSheet("QLabel { background-color : rgba(255, 255, 255, 0); }");
}


