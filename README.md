# Tarea 3

	Tarea 3 - Simulador Gráfico en C++ de la Evolución de una Pandemia.

### Estructura General

El repositorio cuenta con 5 carpetas, un readme.md y un archivo documentacion.pdf para una información más detallada sobre la solución y el código escrito. Cada una de las carpetas resuelve una etapa de ésta y todas poseen los siguientes archivos:

- Comuna.cpp
- Comuna.h
- Pedestrian.cpp
- Pedestrian.h
- Simulator.cpp
- Simulator.h
- Stage1.cpp
- StageX.pro
- StageX.pro.user
- Config.txt

El archivo principal de ejecución (main) es StageX.cpp, donde X varía según la etapa en la que se desee ejecutar. Además, el archivo Config.txt contiene los parámetros de la simulación de la forma:

		<N. de Individuos> <N. de Infectados> <Tiempo que dura la infección [s]> 
		<Ancho de la comuna [m]> <Alto de la comuna [m]>
		<Velocidad de los individuos [m/s]> <∆t [s]> <∆θ [rad]>
		<Distancia de contagio [m]> <Razón de uso de mascarilla> <p0> <p1> <p2> //Probabilidades de Contagio
		<Cant. de Vacunatorios> <Tamaño de los Vacunatorios> <Tiempo para empezar a Vacunar [s]>

### Ejecución

Antes de ejecutar deberemos realizar un seteo previo, a continuación los pasos. 

- Se debe descargar la carpeta de la etapa (Stage) que se desee simular, luego hay que asegurarse de estar dentro del directorio con el comando *> cd \<Nombre del directorio\>*.
- Se debe configurar la variable PATH dentro del archivo makefile. Debe ser modificada al directorio que se encuentren los módulos de JavaFX, como por ejemplo javafx.controls.
- Se debe configurar la variable PATH2 dentro del archivo makefile. Debe ser modificada al directorio de la carpeta principal de la tarea, es decir, por ejemplo: **D:\user\Documents\Tarea2** donde en la carpeta Tarea2 se encuentran las carpetas de las distintas Stage
- Se debe verificar la línea 9 del makefile. Si se ejecuta en un dispositivo con sistema operativo Windows10 entonces debe ser descomentada, en caso de ser ejecutada en dispositivo con sistema operativo Linux entonces debe ser comentada (usar operador # al comienzo de la línea).

Finalmente, para ejecutar cada etapa del programa (con el seteo descrito anteriormente) se escriben en consola los siguientes comandos:

    > make
    > make run
    > make clean
    
Donde el comando **make** realiza la compilación del código, **make run** ejecuta el código y **make clean** limpia los archivos .class generados de la compilación.

Dentro del simulador se encuentran las opciones de Control y Settings, la primera nos permite ejecutar los comandos Start y Stop para poder ejecutar y parar la simulación. Por otro lado, la ventana de Settings nos permite colocar los parámetros de la simulación a gusto dentro de los márgenes impuestos. Por ultimo, con la simulación ya en ejecución, se puede acelerar la simulación presionando la tecla &#8594; y para ralentizar la simulación la tecla &#8592;.

---
### Otros
  Se opta por la  etapa extra.

  Se toma como referencia la Tarea 2 para poder trabajar modularmente, teniendo una referencia en otro lenguaje de programación y ajustando solamente lo necesario. El repositorio se encuentra [aquí](https://gitlab.com/gt12-elo329/andrade.miguel-cruces.manuel-pizarro.kevin-troncoso.pablo-tarea2.2021.1).
