#pragma once

#include <glm/mat4x4.hpp>

class GLRenderer {
	
public:
	GLRenderer() = default;

	void init(const unsigned width, const unsigned height);
	void update();

	void resize(const unsigned width, const unsigned height);

private:
	void calcProjMatrix(const unsigned width, const unsigned height);

	glm::mat4 m_projectionMatrix;
	glm::mat4 m_viewMatrix;
};