//#define NUMX 205
//#define NUMY 400
#define NUM_SERVOS 1

//! PINES SERVO ROTULADO
#define motor_rotulado_a    12       // Pin In1 Driver Puente H Motorreductor rotulado 
#define motor_rotulado_b    9       // Pin In2 Driver Puente H Motorreductor rotulado 
#define sensor_tubo         41      // Pin sensor rotulado tapa (sensor superior)
#define sensor_rotulado1    45     // Pin sensor 1 rotulado tubo (sensor inferior 1) Sensor extremo 1ro
#define sensor_rotulado2    47     // Pin sensor 2 rotulado tubo (sensor inferior 2) Sensor entre rodillos 2do
#define servoMotorOn        3      // Pin relevo servomotor rotulado
#define ServoMotorPin       2      // Pin señal servo motor

//!GRIPPER
#define motorOn             6      // Pin relevo 1 gripper
#define gripClose           5      // Pin relevo 2 gripper

//!SENSORES DE GRADILLA TUBOS
#define sensor_linea1       53      // Pin sensor final de carrera linea 1
#define sensor_linea2       52      // Pin sensor final de carrera linea 2
#define sensor_linea3       51      // Pin sensor final de carrera linea 3
#define sensor_linea4       50      // Pin sensor final de carrera linea 4
#define sensor_tubo_linea1  17      // Pin sensor optico linea 1 (tubos suficientes linea 1)
#define sensor_tubo_linea2  18      // Pin sensor optico linea 2 (tubos suficientes linea 2)
#define sensor_tubo_linea3  16      // Pin sensor optico linea 3 (tubos suficientes linea 3)
#define sensor_tubo_linea4  19      // Pin sensor optico linea 4 (tubos suficientes linea 4)

//! CABECERA Y FIN DE TRAMA
#define cabecera '@'                // Cabecera trama mensaje con SIGA/Interfaz prueba
#define fintrama '&'                // Cola trama mensaje con SIGA/Interfaz prueba

//! Variavles CNC
#define X_DIR_PIN           10      // Pin dir driver eje X
#define X_STEP_PIN          11      // Pin step driver eje X
#define X_ENABLE_PIN        100      // Pin enable driver eje X
#define X_MIN_PIN           49      // Pin sensor herradura home eje X
#define Y_DIR_PIN           7       // Pin dir driver eje Y
#define Y_STEP_PIN          8      // Pin step driver eje Y
#define Y_ENABLE_PIN        101       // Pin enable driver eje Y
#define Y_MIN_PIN           48      // Pin sensor herradura home eje Y

//! Variables Monitoreo IOT Estado Sensores
#define multiplexorEntrada 42                   //Multiplexor monitoreo sensores
#define A 43                                    //Pin A control multiplexor
#define B 44                                    //Pin B control multiplexor
#define multiplexorEntrada2 10003                  //Multiplexor 2 monitoreo sensores
#define A2 10004                                   //Pin A control multiplexor 2
#define B2 10005                                   //Pin B control multiplexor 2
#define multiplexorEntrada3 10006                  //Multiplexor 3 monitoreo sensores
#define A3 10007                                   //Pin A control multiplexor 3
#define B3 10008       

#define sensor_gripper       A8      // Pin señal servo motor
