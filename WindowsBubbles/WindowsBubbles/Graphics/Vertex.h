#pragma once

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

#include <cstddef>

struct Vertex {
	Vertex(const glm::vec2& pos, const glm::vec3& col) : position(pos), color(col) {}

	// Member offsets for data interleaving in OpenGL
	static auto positionOffset() {
		return offsetof(Vertex, position);
	}

	static auto colorOffset() {
		return offsetof(Vertex, color);
	}

	static auto vertexSize() noexcept {
		return sizeof(Vertex);
	}


	glm::vec2 position;
	glm::vec3 color;
};
