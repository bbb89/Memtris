//#include <GLFW\glfw3.h>
//#include "linmath.h"
//#include <stdlib.h>
//#include <stdio.h>
//
//
//int main(void) {
//	if (!glfwInit()) {
//		exit(EXIT_FAILURE);
//	}
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
//
//	GLFWwindow * window = glfwCreateWindow(1200, 800, "My App", NULL, NULL);
//	if (!window) {
//		glfwTerminate();
//		exit(EXIT_FAILURE);
//	}
//	glfwMakeContextCurrent(window);
//	glfwSwapInterval(1);
//
//	unsigned char pixels[16 * 16 * 4];
//	GLFWimage image;
//	image.width = 16;
//	image.height = 16;
//	image.pixels = pixels;
//	GLFWcursor* cursor = glfwCreateCursor(&image, 0, 0);
//
//	glfwSetCursor(window, cursor);
//
//	const float DEG2RAD = 3.14159 / 180;
//	float radius = 0.25;
//	float xOffset = -0.5, yOffset = 0;
//	int xDir = 1, yDir = 1;
//	float x, y;
//
//	float r = 0, g = 0.3, b = 0.6;
//
//	while (!glfwWindowShouldClose(window)) {
//		float ratio;
//		int width, height;
//		glfwGetFramebufferSize(window, &width, &height);
//		ratio = width / (float)height;
//		glViewport(0, 0, width, height);
//		glClear(GL_COLOR_BUFFER_BIT);
//
//
//		r = fmod(r + 0.001, 1);
//		g = fmod(g + 0.002, 1);
//		b = fmod(b + 0.003, 1);
//
//		glColor3f(r, g, b);
//		glBegin(GL_POLYGON);
//		for (int i = 0; i < 360; i++) {
//			float degInRad = i * DEG2RAD;
//			x = cos(degInRad) * radius + xOffset;
//			y = sin(degInRad) * radius + yOffset;
//			glVertex2f(x, y);
//		}
//		glEnd();
//
//		xOffset += 0.01 * xDir;
//		yOffset += 0.005 * yDir;
//
//		if (xOffset >= 1 || xOffset < -1) {
//			xDir *= -1;
//		}
//		if (yOffset >= 1 || yOffset < -1) {
//			yDir *= -1;
//		}
//
//		glfwSwapBuffers(window);
//		glfwPollEvents();
//	}
//
//	glfwDestroyWindow(window);
//	glfwTerminate();
//	exit(EXIT_SUCCESS);
//}