#include "Comuna.h"
#include <QtMath> // for M_PI and functions, see https://doc.qt.io/qt-5/qtmath.html
#include <string>
#include <iostream>
using namespace std;
/**
 * @brief Construct a new Comuna:: Comuna object
 * 
 * @param width: Ancho de la comuna.
 * @param length: Alto de la comuna.
 * @param speed:  Velocidad base de movimiento de los individuos.
 * @param deltaAngle: Variacion de angulo de movimiento de los individuos.
 * @param N_T: Numero total de individuos.
 * @param N_I: Numero de Infectados.
 * @param rec_time: Duracion de la infeccion.
 * @param d: Distancia maxima de contagio.
 * @param p0: Probabilidad de contagio sin mascarillos.
 */
Comuna::Comuna(double width, double length, double speed, double deltaAngle, int N_T, int N_I, double rec_time, double d, double p0) : territory(0, 0, width, length) {
    this->pPerson = new vector <Pedestrian>;
    this->rec_time = rec_time;
    this->d = d;
    this->p0 = p0;
    this->N_I = N_I;
    this->N_T = N_T;
    myRand2 = QRandomGenerator::securelySeeded();
    for(int i=0;i<N_T;i++){
        if(i < N_I){
            pPerson->push_back(Pedestrian(this, speed, deltaAngle));
            pPerson->at(i).infect(rec_time);
        }
        else{
            pPerson->push_back(Pedestrian(this, speed, deltaAngle));
        }
    }
}
/**
 * @brief Comuna::getWidth
 * @return Ancho de la comuna
 */
double Comuna::getWidth() const {
    return territory.width();
}
/**
 * @brief Comuna::getHeight
 * @return Largo de la comuna
 */
double Comuna::getHeight() const {
    return territory.height();
}
/**
 * @brief Comuna::computeNextState
 * @param delta_t Variacion del tiempo entre cada calculo del estado
 */
void Comuna::computeNextState(double delta_t) {
    for(int i=0;i < (int)pPerson->size();i++){ //Calculamos el estado de contagio persona a persona.
        for(int j=0; j< (int)pPerson->size();j++){ //Revisamos el resto de personas.
            if(pPerson->at(i).getState() == S && pPerson->at(j).getState() == I){ 
                double e =  qSqrt(qPow(pPerson->at(i).getX() - pPerson->at(j).getX(),2) + qPow(pPerson->at(i).getY() - pPerson->at(j).getY(),2));
                if(e < d){
                    if(myRand2.generateDouble() <= p0){
                       pPerson->at(i).infect(rec_time);
                    }
                }
            }
        }
    }
    for(int i=0; i < (int)pPerson->size();i++) { //Calculamos los el siguiente estado de todos los individuos.
        pPerson->at(i).computeNextState(delta_t);
    }
}
/**
 * @brief Comuna::updateState Se actualiza la posición del individuo
 */
void Comuna::updateState() {
    for(int i=0; i < (int)pPerson->size();i++) { //Actualizamos el estado de cada persona.
        pPerson->at(i).updateState();
    }
}
/**
 * @brief Comuna::getStateDescription
 * @return Se obtiene la descripcion del estado de la persona
 */
string Comuna::getStateDescription() {
    return Pedestrian::getStateDescription();
}
/**
 * @brief Comuna::getState
 * @return Obtiene los numeros de infectados, recuperados y susceptibles.
 */
string Comuna::getState() const {
    int sus=0,inf=0,rec=0;
    State status;
    for(int i=0; i < (int)pPerson->size();i++){
        status = pPerson->at(i).getState();
        switch (status){
            case R:
                rec++;
                break;
            case I:
                inf++;
                break;
            case S:
                sus++;
                break;
        }
    }
    string s = to_string(inf) + ",\t" + to_string(rec) + ",\t" + to_string(sus);
    return s;
}
