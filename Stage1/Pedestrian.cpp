#include <QtMath> // for M_PI and functions, see https://doc.qt.io/qt-5/qtmath.html
#include <string>
#include "Comuna.h"
#include "Pedestrian.h"

/**
 * @brief Pedestrian::Pedestrian: Clase de los individuos, contiene todos la informacion del individuo, asi como los metodos que utilizan al mismo
 * @param com: comuna a la que pertenece el individuo
 * @param speed: velocidad del individuo
 * @param deltaAngle: Variacion maxima del angulo del individuo
 */
Pedestrian::Pedestrian (Comuna &com, double speed, double deltaAngle): comuna(com) {
    myRand = QRandomGenerator::securelySeeded();
    this->x = myRand.generateDouble()*com->getWidth();
    this->y = myRand.generateDouble()*com->getHeight();
    this->speed = speed*(0.9+0.2*myRand.generateDouble());
    this->deltaAngle = deltaAngle;
}
/**
 * @brief Pedestrian::getState Metodo para obtener el estado actual del individuo
 * @return Retorna string con estado de la persona
 */
string Pedestrian::getState() const {
    string s=to_string(x) + ",\t";
    s+= to_string(y);
    return s;
}
/**
 * @brief Pedestrian::computeNextState: Metodo para calcular el estado del individuo
 * @param delta_t: Cantidad de tiempo que ha pasado desde el calculo anterior
 */
void Pedestrian::computeNextState(double delta_t) {
    double r=myRand.generateDouble(); //Escalar para multiplicar la variacion del angulo
    angle+=deltaAngle*(1-2*r); //Calculamos el nuevo angulo
    x_tPlusDelta=x+speed*qCos(angle)*delta_t; //Calculamos la nueva posicion en X
    y_tPlusDelta=y+speed*qSin(angle)*delta_t; //Calculamos la nueva posicion en Y
    if(x_tPlusDelta < 0){   // rebound logic in x, left side
        angle = M_PI - angle;
        x_tPlusDelta=x+speed*qCos(angle)*delta_t;
        }
    else if( x_tPlusDelta > comuna.getWidth()){ //rebound logic in x, right side
        angle = M_PI - angle;
        x_tPlusDelta=x+speed*qCos(angle)*delta_t;
    }
    if(y_tPlusDelta < 0){   // rebound logic in y, down side
        angle = 2*M_PI - angle;
        y_tPlusDelta=y+speed*qSin(angle)*delta_t;
     }
    else if( y_tPlusDelta > comuna.getHeight()){ //rebound logic in y, up side
        angle = 2*M_PI - angle;
        y_tPlusDelta=y+speed*qSin(angle)*delta_t;
    }
}
/**
 * @brief Pedestrian::updateState: Metodo para actualizar la posicion del individuo
 */
void Pedestrian::updateState(){
    x=x_tPlusDelta;
    y=y_tPlusDelta;
}
