#include <Arduino.h>

#include "hwconfig.h"

#include "lib/TaskManager.h"


// hardware


void bootstrap() {
    Serial.begin(SERIAL_BAUD);
    Serial.println();
    Serial.println("=========================================");
    Serial.println("*     Pigatron Industries OctaSource    *");
    Serial.println("=========================================");
    Serial.println();

    Task* tasks[] = {};
    TaskManager taskManager(tasks, 0);
    taskManager.run();
}
