#include <ft2build.h>
#include FT_FREETYPE_H

#include "dynamic_text.h"

#include <GL/glew.h>
#include "../../engine.h"
#include "../../hero.h"
#include "../shader_manager.h"
#include "IText.h"


namespace bulka {
	DynamicText::DynamicText()
	{
	}
	DynamicText::DynamicText(
		std::string text, unsigned int size, glm::vec3 position, unsigned char r, unsigned char g, unsigned char b, unsigned char a, float scale) 
		: text(text), size(size), position(position), scale(scale)
	{
		setColor(r, g, b, a);
	}

	DynamicText::~DynamicText()
	{
	}
	void DynamicText::init()
	{
		singleSizeFont = TextManager::getSingleSize(size);
		projection = Engine::getHero().getCamera().getProjViewMatrix();
	}
	void DynamicText::render()
	{
		ShaderManager::textShader.bind();
		//ShaderManager::textShader.uniformMat4f("projection", projection);
		ShaderManager::textShader.uniform1f("scale", scale);
		ShaderManager::textShader.uniform4fv("textColor", glm::vec4(
			static_cast<float>((color >> 24) & 0xFF) / 256,
			static_cast<float>((color >> 16) & 0xFF) / 256,
			static_cast<float>((color >> 8) & 0xFF) / 256,
			static_cast<float>((color) & 0xFF) / 256
		));
		glActiveTexture(GL_TEXTURE0);

		std::string::const_iterator c;

		glm::vec3 temp_position = position;
		for (c = text.begin(); c != text.end(); ++c)
		{
			TextManager::SingleSize::Character& character = singleSizeFont->getCharacter(*c);
			glBindVertexArray(character.VAO);
			ShaderManager::textShader.uniform3fv("position", temp_position);
			glBindTexture(GL_TEXTURE_2D, character.texture);
			glDrawArrays(GL_TRIANGLES, 0, 6);
			
			temp_position.x += character.size.x + 2;
		}
		glBindTexture(GL_TEXTURE_2D, 0);
		glBindVertexArray(0);
		ShaderManager::textShader.unbind();
	}
	std::string& DynamicText::getText()
	{
		return text;
	}
	void DynamicText::setText(std::string& text)
	{
		this->text = text;
	}
	int DynamicText::getColor()
	{
		return color;
	}
	void DynamicText::setColor(unsigned int)
	{
		this->color = color;
	}
	void DynamicText::setColor(unsigned char r, unsigned char g, unsigned char b, unsigned char a)
	{
		color = (r << 24) | (g << 16) | (b << 8) | (a);
	}
	int DynamicText::getSize()
	{
		return size;
	}
	void DynamicText::setSize(unsigned int size)
	{
		this->size = size;
		singleSizeFont = TextManager::getSingleSize(size);
	}
	float DynamicText::getScale()
	{
		return scale;
	}
	void DynamicText::setScale(float scale)
	{
		this->scale = scale;
	}
	glm::vec3 DynamicText::getPosition()
	{
		return position;
	}
	void DynamicText::setPosition(glm::vec3 position)
	{
		this->position = position;
	}
}