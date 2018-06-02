#include "Block.h"

int Block::GREEN = 1;
int Block::ORANGE = 2;
int Block::BLUE = 3;
int Block::RED = 4;

Block::Block()
{
}

Block::Block(int _size, int _color, int x, int y, GLuint * _images)
{
	alpha = 1.0;
	size = _size;
	color = _color;
	posX = x;
	posY = y;
	images = _images;
	onRemove = false;
}


Block::~Block()
{

}

void Block::setColor(int _color) {
	color = _color;
}

int Block::getColor() {
	return color;
}

void Block::drawBlock() {

	if (onRemove) glColor4f(1, 1, 1, alpha);
	
	glBindTexture(GL_TEXTURE_2D, images[color]);
	glEnable(GL_TEXTURE_2D);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0); glVertex3f(posX, posY, 0.2f);  // Top left
	glTexCoord2f(0.0, 1.0);	glVertex3f(posX, posY + size, 0.2f);  // Bottom left
	glTexCoord2f(1.0, 1.0);	glVertex3f(posX + size, posY + size, 0.2f);  // Bottom right
	glTexCoord2f(1.0, 0.0);	glVertex3f(posX + size, posY, 0.2f);  // Top right
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glColor4f(1, 1, 1, 1);

}

int Block::getPosX()
{
	return posX;
}

int Block::getPosY()
{
	return posY;
}

void Block::setPosX(int x)
{
	posX = x;
}

void Block::setPosY(int y)
{
	posY = y;
}

void Block::setOnRemove(bool _onRemove)
{
	onRemove = _onRemove;
}

bool Block::isOnRemove()
{
	return onRemove;
}

void Block::setAlpha(double _alpha) {
	alpha = _alpha;
}
