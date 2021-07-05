#include "Comuna.h"
/**
 * @brief Comuna::Comuna Se encarga de crear el objeto correspondiente a la persona, inicializa el tamaño de la comuna y se calcula el siguiente
 * estado del individuo
 * @param width Ancho de la comuna
 * @param length Largo de la comuna
 */
Comuna::Comuna(double width, double length) : territory(0, 0, width, length) {
    pPerson = NULL;
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
 * @brief Comuna::setPerson
 * @param person Se inicializa la persona
 */
void Comuna::setPerson(Pedestrian& person) {
    pPerson = &person;
}
/**
 * @brief Comuna::computeNextState
 * @param delta_t Variacion del tiempo entre cada calculo del estado
 */
void Comuna::computeNextState(double delta_t) {
    pPerson->computeNextState(delta_t);
}
/**
 * @brief Comuna::updateState Se actualiza la posición del individuo
 */
void Comuna::updateState() {
    pPerson->updateState();
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
 * @return La posicion de la persona
 */
string Comuna::getState() const {
    return pPerson->getState();
}
