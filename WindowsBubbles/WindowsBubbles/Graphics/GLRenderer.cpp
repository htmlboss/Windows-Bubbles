#include "GLRenderer.h"
#include "Shader.h"

#include <glm/gtc/matrix_transform.hpp>

#include <iostream>

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

	 m_shaderProgram.init({vertexShader, fragmentShader});

	 m_viewMatrix = glm::lookAt(
		 glm::vec3(0.0f, 0.0f, -5.0f), // Camera is at (0,0,5), in World Space
		 glm::vec3(0.0f), // and looks at the origin
		 glm::vec3(0.0f, 1.0f, 0.0f)  // Head is up (set to 0,-1,0 to look upside-down)
	 );

	 glGenVertexArrays(1, &m_vao);
	 glBindVertexArray(m_vao);

	 glGenBuffers(1, &m_vbo);
	 glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	 glBufferData(GL_ARRAY_BUFFER, sizeof(m_vertices), m_vertices.data(), GL_STATIC_DRAW);

	 glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
	 glEnableVertexAttribArray(0);

	 glGenBuffers(1, &m_ebo);
	 glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
	 glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(m_indices), m_indices.data(), GL_STATIC_DRAW);
}

 /***********************************************************************************/
 void GLRenderer::update()  {
	 glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	 glClear(GL_COLOR_BUFFER_BIT);

	 m_shaderProgram.bind();
	 glBindVertexArray(m_vao);
	 glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
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
	
	calcProjMatrix(width, height);
 }

 /***********************************************************************************/
 void GLRenderer::calcProjMatrix(const unsigned width, const unsigned height) {
	 m_projectionMatrix = glm::ortho(0.0f, static_cast<float>(width), static_cast<float>(height), 0.0f, 0.1f, 10.0f);
 }