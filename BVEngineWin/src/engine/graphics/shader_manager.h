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
			void uniform1iv(const char* name, glm::ivec1 vec);
			void uniform2iv(const char* name, glm::ivec2 vec);
			void uniform3iv(const char* name, glm::ivec3 vec);
			void uniform4iv(const char* name, glm::ivec4 vec);
			void uniform1fv(const char* name, glm::vec1 vec);
			void uniform2fv(const char* name, glm::vec2 vec);
			void uniform3fv(const char* name, glm::vec3 vec);
			void uniform4fv(const char* name, glm::vec4 vec);
			void uniform1uiv(const char* name, glm::uvec1 vec);
			void uniform2uiv(const char* name, glm::uvec2 vec);
			void uniform3uiv(const char* name, glm::uvec3 vec);
			void uniform4uiv(const char* name, glm::uvec4 vec);
			void uniformMat2f(const char* name, glm::mat2& mat);
			void uniformMat3f(const char* name, glm::mat3& mat);
			void uniformMat4f(const char* name, glm::mat4& mat);
		};


		static ShaderProgram mainShader;
		static ShaderProgram textShader;

		static void init();
		static void finalization();


	};
}