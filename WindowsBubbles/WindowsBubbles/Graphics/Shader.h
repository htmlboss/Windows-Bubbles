#pragma once

#include <glad/glad.h>
#include <array>

class Shader {

public:
	Shader() = default;

	void init(const std::string_view path, const int type);
	void attachShader(const GLuint Program) const;
	void detachShader(const GLuint Program) const;
	void deleteShader() const;

private:
	void compile(const GLchar* shaderCode);

	GLuint m_shaderID;
	GLint m_success;
	std::array<GLchar, 1024> m_infoLog;
};
