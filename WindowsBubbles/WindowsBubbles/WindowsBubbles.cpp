#include "WindowsBubbles.h"

#include <SFML/Window/ContextSettings.hpp>

void WindowsBubbles::init() {
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
	
	m_mainWindow = std::make_unique<sf::RenderWindow>(sf::VideoMode{1280, 720}, "Windows Bubbles", sf::Style::Default, settings);
	m_mainWindow->setVerticalSyncEnabled(true);
	m_mainWindow->setActive(true);

	m_renderer = std::make_unique<GLRenderer>();
	m_renderer->init(1280, 720);
}

void WindowsBubbles::update() {
	bool running = true;
	while (running) {
		// Handle events
		sf::Event event;
		while (m_mainWindow->pollEvent(event)) {
			switch (event.type) {
			case sf::Event::Closed:
				running = false;
				break;
			case sf::Event::Resized:
				m_renderer->resize(event.size.width, event.size.height);
				break;
			default:
				break;
			}
		}

		m_renderer->update();

		// Swap back-buffers
		m_mainWindow->display();
	}
}
