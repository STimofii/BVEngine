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
		std::string text, unsigned int size, glm::vec3 position, unsigned char r, unsigned char g, unsigned char b, unsigned char a, float scale) 
		: IText(text, size, position, r, g, b, a, scale)
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


		std::string::const_iterator c;
		ShaderManager::textShader.uniform3fv("text_position", position);

		glm::vec2 char_position = {0, 0};
		for (c = text.begin(); c != text.end(); ++c)
		{
			if (*c == '\n') {
				char_position.x = 0;
				char_position.y += size;
				continue;
			}
			TextManager::SingleSize::Character& character = singleSizeFont->getCharacter(*c);
			if (!character.visible) {
				continue;
			}
			glBindVertexArray(character.VAO);
			ShaderManager::textShader.uniform2fv("char_position", char_position);
			glBindTexture(GL_TEXTURE_2D, character.texture);
			glDrawArrays(GL_TRIANGLES, 0, 6);
			
			char_position.x += (character.advance>>6);
		}
		glBindTexture(GL_TEXTURE_2D, 0);
		glBindVertexArray(0);
		ShaderManager::textShader.unbind();
	}
}