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
 * @brief Simulator::printStateDescription: Metodo para imprimir la cabecera del estado
 */
void Simulator::printStateDescription() const {
    string s = "time,\t" + comuna.getStateDescription();
    out << s << endl;
}

/**
 * @brief Simulator::printState: Metodo para imprimir los valores de estado para un tiempo t
 * @param t: Tiempo en el cual se imprimira el estado
 */
void Simulator::printState(double t) const{
    string s = to_string(t) + ",\t";
    s += comuna.getState();
    out << s << endl;
}

/**
 * @brief Simulator::startSimulation: Metodo para iniciar la simulacion en tiempo 0 y segun el samplingTime
 */
void Simulator::startSimulation(){
    printStateDescription();
    t=0;
    printState(t);
    timer->start(1000*samplingTime);//Llama al metodo start de la clase QTimer para dar inicio al temporizador
}

/**
 * @brief Simulator::simulateSlot: Metodo para ejecutar una seccion de la simulacion
 */
void Simulator::simulateSlot(){
    /**
     * @brief nextStop: Define la duracion de la seccion de simulacion
     */
    double nextStop=t+samplingTime;
    while(t<nextStop) {     // Computa y actualiza nuevos estados hasta que se cumpla el tiempo de la seccion de simulacion
       comuna.computeNextState(delta_t); // Computa el nuevo valor de estado para la comuna
       comuna.updateState();  // Actualiza el estado de la comuna
       t+=delta_t;
    }
    printState(t);  // Al terminar la seccion imprime el estado para ese determinado tiempo 
}