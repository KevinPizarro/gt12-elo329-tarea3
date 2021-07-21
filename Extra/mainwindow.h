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
    /**
     * @brief on_actionSettings_triggered: Si el boton settings es presionado, se llama a este slot.
     */
    void on_actionSettings_triggered();
public slots:
    /**
     * @brief actgraph: Metodo que actualiza el grafico con los ultimos datos obtenidos.
     */
    void actgraph();
    /**
     * @brief CloseSet: Metodo a ejecutar al cerrar la ventana de settings.
     * @param N: Cantidad de individuos nueva.
     * @param I: Cantidad de infectados nueva.
     * @param Itime: Nuevo tiempo de infeccion.
     */
    void CloseSet(int N, int I, int Itime);
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
     * @brief rec: Series superiores para vacunados.
     */
    QLineSeries *vac;
    /**
     * @brief susrec: Series intermedias entre susceptibles y recuperados para un correcto "montaje".
     */
    QLineSeries *susrec;
    /**
     * @brief recinf: : Series intermedias entre recuperados e infectados para un correcto "montaje".
     */
    QLineSeries *recinf;
    /**
     * @brief recinf: : Series intermedias entre vacunados e infectados para un correcto "montaje".
     */
    QLineSeries *vacinf;
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
     * @brief vaca: Series inferiores para vacunados
     */
    QAreaSeries *vaca;
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
    /**
     * @brief flag: Variable para revisar si la simulacion esta en pausa.
     */
    bool flag;
    /**
     * @brief settings: Ventana de settings.
     */
    Settings *settings;
protected:
    bool eventFilter(QObject *obj, QEvent *ev);

};


#endif // MAINWINDOW_H
