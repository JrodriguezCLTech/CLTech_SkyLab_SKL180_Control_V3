# CLTech-SkyLab-SKL180-Control
En este repositorio se encuentra el código de control del SKL-180 utilizando la librería `skylabStepper` donde se presenta mejoras significativas en la velocidades de los motores paso a paso y cambios en el algoritmo de agarre de tubos para mejoras en confiabilidad.

## Clases

- Eprom:
Librería encargada de realizar el cargue y guardado de parámetros críticos funcionamiento máquina como:
  - `HMG`: Posición servo de _Home_
  - `SR`: Posición servo de _Servo rotulado_ (Posición de apriete de servo al momento de rotular tubo)
  - `SL`: Posición servo de _Servo liberar_ (Posición de servo para soltar el tubo)
  - `RTD`: Bandera activación proceso rotulado
  - `V_PT`: Velocidad 1 rotación de rodillo rotulador tubo
  - `V_RT`: Velocidad 2 rotación de rodillo rotulador tubo

- GV:
Archivo encargado de declarar las variables globales para todas las librerías. Nota: Si se desea utilizar alguna variable declarada en librerías una librería en particular se debe agregar `#include "GV.h"`

- Home:
Librería encargada de llevar a Home la máquina. Esta se llama en el `loop()` y se llama siempre que no se realice una rutina de recogida de tubos

- Main:
Librería encargada de lectura periodica de sensores y monitoreo de banderas de funcionamiento, y se llama por medio del _Timer 1_ del _MCU_ con un periodo de `2000ms`.

- MainSerial:
Librería encargada de la comunicación serial del _MCU_ con el _Software SIGA_ y _Software pruebas_. Se encarga de leer y procesar los comandos que recibe. La lista de comandos válidos son:

  - `?est`: Reporte de estado de máquina
  - `hmgrp`: Realizar rutina de prueba de gripper (Abrir, cerrar y abrir gripper)
  - `rt`: Realizar rutina de prueba _Sistema de rotulación_ de proceso de _rotulado_
  - `hm`: Realizar rutina de prueba _Servomotor_ de proceso _Servo home_
  - `sr`: Realizar rutina de prueba _Servomotor_ de proceso _Servo rotulado_
  - `svlb`: Realizar rutina de prueba _Servomotor_ de proceso _Servo liberado_
  - `looplX`: Realizar rutina de prueba _SKL-180_ de agarre y devolución de tubos a la linea `X` (1,2,3,4)
  - `lX`: Realizar rutina de máquina de agarre y rotulado de tubos de la linea `X` (1,2,3,4)
  - `LX`: Realizar rutina (de prueba) de máquina de agarre y rotulado de tubos de la linea `X` (1,2,3,4)

- PinMode:
Librería encargada de configurar el modo de funcionamiento de todos los pines del MCU utilizados (_INPUT_ y _OUTPUT_)

- Pins:
Archivo encargado de declarar las IDs de los pines del MCU utilizados

- Rutina:
Librería encargada de recopilar todas las rutinas de prueba y funcionamiento de la máquina. Entre las cuales se destacan:

  - `griperOpen`: Acción de abrir gripper
  - `griperClose`: Acción de cerrar gripper
  - `posicionarTubo` en _Rutinas_pruebas_ / `RotularTubo` en _Rutinas_: Rutina para posicionar tubo con etiqueta orientada a cierto ángulo
  - `RotularTubo` en _Rutinas_pruebas_ / `Rotulado` en _Rutinas_: Rutina para accionar motor rotulado por 3 seg (rotación simultánea con la impresión de la etiqueta de la impresora interna)
  - `LiberarTubo`: Rutina de liberación tubo (accionar motor rotulado, abrir el servo para dejar caer tubo y volver a home)
  - `RecogerYDevolverTubo`: Rutina de prueba de _SKL-180_ de agarre y devolución de tubos a la linea `X` (1,2,3,4)
  - `RecogerTubo`: Rutina de máquina de agarre y rotulado de tubos de la linea `X` (1,2,3,4). Hay dos versiones: _Rutina_ y _Rutina_pruebas_

## Software pruebas
El programa `SkyLab Control.exe` fue desarrollado para ejecutar los comandos predefinidos, para probar cada subsistema por separado (gripper, servomotor rotulado, motor rotulado, impresora interna) y rutinas de funcionamiento (buscar tubo en linea 1,2,3,4).
