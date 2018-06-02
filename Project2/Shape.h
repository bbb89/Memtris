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
#include "time.h"

#include "ShapeRepository.h"
#include "Block.h"
#include "GameField.h"
#define ILUT_USE_OPENGL

class Shape
{
private:
	int gameFieldX;
	int gameFieldY;
	int relativeX;
	int relativeY;
	GLuint * images;
	int * shape;
	int * field;
	Block * blocks;
	int color;

	void initializeShape();
	int calculateX();
	int calculateY();
	int calculatePositionInField(int positionInShape);
	void selectRandomShape();
	bool outOfFieldTop(Block block);
	bool outOfFieldRight();
	bool outOfFieldLeft();
	void updatePositionsOfBlocks();
	bool leftCollision();
	bool rightCollision();

public:
	Shape();
	Shape(GLuint * _images, int * _field);
	~Shape();
	void goLeft();
	void goRight();
	void goDown();
	void turn();
	bool bottomCollision();
	bool blockCollision();
	int getRelativeX();
	int getRelativeY();
	int * getShape();
	int getColor();
	bool endOfGame();

	void drawActiveBlocks();
	
	static int NUMBER_OF_BLOCKS;
	static int X_BLOCKS;
	static int BLOCK_SIZE;
};

