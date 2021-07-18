#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtCharts>
#include <QChartView>
#include <QLineSeries>
#include <QMainWindow>
#include <QTimer>
#include "Simulator.h"

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
public slots:
    void actgraph();
private:
    Simulator *simulator;
    Ui::MainWindow *ui;
    QLineSeries *inf;
    QLineSeries *sus;
    QLineSeries *rec;
    QLineSeries *susrec;
    QLineSeries *recinf;
    QAreaSeries *infa;
    QAreaSeries *susa;
    QAreaSeries *reca;
    QChart *chart;
    QChartView *chartView;
    QTimer *timer;
};

#endif // MAINWINDOW_H
