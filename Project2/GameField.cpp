#include "GameField.h"

int GameField::BLOCK_SIZE = 32;
int GameField::X_BLOCKS = 10;
int GameField::Y_BLOCKS = 20;
int GameField::FIELD_WIDTH = X_BLOCKS * BLOCK_SIZE;
int GameField::FIELD_HEIGHT = Y_BLOCKS * BLOCK_SIZE;
int GameField::NUMBER_OF_BLOCKS = X_BLOCKS * Y_BLOCKS;
int GameField::BORDER_PIXELS = 5;


GameField::GameField()
{
}

GameField::GameField(GLuint * _images)
{
	alpha = 1.0;
	timeStopped = false;
	positionX = 200;
	positionY = 40;
	images = _images;

	initializeField();
}

GameField::~GameField()
{
	if(field) delete [] field;
	if(blocks) delete [] blocks;
}

void GameField::drawField() {

	glBegin(GL_QUADS);
	glColor4f(1, 1, 1, 0.5);
	glVertex2d(positionX, positionY);
	glVertex2d(positionX, positionY + FIELD_HEIGHT);
	glVertex2d(positionX + FIELD_WIDTH, positionY + FIELD_HEIGHT);
	glVertex2d(positionX + FIELD_WIDTH, positionY);
	glColor4f(1, 1, 1, 1);
	glEnd();

	glBegin(GL_QUADS);
	glColor4f(1, 1, 1, 0.9);
	glVertex2d(positionX - BORDER_PIXELS, positionY - BORDER_PIXELS);
	glVertex2d(positionX - BORDER_PIXELS, positionY + FIELD_HEIGHT + BORDER_PIXELS);
	glVertex2d(positionX + FIELD_WIDTH + BORDER_PIXELS, positionY + FIELD_HEIGHT + BORDER_PIXELS);
	glVertex2d(positionX + FIELD_WIDTH + BORDER_PIXELS, positionY - BORDER_PIXELS);
	glColor4f(1, 1, 1, 1);
	glEnd();

	drawActiveBlocks();
}

void GameField::drawActiveBlocks() {
	int n = NUMBER_OF_BLOCKS;
	for (int i = 0; i < NUMBER_OF_BLOCKS; i++) {
		if (field[i] == 1) {
			blocks[i].drawBlock();
		}
	}

	if (timeStopped) {
		removeAnimation();
	}
}

void GameField::removeAnimation() {
	for (int row = 0; row < Y_BLOCKS; row++) {
		for (int col = 0; col < X_BLOCKS; col++) {
			int n = row * X_BLOCKS + col;
			if (blocks[n].isOnRemove())
				blocks[n].setAlpha(alpha);
		}
	}
	alpha -= 0.05;
	if (alpha <= 0.1) {
		alpha = 1.0;
		fallDown();
		timeStopped = false;
	}
	
}

void GameField::initializeField() {
	field = new int[NUMBER_OF_BLOCKS];
	blocks = new Block[NUMBER_OF_BLOCKS];

	for (int i = 0; i < NUMBER_OF_BLOCKS; i++) {
		field[i] = 0;

		int column = i % X_BLOCKS;
		int row = i / X_BLOCKS;
		int blockXPos = positionX + column * BLOCK_SIZE;
		int blockYPos = positionY + row * BLOCK_SIZE;

		blocks[i] = Block(BLOCK_SIZE, Block::RED, blockXPos, blockYPos, images);
	}
}

void GameField::activateField(int i, int color)
{
	blocks[i].setColor(color);
	field[i] = 1;
}

int * GameField::getField()
{
	return field;
}


int GameField::checkLines() {
	int rowsRemoved = 0;
	for (int row = 0; row < Y_BLOCKS; row++) {
		int rowSum = 0;
		for (int col = 0; col < X_BLOCKS; col++) {
			int n = row * X_BLOCKS + col;
			if (field[n] == 1) rowSum++;
			else break;
		}
		if (rowSum == 10) {
			setOnRemoveOnRow(row);
			rowsRemoved++;
		}
	}

	return rowsRemoved;
}

bool GameField::isTimeStopped()
{
	return timeStopped;
}

void GameField::setOnRemoveOnRow(int row) {
	timeStopped = true;
	//timeState = glfwGetTime();

	for (int col = 0; col < X_BLOCKS; col++) {
		int n = row * X_BLOCKS + col;
		blocks[n].setOnRemove(true);
	}
}

void GameField::fallDown() {
	int * newField = new int[NUMBER_OF_BLOCKS];
	int * colors = new int[NUMBER_OF_BLOCKS];
	int i = 0;
	for (int row = 0; row < Y_BLOCKS; row++) {
		for (int col = 0; col < X_BLOCKS; col++) {
			int n = row * X_BLOCKS + col;
			if (!blocks[n].isOnRemove()) {
				newField[i] = field[n];

				int blockXPos = positionX + col * BLOCK_SIZE;
				int blockYPos = positionY + row * BLOCK_SIZE;
				colors[i] = blocks[n].getColor();

				i++;
			}
			blocks[n].setAlpha(1.0);
			blocks[n].setOnRemove(false);

		}
	}
	for (; i < NUMBER_OF_BLOCKS; i++) {
		newField[i] = 0;
		colors[i] = 0;
	}

	for (int row = 0; row < Y_BLOCKS; row++) {
		for (int col = 0; col < X_BLOCKS; col++) {
			int n = row * X_BLOCKS + col;
			field[n] = newField[n];
			blocks[n].setColor(colors[n]);
		}	
	}

	delete[] newField;

}


