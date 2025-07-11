#pragma once

#include <string>
#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include "IText.h"

namespace bulka {
	class DynamicText : public IText{
	private:
	protected:
	public:
		DynamicText();
		DynamicText(std::string text, unsigned int size = 16, glm::vec3 position = glm::vec3(), unsigned char r = 0, unsigned char g = 0, unsigned char b = 0, unsigned char a = 255, float scale = 1.0f, unsigned int alignment = LEFT_TOP_CORNER);
		DynamicText(std::wstring wtext, unsigned int size = 16, glm::vec3 position = glm::vec3(), unsigned char r = 0, unsigned char g = 0, unsigned char b = 0, unsigned char a = 255, float scale = 1.0f, unsigned int alignment = LEFT_TOP_CORNER);
		~DynamicText();

		virtual void render() override;
		virtual unsigned int getLinesWidths(std::string::const_iterator c, std::string::const_iterator end, unsigned int lines, unsigned int* lines_widths);
		virtual unsigned int getLinesWidthsW(std::wstring::const_iterator c, std::wstring::const_iterator end, unsigned int lines, unsigned int* lines_widths);
		virtual void renderChar(unsigned int c, glm::vec2& char_position, unsigned int* lines_widths, unsigned int& line, unsigned int lineSpace, unsigned int screenWidth);
	};
}
