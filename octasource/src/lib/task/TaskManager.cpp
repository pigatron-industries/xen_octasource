#include "TaskManager.h"

#include <Arduino.h>

TaskManager::TaskManager(Task **_tasks, int _numTasks) :
	tasks(_tasks),
	numTasks(_numTasks)
{
}

void TaskManager::run()
{

	Task **tpp = tasks;
	for(int i = 0; i < numTasks; i++)
	{
		Task *tp = *tpp;
		tp->init();
		tpp++;
	}

	while(1)
	{
		Task **tpp = tasks;
		for(int i = 0; i < numTasks; i++)
		{
			Task *tp = *tpp;
			if(tp->isEnabled())
			{
				tp->run();
			}

			tpp++;
		}
	}
}
