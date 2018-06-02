#include "Engine.h"
#include <stdlib.h>
#include <stdio.h>

int main(void) 
{
	Engine engine;
	engine.initialize();

	while (engine.isWorking()) {
		engine.update();
		engine.render();
	}

	engine.close();
}