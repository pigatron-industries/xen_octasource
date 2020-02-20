#include <Arduino.h>

#include "hwconfig.h"

#include "lib/TaskManager.h"
#include "drivers/CvInputOutput.h"
#include "modules/OctaSource.h"
#include "tasks/InputTask.h"
#include "tasks/OutputTask.h"


// hardware
CvInputOutput cvInputOutput = CvInputOutput(&SPI, CV_CNVT_PIN, CV_SELECT_PIN);

OctaSource octasource  = OctaSource();
InputTask inputTask = InputTask(cvInputOutput, octasource);
OutputTask outputTask = OutputTask(cvInputOutput, octasource);


void bootstrap() {
    Serial.begin(SERIAL_BAUD);
    Serial.println();
    Serial.println("=========================================");
    Serial.println("*     Pigatron Industries OctaSource    *");
    Serial.println("=========================================");
    Serial.println();

    Task* tasks[] = {&inputTask, &outputTask};
    TaskManager taskManager(tasks, 2);
    taskManager.run();
}
