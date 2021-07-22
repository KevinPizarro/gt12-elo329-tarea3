#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtCharts>
#include <QChartView>
#include <QLineSeries>
#include <QMainWindow>
#include <QTimer>
#include "Simulator.h"
#include "settings.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT;

public:
    explicit MainWindow(QWidget *parent = 0, Simulator *sim = NULL);
    ~MainWindow();
    void resetgraph();

private slots:
    void on_actionStart_triggered();
    void on_actionStop_triggered();
    void on_actionSettings_triggered();
public slots:
    void actgraph();
    void CloseSet(int N, int I, int Itime);
private:
    Simulator *simulator;
    Ui::MainWindow *ui;
    QLineSeries *inf;
    QLineSeries *sus;
    QLineSeries *rec;
    QLineSeries *vac;
    QLineSeries *susrec;
    QLineSeries *recinf;
    QLineSeries *vacinf;
    QAreaSeries *infa;
    QAreaSeries *susa;
    QAreaSeries *reca;
    QAreaSeries *vaca;
    QChart *chart;
    QChartView *chartView;
    QTimer *timer;
    bool flag;
    Settings *settings;
};


#endif // MAINWINDOW_H
