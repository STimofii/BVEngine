#include <ft2build.h>
#include FT_FREETYPE_H

#include "dynamic_text.h"

#include <GL/glew.h>
#include "../../engine.h"
#include "../../hero.h"
#include "../shader_manager.h"

namespace bulka {
	DynamicText::DynamicText()
	{
	}
	DynamicText::DynamicText(
		std::string text, unsigned int size, glm::vec3 position, unsigned char r, unsigned char g, unsigned char b, unsigned char a, float scale, unsigned int alignment) 
		: IText(text, size, position, r, g, b, a, scale, alignment)
	{
	}

	DynamicText::~DynamicText()
	{
	}
	void DynamicText::init()
	{
		singleSizeFont = TextManager::getSingleSize(size);
	}
	void DynamicText::render()
	{
		ShaderManager::textShader.bind();
		ShaderManager::textShader.uniformMat4f("projection", *projection);
		ShaderManager::textShader.uniform1f("scale", scale);
		ShaderManager::textShader.uniform4fv("textColor", glm::vec4(
			static_cast<float>((color >> 24) & 0xFF) / 256,
			static_cast<float>((color >> 16) & 0xFF) / 256,
			static_cast<float>((color >> 8) & 0xFF) / 256,
			static_cast<float>((color) & 0xFF) / 256
		));
		glActiveTexture(GL_TEXTURE0);

		ShaderManager::textShader.uniform3fv("text_position", position);

		glm::vec2 char_position = {0, 0};

		std::string::const_iterator c;
		std::string::const_iterator end;

		unsigned int lines;
		unsigned int* lines_widths = 0;
		unsigned int maxLineWidth = 0;

		if (alignment & DRAW_LINES_UP || alignment & DRAW_LINE_RIGHT_SIDE) {
			lines = std::count(text.begin(), text.end(), '\n') + 1;
		}

		if (alignment & DRAW_LINE_RIGHT_SIDE) {
			lines_widths = new unsigned int[lines] {};
			maxLineWidth = 0;
			c = text.begin();
			end = text.end();
			for (unsigned int i = 0; i < lines; i++) {
				for (; c != end; ++c)
				{
					if ((*c) == '\n') {
						++c;
						break;
					}
					TextManager::SingleSize::Character* character = &singleSizeFont->getCharacter(*c);
					lines_widths[i] += (character->advance >> 6);

				}
				unsigned int width = lines_widths[i];
				if (maxLineWidth < width) {
					maxLineWidth = width;
				}
			}
		}

		unsigned int lineSpace = size;
		unsigned int screenWidth = 0;


		if (alignment & TOP_EDGE) {
			char_position.y = ((1 / projection[0][1].y) * 2);
		}
		else {
			char_position.y = 0;
		}
		if (alignment & RIGHT_EDGE) {
			screenWidth = ((1 / projection[0][0].x) * 2);
			char_position.x = screenWidth;
		}
		else {
			char_position.x = 0;
		}
		if (alignment & DRAW_LINE_RIGHT_SIDE) {
			char_position.x -= static_cast<float>(lines_widths[0]);
		}
		else {

		}
		if (alignment & DRAW_LINES_UP) {
			char_position.y += lineSpace * (lines - 1);
		}
		else {
			char_position.y -= lineSpace;
		}

		c = text.begin();
		end = text.end();
		unsigned int line = 0;
		for (; c != end; ++c)
		{
			renderChar(*c, char_position, lines_widths, line, lineSpace, screenWidth);
		}
		delete[] lines_widths;
		glBindTexture(GL_TEXTURE_2D, 0);
		glBindVertexArray(0);
		ShaderManager::textShader.unbind();
	}
	void DynamicText::renderChar(unsigned int c, glm::vec2& char_position, unsigned int* lines_widths, unsigned int& line, unsigned int lineSpace, unsigned int screenWidth)
	{
		if (c == '\n') {
			if (alignment & DRAW_LINE_RIGHT_SIDE) {
				char_position.x = -static_cast<float>(lines_widths[++line]);
			}
			else {
				char_position.x = 0;
			}
			if (alignment & RIGHT_EDGE) {
				char_position.x = screenWidth + char_position.x;
			}
			char_position.y -= lineSpace;
			return;
		}
		TextManager::SingleSize::Character& character = singleSizeFont->getCharacter(c);

		glBindVertexArray(character.VAO);
		ShaderManager::textShader.uniform2f("char_position", char_position.x + character.bearing.x, char_position.y + character.bearing.y - character.size.y);
		glBindTexture(GL_TEXTURE_2D, character.texture);
		glDrawArrays(GL_TRIANGLES, 0, 6);
		char_position.x += (static_cast<float>(character.advance >> 6));
	}
}