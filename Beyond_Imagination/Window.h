#ifndef WINDOW_H
#define WINDOW_H

#include "Vector3.h"

class Window
{
public:
	Window(uint16 width, uint16 height);
	~Window();	

	void update();

private:
	uint16 width;
	uint16 height;
	
};

#endif