#include "Comuna.h"
#include <QtMath>
#include <string>
#include <iostream>
using namespace std;

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
Comuna::Comuna(double width, double length, double speed, double deltaAngle, int N_T, int N_I, double rec_time, double d, double M, double p0, double p1, double p2, int NumVac, int VacSize, int VacTime) : territory(0, 0, width, length) {
    this->pPerson = new vector <Pedestrian>;
    this->rec_time = rec_time;
    this->speed = speed;
    this->deltaAngle = deltaAngle;
    this->d = d;
    this->M = M;
    this->p0 = p0;
    this->p1 = p1;
    this->p2 = p2;
    this->N_I = N_I;
    this->N_T = N_T;
    this->NumVac = NumVac;
    this->VacSize = VacSize;
    this->VacTime = VacTime;
    this->vacflag = true;
    myRand2 = QRandomGenerator::securelySeeded();
    for(int i=0;i<N_T;i++){//Inicializacion de todos los individuos
        if(i < N_I){//Se infectan N_I individuos inicialmente
            pPerson->push_back(Pedestrian(this, speed, deltaAngle));
            pPerson->at(i).infect(rec_time);
            if(i < N_I*M){//Logica para colocar mascarillas
                pPerson->at(i).putMask();
            }
        }
        else{
            pPerson->push_back(Pedestrian(this, speed, deltaAngle));
            if(i - N_I < (N_T-N_I)*M){//Logica para colocar mascarillas
                pPerson->at(i).putMask();
            }
       }
    }
}
/**
 * @brief Comuna::getWidth: Metodo que obtiene el ancho de la comuna
 * @return Ancho de la comuna
 */
double Comuna::getWidth() const {
    return territory.width();
}
/**
 * @brief Comuna::getHeight: Metodo que obtiene el largo de la comuna
 * @return Largo de la comuna
 */
double Comuna::getHeight() const {
    return territory.height();
}
/**
 * @brief Comuna::computeNextState: Metodo que computa el proximo estado para todos los individuos
 * @param delta_t Variacion del tiempo entre cada calculo del estado
 */
