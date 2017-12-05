#include "ShaderProgram.h"

#include "Shader.h"

#include <iostream>

#include <glm/gtc/type_ptr.hpp>

/***********************************************************************************/
ShaderProgram::~ShaderProgram() {
	deleteProgram();
}

/***********************************************************************************/
void ShaderProgram::init(const std::initializer_list<Shader> shaders) {
	m_programID = glCreateProgram();

	for (const auto& shader : shaders) {
		shader.attachShader(m_programID);
	}

	if (linkAndValidate()) {
		getUniforms();
	}

	// Cleanup
	for (const auto& shader : shaders) {
		shader.detachShader(m_programID);
		shader.deleteShader();
	}
}

/***********************************************************************************/
void ShaderProgram::bind() const {
	glUseProgram(m_programID);
}

/***********************************************************************************/
void ShaderProgram::deleteProgram() const {
	if (m_programID != 0) {
		glDeleteProgram(m_programID);
	}
}

/***********************************************************************************/
ShaderProgram& ShaderProgram::SetUniform(const std::string& uniformName, const glm::vec2& value) {
	glUniform2f(m_uniforms.at(uniformName), value.x, value.y);

	return *this;
}

/***********************************************************************************/
ShaderProgram& ShaderProgram::SetUniform(const std::string& uniformName, const glm::vec3& value) {
	glUniform3f(m_uniforms.at(uniformName), value.x, value.y, value.z);

	return *this;
}

/***********************************************************************************/
ShaderProgram& ShaderProgram::SetUniform(const std::string& uniformName, const glm::mat4x4& value) {
	glUniformMatrix4fv(m_uniforms.at(uniformName), 1, GL_FALSE, value_ptr(value));

	return *this;
}

/***********************************************************************************/
bool ShaderProgram::linkAndValidate() {
	glLinkProgram(m_programID);
	glGetProgramiv(m_programID, GL_LINK_STATUS, &m_success);
	if (!m_success) {
		glGetProgramInfoLog(m_programID, m_infoLog.size(), nullptr, m_infoLog.data());
		std::cerr << "Shader Program Linking Error: " << m_infoLog.data() << std::endl;
		return false;
	}

	glValidateProgram(m_programID);
	glGetProgramiv(m_programID, GL_VALIDATE_STATUS, &m_success);
	if (!m_success) {
		glGetProgramInfoLog(m_programID, m_infoLog.size(), nullptr, m_infoLog.data());
		std::cerr << "Shader Program Validation Error: " << m_infoLog.data() << std::endl;
		return false;
	}

	return true;
}

/***********************************************************************************/
void ShaderProgram::getUniforms() {
	auto total = -1;
	glGetProgramiv(m_programID, GL_ACTIVE_UNIFORMS, &total);
	for (auto i = 0; i < total; ++i) {
		auto name_len = -1, num = -1;
		GLenum type = GL_ZERO;
		char name[100];
		glGetActiveUniform(m_programID, GLuint(i), sizeof(name) - 1, &name_len, &num, &type, name);
		name[name_len] = 0;

		const auto nameStr = std::string(name);

		// TODO: Filter out uniform block members using glGetActiveUniformsiv
		m_uniforms.try_emplace(nameStr, glGetUniformLocation(m_programID, name));
	}
}
