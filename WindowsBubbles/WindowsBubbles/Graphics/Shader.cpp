#include "Shader.h"

#include <iostream>
#include <fstream>

/***********************************************************************************/
void Shader::init(const std::string_view path, const int type) {
	m_shaderID = glCreateShader(type);

	std::ifstream in(path.data(), std::ios::in);
	in.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	if (!in) {
		std::cerr << "File loading error: " + *path.data() << " " << errno << '\n';
		std::abort();
	}

	const auto shaderCode = std::string(std::istreambuf_iterator<char>(in), std::istreambuf_iterator<char>());

	compile(shaderCode.data());
}

/***********************************************************************************/
void Shader::attachShader(const GLuint Program) const {
	glAttachShader(Program, m_shaderID);
}

/***********************************************************************************/
void Shader::detachShader(const GLuint Program) const {
	glDetachShader(Program, m_shaderID);
}

/***********************************************************************************/
void Shader::deleteShader() const {
	glDeleteShader(m_shaderID);
}

/***********************************************************************************/
void Shader::compile(const GLchar* shaderCode) {
	glShaderSource(m_shaderID, 1, &shaderCode, nullptr);
	glCompileShader(m_shaderID);

	glGetShaderiv(m_shaderID, GL_COMPILE_STATUS, &m_success);
	if (!m_success) {
		glGetShaderInfoLog(m_shaderID, m_infoLog.size(), nullptr, m_infoLog.data());
		std::cerr << "Shader Error: " << m_infoLog.data() << std::endl;
	}
}
