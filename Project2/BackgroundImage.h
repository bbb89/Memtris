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
#define ILUT_USE_OPENGL

class BackgroundImage
{
private:
	int width;
	int height;
	GLuint * images;

public:
	BackgroundImage();
	BackgroundImage(int _width, int _height, GLuint *_images);
	~BackgroundImage();
	void displayBackground();
};

