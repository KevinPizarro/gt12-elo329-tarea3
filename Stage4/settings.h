#ifndef SETTINGS_H
#define SETTINGS_H

#include <QDialog>
#include <QString>
namespace Ui {
class Settings;
}

class Settings : public QDialog
{
    Q_OBJECT

public:
    explicit Settings(QWidget *parent, int N, int I, int I_time);
    ~Settings();
    int N;
    int I;
    int I_time;
private slots:
    void on_pushButton_clicked();

private:
    Ui::Settings *ui;
};

#endif // SETTINGS_H
