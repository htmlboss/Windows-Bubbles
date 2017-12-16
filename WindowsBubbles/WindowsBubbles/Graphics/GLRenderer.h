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

	std::size_t m_vertexCount = 60;
};
