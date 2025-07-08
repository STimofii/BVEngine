#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>
#include <fstream>
#include <sstream>
#include <exception>
#include <iostream>
namespace bulka {
	class ShaderManager {
	private:
	protected:
	public:
		class ShaderProgram {
		private:
			unsigned int programID = 0;
		protected:
		public:
			ShaderProgram();
			~ShaderProgram();
			unsigned int load(std::string vertexPath, std::string fragmentPath);
			void bind();
			void unbind();
			int getUniformLocation(const char* name);
		};


		static ShaderProgram mainShader;

		static void init();
		static void finalization();


	};
}