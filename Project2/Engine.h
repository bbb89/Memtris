#pragma once
#include <GLFW\glfw3.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include "linmath.h"


class Engine
{
private:
	static GLFWwindow * window;
	void initializeCursor();
	void initGLFW();
	void initWindowAndSetupVideoMode();
public:
	static int SCREEN_WIDTH;
	static int SCREEN_HEIGHT;

	Engine();
	~Engine();

	bool initialize();
	void update();
	void render();
	void close();
	bool isWorking();
};

