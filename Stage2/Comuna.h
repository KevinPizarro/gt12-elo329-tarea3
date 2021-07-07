#ifndef COMUNA_H
#define COMUNA_H
#include "Pedestrian.h"
#include <QRect>
#include <string>
#include <vector>
using namespace std;
class Comuna {
private:
    /**
     * @brief Vector de personas.
     * 
     */
    vector <Pedestrian> *pPerson;
    /**
     * @brief Rectangulo que representa la comuna.
     * 
     */
    QRect territory; // Alternatively: double width, length;
    // but more methods would be needed.
    /**
     * @brief Numero de infectados.
     * 
     */
    int N_I;
    /**
     * @brief Numero total de individuos.
     * 
     */
    int N_T;
    /**
     * @brief Timepo para recuperarse de la infeccion.
     * 
     */
    double rec_time;
    /**
     * @brief Distancia de contagio
     * 
     */
    double d;
    /**
     * @brief Probabilidad de contagio sin mascarillas.
     * 
     */
    double p0;
    QRandomGenerator myRand2;

public:
    Comuna(double width, double length, double speed, double deltaAngle, int N_T, int N_I, double rec_time, double d, double p0);
    double getWidth() const;
    double getHeight() const;
    void computeNextState (double delta_t);
    void updateState ();
    static string getStateDescription();
    string getState() const;
 };

#endif // COMUNA_H
