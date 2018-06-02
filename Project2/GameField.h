#pragma once
#include <glad/glad.h>
#include <IL/il.h>
#include <IL/ilu.h>
#include <IL/ilut.h>
#include <GLFW/glfw3.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string>

#include "Block.h"
#define ILUT_USE_OPENGL



class GameField
{
private:
	double alpha;
	int positionX;
	int positionY;
	GLuint * images;
	int * field;
	Block * blocks;
	bool timeStopped;
	double timeState;
	
	void initializeField();
	void drawActiveBlocks();
	void setOnRemoveOnRow(int row);
	void removeAnimation();
	void fallDown();

public:
	static int BLOCK_SIZE;
	static int X_BLOCKS;
	static int Y_BLOCKS;
	static int FIELD_WIDTH;
	static int FIELD_HEIGHT;
	static int NUMBER_OF_BLOCKS;
	static int BORDER_PIXELS;

	GameField();
	GameField(GLuint * _images);
	~GameField();

	void drawField();
	void activateField(int i, int color);
	int * getField();
	int checkLines();
	bool isTimeStopped();
};

