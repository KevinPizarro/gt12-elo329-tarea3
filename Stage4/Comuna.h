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
     */
    vector <Pedestrian> *pPerson;
    /**
     * @brief Rectangulo que representa la comuna.
     */
    QRect territory; 
    /**
     * @brief Numero de infectados.
     */
    int N_I;
    /**
     * @brief Numero total de individuos.
     */
    int N_T;
    /**
     * @brief Tiempo para recuperarse de la infeccion.
     */
    double rec_time;
    /**
     *  @brief Velocidad de movimiento de los individuos.
     */
    double speed;
    /**
     *  @brief Variacion maxima del angulo del individuo
     */
    double deltaAngle;
    /**
     * @brief Distancia de contagio
     */
    double d;
    /**
     * @brief Proporcion de individuos con mascarilla.
     */
    double M;
    /**
     * @brief Probabilidad de contagio sin mascarillas.
     */
    double p0;
    /**
     * @brief Probabilidad de contagio un individuo sin mascarilla.
     */
    double p1;
    /**
     * @brief Probabilidad de contagio de ambos individuos con mascarilla.
     */
    double p2;
    /**
     * @brief Numero aleatorio para comprobar si hay o no infeccion.
     */
    QRandomGenerator myRand2;

public:
    /**
     * @brief Construct a new Comuna::Comuna object
     * @param width: Ancho de la comuna.
     * @param length: Alto de la comuna.
     * @param speed: Velocidad base de movimiento de los individuos.
     * @param deltaAngle: Variacion de angulo de movimiento de los individuos.
     * @param N_T: Numero total de individuos.
     * @param N_I: Numero de Infectados.
     * @param rec_time: Duracion de la infeccion.
     * @param d: Distancia maxima de contagio.
     * @param M: Proporcion de individuos con mascarilla.
     * @param p0: Probabilidad de contagio sin mascarillas.
     * @param p1: Probabilidad de contagio un individuo sin mascarilla.
     * @param p2: Probabilidad de contagio con mascarillas.
     */
    Comuna(double width, double length, double speed, double deltaAngle, int N_T, int N_I, double rec_time, double d, double M, double p0, double p1, double p2);
    /**
     * @brief Comuna::getWidth: Metodo que obtiene el ancho de la comuna
     * @return Ancho de la comuna
     */
    double getWidth() const;
    /**
     * @brief Comuna::getHeight: Metodo que obtiene el largo de la comuna
     * @return Largo de la comuna
     */
    double getHeight() const;
    /**
     * @brief Comuna::computeNextState:  Metodo que computa el proximo estado para todos los individuos
     * @param delta_t Variacion del tiempo entre cada calculo del estado
     */
    void computeNextState (double delta_t);
    /**
     * @brief Comuna::updateState Se actualiza la posición del individuo
     */
    void updateState ();
    /**
     * @brief Comuna::getStateDescription: Metodo que entrega el encabezado de la salida por consola
     * @return Se obtiene la descripcion del estado de la persona
     */
    static string getStateDescription();
    /**
     * @brief getState: Metodo que regresa la cantidad de individuos en relacion a su estado de salud.
     * @return Obtiene los numeros de infectados, recuperados y susceptibles.
     */
    string getState() const;
    /**
     * @brief getinf: Metodo para obtener la cantidad actual de individuos infectados.
     * @return int con la cantidad de individuos infectados.
     */
    int getinf();
    /**
     * @brief getsus: Metodo para obtener la cantidad actual de individuos susceptibles.
     * @return int con la cantidad de individuos susceptibles.
     */
    int getsus();
    /**
     * @brief getrec: Metodo para obtener la cantidad actual de individuos recuperados.
     * @return int con la cantidad de individuos recuperados.
     */
    int getrec();
    /**
     * @brief setPerson: Metodo para reiniciar las personas de la comuna.
     */
    void setPerson();
 };

#endif // COMUNA_H
