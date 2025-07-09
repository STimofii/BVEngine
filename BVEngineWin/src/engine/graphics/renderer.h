#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>



namespace bulka {
	class Texture;
	class TexturedMesh;
	class Renderer {
	private:
	protected:
	public:
		static void init();
		static void finalization();
		static void render(TexturedMesh& mesh);
	};
}