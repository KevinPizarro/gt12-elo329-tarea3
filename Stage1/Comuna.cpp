#include "Comuna.h"
Comuna::Comuna(double width, double length): territory(0,0,width,length){
    pPerson=NULL;
}
double Comuna::getWidth() const {
    return //.....
}
double Comuna::getHeight() const {
    return //.....
}
void Comuna::setPerson(Pedestrian & person){
   //....
}
void Comuna::computeNextState (double delta_t) {
   //...
}
void Comuna::updateState () {
   //....
}
string Comuna::getStateDescription(){
    return //....
}
string Comuna::getState() const{
    return //...
}
