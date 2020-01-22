#include "Task.h"

#include <Arduino.h>

void Task::init()
{
		enabled = true;
		time = micros();
		interval = 1;
		lastExecutionTime = 0;
		lastExecutionDiff = 0;
}

void Task::setEnabled(bool _enabled) {
		enabled = _enabled;
		if(enabled) {
				init();
		}
}

void Task::run()
{
		time = micros();
		lastExecutionDiff = time - lastExecutionTime;

  	if(lastExecutionDiff >= interval)
  	{
				lastExecutionTime = time;
	  		execute();
  	}
}
