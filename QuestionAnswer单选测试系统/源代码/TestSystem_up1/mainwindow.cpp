#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "adminlogin.h"
#include "settingquantity.h"
#include <QtDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_manage_button_clicked()
{
    AdminLogin *al = new AdminLogin;
    al->exec();
}

void MainWindow::on_test_button_clicked()
{
    qDebug()<<"No Problem On TestButton";
    SettingQuantity *set = new SettingQuantity;
    set->exec();
}
