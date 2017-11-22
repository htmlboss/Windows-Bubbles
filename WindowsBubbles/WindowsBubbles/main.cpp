#ifdef _DEBUG
// CRT Memory Leak detection
#define _CRTDBG_MAP_ALLOC  
#include <stdlib.h>  
#include <crtdbg.h>
#endif

#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>

int main() {
#ifdef _DEBUG
	// Detects memory leaks upon program exit
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

	sf::ContextSettings settings;
#ifdef _DEBUG
	// Create debug context
	settings.attributeFlags = sf::ContextSettings::Core | sf::ContextSettings::Debug;
#else
	settings.attributeFlags = sf::ContextSettings::Core
#endif
	settings.depthBits = 24;
	settings.stencilBits = 8;
	settings.antialiasingLevel = 4;
	settings.majorVersion = 4;
	settings.minorVersion = 5;

	sf::RenderWindow window({ 1280, 720 }, "Windows Bubbles", sf::Style::Default, settings);
	window.setVerticalSyncEnabled(true);
	window.setActive(true);

	bool running = true;
	while (running) {
		// Handle events
		sf::Event event;
		while (window.pollEvent(event)) {
			switch (event.type) {
			case sf::Event::Closed:
				running = false;
				break;
			case sf::Event::Resized:
				glViewport(0, 0, event.size.width, event.size.height);
				break;
			default:
				break;
			}
		}

		// clear the buffers
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// draw...

		// end the current frame (internally swaps the front and back buffers)
		window.display();
	}

	return 0;
}