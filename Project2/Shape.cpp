#include "Shape.h"


int Shape::NUMBER_OF_BLOCKS = 16;
int Shape::X_BLOCKS = 4;
int Shape::BLOCK_SIZE = 32;


Shape::Shape()
{
}

Shape::Shape(GLuint * _images, int * _field)
{
	srand(time(NULL));
	images = _images;
	field = _field;
	gameFieldX = 200;
	gameFieldY = 40;
	relativeX = 4;
	relativeY = 19;
	selectRandomShape();
	initializeShape();
}

Shape::~Shape()
{
}

int Shape::calculateX() {
	return gameFieldX + BLOCK_SIZE * relativeX;
}

int Shape::calculateY() {
	return gameFieldY + BLOCK_SIZE * relativeY;
}

void Shape::initializeShape() {

	blocks = new Block[NUMBER_OF_BLOCKS];
	color = rand() % 3 + 1;

	for (int i = 0; i < NUMBER_OF_BLOCKS; i++) {
		int column = i % 4;
		int row = i / 4;
		int blockXPos = calculateX() + column * 32;
		int blockYPos = calculateY() + row * 32;

		blocks[i] = Block(32, color, blockXPos, blockYPos, images);
	}
}

void Shape::selectRandomShape() {

	int * _shape;
	int randomShape = rand() % 6;

	switch (randomShape)
	{
	case 0:
		_shape = ShapeRepository::I;
		break;
	case 1:
		_shape = ShapeRepository::J;
		break;
	case 2:
		_shape = ShapeRepository::L;
		break;
	case 3:
		_shape = ShapeRepository::O;
		break;
	case 4:
		_shape = ShapeRepository::S;
		break;
	case 5:
		_shape = ShapeRepository::T;
		break;
	case 6:
		_shape = ShapeRepository::Z;
		break;

	default:
		_shape = ShapeRepository::Z;
		break;
	}

	shape = new int[NUMBER_OF_BLOCKS];

	for (int i = 0; i < NUMBER_OF_BLOCKS; i++) {
		shape[i] = _shape[i];
	}

	int numberOfTurns = rand() % 3;
	for (int i = 0; i < numberOfTurns; i++) {
		turn();
	}

}

void Shape::turn() {
	int * newShape = new int[NUMBER_OF_BLOCKS];
	for (int i = 0; i < NUMBER_OF_BLOCKS; i++) {
		int column = i % 4;
		int row = i / 4;
		int newIndex = (12 + row) - column * 4;
		newShape[i] = shape[newIndex];
	}
	
	bool collision = false;
	int maxPosition = GameField::X_BLOCKS * GameField::Y_BLOCKS;
	for (int i = 0; i < NUMBER_OF_BLOCKS; i++) {
		int blockPosition = calculatePositionInField(i);

		if (blockPosition < maxPosition && field[blockPosition] == 1) {
			collision = true;
		}
	}

	while (outOfFieldRight()) {
		relativeX--;
	}

	if (!collision) {
		if (shape) int * oldShape = shape;
		shape = newShape;

		while (outOfFieldRight()) {
			relativeX--;
		}
		while (outOfFieldLeft()) {
			relativeX++;
		}
	}
	else {
		delete[] newShape;
	}

	//int width = 4;
	//for (int i = 0; i < NUMBER_OF_BLOCKS; i++) {
	//	int column = i % width;
	//	int row = i / width;
	//	
	//	shape[i] = 12 + row - (column * width);
	//	
	//}
}

bool Shape::outOfFieldRight() {
	for (int i = 0; i < NUMBER_OF_BLOCKS; i++) {
		if (shape[i] == 1) {
			int column = i % 4;
			if (relativeX + column > 9) return true;
		}
	}

	return false;
}

bool Shape::outOfFieldLeft() {
	for (int i = 0; i < NUMBER_OF_BLOCKS; i++) {
		if (shape[i] == 1) {
			int column = i % 4;
			if (relativeX + column < 0) return true;
		}
	}

	return false;
}

void Shape::drawActiveBlocks() {
	int n = NUMBER_OF_BLOCKS;
	for (int i = 0; i < NUMBER_OF_BLOCKS; i++) {
		if (shape[i] == 1 && !outOfFieldTop(blocks[i])) {
			blocks[i].drawBlock();
		}
	}

	updatePositionsOfBlocks();
}

bool Shape::outOfFieldTop(Block block)
{
	return block.getPosY() >= gameFieldY + 640;
}

bool Shape::leftCollision() {
	for (int i = 0; i < NUMBER_OF_BLOCKS; i++) {
		int column = i % 4;
		if (shape[i] == 1) {
			if(relativeX + column == 0) return true;

			int blockAtLeft = calculatePositionInField(i) - 1;
			if (field[blockAtLeft] == 1) return true;
		}
	}

	return false;
}

bool Shape::rightCollision() {
	for (int i = 0; i < NUMBER_OF_BLOCKS; i++) {
		int column = i % 4;
		if (shape[i] == 1) {
			if(relativeX + column == 9) return true;

			int blockAtRight = calculatePositionInField(i) + 1;
			if (field[blockAtRight] == 1) return true;
		}
	}

	return false;
}

bool Shape::bottomCollision() {
	for (int i = 0; i < NUMBER_OF_BLOCKS; i++) {
		int row = i / 4;
		if (shape[i] == 1 && relativeY + row == 0) {
			return true;
		}
	}

	return false;
}

bool Shape::blockCollision() {
	for (int i = 0; i < NUMBER_OF_BLOCKS; i++) {
		if (shape[i] == 1) {
			int blockUnder = calculatePositionInField(i) - GameField::X_BLOCKS;

			if (blockUnder > 0 && field[blockUnder] == 1) {
				//std::cout << field[blockUnder];
				return true;
			}
			
		}
	}

	return false;
}

bool Shape::endOfGame() {
	if (field[193] + field[194] + field[195] + field[196] + field[197] > 1) {
		return true;
	}

	return false;
}

int Shape::calculatePositionInField(int positionInShape) {
	int shapeRow = positionInShape / 4;
	int fieldColumn = relativeX + (positionInShape % X_BLOCKS);
	int fieldRow = relativeY + shapeRow;

	return fieldRow * GameField::X_BLOCKS + fieldColumn;
}

void Shape::updatePositionsOfBlocks()
{
	for (int i = 0; i < NUMBER_OF_BLOCKS; i++) {
		int column = i % 4;
		int row = i / 4;
		int blockXPos = calculateX() + column * 32;
		int blockYPos = calculateY() + row * 32;

		blocks[i].setPosX(blockXPos);
		blocks[i].setPosY(blockYPos);
	}

}

void Shape::goLeft()
{
	if (!leftCollision()) {
		relativeX--;
	}
}

void Shape::goRight()
{
	if (!rightCollision()) {
		relativeX++;
	}
}

void Shape::goDown()
{
	relativeY--;
}

int Shape::getRelativeX()
{
	return relativeX;
}

int Shape::getRelativeY()
{
	return relativeY;
}

int * Shape::getShape()
{
	return shape;
}

int Shape::getColor()
{
	return color;
}

