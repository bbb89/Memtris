#include "Engine.h"


int Engine::SCREEN_WIDTH = 1200;
int Engine::SCREEN_HEIGHT = 720;
double Engine::INITIAL_STEP_SPEED = 0.6;
double Engine::SPACE_STEP_SPEED_MODIFICATOR = 0.2;

GLFWwindow * Engine::window = NULL;

Engine::Engine()
{
	endOfGame = false;
	stepSpeed = INITIAL_STEP_SPEED;
	images = new GLuint[5];
	memes = new GLuint[16];
	initialLeftKeyState = GLFW_PRESS;
	initialRightKeyState = GLFW_PRESS;
	initialSpaceKeyState = GLFW_PRESS;
	lastStepTime = 0;
	lastGoFasterTime = 0;
	score = 0L;
	memNum = 0;
	memActive = false;
}

Engine::~Engine()
{

}

bool Engine::initialize() 
{
	initGLFW();
	initWindowAndSetupVideoMode();
	initializeDependencies();
	setPositionOfWindow();
	setupOrthoAndViewportToWindowSize();
	glfwSwapInterval(1);
	loadImages();
	loadAudio();

	initGameElements();

	return true;
}

void Engine::loadImages() {
	images[0] = ilutGLLoadImage((char *) "img/background.png");
	images[1] = ilutGLLoadImage((char *) "img/block-green.png");
	images[2] = ilutGLLoadImage((char *) "img/block-orange.png");
	images[3] = ilutGLLoadImage((char *) "img/block-blue.png");
	images[4] = ilutGLLoadImage((char *) "img/block-red.png");

	memes[0] = ilutGLLoadImage((char *) "memes/16.jpg");
	memes[1] = ilutGLLoadImage((char *) "memes/1.jpg");
	memes[2] = ilutGLLoadImage((char *) "memes/2.jpg");
	memes[3] = ilutGLLoadImage((char *) "memes/3.jpg");
	memes[4] = ilutGLLoadImage((char *) "memes/4.jpg");
	memes[5] = ilutGLLoadImage((char *) "memes/5.jpg");
	memes[6] = ilutGLLoadImage((char *) "memes/6.jpg");
	memes[7] = ilutGLLoadImage((char *) "memes/7.jpg");
	memes[8] = ilutGLLoadImage((char *) "memes/8.jpg");
	memes[9] = ilutGLLoadImage((char *) "memes/9.jpg");
	memes[10] = ilutGLLoadImage((char *) "memes/10.jpg");
	memes[11] = ilutGLLoadImage((char *) "memes/11.jpg");
	memes[12] = ilutGLLoadImage((char *) "memes/12.jpg");
	memes[13] = ilutGLLoadImage((char *) "memes/13.jpg");
	memes[14] = ilutGLLoadImage((char *) "memes/14.jpg");
	memes[15] = ilutGLLoadImage((char *) "memes/15.jpg");

}

void Engine::loadAudio() {
	sndPlaySound("audio/main-theme", SND_LOOP | SND_ASYNC);
}

void Engine::initGLFW() 
{
	if (!glfwInit()) {
		exit(EXIT_FAILURE);
	}
}

