#include <ft2build.h>
#include FT_FREETYPE_H

#include "text.h"

#include <GL/glew.h>
#include "../engine.h"
#include "../hero.h"
#include "shader_manager.h"


namespace bulka {
	Text::Text()
	{
	}
	Text::Text(std::string text, unsigned int size, unsigned char r, unsigned char g, unsigned char b, unsigned char a) : text(text), size(size)
	{
		setColor(r, g, b, a);
	}

	Text::~Text()
	{
	}
	void Text::init()
	{
		singleSizeFont = TextRenderer::getSingleSize(size);
		projection = Engine::getHero().getCamera().getProjViewMatrix();
	}
	void Text::render()
	{
		ShaderManager::textShader.bind();
		//ShaderManager::textShader.uniformMat4f("projection", projection);
		ShaderManager::textShader.uniform4fv("textColor", glm::vec4(
			static_cast<float>((color >> 24) & 0xFF) / 256,
			static_cast<float>((color >> 16) & 0xFF) / 256,
			static_cast<float>((color >> 8) & 0xFF) / 256,
			static_cast<float>((color) & 0xFF) / 256
		));
		glActiveTexture(GL_TEXTURE0);

		std::string::const_iterator c;
		glm::vec2 pos(50, 50);


		for (c = text.begin(); c != text.end(); ++c)
		{
			TextRenderer::SingleSize::Character& character = singleSizeFont->getCharacter(*c);
			glBindVertexArray(character.VAO);
			ShaderManager::textShader.uniform2fv("position", pos);
			glBindTexture(GL_TEXTURE_2D, character.texture);
			glDrawArrays(GL_TRIANGLES, 0, 6);
			
			pos.x += character.size.x;
		}
		glBindTexture(GL_TEXTURE_2D, 0);
		glBindVertexArray(0);
		ShaderManager::textShader.unbind();
	}
	int Text::getColor()
	{
		return color;
	}
	void Text::setColor(unsigned int)
	{
		this->color = color;
	}
	void Text::setColor(unsigned char r, unsigned char g, unsigned char b, unsigned char a)
	{
		color = (r << 24) | (g << 16) | (b << 8) | (a);
	}
	int Text::getSize()
	{
		return size;
	}
	void Text::setSize(unsigned int size)
	{
		this->size = size;
		singleSizeFont = TextRenderer::getSingleSize(size);
	}
}