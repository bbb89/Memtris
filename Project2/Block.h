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

class Block
{
private:
	int size;
	int color;
	int posX;
	int posY;
	bool onRemove;
	double alpha;
	GLuint * images;

public:
	Block();
	Block(int _size, int _color, int x, int y, GLuint * _images);
	~Block();

	void setColor(int _color);
	int getColor();
	void drawBlock();
	int getPosX();
	int getPosY();
	void setPosX(int x);
	void setPosY(int y);
	void setOnRemove(bool _onRemove);
	bool isOnRemove();
	void setAlpha(double _alpha);

	static int GREEN;
	static int ORANGE;
	static int BLUE;
	static int RED;
};

