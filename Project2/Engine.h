#pragma once
#pragma comment(lib, "winmm.lib")

#include <glad/glad.h>
#include <IL/il.h>
#include <IL/ilu.h>
#include <IL/ilut.h>
#include <GLFW/glfw3.h>
#include <Windows.h>
#include <mmsystem.h>

#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string>

#include "BackgroundImage.h";
#include "GameField.h";
#include "Shape.h";
#include "ShapeRepository.h";
#define ILUT_USE_OPENGL




class Engine
{
private:
	static GLFWwindow * window;
	GLuint * images;
	GLuint * memes;
	GameField * gameField;
	BackgroundImage * background;
	Shape * shape;
	double lastStepTime;
	double stepSpeed;
	double lastGoFasterTime;
	int memNum;
	bool memActive;

	int initialLeftKeyState;
	int initialRightKeyState;
	int initialSpaceKeyState;
	long score;
	bool endOfGame;

	void initGLFW();
	void initWindowAndSetupVideoMode();
	void drawFrame();
	void initializeDependencies();
	void setPositionOfWindow();
	void setupOrthoAndViewportToWindowSize();
	void initGameElements();
	void loadImages();
	void loadAudio();
	void updateTimer();
	void handleInput();
	void detectColission();
	void goFaster();
	void checkIfGameOver();
	void displayMeme();

public:
	static int SCREEN_WIDTH;
	static int SCREEN_HEIGHT;
	static double INITIAL_STEP_SPEED;
	static double SPACE_STEP_SPEED_MODIFICATOR;

	Engine();
	~Engine();

	bool initialize();
	void update();
	void render();
	void close();
	bool isWorking();
};

