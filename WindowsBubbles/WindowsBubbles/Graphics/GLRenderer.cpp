#include "GLRenderer.h"

#include <SFML/OpenGL.hpp>

#include <glm/gtc/matrix_transform.hpp>

/***********************************************************************************/
 void GLRenderer::init(const unsigned width, const unsigned height) {
	 glViewport(0, 0, width, height);

	 m_viewMatrix = glm::lookAt(
		 glm::vec3(0.0f, 0.0f, -5.0f), // Camera is at (0,0,5), in World Space
		 glm::vec3(0.0f), // and looks at the origin
		 glm::vec3(0.0f, 1.0f, 0.0f)  // Head is up (set to 0,-1,0 to look upside-down)
	 );
}

 /***********************************************************************************/
 void GLRenderer::update()  {
	 glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	 glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
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
