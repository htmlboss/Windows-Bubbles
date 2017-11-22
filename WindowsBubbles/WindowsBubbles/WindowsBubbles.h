#pragma once
#include <SFML/Graphics.hpp>

#include "Graphics/GLRenderer.h"

#include <memory>

class WindowsBubbles {

public:
	WindowsBubbles() = default;

	void init();
	void update();

private:
	std::unique_ptr<sf::RenderWindow> m_mainWindow;
	std::unique_ptr<GLRenderer> m_renderer;
};

