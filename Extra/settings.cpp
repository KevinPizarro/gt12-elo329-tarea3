#include "settings.h"
#include "ui_settings.h"
#include <iostream>
using namespace std;
Settings::Settings(QWidget *parent, int N, int I, int I_time) :
    QDialog(parent),
    ui(new Ui::Settings)

{
    ui->setupUi(this);
    this->N = N;
    this->I = I;
    this->I_time = I_time;
    ui->lineN->setText(QString::number(N));
    ui->lineI->setText(QString::number(I));
    ui->lineItime->setText(QString::number(I_time));

}
Settings::~Settings()
{
    delete ui;
}

void Settings::on_pushButton_clicked()
{
    this->N = ui->lineN->text().toInt();
    this->I = ui->lineI->text().toInt();
    this->I_time = ui->lineItime->text().toInt();
    this->close();
}

