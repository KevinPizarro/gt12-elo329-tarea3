#include "Comuna.h"
#include "Simulator.h"
#include "Pedestrian.h"
#include <QCoreApplication>
#include <iostream>
#include <fstream>
using namespace std;
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    if (argc != 2){
        cout << "Usage: stage1 <configurationFile.txt>" << endl;
        exit(-1);
    }
    ifstream fin(argv[1]); //Recibimos los argumentos de entrada
    /**
     * @brief N: Cantidad de individuos total.
     */
    double N;
    /**
     * @brief I: Cantidad inicial de individuos infectados.
     */
    double I;
    /**
     * @brief I_time: Tiempo de duracion de la infeccion.
     */
    double I_time;
    /**
     * @brief comunaWidth: Ancho de la comuna.
     */
    double comunaWidth;
    /**
     * @brief comunaLength: Alto de la comuna.
     */
    double comunaLength;
    /**
     * @brief speed: Parametro de velocidad, el individuo se movera entre 0.9 y 1.1 veces esta velocidad.
     */
    double speed;
    /**
     * @brief delta_t: Variacion del paso de tiempo.
     */
    double delta_t;
    /**
     * @brief deltaAngle: Variacion maxima del angulo de movimiento.
     */
    double deltaAngle;
    //Guardamos los parametros en las variables
    fin >> N >> I >> I_time;
    fin >> comunaWidth >> comunaLength;
    fin >> speed >> delta_t >> deltaAngle;
    /**
     * @brief samplingTime: Tiempo de muestreo.
     */
    double samplingTime = 1.0;
    /**
     * @brief comuna: Comuna de la simulacion.
     * @return Objeto de tipo comuna.
     */
    Comuna comuna(comunaWidth, comunaLength);
    /**
     * @brief person: Individuo de la simulacion.
     * @return Objeto de tipo pedestrian.
     */
    Pedestrian person(comuna, speed, deltaAngle);
    comuna.setPerson(person);
    /**
     * @brief sim: Simulador.
     * @return Objeto de tipo simulator.
     */
    Simulator sim(cout, comuna, delta_t, samplingTime);
    sim.startSimulation(); //Iniciamos la simulacion.
    return a.exec();
}
