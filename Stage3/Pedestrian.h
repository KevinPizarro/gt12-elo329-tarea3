#ifndef PEDESTRIAN_H
#define PEDESTRIAN_H
#include <string>
#include <QRandomGenerator>

using namespace std;
enum State{
    S,I,R //S para susceptibles, I para infectados, R para recuperados
};
class Comuna;
class Pedestrian{
private:
    double x, y, speed, angle, deltaAngle;
    double x_tPlusDelta, y_tPlusDelta;
    double rec_time;
    State state;
    Comuna *comuna;
    QRandomGenerator myRand; // see https://doc.qt.io/qt-5/qrandomgenerator.html

public:
    Pedestrian(Comuna *com, double speed, double deltaAngle);
    static string getStateDescription() {
        return "Inf,\tRec,\tSus";
    };
    State getState();
    void computeNextState(double delta_t);
    void updateState();
    double getX();
    double getY();
    void infect(double rec);
};


#endif // PEDESTRIAN_H
