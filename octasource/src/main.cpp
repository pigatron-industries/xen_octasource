#include <Arduino.h>

#include "hwconfig.h"

#include "lib/TaskManager.h"
#include "drivers/CvInputOutput.h"
#include "tasks/OutputTask.h"


// hardware
CvInputOutput cvInputOutput = CvInputOutput(&SPI, CV_CNVT_PIN, CV_SELECT_PIN);

OutputTask outputTask = OutputTask(cvInputOutput);


void bootstrap() {
    Serial.begin(SERIAL_BAUD);
    Serial.println();
    Serial.println("=========================================");
    Serial.println("*     Pigatron Industries OctaSource    *");
    Serial.println("=========================================");
    Serial.println();

    Task* tasks[] = {&outputTask};
    TaskManager taskManager(tasks, 1);
    taskManager.run();
}
