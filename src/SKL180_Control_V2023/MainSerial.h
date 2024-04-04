#include <EEPROM.h>
#include "Rutinas_prueba.h"
#include "Rutinas.h"
#include "GV.h"
#include "estadoSensores.h"
#include "Eprom.h"

class MainSerial {
public:
    void conect();
    void Run(String);
    int init1;
    Rutinas rutinas;
    estadoSensores estadoSensoresAux;
    Eprom EpromAux;
    
private:
    Rutinas_prueba rutinas_p;
    int varPrueba = 0;
};
