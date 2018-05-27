#include "Engine.h"

int Engine::SCREEN_WIDTH = 1200;
int Engine::SCREEN_HEIGHT = 720;
GLFWwindow * Engine::window = NULL;

Engine::Engine()
{

}

Engine::~Engine()
{

}

bool Engine::initialize() {
	initGLFW();
	initWindowAndSetupVideoMode();
	//initializeCursor();

	return true;
}

void Engine::initGLFW() {
	if (!glfwInit()) {
		exit(EXIT_FAILURE);
	}
}

void Engine::initWindowAndSetupVideoMode() {
	window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Memtris", NULL, NULL);
	if (!window) {
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);

	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	glViewport(0, 0, width, height);

	const GLFWvidmode * mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
	int xPos = (mode->width - SCREEN_WIDTH) / 2;
	int yPos = (mode->height - SCREEN_HEIGHT) / 2;
	glfwSetWindowPos(window, xPos, yPos);

	glMatrixMode(GL_PROJECTION);

	glEnable(GL_ALPHA_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

}


void Engine::initializeCursor() {
	unsigned char pixels[16 * 16 * 4];
	GLFWimage image;
	image.width = 16;
	image.height = 16;
	image.pixels = pixels;
	GLFWcursor* cursor = glfwCreateCursor(&image, 0, 0);

	glfwSetCursor(window, cursor);
}

void Engine::update()
{
	glfwPollEvents();
}

void Engine::render()
{
	glClearColor(0, 1, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glfwSwapBuffers(window);
}

void Engine::close() {
	glfwDestroyWindow(window);
	glfwTerminate();
	exit(EXIT_SUCCESS);
}

bool Engine::isWorking() {
	return !glfwWindowShouldClose(window);
}
