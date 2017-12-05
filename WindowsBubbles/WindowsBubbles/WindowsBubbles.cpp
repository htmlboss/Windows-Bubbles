#include "WindowsBubbles.h"

#include <SFML/Window/ContextSettings.hpp>

/***********************************************************************************/
// https://stackoverflow.com/questions/12945277/drawing-antialiased-circle-using-shaders
void WindowsBubbles::init() {
	// Setup SFML
	sf::ContextSettings settings;
#ifdef _DEBUG
	// Create debug context
	settings.attributeFlags = sf::ContextSettings::Core | sf::ContextSettings::Debug;
#else
	settings.attributeFlags = sf::ContextSettings::Core;
#endif
	settings.depthBits = 24;
	settings.stencilBits = 8;
	settings.antialiasingLevel = 4;
	settings.majorVersion = 4;
	settings.minorVersion = 4;
	
	// Window
	m_mainWindow = std::make_unique<sf::RenderWindow>(sf::VideoMode{1280, 720}, "Windows Bubbles", sf::Style::Default, settings);
	m_mainWindow->setVerticalSyncEnabled(true);
	m_mainWindow->setActive(true);

	// Renderer
	m_renderer = std::make_unique<GLRenderer>();
	m_renderer->init(1280, 720);

	// Physics
	m_physics = std::make_unique<Physics>();
	m_physics->init(1);
}

/***********************************************************************************/
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

		m_physics->update();

		const auto pos = m_physics->getPosition();
		m_renderer->update({pos.x, pos.y, 0.0f});

		m_mainWindow->display();
	}

	m_renderer->shutdown();
}