void Engine::initWindowAndSetupVideoMode() 
{
	window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Memtris", NULL, NULL);
	if (!window) {
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwMakeContextCurrent(window);
}

void Engine::initializeDependencies() {
	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

	if ((iluGetInteger(IL_VERSION_NUM) < IL_VERSION) || (iluGetInteger(ILU_VERSION_NUM) < ILU_VERSION) || (ilutGetInteger(ILUT_VERSION_NUM) < ILUT_VERSION))
	{
		std::cout << "Zla wersja biblioteki Devil" << std::endl;
		exit(EXIT_FAILURE);
	}

	ilInit();
	iluInit();
	ilutInit();
	ilutRenderer(ILUT_OPENGL);
}

void Engine::setPositionOfWindow() {
	const GLFWvidmode * mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
	int xPos = (mode->width - SCREEN_WIDTH) / 2;
	int yPos = (mode->height - SCREEN_HEIGHT) / 2;
	glfwSetWindowPos(window, xPos, yPos);
}

void Engine::setupOrthoAndViewportToWindowSize() {
	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	glEnable(GL_DEPTH_TEST);
	glViewport(0.0f, 0.0f, width, height);
	glMatrixMode(GL_PROJECTION);
	glOrtho(0, width, 0, height, -1, 1);
	glMatrixMode(GL_MODELVIEW);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
}

void Engine::initGameElements()
{
	background = new BackgroundImage(SCREEN_WIDTH, SCREEN_HEIGHT, images);
	gameField = new GameField(images);
	shape = new Shape(images, gameField->getField());
}

void Engine::update()
{
	if (!endOfGame) {
		score += 10 * gameField->checkLines();
		updateTimer();
		handleInput();
		detectColission();
		goFaster();
		checkIfGameOver();
	}
	glfwPollEvents();
}

void Engine::goFaster() {
	double time = glfwGetTime();
	if (time - lastGoFasterTime > 10) {
		INITIAL_STEP_SPEED -= 0.05;
		lastGoFasterTime = time;
	}

}

void Engine::updateTimer() {	
	double time = glfwGetTime();
	if (time - lastStepTime > stepSpeed) {
		system("cls");
		std::cout << "Your score: " << score << std::endl;

		lastStepTime = time;
		if (!gameField->isTimeStopped()) {
			shape->goDown();
		}

	}
}

void Engine::handleInput() {
	int newLeftKeyState = glfwGetKey(window, GLFW_KEY_LEFT);
	if (newLeftKeyState == GLFW_PRESS && initialLeftKeyState == GLFW_RELEASE) {
		shape->goLeft();
	}
	initialLeftKeyState = newLeftKeyState;

	int newRightKeyState = glfwGetKey(window, GLFW_KEY_RIGHT);
	if (newRightKeyState == GLFW_PRESS && initialRightKeyState == GLFW_RELEASE) {
		shape->goRight();
	}
	initialRightKeyState = newRightKeyState;

	int newSpaceKeyState = glfwGetKey(window, GLFW_KEY_SPACE);
	if (newSpaceKeyState == GLFW_PRESS && initialSpaceKeyState == GLFW_RELEASE) {
		shape->turn();
	}
	initialSpaceKeyState = newSpaceKeyState;

	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
		stepSpeed = INITIAL_STEP_SPEED * SPACE_STEP_SPEED_MODIFICATOR;
	}

	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_RELEASE) {
		stepSpeed = INITIAL_STEP_SPEED;
	}

}

void Engine::render()
{
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	if (!endOfGame) {
		drawFrame();
	}

	glfwSwapBuffers(window);
}

void Engine::drawFrame()
{
	background->displayBackground();
	gameField->drawField();
	shape->drawActiveBlocks();
	if (shape->getRelativeY() < 14) {
		if (!memActive) {
			memNum = rand() % 16;
		}
		memActive = true;
		displayMeme();
	}
	else if (memActive) {
		memActive = false;
	}


}

void Engine::close() 
{
	glfwDestroyWindow(window);
	glfwTerminate();
	exit(EXIT_SUCCESS);
}

bool Engine::isWorking() 
{
	return !glfwWindowShouldClose(window);
}

void Engine::detectColission() {
	bool collision = shape->bottomCollision() || shape->blockCollision();
	if (collision) {
		int * activeBlocks = shape->getShape();
		int shapeXPos = shape->getRelativeX();
		int shapeYPos = shape->getRelativeY();

		int n = Shape::NUMBER_OF_BLOCKS;
		for (int i = 0; i < n; i++) {
			if (activeBlocks[i] == 1) {
				int row = (i / Shape::X_BLOCKS);
				int yOffset = shapeYPos * GameField::X_BLOCKS;
				int widthDifference = GameField::X_BLOCKS - Shape::X_BLOCKS;
				int fieldToActivate = shapeXPos + i + row * widthDifference + yOffset;
				gameField->activateField(fieldToActivate, shape->getColor());
			}
		}

		delete shape;
		shape = new Shape(images, gameField->getField());

	}
}

void Engine::checkIfGameOver() {
	if (shape->endOfGame()) {
		endOfGame = true;
		system("cls");
		std::cout << "Game Over\nYour score was: " << score;
		glfwDestroyWindow(window);
		glfwTerminate();
	}
}

void Engine::displayMeme()
{
	int memWidth = 500;
	int memHeight = 500;

	glBegin(GL_QUADS);
	glColor4f(0, 0.5, 1, 0.4);
	glVertex2d(650 - 5, 100 - 5);
	glVertex2d(650 - 5, 100 + memHeight + 5);
	glVertex2d(650 + memWidth + 5, 100 + memHeight + 5);
	glVertex2d(650 + memWidth + 5, 100 - 5);
	glColor4f(1, 1, 1, 1);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, memes[memNum]);
	glEnable(GL_TEXTURE_2D);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0); glVertex3f(650, 100, 0.2f);  // Top left
	glTexCoord2f(0.0, 1.0);	glVertex3f(650, 100 + memHeight, 0.2f);  // Bottom left
	glTexCoord2f(1.0, 1.0);	glVertex3f(650 + memWidth, 100 + memHeight, 0.2f);  // Bottom right
	glTexCoord2f(1.0, 0.0);	glVertex3f(650 + memWidth, 100, 0.2f);  // Top right
	glEnd();
	glDisable(GL_TEXTURE_2D);
}
