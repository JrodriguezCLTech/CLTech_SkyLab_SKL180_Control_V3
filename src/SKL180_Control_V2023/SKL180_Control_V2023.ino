
/*****************************************CLTECH*****************************************************
                                        CLTECH LTD.
  
                                    http://WWW.CLTECH.NET

Ultima modificación: 05/11/2023
Modelo:
SKL180
    sistemas CNC(aceroplata)
    sistema de rotulacion
    codifo VSC
Version SKL180_VSC

Modificaciones
[2019]
    -
[2020]
    -
[2023]
    - Cambio de librería (skylabStepper) para control de los motores paso a paso, stepper.h V1.2, 
    aumentando al máximo la velocidad de movimiento
    - Se modificó algoritmo llegada a Home
    - Se modificó algoritmo de recogida y dejada de tubo
    - Cambios menores en ajuste de parámetros
    - Cambios menores posicionamiento gripper
    - Cambios menores en algoritmo de abertura/cierre de gripper
    - Cambios menores en algoritmo de accionamiento servorotulado
*/

//Prueba clonar repositorio desde mi PC personal (Camilo)

extern volatile unsigned long timer0_millis;
unsigned long new_value = 0;

//  import
//#include <loopTimer.h>
#include <TimerOne.h>
#include <EEPROM.h>
#include <skylabStepper.h>
#include <Servo.h>
#include <TimeLib.h>
#include "millisDelay.h"

//  include
#include "PinMode.h"
#include "MainSerial.h"
#include "Home.h"
#include "Main.h"
#include "Eprom.h"  
#include "lecturaSensores.h"

MainSerial mainSerial;
Home homeXY;
PinMode pinmode;
millisDelay Delay;
Main main_IRS;
Eprom EProm;
lecturaSensores lecturaSensoresAux;

#define STEPS 2000

int servoPins[] = {ServoMotorPin};
int servoPosSafeStart[NUM_SERVOS];
Servo Servos[NUM_SERVOS];

//  variables
bool doHomeXY = true,
     encendidoMaquina = true;
     
byte ZRO = 0,
     HMG = 30,
     SR = 40,
     SL = 0 ,
     RTD = 1,
     V_PT = 90,
     V_RT = 180,
     value,
     sec = 1;
int
    vlr_sensor_rotulado1,
    vlr_sensor_tubo,
    vlr_sensor_ln1,
    vlr_sensor_ln2,
    vlr_sensor_ln3,
    vlr_sensor_ln4,
    e_endX,
    e_endY,
    cnt_in,
    cnt_time = 0,
    cnt_time2 = 0,
    addr,
    millisXFromHomeToLine1 = 750,
    millisXBetweenLines = 130,
    millisYToPickupTube = 250,
    millisYFromHomeToPickupTube = 900,
    millisYFromHomeToReleaseTube = 500,
    speedAcelerate = 30,
    stepsYHomeToPickTube = 18000,
    stepsYHomeToReleaseTube = 7000,
    stepsXCalibrateLine1 = -350, 
    stepsXCalibrateLine2 = -350,
    stepsXCalibrateLine3 = -350,
    stepsXCalibrateLine4 = -350,
    stepsXLine1 = 12000, 
    stepsXLine2 = 14100,
    stepsXLine3 = 16200,
    stepsXLine4 = 18300,
    stepsXCalibrateReleaseTube = 0,
    pprX = 400,
    pprY = 400;

double
    rpmMaxX = 3500,
    rpmMaxY = 3500,
    rpmMediaX = 600,
    rpmMediaY = 600,
    acelerationX = 6000,
    acelerationY = 6000,
    t_reset = 0;

int contaTubOk;
int contaTubNotOk;
int contaFallos;
int contaTubosL1;
int contaTubosL2;
int contaTubosL3;
int contaTubosL4;
int contaHistorialFallos;
int banderaIOT;
String espacio = " ";
int varSensoresOk;
String falloStop;
String falloActual;
String falloAnterior;
String cliente = "CLIENTE";
String version = "V_2";

// Variables Aceleracion motores paso
skylabStepper stepperAX(skylabStepper::skylabSKL180EjeX,0,X_DIR_PIN,X_STEP_PIN,X_ENABLE_PIN);
skylabStepper stepperAY(skylabStepper::skylabSKL180EjeY,1,Y_DIR_PIN,Y_STEP_PIN,Y_ENABLE_PIN);

String readString;
String trama = "";
String cmd;
String rta;
String V_linea;

bool flag_first = false;
bool flag_rx = false;
bool flag_hm = false;
bool flag_time = false;
bool flag_time2 = false;
bool tube_true = false;
bool flag_disp = false;
bool banderaSRFallo = false;

