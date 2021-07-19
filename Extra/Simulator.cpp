#include "Simulator.h"
/**
 * @brief Simulator::Simulator: Constructor de la clase Simulator, la cual inicializa los datos segun lo leido desde el archivo config.txt
 * @param output: Objeto para imprimir datos de salida
 * @param com: Comuna a la que pertenece el individuo
 * @param delta: Variacion del paso de tiempo
 * @param st: Tiempo de muestreo para la simulacion
 */
Simulator::Simulator(ostream &output, Comuna &com,
                     double delta, double st): comuna(com),out(output){
    t=0;
    delta_t=delta;
    samplingTime=st;
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()),
            this, SLOT(simulateSlot()));
}
/**
 * @brief Simulator::~Simulator : Destructor de la clase simulator que cierra el archivo
 */
Simulator::~Simulator(){
    this->archivo.close();
}
/**
 * @brief Simulator::printStateDescription: Metodo para imprimir la cabecera del estado
 */
string Simulator::printStateDescription() const {
    string s = "Time,\t" + comuna.getStateDescription();
    out << s << endl;
    return s;
}

/**
 * @brief Simulator::printState: Metodo para imprimir los valores de estado para un tiempo t
 * @param t: Tiempo en el cual se imprimira el estado
 */
string Simulator::printState(double t) const{
    string s = to_string(t) + ",\t";
    s += comuna.getState();
    out << s << endl;
    return s;
}

/**
 * @brief Simulator::startSimulation: Metodo para iniciar la simulacion en tiempo 0 y segun el samplingTime
 */
void Simulator::startSimulation(){
    stopSimulation();
    this->archivo.open("Salida.txt");
    archivo << printStateDescription() << endl;
    t=0;
    archivo << printState(t) << endl;
    timer->start(1000*samplingTime);//Llama al metodo start de la clase QTimer para dar inicio al temporizador
}
/**
 * @brief Simulator::stopSimulation: Metodo para parar la simulacion.
 */
void Simulator::stopSimulation(){
    timer->stop();
    archivo.close();
    this->comuna.setPerson();
}
/**
 * @brief Simulator::simulateSlot: Metodo para ejecutar una seccion de la simulacion
 */
void Simulator::simulateSlot(){
    /**
     * @brief nextStop: Define la duracion de la seccion de simulacion
     */
    double nextStop=t+samplingTime;
    while(t < nextStop) {     // Computa y actualiza nuevos estados hasta que se cumpla el tiempo de la seccion de simulacion
       this->comuna.computeNextState(delta_t,gettime()); // Computa el nuevo valor de estado para la comuna
       this->comuna.updateState();  // Actualiza el estado de la comuna
       t+=delta_t;
    }
    archivo << printState(t) << endl;  // Al terminar la seccion imprime el estado para ese determinado tiempo
}
/**
 * @brief Comuna::getinf: Metodo para obtener la cantidad actual de individuos infectados.
 * @return int con la cantidad de individuos infectados.
 */
int Simulator::getinf(){
    return this->comuna.getinf();
}
/**
 * @brief Comuna::getrec: Metodo para obtener la cantidad actual de individuos recuperados.
 * @return int con la cantidad de individuos recuperados.
 */
int Simulator::getrec(){
    return this->comuna.getrec();
}
/**
 * @brief Comuna::getsus: Metodo para obtener la cantidad actual de individuos susceptibles.
 * @return int con la cantidad de individuos susceptibles.
 */
int Simulator::getsus(){
    return this->comuna.getsus();
}

/**
 * @brief Comuna::getvac: Metodo para obtener la cantidad actual de individuos vacunados.
 * @return int con la cantidad de individuos vacunados.
 */
int Simulator::getvac(){
    return this->comuna.getvac();
}
/**
 * @brief Simulator::gettime: Metodo para obtener el tiempo actual de la simulacion.
 * @return int con el tiempo actual.
 */
int Simulator::gettime(){
    return t;
}
/**
 * @brief getN: Obtiene el numero de individuos de la simulacion.
 * @return Int con la cantidad de individuos.
 */
int Simulator::getN(){
    return this->comuna.getN();
}

/**
 * @brief setN: Modifica la cantidad de individuos de la simulacion.
 * @param N: Cantidad de individuos.
 */
void Simulator::setN(int N){
    this->comuna.setN(N);
}

/**
 * @brief getI: Obtiene el numero de individuos infectados de la simulacion.
 * @return Int con la cantidad de individuos infectados.
 */
int Simulator::getI(){
    return this->comuna.getI();
}

/**
 * @brief setN: Modifica la cantidad de individuos infectados de la simulacion.
 * @param I: Cantidad de individuos infectados.
 */
void Simulator::setI(int I){
    this->comuna.setI(I);
}

/**
 * @brief getItime: Obtiene el tiempo de infeccion de la simulacion.
 * @return Int que representa la cantidad de tiempo que dura la infeccion.
 */
int Simulator::getItime(){
    return this->comuna.getItime();
}

/**
 * @brief setItime: Modifica el tiempo de infeccion de la simulacion.
 * @param Itime: Nuevo tiempo de infeccion.
 */
void Simulator::setItime(int Itime){
    this->comuna.setItime(Itime);
}
/**
 * @brief Simulator::faster: Metodo para acelerar el paso del tiempo de la simulacion.
 */
void Simulator::faster(){
    this->timer->setInterval(timer->interval()/2);
}
/**
 * @brief Simulator::slower: Metodo para disminuir el paso del tiempo de la simulacion.
 */
void Simulator::slower(){
    this->timer->setInterval(timer->interval()*2);
}
/**
 * @brief Simulator::neutral: Metodo para reiniciar el paso del tiempo de la simulacion.
 */
void Simulator::neutral(){
    this->timer->setInterval(1000*samplingTime);
}
