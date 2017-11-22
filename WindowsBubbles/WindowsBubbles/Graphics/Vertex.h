#pragma once

#include <SFML/System/Vector3.hpp>
#include <SFML/System/Vector2.hpp>
#include <cstddef>

struct Vertex {
	Vertex(const sf::Vector2f& pos, const sf::Vector3f& col) : position(pos), color(col) {}

	// Member offsets for data interleaving in OpenGL
	static auto positionOffset() {
		return offsetof(Vertex, position);
	}

	static auto colorOffset() {
		return offsetof(Vertex, color);
	}


	sf::Vector2f position;
	sf::Vector3f color;
};
