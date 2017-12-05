#pragma once

#include "ShaderProgram.h"

class GLRenderer {
	
public:
	GLRenderer() = default;

	void init(const unsigned width, const unsigned height);
	void update(const glm::vec3& pos);
	// Cleans up OpenGL resources
	void shutdown() const;

	void resize(const unsigned width, const unsigned height);

private:
	void updateMatrices(const unsigned width, const unsigned height);
	
	glm::mat4x4 m_projectionMatrix, m_viewMatrix, m_projViewMatrix;
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
