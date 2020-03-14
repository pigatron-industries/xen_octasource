#ifndef TaskManager_h
#define TaskManager_h

#include "Task.h"

class TaskManager
{

public:

	TaskManager(Task **tasks, int numTasks);
	void run();

private:

	Task **tasks;
	int numTasks;

};

#endif
