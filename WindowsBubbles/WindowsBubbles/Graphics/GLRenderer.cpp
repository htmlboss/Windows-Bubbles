#define _USE_MATH_DEFINES
#include "GLRenderer.h"
#include "Shader.h"

#include <glm/gtc/matrix_transform.hpp>

#include <iostream>
//#include <cmath>

/***********************************************************************************/
 void GLRenderer::init(const unsigned width, const unsigned height) {
	 if (!gladLoadGL()) {
		 std::cerr << "GLAD failed to initialize.\n";
		 std::abort();
	 }

	 glViewport(0, 0, width, height);

	 Shader vertexShader, fragmentShader;
	 vertexShader.init("Data/Shaders/basic.vert", GL_VERTEX_SHADER);
	 fragmentShader.init("Data/Shaders/basic.frag", GL_FRAGMENT_SHADER);
	 m_shaderProgram.init({ vertexShader, fragmentShader });

	 m_viewMatrix = glm::lookAt({0.0f, 0.0f, -1.0f}, glm::vec3(0.0f), {0.0f, 1.0f, 0.0f});
	 updateMatrices(width, height);

	 // Generate vertices for circle using polar coords
	 std::array<float, 180> vertices;
	 const auto pi_one_eighty = M_PI / 180.0f;
	 auto theta = 0;
	 auto currentSize = 0;
	 while (theta < 360) {

		 vertices[currentSize++] = 0.25f * std::cosf(theta * pi_one_eighty); // x-coord
		 vertices[currentSize++] = 0.25f * std::sinf(theta * pi_one_eighty); // y-coord
		 vertices[currentSize++] = 0.0f; // z-coord

		 theta += (360 / m_vertexCount); // Go around the circle in increments
	 }

	 glGenVertexArrays(1, &m_vao);
	 glBindVertexArray(m_vao);

	 glGenBuffers(1, &m_vbo);
	 glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	 glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices.data(), GL_STATIC_DRAW);

	 glEnableVertexAttribArray(0);
	 glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
}

 /***********************************************************************************/
 void GLRenderer::update(const glm::vec3& pos)  {
	 glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	 glClear(GL_COLOR_BUFFER_BIT);

	 m_shaderProgram.bind();
	 m_shaderProgram.SetUniform("pos", glm::translate(glm::mat4(1.0f), pos));
	 m_shaderProgram.SetUniform("projView", m_projViewMatrix);
	 glBindVertexArray(m_vao);
	 glDrawArrays(GL_TRIANGLE_FAN, 0, m_vertexCount);
 }

 /***********************************************************************************/
 void GLRenderer::shutdown() const {
	 glDeleteBuffers(1, &m_vbo);
	 glDeleteBuffers(1, &m_ebo);
	 glDeleteVertexArrays(1, &m_vao);

	 m_shaderProgram.deleteProgram();
 }

 /***********************************************************************************/
 void GLRenderer::resize(const unsigned width, const unsigned height) {
	glViewport(0, 0, width, height);
	
	updateMatrices(width, height);
 }

 /***********************************************************************************/
 void GLRenderer::updateMatrices(const unsigned width, const unsigned height) {
	 // https://solarianprogrammer.com/2013/05/22/opengl-101-matrices-projection-view-model/
	 m_projectionMatrix = glm::ortho(-static_cast<float>(width) / static_cast<float>(height), static_cast<float>(width) / static_cast<float>(height), -1.0f, 1.0f, -1.0f, 1.0f);
	 // Pre-compute the projection-view matrix product since it rarely changes.
	 // Saves the GPU from computing it for every vertex.
	 m_projViewMatrix = m_projectionMatrix * m_viewMatrix;
 }
