#include "shader_manager.h"

namespace bulka {
	ShaderManager::ShaderProgram ShaderManager::mainShader;
	void ShaderManager::init() {
		if (mainShader.load("res/shaders/main.vert", "res/shaders/main.frag") == 0) {
			throw std::exception("Can't load shaders: res/shaders/main.frag, res/shaders/main.vert");
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
}