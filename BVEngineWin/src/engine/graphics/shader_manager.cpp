#include "shader_manager.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <fstream>
#include <sstream>
#include <exception>
#include <iostream>

namespace bulka {
	ShaderManager::ShaderProgram ShaderManager::mainShader;
	ShaderManager::ShaderProgram ShaderManager::textShader;
	void ShaderManager::init() {
		if (mainShader.load("res/shaders/3d/main.vert", "res/shaders/3d/main.frag") == 0) {
			throw std::exception("Can't load shaders: res/shaders/3d/main.frag, res/shaders/3d/main.vert");
		}
		if (textShader.load("res/shaders/text/text.vert", "res/shaders/text/text.frag") == 0) {
			throw std::exception("Can't load shaders: res/shaders/text/text.vert, res/shaders/text/text.frag");
		}
	}
	void ShaderManager::finalization() {

	}

	ShaderManager::ShaderProgram::ShaderProgram()
	{
	}
	ShaderManager::ShaderProgram::~ShaderProgram()
	{
		glDeleteProgram(programID);
	}
	unsigned int ShaderManager::ShaderProgram::load(std::string vertexPath, std::string fragmentPath)
	{
		std::string vertexCode;
		std::string fragmentCode;
		try {

			std::ifstream vShaderFile;
			std::ifstream fShaderFile;
			vShaderFile.exceptions(std::ifstream::badbit);
			fShaderFile.exceptions(std::ifstream::badbit);
			vShaderFile.open(vertexPath);
			fShaderFile.open(fragmentPath);
			if (!vShaderFile.is_open()) {
				throw std::exception((std::string("Can't open shader file ") + std::string(vertexPath)).c_str());
			}
			if (!fShaderFile.is_open()) {
				throw std::exception((std::string("Can't open shader file ") + std::string(fragmentPath)).c_str());
			}
			std::stringstream vShaderStream, fShaderStream;

			vShaderStream << vShaderFile.rdbuf();
			fShaderStream << fShaderFile.rdbuf();

			vShaderFile.close();
			fShaderFile.close();

			vertexCode = vShaderStream.str();
			fragmentCode = fShaderStream.str();
		}
		catch (std::exception& e) {
			std::cerr << e.what() << std::endl;
			return 0;
		}
		const char* vShaderCode = vertexCode.c_str();
		const char* fShaderCode = fragmentCode.c_str();

		GLuint vertex, fragment;
		GLint success;
		char infoLog[512];

		vertex = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertex, 1, &vShaderCode, nullptr);
		glCompileShader(vertex);
		glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
		if (!success) {
			glGetShaderInfoLog(vertex, 512, nullptr, infoLog);
			std::cerr << "Can't compile vertex shader!!! Error: " << success << ":\n" << infoLog;
			glDeleteShader(vertex);
			return 0;
		}
		fragment = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragment, 1, &fShaderCode, nullptr);
		glCompileShader(fragment);
		glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
		if (!success) {
			glGetShaderInfoLog(fragment, 512, nullptr, infoLog);
			std::cerr << "Can't compile fragment shader!!! Error: " << success << ":\n" << infoLog;
			glDeleteShader(fragment);
			return 0;
		}

		programID = glCreateProgram();
		glAttachShader(programID, vertex);
		glAttachShader(programID, fragment);
		glLinkProgram(programID);
		glGetProgramiv(programID, GL_LINK_STATUS, &success);
		if (!success) {
			glGetProgramInfoLog(programID, 512, nullptr, infoLog);
			std::cerr << "Can't link shader!!! Error: " << success << ":\n" << infoLog;

			glDeleteShader(vertex);
			glDeleteShader(fragment);
			glDeleteProgram(programID);
			programID = 0;
			return 0;
		}

		glDeleteShader(vertex);
		glDeleteShader(fragment);
		return programID;
	}
	void ShaderManager::ShaderProgram::bind()
	{
		glUseProgram(programID);
	}
	void ShaderManager::ShaderProgram::unbind()
	{
		glUseProgram(0);
	}
	int ShaderManager::ShaderProgram::getUniformLocation(const char* name)
	{
		return glGetUniformLocation(programID, name);
	}

	void ShaderManager::ShaderProgram::uniform1i(const char* name, int x) {
		glUniform1i(glGetUniformLocation(programID, name), x);
	}
	void ShaderManager::ShaderProgram::uniform2i(const char* name, int x, int y) {
		glUniform2i(glGetUniformLocation(programID, name), x, y);
	}
	void ShaderManager::ShaderProgram::uniform3i(const char* name, int x, int y, int z) {
		glUniform3i(glGetUniformLocation(programID, name), x, y, z);
	}
	void ShaderManager::ShaderProgram::uniform4i(const char* name, int x, int y, int z, int w) {
		glUniform4i(glGetUniformLocation(programID, name), x, y, z, w);
	}
	void ShaderManager::ShaderProgram::uniform1f(const char* name, float x) {
		glUniform1f(glGetUniformLocation(programID, name), x);
	}
	void ShaderManager::ShaderProgram::uniform2f(const char* name, float x, float y) {
		glUniform2f(glGetUniformLocation(programID, name), x, y);
	}
	void ShaderManager::ShaderProgram::uniform3f(const char* name, float x, float y, float z) {
		glUniform3f(glGetUniformLocation(programID, name), x, y, z);
	}
	void ShaderManager::ShaderProgram::uniform4f(const char* name, float x, float y, float z, float w) {
		glUniform4f(glGetUniformLocation(programID, name), x, y, z, w);
	}
	void ShaderManager::ShaderProgram::uniform1ui(const char* name, unsigned int x) {
		glUniform1ui(glGetUniformLocation(programID, name), x);
	}
	void ShaderManager::ShaderProgram::uniform2ui(const char* name, unsigned int x, unsigned int y) {
		glUniform2ui(glGetUniformLocation(programID, name), x, y);
	}
	void ShaderManager::ShaderProgram::uniform3ui(const char* name, unsigned int x, unsigned int y, unsigned int z) {
		glUniform3ui(glGetUniformLocation(programID, name), x, y, z);
	}
	void ShaderManager::ShaderProgram::uniform4ui(const char* name, unsigned int x, unsigned int y, unsigned int z, unsigned int w) {
		glUniform4ui(glGetUniformLocation(programID, name), x, y, z, w);
	}
	void ShaderManager::ShaderProgram::uniform1iv(const char* name, glm::ivec1 vec)
	{
		glUniform1iv(glGetUniformLocation(programID, name), 1, glm::value_ptr(vec));
	}
	void ShaderManager::ShaderProgram::uniform2iv(const char* name, glm::ivec2 vec)
	{
		glUniform2iv(glGetUniformLocation(programID, name), 1, glm::value_ptr(vec));
	}
	void ShaderManager::ShaderProgram::uniform3iv(const char* name, glm::ivec3 vec)
	{
		glUniform3iv(glGetUniformLocation(programID, name), 1, glm::value_ptr(vec));
	}
	void ShaderManager::ShaderProgram::uniform4iv(const char* name, glm::ivec4 vec)
	{
		glUniform4iv(glGetUniformLocation(programID, name), 1, glm::value_ptr(vec));
	}
	void ShaderManager::ShaderProgram::uniform1fv(const char* name, glm::vec1 vec)
	{
		glUniform1fv(glGetUniformLocation(programID, name), 1, glm::value_ptr(vec));
	}
	void ShaderManager::ShaderProgram::uniform2fv(const char* name, glm::vec2 vec)
	{
		glUniform2fv(glGetUniformLocation(programID, name), 1, glm::value_ptr(vec));
	}
	void ShaderManager::ShaderProgram::uniform3fv(const char* name, glm::vec3 vec)
	{
		glUniform3fv(glGetUniformLocation(programID, name), 1, glm::value_ptr(vec));
	}
	void ShaderManager::ShaderProgram::uniform4fv(const char* name, glm::vec4 vec)
	{
		glUniform4fv(glGetUniformLocation(programID, name), 1, glm::value_ptr(vec));
	}
	void ShaderManager::ShaderProgram::uniform1uiv(const char* name, glm::uvec1 vec)
	{
		glUniform1uiv(glGetUniformLocation(programID, name), 1, glm::value_ptr(vec));
	}
	void ShaderManager::ShaderProgram::uniform2uiv(const char* name, glm::uvec2 vec)
	{
		glUniform2uiv(glGetUniformLocation(programID, name), 1, glm::value_ptr(vec));
	}
	void ShaderManager::ShaderProgram::uniform3uiv(const char* name, glm::uvec3 vec)
	{
		glUniform3uiv(glGetUniformLocation(programID, name), 1, glm::value_ptr(vec));
	}
	void ShaderManager::ShaderProgram::uniform4uiv(const char* name, glm::uvec4 vec)
	{
		glUniform4uiv(glGetUniformLocation(programID, name), 1, glm::value_ptr(vec));
	}


	void ShaderManager::ShaderProgram::uniformMat2f(const char* name, glm::mat2& mat) {
		glUniformMatrix2fv(glGetUniformLocation(programID, name), 1, GL_FALSE, glm::value_ptr(mat));
	}
	void ShaderManager::ShaderProgram::uniformMat3f(const char* name, glm::mat3& mat) {
		glUniformMatrix3fv(glGetUniformLocation(programID, name), 1, GL_FALSE, glm::value_ptr(mat));
	}
	void ShaderManager::ShaderProgram::uniformMat4f(const char* name, glm::mat4& mat) {
		glUniformMatrix4fv(glGetUniformLocation(programID, name), 1, GL_FALSE, glm::value_ptr(mat));
	}
}