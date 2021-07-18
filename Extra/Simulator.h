#ifndef SIMULATOR_H
#define SIMULATOR_H
#include "Comuna.h"
#include <ostream>
#include <QTimer>
#include <string>
#include <fstream>
class Simulator: public QObject { // By inheriting from QObject,
    //our class can use signal and slot mechanism Qt provides.
    Q_OBJECT
private:
    Comuna &comuna;
    ostream &out;
    double t;
    double delta_t, samplingTime;
    ofstream archivo;
public:
    Simulator (ostream &output, Comuna &comuna, double delta_t, double samplingTime);
    ~Simulator();
    string printStateDescription() const;
    string printState(double t) const;
    void startSimulation();
    void stopSimulation();
    int getinf();
    int getsus();
    int getrec();
    int getvac();
    int gettime();
    QTimer * timer;  // see https://doc.qt.io/qt-5.12/qtimer.html
    int getN();
    void setN(int N);
    int getI();
    void setI(int I);
    int getItime();
    void setItime(int Itime);
public slots:
    void simulateSlot();
};

#endif // SIMULATOR_H