bool varSO1 = 0;
bool varSO2 = 0;
bool varSO3 = 0;
bool varSO4 = 0;
bool varSO5 = 0;
bool varSO6 = 0;
bool varSO7 = 0;
bool varSO8 = 0;
bool varSH1 = 0;
bool varSH2 = 0;
bool varSH3 = 0;
bool varSH4 = 0;
bool varSH5 = 0;
bool varSH6 = 0;
bool varSH7 = 0;
bool varSSR = 0;
bool varSGPR = 0;

char buffer[16];
char readC;

void setup()
{
    Timer1.initialize(2000000); // 2mS
    Timer1.attachInterrupt(ISR_Mode);
    Serial.begin(9600);
    pinmode.initPin();
    // EeProm();
    addr = EEPROM.length();    // read a byte from the current address of the EEPROM
    value = EEPROM.read(addr); // Serial.print(value);
    EProm.initEprom();
    // Servo
    servoPosSafeStart[0] = {int(HMG)}; //  Ir a HMG
    initServos();
    
    stepperAX.configurarCNCSimp(X_MIN_PIN,1,true);
    stepperAY.configurarCNCSimp(Y_MIN_PIN,1,true);
    stepperAX.configurarMaxMovAxis(19000);
    stepperAY.configurarMaxMovAxis(8990);

    mainSerial.rutinas.varIOT[2] = "0";
    
    pinMode(gripClose, LOW); // ABRO GRIPPER
    delay(200);
    pinMode(motorOn, HIGH); // PRENDO MOTOR
    delay(800);
    pinMode(motorOn, LOW); // APAGO MOTOR

    t_reset = millis();

    for (int i=0; i<=11; i++)
    {
        mainSerial.rutinas.varIOT[i] = "-";
    }
    varSensoresOk = 0;
}

/*void setMillis(unsigned long new_millis){
  uint8_t oldSREG = SREG;
  cli();
  timer0_millis = new_millis;
  SREG = oldSREG;
}*/

unsigned long temp1 = 0;
void loop()
{
    //lecturaSensoresAux.leerSensoresTCRT5000();
    if(mainSerial.rutinas.sinTubo == 1)
    {
        mainSerial.rutinas.sinTubo = 0;
        varSensoresOk = 2;
    }

    //loopTimer.check(Serial);
    interrupts();
    mainSerial.conect();

    if(varSensoresOk == 1)
    {
        varSensoresOk = 0;
        flag_hm = false;
        if (flag_hm == false){
            homeXY.initHome();
            //Home IOT
            lecturaSensoresAux.deteccionSensores();
            if(lecturaSensoresAux.varIOTSensores[8] == 1 && lecturaSensoresAux.varIOTSensores[9] == 1){
                mainSerial.rutinas.varIOT[2] = "1";
            }
            else if(lecturaSensoresAux.varIOTSensores[8] == 0 && lecturaSensoresAux.varIOTSensores[9] == 0){
                mainSerial.rutinas.varIOT[2] = "0";
                mainSerial.rutinas.procesoIOT();
                mainSerial.rutinas.stopIOT();
            }
            flag_time = false;
            cnt_time = 0;
            flag_time2 = false;
            cnt_time2 = 0;
        } else {
            flag_hm = true;
        }

        /*if (millis() - t_reset < 0 ) {
        t_reset = millis();
        }*/
        
        
        /*switch(sec) {
        case 1:
            mainSerial.Run("l1");
            break;
        case 2:
            mainSerial.Run("l2");
            break;
        case 3:
            mainSerial.Run("l3");
            break;
        case 4:
            mainSerial.Run("l4");
            sec = 0;
            break;
        }
        sec ++;*/
        //mainSerial.Run("l2");

        if (millis()-temp1 >= 1000) {
            temp1 = millis();
            /*Serial.print(digitalRead(sensor_rotulado1));
            Serial.print(" ");
            Serial.print(digitalRead(sensor_rotulado2));
            Serial.print(" ");
            Serial.println(digitalRead(sensor_tubo));*/
        }
    }
    else{ }   
}
// ISR INTERRPCIONES
void ISR_Mode()
{
    main_IRS.ISRMode();
    if (millis() - t_reset >= 500) {
      t_reset = millis();
      //Serial.print(digitalRead(sensor_tubo));
      //Serial.print(" ");
      //Serial.println(digitalRead(sensor_rotulado1));
      //reset();
      //setMillis(new_value);
      //Serial.println("Reinicio millis()");
    }
}
//! Init servos
void initServos()
{
    for (int i = 0; i < NUM_SERVOS; i++)
    {
        Servos[i].attach(servoPins[i]); // servo setup
        Servos[i].write(servoPosSafeStart[i]);
    }
}

void resetArduino()
{
    asm volatile(" jmp 0");
}