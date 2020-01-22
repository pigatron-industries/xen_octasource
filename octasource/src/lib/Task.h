#ifndef Task_h
#define Task_h


class Task
{

public:

	virtual void init();
	virtual void execute() = 0;
	void run();
	bool isEnabled() { return enabled; }
	void setEnabled(bool _enabled);

protected:

	void resetUserTime();
	unsigned long getTime()     { return time; }
	unsigned long getInterval() { return interval; }
  void setInterval(unsigned long _interval) { interval = _interval; }

private:

	unsigned long time;               // start time of currently executing iteration
	unsigned long interval;           // wait time interval until next execution
	unsigned long lastExecutionTime;  // previous time of execution
	unsigned long lastExecutionDiff;  // length of time between executions
	bool enabled;

};

#endif
