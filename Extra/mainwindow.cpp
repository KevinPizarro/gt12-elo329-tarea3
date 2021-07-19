#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
using namespace std;
/**
 * @brief MainWindow::MainWindow: Constructor de la clase MainWindow.
 * @param parent: Widget padre de la ventana principal.
 * @param sim: Simulador.
 */
MainWindow::MainWindow(QWidget *parent,Simulator *sim) :
    QMainWindow(parent),
    simulator(sim),
    ui(new Ui::MainWindow)
{
    timer = new QTimer(this); //Timer para determinar la frecuencia de actualizacion del grafico.
    connect(this->timer,SIGNAL(timeout()),this,SLOT(actgraph()));
    ui->setupUi(this);
    //Iniciamos el grafico.
    this->inf = new QLineSeries();
    this->sus = new QLineSeries();
    this->rec = new QLineSeries();
    this->vac = new QLineSeries();
    this->susrec = new QLineSeries();
    this->recinf = new QLineSeries();
    this->vacinf = new QLineSeries();
    this->vaca = new QAreaSeries(vac);
    this->infa = new QAreaSeries(vacinf,vac);
    this->reca = new QAreaSeries(recinf,inf);
    this->susa = new QAreaSeries(susrec,rec);
    susa->setName("Susceptibles");
    infa->setName("Infectados");
    reca->setName("Recuperados");
    vaca->setName("Vacunados");
    vaca->setColor(QColor(149, 255, 128, 255));
    susa->setColor(QColor(30,120,255,255));
    infa->setColor(QColor(255,0,0,255));
    reca->setColor(QColor(96,46,15,255));
    this->chart = new QChart();
    chart->addSeries(susa);
    chart->addSeries(reca);
    chart->addSeries(infa);
    chart->addSeries(vaca);
    chart->setTitle("Evolucion de la pandemia");
    chart->createDefaultAxes();
    this->chartView = new QChartView(chart);
    this->setCentralWidget(chartView);
    this->flag = true;
    settings = new Settings(this,this->simulator->getN(),this->simulator->getI(),this->simulator->getItime());
    this->installEventFilter(this);
}
/**
 * @brief MainWindow::~MainWindow: Destructor de Mainwindow.
 */
MainWindow::~MainWindow()
{
    delete ui;
}
/**
 * @brief MainWindow::on_actionStart_triggered: SLOT a ejecutar al pulsar start.
 */
void MainWindow::on_actionStart_triggered()
{
    this->CloseSet(this->settings->N,this->settings->I,this->settings->I_time);
    this->resetgraph();
    timer->start(200);
    simulator->startSimulation();
    flag = false;
}

/**
 * @brief MainWindow::on_actionStop_triggered: SLOT a ejecutar al pulsar stop.
 */
void MainWindow::on_actionStop_triggered()
{
    simulator->stopSimulation();
    this->simulator->neutral();
    timer->stop();
    flag = true;
}
/**
 * @brief MainWindow::on_actionSettings_triggered: SLOT a ejecutar al pulsar settings.
 */
void MainWindow::on_actionSettings_triggered(){
    if(flag){
        settings->show();
    }
}
/**
 * @brief MainWindow::actgraph: SLOT a ejecutar cada timeout del Timer.
 */
void MainWindow::actgraph(){
    //Agregamos los nuevos puntos al grafico.
    this->vac->append(simulator->gettime(),simulator->getvac());
    this->inf->append(simulator->gettime(),simulator->getinf());
    this->rec->append(simulator->gettime(),simulator->getrec());
    this->sus->append(simulator->gettime(),simulator->getsus());
    this->susrec->append(simulator->gettime(),simulator->getvac()+simulator->getsus()+simulator->getrec()+simulator->getinf());
    this->recinf->append(simulator->gettime(),simulator->getvac()+simulator->getinf()+simulator->getrec());
    this->vacinf->append(simulator->gettime(),simulator->getvac()+simulator->getinf());
    delete this->vaca;
    delete this->infa;
    delete this->reca;
    delete this->susa;
    this->vaca = new QAreaSeries(vac);
    this->infa = new QAreaSeries(vacinf,vac);
    this->reca = new QAreaSeries(recinf,inf);
    this->susa = new QAreaSeries(susrec,rec);
    susa->setName("Susceptibles");
    infa->setName("Infectados");
    reca->setName("Recuperados");
    vaca->setName("Vacunados");
    vaca->setColor(QColor(149, 255, 128, 255));
    susa->setColor(QColor(30,120,255,255));
    infa->setColor(QColor(255,0,0,255));
    reca->setColor(QColor(96,46,15,255));
    chart->removeAllSeries();
    chart->addSeries(susa);
    chart->addSeries(reca);
    chart->addSeries(infa);
    chart->addSeries(vaca);
    chart->setTitle("Evolucion de la pandemia");
    chart->createDefaultAxes();
    chartView->setChart(chart);
}

/**
 * @brief MainWindow::resetgraph: Metodo para reiniciar el grafico.
 */
void MainWindow::resetgraph(){
    delete this->inf;
    delete this->sus;
    delete this->rec;
    delete this->infa;
    delete this->susa;
    delete this->reca;
    delete this->vaca;
    delete this->chart;
    delete this->chartView;
    this->inf = new QLineSeries();
    this->sus = new QLineSeries();
    this->rec = new QLineSeries();
    this->vac = new QLineSeries();
    this->susrec = new QLineSeries();
    this->recinf = new QLineSeries();
    this->vacinf = new QLineSeries();
    this->vaca = new QAreaSeries(vac);
    this->infa = new QAreaSeries(vacinf,vac);
    this->reca = new QAreaSeries(recinf,inf);
    this->susa = new QAreaSeries(susrec,rec);
    susa->setName("Susceptibles");
    infa->setName("Infectados");
    reca->setName("Recuperados");
    vaca->setName("Vacunados");
    vaca->setColor(QColor(149, 255, 128, 255));
    susa->setColor(QColor(30,120,255,255));
    infa->setColor(QColor(255,0,0,255));
    reca->setColor(QColor(96,46,15,255));
    this->chart = new QChart();
    chart->addSeries(susa);
    chart->addSeries(reca);
    chart->addSeries(infa);
    chart->addSeries(vaca);
    chart->setTitle("Evolucion de la pandemia");
    chart->createDefaultAxes();
    this->chartView = new QChartView(chart);
    this->setCentralWidget(chartView);
}
/**
 * @brief MainWindow::CloseSet: Al cerrar ventana de settings guarda los valores
 */
void MainWindow::CloseSet(int N, int I, int Itime){
    this->simulator->setN(N);
    this->simulator->setI(I);
    this->simulator->setItime(Itime);
}

/**
 *  @brief MainWindow::eventFilter: Metodo que realiza la logica para acelerar y ralentizar segun la tecla presionada
 */
bool MainWindow::eventFilter(QObject *obj, QEvent *event){
    if (obj == this) {
        if (event->type() == QEvent::KeyPress) {
            QKeyEvent *keyEvent = static_cast<QKeyEvent*>(event);
            if(keyEvent->key() == 16777234){
                this->simulator->slower();
            }
            else if(keyEvent->key() == 16777236){
                this->simulator->faster();
            }
            return true;
        }
        else {
            return false;
        }
    }
    else {
        // pass the event on to the parent class
        return QMainWindow::eventFilter(obj, event);
    }
}
