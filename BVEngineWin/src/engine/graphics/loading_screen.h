#pragma once

#include <glm/glm.hpp>
#include <glm/ext.hpp>
namespace bulka {
	class LoadingScreen{
	private:
	protected:
		bool visible = false;
		unsigned int VAO;
		unsigned int VBO;
		glm::mat4 rotation = 1.0f;
	public:
		LoadingScreen(bool visible = false);
		~LoadingScreen();
		void init();
		void render();
		bool isVisible();
		void setVisible(bool val);
	};


}