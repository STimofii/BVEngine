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
			inline void bind();
			inline void unbind();
		};


		static ShaderProgram testShader;

		static void init();
		static void finalization();


	};
}