#pragma once

#include "ShaderProgram.h"

#include <glm/mat4x4.hpp>

class GLRenderer {
	
public:
	GLRenderer() = default;

	void init(const unsigned width, const unsigned height);
	void update();
	void shutdown() const;

	void resize(const unsigned width, const unsigned height);

private:
	void calcProjMatrix(const unsigned width, const unsigned height);

	glm::mat4 m_projectionMatrix;
	glm::mat4 m_viewMatrix;

	unsigned int m_vao, m_vbo, m_ebo;

	ShaderProgram m_shaderProgram;
	
	// Sprite vertex data
	const std::array<float, 12> m_vertices {
		0.5f,  0.5f, 0.0f,  // top right
		0.5f, -0.5f, 0.0f,  // bottom right
		-0.5f, -0.5f, 0.0f,  // bottom left
		-0.5f,  0.5f, 0.0f   // top left 
	};

	const std::array<unsigned int, 6> m_indices {
		0, 1, 3,   // first triangle
		1, 2, 3    // second triangle
	};
};
