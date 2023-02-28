#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_test_button_clicked()
{
    ui->lineEdit->setText(QCoreApplication::applicationFilePath());
    qDebug() << "res: " << Desktop_Creator::deleteDesktop();
}


void MainWindow::on_pushButton_clicked()
{
    qDebug() << "res: " << Desktop_Creator::createDesktop();
    
}

