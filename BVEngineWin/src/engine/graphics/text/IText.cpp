#include "IText.h"

namespace bulka {
	IText::IText()
	{
	}
	IText::IText(std::string text, unsigned int size, glm::vec3 position, unsigned char r, unsigned char g, unsigned char b, unsigned char a, float scale, unsigned int alignment) : text(text), size(size), position(position), scale(scale), alignment(alignment)
	{
		setColor(r, g, b, a);
	}
	IText::~IText()
	{
	}

	std::string& IText::getText()
	{
		return text;
	}
	void IText::setText(std::string& text)
	{
		this->text = text;
	}
	int IText::getColor()
	{
		return color;
	}
	void IText::setColor(unsigned int)
	{
		this->color = color;
	}
	void IText::setColor(unsigned char r, unsigned char g, unsigned char b, unsigned char a)
	{
		color = (r << 24) | (g << 16) | (b << 8) | (a);
	}
	int IText::getSize()
	{
		return size;
	}
	void IText::setSize(unsigned int size)
	{
		this->size = size;
		singleSizeFont = TextManager::getSingleSize(size);
	}
	float IText::getScale()
	{
		return scale;
	}
	void IText::setScale(float scale)
	{
		this->scale = scale;
	}
	glm::vec3 IText::getPosition()
	{
		return position;
	}
	void IText::setPosition(glm::vec3 position)
	{
		this->position = position;
	}

	glm::mat4* IText::getProjection()
	{
		return projection;
	}

	void IText::setProjection(glm::mat4* projection)
	{
		this->projection = projection;
	}

}