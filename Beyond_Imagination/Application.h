#ifndef APPLICATION_H
#define APPLICATION_H

#include "Global\Global.h"

class Application
{
public:
	Application(uint16 width, uint16 height);
	~Application();

	void initialize();
	void update();

	bool isRunning();

private:
	bool status;
};

#endif
