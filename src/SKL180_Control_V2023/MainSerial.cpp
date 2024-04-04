#include "MainSerial.h"

// MÉTODO PARA LEER BUFFER DE SERIAL
void MainSerial::conect() {
    if (Serial.available()) {
        readC = Serial.read();
        //Serial.print(readC);
        if (readC == 64) {
            cnt_in = 0;
            cmd = "";
        } else if (readC != 38) { // Recibe y almacena los caracteres desde el ultimo hasta que uart_rx es '&'
            buffer[cnt_in] = readC; // Almacena en vector externo bufferin posicion contrx el caracter uart_rx recibido
            cnt_in += 1;            // Aumenta la variable externa tipo entera cnt para guardar en la siguiente posicion del vector el dato
        } else {
            flag_rx = true; // Bandera de Recepcion Uart BT
            for (int i = 0; i < cnt_in; i++) {
                // Serial.println(i);
                cmd = cmd + buffer[i];
            }
            // Serial.println("CMD_: "+cmd);
        }
        if (flag_rx == true) {
            Run(cmd);
        }
    }
}

// MÉTODO PARA PROCESAMIENTO COMANDOS USUARIO (SERIAL)
void MainSerial::Run(String cmd) {

    /*if (cmd == "inip") {
        rutinas.procesoIOTpruebaSensores();
    }

    if (cmd == "inif") {
        rutinas.procesoIOTprueba();
        //rutinas.varIOT[0] = 1;
        //rutinas.procesoIOT();
    }*/

    if (cmd == "init") {
        estadoSensoresAux.monitoreoVectorEstadoSistema();
        EEPROM.get(500, contaTubosL1);
        EEPROM.get(510, contaTubosL2);
        EEPROM.get(520, contaTubosL3);
        EEPROM.get(530, contaTubosL4);

        if(contaTubosL1 <= 1 && contaTubosL2 <= 1 && contaTubosL3 <= 1 && contaTubosL4 <= 1)
        {    
            contaTubosL1 = 30;
            contaTubosL2 = 30;
            contaTubosL3 = 30;
            contaTubosL4 = 30;
            EEPROM.put(500, contaTubosL1);
            EEPROM.put(510, contaTubosL2);
            EEPROM.put(520, contaTubosL3);
            EEPROM.put(530, contaTubosL4);
        }
        init1 = 1;
        //rutinas.varIOT[0] = 1;
        //rutinas.procesoIOT();
    }
    
    if(init1 == 1 && varSensoresOk == 2)
    {
        //Serial.println("-----Inicio Nuevo Testo-----");
        estadoSensoresAux.monitoreoVectorEstadoSistema();
    }

    if (cmd == "hist") {
        rutinas.verHistorialFallos();
    }

    if (cmd == "ultfal") {
        rutinas.ultimoFallo();
    }
    
    if (cmd == "conts") {
        rutinas.verContadores();
    }
    
    if (cmd == "clreeprom") {
        Serial.println("...Espere un instante estamos restableciendo los valores de la memoria...");
        EpromAux.borrarEEPROM();
        Serial.println("Registros de memoria limpios");
    }
     
    if (cmd == "senhab") {
        rutinas.monitorearSensoresHabilitados();
    }

    if (cmd == "SGL1 OFF") {
        Serial.println("Sensor llenado gradilla L1 deshabilitado");
        varSO1 = 1;
        EEPROM.put(600, varSO1);
    }else if (cmd == "SGL1 ON") {
        Serial.println("Sensor llenado gradilla L1 habilitado");
        varSO1 = 0;
        EEPROM.put(600, varSO1);
    }

    if (cmd == "SGL2 OFF") {
        Serial.println("Sensor llenado gradilla L2 deshabilitado");
        varSO2 = 1;
        EEPROM.put(610, varSO2);
    }else if (cmd == "SGL2 ON") {
        Serial.println("Sensor llenado gradilla L2 habilitado");
        varSO2 = 0;
        EEPROM.put(610, varSO2);
    }
    
    if (cmd == "SGL3 OFF") {
        Serial.println("Sensor llenado gradilla L3 deshabilitado");
        varSO3 = 1;
        EEPROM.put(620, varSO3);
    }else if (cmd == "SGL3 ON") {
        Serial.println("Sensor llenado gradilla L3 habilitado");
        varSO3 = 0;
        EEPROM.put(620, varSO3);
    }
    
    if (cmd == "SGL4 OFF") {
        Serial.println("Sensor llenado gradilla L4 deshabilitado");
        varSO4 = 1;
        EEPROM.put(630, varSO4);
    }else if (cmd == "SGL4 ON") {
        Serial.println("Sensor llenado gradilla L4 habilitado");
        varSO4 = 0;
        EEPROM.put(630, varSO4);
    }

    if (cmd == "SSR1 OFF") {
        Serial.println("Sensor de tapa SR deshabilitado");
        varSO7 = 1;
        EEPROM.put(660, varSO7);
    }else if (cmd == "SSR1 ON") {
        Serial.println("Sensor de tapa SR habilitado");
        varSO7 = 0;
        EEPROM.put(660, varSO7);
    }
    
    if (cmd == "SSR2 OFF") {
        Serial.println("Sensor posicion 2 (entre rodillos) SR deshabilitado");
        varSO6 = 1;
        EEPROM.put(650, varSO6);
    }else if (cmd == "SSR2 ON") {
        Serial.println("Sensor posicion 2 (entre rodillos) SR habilitado");
        varSO6 = 0;
        EEPROM.put(650, varSO6);
    }

    if (cmd == "SSR3 OFF") {
        Serial.println("Sensor posicion 1 (extremo) SR deshabilitado");
        varSO5 = 1;
        EEPROM.put(640, varSO5);
    }else if (cmd == "SSR3 ON") {
        Serial.println("Sensor posicion 1 (extremo) SR habilitado");
        varSO5 = 0;
        EEPROM.put(640, varSO5);
    }

    if (cmd == "SSRPOS OFF") {
        Serial.println("Sensores de posicionamiento de SR deshabilitados");
        varSSR = 1;
        EEPROM.put(750, varSSR);
        varSO5 = 1;
        EEPROM.put(640, varSO5);
        varSO6 = 1;
        EEPROM.put(650, varSO6);
    }else if (cmd == "SSRPOS ON") {
        Serial.println("Sensores de posicionamiento de SR habilitados");
        varSSR = 0;
        EEPROM.put(750, varSSR);
        varSO5 = 0;
        EEPROM.put(640, varSO5);
        varSO6 = 0;
        EEPROM.put(650, varSO6);
    }

    if (cmd == "SO8 OFF") {
        Serial.println("Sensor optico 8 deshabilitado");
        varSO8 = 1;
        EEPROM.put(670, varSO8);
    }else if (cmd == "SO8 ON") {
        Serial.println("Sensor optico 8 habilitado");
        varSO8 = 0;
        EEPROM.put(670, varSO8);
    }

    if (cmd == "SCNCX OFF") {
        Serial.println("Sensor Home eje X deshabilitado");
        varSH1 = 1;
        EEPROM.put(680, varSH1);
    }else if (cmd == "SCNCX ON") {
        Serial.println("Sensor Home eje X habilitado");
        varSH1 = 0;
        EEPROM.put(680, varSH1);
    }

    if (cmd == "SCNCY OFF") {
        Serial.println("Sensor Home eje Y deshabilitado");
        varSH2 = 1;
        EEPROM.put(690, varSH2);
    }else if (cmd == "SCNCY ON") {
        Serial.println("Sensor Home eje Y habilitado");
        varSH2 = 0;
        EEPROM.put(690, varSH2);
    }

    if (cmd == "SL1 OFF") {
        Serial.println("Sensor Ir a L1 deshabilitado");
        varSH3 = 1;
        EEPROM.put(700, varSH3);
    }else if (cmd == "SL1 ON") {
        Serial.println("Sensor Ir a L1 habilitado");
        varSH3 = 0;
        EEPROM.put(700, varSH3);
    }

    if (cmd == "SL2 OFF") {
        Serial.println("Sensor Ir a L2 deshabilitado");
        varSH4 = 1;
        EEPROM.put(710, varSH4);
    }else if (cmd == "SL2 ON") {
        Serial.println("Sensor Ir a L2 habilitado");
        varSH4 = 0;
        EEPROM.put(710, varSH4);
    }

    if (cmd == "SL3 OFF") {
        Serial.println("Sensor Ir a L3 deshabilitado");
        varSH5 = 1;
        EEPROM.put(720, varSH5);
    }else if (cmd == "SL3 ON") {
        Serial.println("Sensor Ir a L3 habilitado");
        varSH5 = 0;
        EEPROM.put(720, varSH5);
    }

    if (cmd == "SL4 OFF") {
        Serial.println("Sensor Ir a L4 deshabilitado");
        varSH6 = 1;
        EEPROM.put(730, varSH6);
    }else if (cmd == "SL4 ON") {
        Serial.println("Sensor Ir a L4 habilitado");
        varSH6 = 0;
        EEPROM.put(730, varSH6);
    }

    if (cmd == "SGPR OFF") {
        Serial.println("Sensor gripper deshabilitado");
        varSGPR = 1;
        EEPROM.put(760, varSGPR);
        varSH7 = 1;
        EEPROM.put(740, varSH7);
    }else if (cmd == "SGPR ON") {
        Serial.println("Sensor gripper habilitado");
        varSGPR = 0;
        EEPROM.put(760, varSGPR);
        varSH7 = 0;
        EEPROM.put(740, varSH7);
    }

    if (cmd == "ALLSKL180 OFF") {
        Serial.println("Todos los sensores del SKL180 estan deshabilitados");
        varSO1 = 1;
        EEPROM.put(600, varSO1);
        varSO2 = 1;
        EEPROM.put(610, varSO2);
        varSO3 = 1;
        EEPROM.put(620, varSO3);
        varSO4 = 1;
        EEPROM.put(630, varSO4);
        varSO7 = 1;
        EEPROM.put(660, varSO7);
        varSO6 = 1;
        EEPROM.put(650, varSO6);
        varSO5 = 1;
        EEPROM.put(640, varSO5);
        varSSR = 1;
        EEPROM.put(750, varSSR);
        varSO5 = 1;
        EEPROM.put(640, varSO5);
        varSO6 = 1;
        EEPROM.put(650, varSO6);
        varSO8 = 1;
        EEPROM.put(670, varSO8);
        varSH1 = 1;
        EEPROM.put(680, varSH1);
        varSH2 = 1;
        EEPROM.put(690, varSH2);
        varSH3 = 1;
        EEPROM.put(700, varSH3);
        varSH4 = 1;
        EEPROM.put(710, varSH4);
        varSH5 = 1;
        EEPROM.put(720, varSH5);
        varSH6 = 1;
        EEPROM.put(730, varSH6);
        varSGPR = 1;
        EEPROM.put(760, varSGPR);
        varSH7 = 1;
        EEPROM.put(740, varSH7);
    }else if (cmd == "ALLSKL180 ON") {
        Serial.println("Todos los sensores del SKL180 estan habilitados");
        varSO1 = 0;
        EEPROM.put(600, varSO1);
        varSO2 = 0;
        EEPROM.put(610, varSO2);
        varSO3 = 0;
        EEPROM.put(620, varSO3);
        varSO4 = 0;
        EEPROM.put(630, varSO4);
        varSO7 = 0;
        EEPROM.put(660, varSO7);
        varSO6 = 0;
        EEPROM.put(650, varSO6);
        varSO5 = 0;
        EEPROM.put(640, varSO5);
        varSSR = 0;
        EEPROM.put(750, varSSR);
        varSO5 = 0;
        EEPROM.put(640, varSO5);
        varSO6 = 0;
        EEPROM.put(650, varSO6);
        varSO8 = 0;
        EEPROM.put(670, varSO8);
        varSH1 = 0;
        EEPROM.put(680, varSH1);
        varSH2 = 0;
        EEPROM.put(690, varSH2);
        varSH3 = 0;
        EEPROM.put(700, varSH3);
        varSH4 = 0;
        EEPROM.put(710, varSH4);
        varSH5 = 0;
        EEPROM.put(720, varSH5);
        varSH6 = 0;
        EEPROM.put(730, varSH6);
        varSGPR = 0;
        EEPROM.put(760, varSGPR);
        varSH7 = 0;
        EEPROM.put(740, varSH7);
    }

    if (cmd == "hmgrp") {
        rutinas.griperClose();
        delay(300);
        rutinas.griperOpen();
        Delay.start(2600);
        rutinas.griperClose();
        Delay.start(2600);
        pinMode(gripClose, LOW);
        rutinas.griperOpen();
        //Serial.print(cabecera + "GROK" + fintrama);
    }
      
    if (cmd == "RL1") {
        Serial.println("Reiniciando contador gradilla L1");
        EEPROM.get(500, contaTubosL1);
        contaTubosL1 = 30;
        EEPROM.put(500, contaTubosL1);
    } 
    if (cmd == "RL2") {
        Serial.println("Reiniciando contador gradilla L2");
        EEPROM.get(510, contaTubosL2);
        contaTubosL2 = 30;
        EEPROM.put(510, contaTubosL2);
    } 
    if (cmd == "RL3") {
        Serial.println("Reiniciando contador gradilla L3");
        EEPROM.get(520, contaTubosL3);
        contaTubosL3 = 30;
        EEPROM.put(520, contaTubosL3);
    } 
    if (cmd == "RL4") {
        Serial.println("Reiniciando contador gradilla L4");
        EEPROM.get(530, contaTubosL4);
        contaTubosL4 = 30;
        EEPROM.put(530, contaTubosL4);
    } 

    if(estadoSensoresAux.estadoSistema[0] == 1 && estadoSensoresAux.estadoSistema[1] == 1 && estadoSensoresAux.estadoSistema[2] == 1)
    {
        varSensoresOk = 1;

        if (cmd == "loopl1") {
            rutinas.LiberarTubo();
            delay(400);
            rutinas.griperOpen();
            delay(400);
            pinMode(gripClose, LOW); // APAGO MOTOR
            rutinas.RecogerYDevolverTubo("L1");
        } else if (cmd == "loopl2") {
            rutinas.LiberarTubo();
            delay(400);
            rutinas.griperOpen();
            delay(400);
            pinMode(gripClose, LOW); // APAGO MOTOR
            rutinas.RecogerYDevolverTubo("L2");
        } else if (cmd == "loopl3") {
            rutinas.LiberarTubo();
            delay(400);
            rutinas.griperOpen();
            delay(400);
            pinMode(gripClose, LOW); // APAGO MOTOR
            rutinas.RecogerYDevolverTubo("L3");
        } else if (cmd == "loopl4") {
            rutinas.LiberarTubo();
            delay(400);
            rutinas.griperOpen();
            delay(400);
            pinMode(gripClose, LOW); // APAGO MOTOR
            rutinas.RecogerYDevolverTubo("L4");
        } else if (cmd == "l1") {
            //Comentado por JRodriguez
            /*
            rutinas.LiberarTubo();
            delay(400);
            rutinas.griperOpen();
            delay(400);
            pinMode(gripClose, LOW); // APAGO MOTOR*/
            rutinas.RecogerTubo("L1");
            varPrueba = 1;
        } else if (cmd == "l2") {
            //Comentado por JRodriguez
            /*
            rutinas.LiberarTubo();
            delay(400);
            rutinas.griperOpen();
            delay(400);
            pinMode(gripClose, LOW); // APAGO MOTOR*/
            rutinas.RecogerTubo("L2");
            varPrueba = 1;
        } else if (cmd == "l3") {
            //Comentado por JRodriguez
            /*
            rutinas.LiberarTubo();
            delay(400);
            rutinas.griperOpen();
            delay(400);
            pinMode(gripClose, LOW); // APAGO MOTOR*/
            rutinas.RecogerTubo("L3");
            varPrueba = 1;
        } else if (cmd == "l4") {
            //Comentado por JRodriguez
            /*
            rutinas.LiberarTubo();
            delay(400);
            rutinas.griperOpen();
            delay(400);
            pinMode(gripClose, LOW); // APAGO MOTOR*/
            rutinas.RecogerTubo("L4");
            varPrueba = 1;
        } else if (cmd == "L1") {
            rutinas_p.LiberarTubo();
            delay(400);
            rutinas_p.griperOpen();
            delay(400);
            pinMode(gripClose, LOW); // APAGO MOTOR
            rutinas_p.RecogerTubo("L1");
            varPrueba = 0;
        } else if (cmd == "L2") {
            rutinas_p.LiberarTubo();
            delay(400);
            rutinas_p.griperOpen();
            delay(400);
            pinMode(gripClose, LOW); // APAGO MOTOR
            rutinas_p.RecogerTubo("L2");
            varPrueba = 0;
        } else if (cmd == "L3") {
            rutinas_p.LiberarTubo();
            delay(400);
            rutinas_p.griperOpen();
            delay(400);
            pinMode(gripClose, LOW); // APAGO MOTOR
            rutinas_p.RecogerTubo("L3");
            varPrueba = 0;
        } else if (cmd == "L4") {
            rutinas_p.LiberarTubo();
            delay(400);
            rutinas_p.griperOpen();
            delay(400);
            pinMode(gripClose, LOW); // APAGO MOTOR
            rutinas_p.RecogerTubo("L4");
            varPrueba = 0;
        } else if (cmd == "lb") {
            rutinas.LiberarTubo();
            Servos[0].write(SL);
            String String_SL = String(SL);
            Serial.print(cabecera + String_SL + fintrama);
            Serial.print("@OK&");
        } else if (cmd == "+sl") {
            if (SL != 255) {
                SL += 1;
            }
            EEPROM.write(22, SL);
            // Serial.print(cabecera+"OK"+fintrama);
            Serial.print("@OK&");
        } else if (cmd == "-sl") {
            if (SL != 255) {
                SL -= 1;
            }
            EEPROM.write(22, SL);
            // Serial.print(cabecera+"OK"+fintrama);
            Serial.print("@OK&");
        } else if (cmd == "vrt") {
            // Serial.print("@VALOR DE VELOCIDAD ROTULADO&");
            String String_VR = String(V_RT);
            Serial.print(cabecera + String_VR + fintrama);
            // Serial.print(V_RT,DEC);
        } else if (cmd == "vpt") {
            // Serial.print("@VALOR DE VELOCIDAD POSICIONAMIENTO&");
            String String_VP = String(V_PT);
            Serial.print(cabecera + String_VP + fintrama);
            // Serial.print(V_PT,DEC);
        } else if (cmd == "svlb") {
            rutinas.LiberarTubo();
            Serial.print("@OK&");
        } else if (cmd == "sr") {
            pinMode(servoMotorOn, OUTPUT); // PRENDO MOTOR
            Servos[0].write(SR);
            delay(600);
            pinMode(servoMotorOn, INPUT); // APAGO MOTOR
            String String_SR = String(SR);
            Serial.println(cabecera + String_SR + fintrama);
            // Serial.print(SR,DEC);
        } else if (cmd == "+sr") {
            if (SR != 255) {
                SR += 1;
            }
            EEPROM.write(21, SR);
            // Serial.print(cabecera+"OK"+fintrama);
            Serial.print("@OK&");
        } else if (cmd == "-sr") {
            if (SR != 255) {
                SR -= 1;
            }
            EEPROM.write(21, SR);
            // Serial.print(cabecera+"OK"+fintrama);
            Serial.print("@OK&");
        } else if (cmd == "hm") {
            pinMode(servoMotorOn, OUTPUT); // PRENDO MOTOR
            Servos[0].write(HMG);
            delay(600);
            pinMode(servoMotorOn, INPUT); // APAGO MOTOR
            delay(200);
            String String_HM = String(HMG);
            Serial.println(cabecera + String_HM + fintrama);
        } else if (cmd == "+hm") {
            if (HMG != 255) {
                HMG += 1;
            }
            EEPROM.write(20, HMG);
            // Serial.print(cabecera+"OK"+fintrama);
            Serial.print("@OK&");
        } else if (cmd == "-hm") {
            if (HMG != 255) {
                HMG -= 1;
            }
            EEPROM.write(20, HMG);
            // Serial.print(cabecera+"OK"+fintrama);
            Serial.print("@OK&");
        } else if (cmd == "?est") {
            rutinas.procesoIOT();

            /*
            String String_EST = " HM: " + String(HMG) + "SR: " + String(SR) + "HM: " + String(HMG) + "LB: " + String(SL) + "\n" 
            + " l1: " + String(vlr_sensor_ln1) + " l2: " + String(vlr_sensor_ln2) + " l3: " + String(vlr_sensor_ln3) + " l4: " + String(vlr_sensor_ln4) + "\n" 
            + " SensorHmX: " + String(e_endX) + " SensorHmY: " + String(e_endY) + " SensorTubo: " + String(vlr_sensor_tubo);
            Serial.println(cabecera + String_EST + fintrama);*/
        }else if (cmd == "ptp") {
            //rutinas.PosicionTubo();
            Serial.print(cabecera + rta + fintrama);
        } else if (cmd == "pt") {
            //rutinas.RotularTubo();
            rutinas_p.PosicionarTubo();
            Serial.print(cabecera + rta + fintrama);
            // Serial.print("@PT&");
        } else if (cmd == "rt") {
            //Comentado por JRodriguez
            /*
            if (RTD == 1) {
                //rutinas.Rotulado();
                rutinas_p.RotularTubo();
            } else {
                rutinas.LiberarTubo();
            }
            // Serial.print(cabecera+"OK"+fintrama);
            Serial.print("@OK&");
            */

            //Codificado por JRodriguez
            if(varPrueba == 1)
            {
                if (RTD == 1) {
                //rutinas.Rotulado();
                rutinas.Rotulado();
                } else {
                    rutinas.LiberarTubo();
                }
                // Serial.print(cabecera+"OK"+fintrama);
                //Serial.print("@OK&");
                
                estadoSensoresAux.estadoSistema[0] = 0;
                estadoSensoresAux.estadoSistema[1] = 0;
                estadoSensoresAux.estadoSistema[2] = 0;
                varSensoresOk = 2;
            }

            else if(varPrueba == 0)
            {
                if (RTD == 1) {
                //rutinas.Rotulado();
                rutinas_p.RotularTubo();
                } else {
                    rutinas_p.LiberarTubo();
                }
                // Serial.print(cabecera+"OK"+fintrama);
                Serial.print("@OK&");
            }
        } else if (cmd == "rton") {
            RTD = 1;
            EEPROM.write(26, RTD);
            Serial.print("@OK&");
        } else if (cmd == "rtof") {
            RTD = 0;
            EEPROM.write(26, RTD);
            Serial.print("@OK&");
        } else if (cmd == "svlo") {
            analogWrite(motor_rotulado_b, 245);
            rutinas.LiberarTubo();
            analogWrite(motor_rotulado_b, 0);
        } else if (cmd == "sv0") {
            pinMode(servoMotorOn, OUTPUT); // PRENDO MOTOR
            Servos[0].write(ZRO);
            delay(600);
            pinMode(servoMotorOn, INPUT); // APAGO MOTOR
            delay(200);
            String String_ZRO = String(ZRO);
            Serial.print(cabecera + String_ZRO + fintrama);
        } else if (cmd == "m2a") {
            analogWrite(motor_rotulado_a, V_RT);
            delay(1000);
            analogWrite(motor_rotulado_a, 0);
            Serial.print("@OK&");
        } else if (cmd == "m2b") {
            analogWrite(motor_rotulado_b, V_RT);
            delay(1000);
            analogWrite(motor_rotulado_b, 0);
            Serial.print("@OK&");
        } else if (cmd == "H") {
            Serial.println("hola");
        }

        flag_rx = false;
    }
}
