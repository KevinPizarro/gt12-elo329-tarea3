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
        cout << "Usage: stage3 <configurationFile.txt>" << endl;
        exit(-1);
    }
    ifstream fin(argv[1]); //Recibimos los argumentos de entrada
    /**
     * @brief N: Cantidad de individuos total.
     */
    int N;
    /**
     * @brief I: Cantidad inicial de individuos infectados.
     */
    int I;
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
    /**
     * @brief d: Distancia minima para que exista riesgo de contagio.
     */
    double d;
    /**
     * @brief M: Fraccion de individuos de cada tipo que usan mascarilla.
     */
    double M;
    /**
     * @brief p0: Probabilidad de contagio si ninguno de los dos individuos involucrados porta mascarilla.
     */
    double p0;
    /**
     * @brief p1: Probabilidad de contagio si solo uno de los dos individuos involucrados porta mascarilla.
     */
    double p1;
    /**
     * @brief p2: Probabilidad de contagio si ambos individuos involucrados portan mascarilla.
     */
    double p2;

    //Guardamos los parametros en las variables
    fin >> N >> I >> I_time;
    fin >> comunaWidth >> comunaLength;
    fin >> speed >> delta_t >> deltaAngle;
    fin >> d >> M >> p0 >> p1 >> p2;
    /**
     * @brief samplingTime: Tiempo de muestreo.
     */
    double samplingTime = 1.0;
    /**
     * @brief comuna: Comuna de la simulacion.
     * @return Objeto de tipo comuna.
     */
    Comuna comuna(comunaWidth, comunaLength, speed, deltaAngle, N, I, I_time, d, p0);
    /**
     * @brief sim: Simulador.
     * @return Objeto de tipo simulator.
     */
    Simulator sim(cout, comuna, delta_t, samplingTime);
    sim.startSimulation(); //Iniciamos la simulacion.
    return a.exec();
}
