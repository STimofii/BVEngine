#pragma once

#include <string>
#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include "text_renderer.h"

namespace bulka {
	
	class Text {
	private:
		std::string text;
		unsigned int color = 0;
		unsigned int size = 16;
		float scale = 1.0f;
		TextRenderer::SingleSize* singleSizeFont;
		glm::mat4 projection;
	protected:
	public:
		Text();
		Text(std::string text, unsigned int size = 16, unsigned char r = 0, unsigned char g = 0, unsigned char b = 0, unsigned char a = 255, float scale = 1.0f);
		~Text();

		void render();
		void init();
		int getColor();
		void setColor(unsigned int color);
		void setColor(unsigned char r = 0, unsigned char g = 0, unsigned char b = 0, unsigned char a = 0);
		int getSize();
		void setSize(unsigned int size);
		float getScale();
		void setScale(float scale);
	};
}
