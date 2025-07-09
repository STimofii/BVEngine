#pragma once


#include <string>
#include <glm/glm.hpp>
#include <glm/ext.hpp>

namespace bulka {
	class ShaderManager {
	private:
	protected:
	public:
		class ShaderProgram {
		private:
		protected:
		public:
			unsigned int programID = 0;
			ShaderProgram();
			~ShaderProgram();
			unsigned int load(std::string vertexPath, std::string fragmentPath);
			void bind();
			void unbind();
			int getUniformLocation(const char* name);
			void uniform1i(const char* name, int x);
			void uniform2i(const char* name, int x, int y);
			void uniform3i(const char* name, int x, int y, int z);
			void uniform4i(const char* name, int x, int y, int z, int w);
			void uniform1f(const char* name, float x);
			void uniform2f(const char* name, float x, float y);
			void uniform3f(const char* name, float x, float y, float z);
			void uniform4f(const char* name, float x, float y, float z, float w);
			void uniform1ui(const char* name, unsigned int x);
			void uniform2ui(const char* name, unsigned int x, unsigned int y);
			void uniform3ui(const char* name, unsigned int x, unsigned int y, unsigned int z);
			void uniform4ui(const char* name, unsigned int x, unsigned int y, unsigned int z, unsigned int w);
			void uniformMat2f(const char* name, glm::mat2& mat);
			void uniformMat3f(const char* name, glm::mat3& mat);
			void uniformMat4f(const char* name, glm::mat4& mat);
		};


		static ShaderProgram mainShader;

		static void init();
		static void finalization();


	};
}