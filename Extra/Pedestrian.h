#ifndef PEDESTRIAN_H
#define PEDESTRIAN_H
#include <string>
#include <QRandomGenerator>

using namespace std;
enum State{
    S,I,R,V //S para susceptibles, I para infectados, R para recuperados, V para Vacunados
};
class Comuna;
class Pedestrian{
private:
    double x, y, speed, angle, deltaAngle;
    double x_tPlusDelta, y_tPlusDelta;
    double rec_time;
    bool mask;
    State state;
    Comuna *comuna;
    QRandomGenerator myRand;

public:
    Pedestrian(Comuna *com, double speed, double deltaAngle);
    static string getStateDescription() {
        return "Vac\tInf,\tRec,\tSus";
    };
    State getState();
    void computeNextState(double delta_t);
    void updateState();
    double getX();
    double getY();
    void infect(double rec);
    void putMask();
    bool getMask();
    void vaccine();
};


#endif // PEDESTRIAN_H
