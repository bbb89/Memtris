#include "BackgroundImage.h"



BackgroundImage::BackgroundImage()
{
}

BackgroundImage::BackgroundImage(int _width, int _height, GLuint * _images)
{
	width = _width;
	height = _height;
	images = _images;
}

BackgroundImage::~BackgroundImage()
{

}

void BackgroundImage::displayBackground() {

	glBindTexture(GL_TEXTURE_2D, images[0]);
	glEnable(GL_TEXTURE_2D);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0); glVertex3f(0, 0, -0.1);  // Top left
	glTexCoord2f(0.0, 1.0);	glVertex3f(0, height, -0.1);  // Bottom left
	glTexCoord2f(1.0, 1.0);	glVertex3f(width, height, -0.1);  // Bottom right
	glTexCoord2f(1.0, 0.0);	glVertex3f(width, 0, -0.1);  // Top right
	glEnd();
	glDisable(GL_TEXTURE_2D);

}