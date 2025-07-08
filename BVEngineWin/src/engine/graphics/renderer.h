#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "mesh/textured_mesh.h"


namespace bulka {
	class Renderer {
	private:
	protected:
	public:
		static void init();
		static void finalization();
		static void render(TexturedMesh& mesh);
	};
}