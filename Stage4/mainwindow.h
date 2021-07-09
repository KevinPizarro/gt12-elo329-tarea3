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
    /**
     * @brief resetgraph: Metodo que reinicia el grafico de la UI.
     */
    void resetgraph();

private slots:
    /**
     * @brief on_actionStart_triggered: Si el boton start es presionado entonces da inicio a la simulacion.
     */
    void on_actionStart_triggered();
    /**
     * @brief on_actionStop_triggered: Si el boton stop es presionado entonces para la simulacion.
     */
    void on_actionStop_triggered();

public slots:
    /**
     * @brief actgraph: Metodo que actualiza el grafico con los ultimos datos obtenidos.
     */
    void actgraph();
private:
    /**
     * @brief simulator Se crea un objeto de la clase Simulator.
     */
    Simulator *simulator;

    Ui::MainWindow *ui;
    /**
     * @brief inf: Series superiores para infectados.
     */
    QLineSeries *inf;
    /**
     * @brief sus: Series superiores para susceptibles.
     */
    QLineSeries *sus;
    /**
     * @brief rec: Series superiores para recuperados.
     */
    QLineSeries *rec;
    /**
     * @brief susrec: Series intermedias entre susceptibles y recuperados para un correcto "montaje".
     */
    QLineSeries *susrec;
    /**
     * @brief recinf: : Series intermedias entre recuperados e infectados para un correcto "montaje".
     */
    QLineSeries *recinf;
    /**
     * @brief infa: Series inferiores para infectados.
     */
    QAreaSeries *infa;
    /**
     * @brief susa: Series inferiores para susceptibles.
     */
    QAreaSeries *susa;
    /**
     * @brief reca: Series inferiores para recuperados.
     */
    QAreaSeries *reca;
    /**
     * @brief chart: Grafico.
     */
    QChart *chart;
    /**
     * @brief chartView: Vista de grafico.
     */
    QChartView *chartView;
    /**
     * @brief timer: Temporizador para la simulacion.
     */
    QTimer *timer;
};


#endif // MAINWINDOW_H
