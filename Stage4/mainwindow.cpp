#include "mainwindow.h"
#include "ui_mainwindow.h"
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
    this->susrec = new QLineSeries();
    this->recinf = new QLineSeries();
    this->infa = new QAreaSeries(inf);
    this->reca = new QAreaSeries(rec,inf);
    this->susa = new QAreaSeries(sus,rec);
    susa->setName("Susceptibles");
    infa->setName("Infectados");
    reca->setName("Recuperados");
    susa->setColor(QColor(30,120,255,255));
    infa->setColor(QColor(255,0,0,255));
    reca->setColor(QColor(96,46,15,255));
    this->chart = new QChart();
    chart->addSeries(infa);
    chart->addSeries(reca);
    chart->addSeries(susa);
    chart->setTitle("Evolucion de la pandemia");
    chart->createDefaultAxes();
    this->chartView = new QChartView(chart);
    this->setCentralWidget(chartView);
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
    this->resetgraph();
    timer->start(200);
    simulator->startSimulation();
}

/**
 * @brief MainWindow::on_actionStop_triggered: SLOT a ejecutar al pulsar stop.
 */
void MainWindow::on_actionStop_triggered()
{
    simulator->stopSimulation();
    timer->stop();
}

/**
 * @brief MainWindow::actgraph: SLOT a ejecutar cada timeout del Timer.
 */
void MainWindow::actgraph(){
    //Agregamos los nuevos puntos al grafico.
    this->inf->append(simulator->gettime(),simulator->getinf());
    this->rec->append(simulator->gettime(),simulator->getrec());
    this->sus->append(simulator->gettime(),simulator->getsus());
    this->susrec->append(simulator->gettime(),simulator->getsus()+simulator->getrec()+simulator->getinf());
    this->recinf->append(simulator->gettime(),simulator->getinf()+simulator->getrec());
    delete this->infa;
    delete this->reca;
    delete this->susa;
    this->infa = new QAreaSeries(inf);
    this->reca = new QAreaSeries(recinf,inf);
    this->susa = new QAreaSeries(susrec,rec);
    susa->setName("Susceptibles");
    infa->setName("Infectados");
    reca->setName("Recuperados");
    susa->setColor(QColor(30,120,255,255));
    infa->setColor(QColor(255,0,0,255));
    reca->setColor(QColor(96,46,15,255));
    chart->removeAllSeries();
    chart->addSeries(susa);
    chart->addSeries(reca);
    chart->addSeries(infa);
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
    delete this->chart;
    delete this->chartView;
    this->inf = new QLineSeries();
    this->sus = new QLineSeries();
    this->rec = new QLineSeries();
    this->susrec = new QLineSeries();
    this->recinf = new QLineSeries();
    this->infa = new QAreaSeries(inf);
    this->reca = new QAreaSeries(recinf,inf);
    this->susa = new QAreaSeries(susrec,rec);
    susa->setName("Susceptibles");
    infa->setName("Infectados");
    reca->setName("Recuperados");
    susa->setColor(QColor(30,120,255,255));
    infa->setColor(QColor(255,0,0,255));
    reca->setColor(QColor(96,46,15,255));
    this->chart = new QChart();
    chart->addSeries(infa);
    chart->addSeries(reca);
    chart->addSeries(susa);
    chart->setTitle("Evolucion de la pandemia");
    chart->createDefaultAxes();
    this->chartView = new QChartView(chart);
    this->setCentralWidget(chartView);
}
