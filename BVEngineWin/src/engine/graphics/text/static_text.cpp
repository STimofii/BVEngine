#include <ft2build.h>
#include FT_FREETYPE_H

#include "static_text.h"

#include <GL/glew.h>
#include "../../engine.h"
#include "../../hero.h"
#include "../shader_manager.h"

#include <codecvt> 


namespace bulka {
	StaticText::StaticText()
	{
	}
	StaticText::StaticText(
		std::string text, unsigned int size, glm::vec3 position, unsigned char r, unsigned char g, unsigned char b, unsigned char a, float scale, unsigned int alignment) 
		: IText(text, size, position, r, g, b, a, scale, alignment)
	{
	}
	StaticText::StaticText(
		std::wstring wtext, unsigned int size, glm::vec3 position, unsigned char r, unsigned char g, unsigned char b, unsigned char a, float scale, unsigned int alignment) 
		: IText(wtext, size, position, r, g, b, a, scale, alignment)
	{
		setTextW(wtext);
	}

	StaticText::~StaticText()
	{
	}
	void StaticText::init()
	{
		singleSizeFont = TextManager::getSingleSize(size);
	}
	void StaticText::render()
	{
	}
	std::string StaticText::getText()
	{
		return text;
	}
	void StaticText::setText(std::string text)
	{
		this->text = text;
	}
	std::wstring StaticText::getTextW()
	{
		std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
		return converter.from_bytes(text);
	}
	void StaticText::setTextW(std::wstring text)
	{
		std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
		this->text = converter.to_bytes(text);
	}
}