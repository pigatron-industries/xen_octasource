#include <Arduino.h>

#include "hwconfig.h"

#include "lib/TaskManager.h"
#include "drivers/CvInputOutput.h"
#include "tasks/OutputUpdateTask.h"


// hardware
uint8_t cvSelectPins[CV_DEVICES] = CV_SELECT_PINS;
CvInputOutput cvInputOutput = CvInputOutput(&SPI, CV_CNVT_PIN, cvSelectPins, CV_DEVICES);

OutputUpdateTask outputUpdateTask = OutputUpdateTask(cvInputOutput);


void bootstrap() {
    Serial.begin(SERIAL_BAUD);
    Serial.println();
    Serial.println("=========================================");
    Serial.println("*     Pigatron Industries OctaSource    *");
    Serial.println("=========================================");
    Serial.println();

    Task* tasks[] = {&outputUpdateTask};
    TaskManager taskManager(tasks, 1);
    taskManager.run();
}
