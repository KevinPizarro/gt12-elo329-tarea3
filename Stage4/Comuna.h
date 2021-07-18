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
     * @brief Vac: Vector de vacunatorios.
     */
    vector <QRect> *Vac;
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
     * @brief NumVac: Cantidad de Vacunatorios.
     */
    int NumVac;
    /**
     * @brief VacSize: Tamano de los vacunatorios.
     */
    int VacSize;
    /**
     * @brief VacTime: Tiempo para empezar a vacunar.
     */
    int VacTime;
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
     * @param NumVac: Cantidad de Vacunatorios.
     * @param VacSize: Tamano de los Vacunatorios.
     * @param VacTime: Tiempo al que empezar a Vacunar.
     */
    Comuna(double width, double length, double speed, double deltaAngle, int N_T, int N_I, double rec_time, double d, double M, double p0, double p1, double p2, int NumVac, int VacSize, int VacTime);
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
    /**
     * @brief computeNextState: Metodo que computa el proximo estado para todos los individuos
     * @param delta_t Variacion del tiempo entre cada calculo del estado
     * @param simt: tiempo actual de la simulacion.
     */
    void computeNextState(double delta_t, double st);
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
     * @brief getvac: Metodo para obtener la cantidad actual de individuos vacunados.
     * @return int con la cantidad de individuos vacunados.
     */
    int getvac();
    /**
     * @brief setPerson: Metodo para reiniciar las personas de la comuna.
     */
    void setPerson();

    /**
     * @brief getN: Obtiene el numero de individuos de la simulacion.
     * @return Int con la cantidad de individuos.
     */
    int getN();

    /**
     * @brief setN: Modifica la cantidad de individuos de la simulacion.
     * @param N: Cantidad de individuos.
     */
    void setN(int N);

    /**
     * @brief getI: Obtiene el numero de individuos infectados de la simulacion.
     * @return Int con la cantidad de individuos infectados.
     */
    int getI();

    /**
     * @brief setN: Modifica la cantidad de individuos infectados de la simulacion.
     * @param I: Cantidad de individuos infectados.
     */
    void setI(int I);

    /**
     * @brief getItime: Obtiene el tiempo de infeccion de la simulacion.
     * @return Int que representa la cantidad de tiempo que dura la infeccion.
     */
    int getItime();

    /**
     * @brief setItime: Modifica el tiempo de infeccion de la simulacion.
     * @param Itime: Nuevo tiempo de infeccion.
     */
    void setItime(int Itime);
    /**
     * @brief vacflag: Variable para verificar si se colocaron los vacunatorios.
     */
    bool vacflag;
    /**
     * @brief setVac: Metodo para setear los vacunatorios.
     */
    void setVac();
    /**
     * @brief exisVac: Metodo para revisar si existe un vacunatorio en la posicion del individuo.
     * @param X: Posicion en X del individuo.
     * @param Y: Posicion en Y del individuo.
     * @return true en caso de que este en un vacunatorio, false en caso contrario.
     */
    bool existVac(Pedestrian p);
    /**
     * @brief interVac: Metodo para verificar si intersecta con alguno de los vacunatorios ya creados.
     * @param vac: Vacunatorio nuevo.
     * @return true en caso de que intersecte, false en caso contrario
     */
    bool interVac(QRect vac);
 };

#endif // COMUNA_H
