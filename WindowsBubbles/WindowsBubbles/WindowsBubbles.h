#pragma once
#include <SFML/Graphics.hpp>

#include "Graphics/GLRenderer.h"
#include "Physics/Physics.h"

#include <memory>

class WindowsBubbles {

public:
	WindowsBubbles() = default;

	void init();
	void update();

private:
	// Window
	std::unique_ptr<sf::RenderWindow> m_mainWindow;
	// Renderer
	std::unique_ptr<GLRenderer> m_renderer;
	// Physics
	std::unique_ptr<Physics> m_physics;
};

