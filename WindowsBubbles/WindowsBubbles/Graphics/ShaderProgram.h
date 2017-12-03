#pragma once

#include <initializer_list>
#include <array>
#include <unordered_map>

class Shader;

class ShaderProgram {

public:
	ShaderProgram() = default;
	~ShaderProgram();

	void init(const std::initializer_list<Shader> shaders);
	void bind() const;
	void deleteProgram() const;

private:
	bool linkAndValidate();
	void getUniforms();

	std::unordered_map<std::string, int> m_uniforms;

	unsigned int m_programID;

	//  To check for compile-time errors
	int m_success;
	std::array<char, 1024> m_infoLog;
};
