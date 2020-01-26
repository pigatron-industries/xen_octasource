#include <Arduino.h>

#include "hwconfig.h"

#include "lib/TaskManager.h"
#include "drivers/CvInputOutput.h"
#include "tasks/OutputUpdateTask.h"


// hardware
CvInputOutput cvInputOutput = CvInputOutput(&SPI, CV_CNVT_PIN, CV_SELECT_PIN);

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