void Comuna::computeNextState(double delta_t, double st) {
    if(this->VacTime <= st && vacflag){
        this->setVac();
        this->vacflag = false;
    }
    for(int i=0;i < (int)pPerson->size();i++){ //Calculamos el estado de contagio persona a persona.
        for(int j=0; j< (int)pPerson->size();j++){ //Revisamos el resto de personas.
            if(st >= this->VacTime){
                if(pPerson->at(i).getState() == S && existVac(pPerson->at(i))){
                    pPerson->at(i).vaccine();
                }
            }
            if(pPerson->at(i).getState() == S && pPerson->at(j).getState() == I){
                double e =  qSqrt(qPow(pPerson->at(i).getX() - pPerson->at(j).getX(),2) + qPow(pPerson->at(i).getY() - pPerson->at(j).getY(),2));
                if(e < d){
                    if((pPerson->at(i).getMask() == true) && (pPerson->at(j).getMask() == true)){
                        if(myRand2.generateDouble() <= p2){
                            pPerson->at(i).infect(rec_time);
                        }
                    }
                    else if(((pPerson->at(i).getMask() == true) && (pPerson->at(j).getMask() == false)) || ((pPerson->at(i).getMask() == false) && (pPerson->at(j).getMask() == true))){
                        if(myRand2.generateDouble() <= p1){
                            pPerson->at(i).infect(rec_time);
                        }
                    }
                    else{
                        if(myRand2.generateDouble() <= p0){
                            pPerson->at(i).infect(rec_time);
                        }
                    }
                }
            }
        }
    }
    for(int i=0; i < (int)pPerson->size();i++) { //Calculamos los el siguiente estado de todos los individuos.
        pPerson->at(i).computeNextState(delta_t);
    }
    st += delta_t;
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
 * @brief Comuna::getStateDescription: Metodo que entrega el encabezado de la salida por consola
 * @return Se obtiene la descripcion del estado de la persona
 */
string Comuna::getStateDescription() {
    return Pedestrian::getStateDescription();
}
/**
 * @brief Comuna::getState: Metodo que regresa la cantidad de individuos en relacion a su estado de salud.
 * @return Obtiene los numeros de infectados, recuperados y susceptibles.
 */
string Comuna::getState() const {
    int sus=0,inf=0,rec=0,vac=0;
    for(int i=0; i < (int)pPerson->size();i++){//Revisa el estado para cada individuo e incrementa sus contadores respectivos
        State status = pPerson->at(i).getState();
        switch (status){
        case V:
            vac++;
            break;
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
    string s = to_string(vac) + ",\t" + to_string(inf) + ",\t" + to_string(rec) + ",\t" + to_string(sus);
    return s;
}
/**
 * @brief Comuna::getinf: Metodo para obtener la cantidad actual de individuos infectados.
 * @return int con la cantidad de individuos infectados.
 */
int Comuna::getinf(){
    int inf = 0;
    for(int i=0; i < (int)pPerson->size();i++){
        if(pPerson->at(i).getState() == I){
            inf++;
        }
    }
    return inf;
}

/**
 * @brief Comuna::getrec: Metodo para obtener la cantidad actual de individuos recuperados.
 * @return int con la cantidad de individuos recuperados.
 */
int Comuna::getrec(){
    int rec = 0;
    for(int i=0; i < (int)pPerson->size();i++){
        if(pPerson->at(i).getState() == R){
            rec++;
        }
    }
    return rec;
}

/**
 * @brief Comuna::getsus: Metodo para obtener la cantidad actual de individuos susceptibles.
 * @return int con la cantidad de individuos susceptibles.
 */
int Comuna::getsus(){
    int sus = 0;
    for(int i=0; i < (int)pPerson->size();i++){
        if(pPerson->at(i).getState() == S){
            sus++;
        }
    }
    return sus;
}

/**
 * @brief Comuna::getvac: Metodo para obtener la cantidad actual de individuos vacunados.
 * @return int con la cantidad de individuos vacunados.
 */
int Comuna::getvac(){
    int vac = 0;
    for(int i=0; i < (int)pPerson->size();i++){
        if(pPerson->at(i).getState() == V){
            vac++;
        }
    }
    return vac;
}


/**
 * @brief Comuna::setPerson: Metodo para reiniciar las personas de la comuna.
 */
void Comuna::setPerson(){
    this->pPerson = new vector<Pedestrian>;
    for(int i=0;i<N_T;i++){
        if(i < N_I){
            pPerson->push_back(Pedestrian(this, speed, deltaAngle));
            pPerson->at(i).infect(rec_time);
            if(i < N_I*M){
                pPerson->at(i).putMask();
            }
        }
        else{
            pPerson->push_back(Pedestrian(this, speed, deltaAngle));
            if(i - N_I < (N_T-N_I)*M){
                pPerson->at(i).putMask();
            }
        }
    }
}
/**
 * @brief Comuna::getN
 * @return el numero total de individuos
 */
int Comuna::getN(){
    return this->N_T;
}
/**
 * @brief Comuna::setN
 * @param N El nuevo numero total de individuos
 */
void Comuna::setN(int N){
    this->N_T = N;
}
/**
 * @brief Comuna::getI
 * @return Numero de infectados
 */
int Comuna::getI(){
    return this->N_I;
}
/**
 * @brief Comuna::setI
 * @param I El nuevo numero de infectados
 */
void Comuna::setI(int I){
    this->N_I = I;
}
/**
 * @brief Comuna::getItime
 * @return El tiempo de recuperacion
 */
int Comuna::getItime(){
    return this->rec_time;
}
/**
 * @brief Comuna::setItime
 * @param Itime El nuevo tiempo de recuperacion
 */
void Comuna::setItime(int Itime){
    this->rec_time = Itime;
}
/**
 * @brief Comuna::setVac Contiene la logica de vacunacion
 */
void Comuna::setVac(){
    double x;
    double y;
    bool flag = false;
    int cont = 0;
    QRect vac;
    QRect vac1;
    do{
        this->Vac = new vector <QRect>;
        cont = 0;
        flag = false;
        for(int i = 0; i < this->NumVac ; i++){
            x = myRand2.generateDouble()*this->getWidth();
            y = myRand2.generateDouble()*this->getHeight();
            if(x >= this->getWidth() - this->VacSize){
                x -= this->VacSize;
                if(x < 0){
                    x = 0;
                }
            }
            if(y >= this->getHeight() - this->VacSize){
                y -= this->VacSize;
                if(y < 0){
                    y = 0;
                }
            }
            if(i == 0){
                vac1 = QRect(x,y,this->VacSize,this->VacSize);
                this->Vac->push_back(vac1);
            }
            else{
                vac = QRect(x,y,this->VacSize,this->VacSize);
                if(interVac(vac)){
                    while(interVac(vac)){
                        x = myRand2.generateDouble()*this->getWidth();
                        y = myRand2.generateDouble()*this->getHeight();
                        if(x >= this->getWidth() - this->VacSize){
                            x -= this->VacSize;
                            if(x < 0){
                                x = 0;
                            }
                        }
                        if(y >= this->getHeight() - this->VacSize){
                            y -= this->VacSize;
                            if(y < 0){
                                y = 0;
                            }
                        }
                        vac = QRect(x,y,this->VacSize,this->VacSize);
                        cont++;
                        if(cont > 10){
                            flag = true;
                            delete(this->Vac);
                            break;
                        }
                    }
                }
            this->Vac->push_back(vac);
            }
        }
    } while(flag);
}
/**
 * @brief Comuna::existVac
 * @param p El pedestrian sobre el que se hace la consutla
 * @return Si el pedestrian esta sobre un vacunatorio
 */
bool Comuna::existVac(Pedestrian p){
    for(int i=0; i < (int)this->Vac->size();i++){
        if(this->Vac->at(i).contains(p.getX(),p.getY())){
            return true;
        }
    }
    return false;
}
/**
 * @brief Comuna::interVac
 * @param vac Vacunatorio
 * @return Si es que el vacunatorio consultado se intersecta con otro ya creado
 */
bool Comuna::interVac(QRect vac){
    for(int i=0; i < (int)this->Vac->size();i++){
        if(this->Vac->at(i).intersects(vac)){
            return true;
        }
    }
    return false;
}
