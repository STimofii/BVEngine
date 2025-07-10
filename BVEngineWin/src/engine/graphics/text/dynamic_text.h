#pragma once

#include <string>
#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include "text_manager.h"

namespace bulka {
	
	class DynamicText {
	private:
		std::string text;
		unsigned int color = 0;
		unsigned int size = 16;
		float scale = 1.0f;
		TextManager::SingleSize* singleSizeFont;
		glm::mat4 projection = 1.0f;
		glm::vec3 position;
	protected:
	public:
		DynamicText();
		DynamicText(std::string text, unsigned int size = 16, glm::vec3 position = glm::vec3(), unsigned char r = 0, unsigned char g = 0, unsigned char b = 0, unsigned char a = 255, float scale = 1.0f);
		~DynamicText();

		void render();
		void init();
		std::string& getText();
		void setText(std::string& text);
		int getColor();
		void setColor(unsigned int color);
		void setColor(unsigned char r = 0, unsigned char g = 0, unsigned char b = 0, unsigned char a = 0);
		int getSize();
		void setSize(unsigned int size);
		float getScale();
		void setScale(float scale);
		glm::vec3 getPosition();
		void setPosition(glm::vec3 scale);
	};
}
