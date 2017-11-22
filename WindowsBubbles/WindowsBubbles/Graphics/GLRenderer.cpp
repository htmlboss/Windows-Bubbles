#include "GLRenderer.h"

#include <SFML/OpenGL.hpp>

 void GLRenderer::init(const unsigned width, const unsigned height) {
	 glViewport(0, 0, width, height);
}

 void GLRenderer::update()  {
	 glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	 glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
 }

 void GLRenderer::resize(const unsigned width, const unsigned height) {
	 glViewport(0, 0, width, height);
 }
