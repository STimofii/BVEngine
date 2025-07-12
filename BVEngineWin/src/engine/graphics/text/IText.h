#pragma once

#include <string>
#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include "../../engine.h"
#include "../../hero.h"
#include "text_manager.h"


namespace bulka {
#define DRAW_LINES_DOWN 0b00000000'00000000'00000000'00000000
#define DRAW_LINES_UP 0b00000000'00000000'00000000'00000001
#define DRAW_LINE_LEFT_SIDE 0b00000000'00000000'00000000'00000000
#define DRAW_LINE_RIGHT_SIDE 0b00000000'00000000'00000000'00000010

#define BOTTOM_EDGE 0b00000000'00000000'00000000'00000000
#define TOP_EDGE 0b00000000'00000000'00000001'00000000
#define LEFT_EDGE 0b00000000'00000000'00000000'00000000
#define RIGHT_EDGE 0b00000000'00000000'00000010'00000000

#define LEFT_BOTTOM_CORNER (DRAW_LINES_UP | DRAW_LINE_LEFT_SIDE | LEFT_EDGE | BOTTOM_EDGE)
#define LEFT_TOP_CORNER (DRAW_LINES_DOWN | DRAW_LINE_LEFT_SIDE | LEFT_EDGE | TOP_EDGE)
#define RIGHT_BOTTOM_CORNER (DRAW_LINES_UP | DRAW_LINE_RIGHT_SIDE | RIGHT_EDGE | BOTTOM_EDGE)
#define RIGHT_TOP_CORNER (DRAW_LINES_DOWN | DRAW_LINE_RIGHT_SIDE | RIGHT_EDGE | TOP_EDGE)
	class IText{
	private:
	protected:
		std::string text;
		std::wstring wtext;
		unsigned int color = 0xFF;
		unsigned int size = 16;
		float scale = 1.0f;
		unsigned int alignment = DRAW_LINE_LEFT_SIDE | DRAW_LINES_UP;
		TextManager::SingleSize* singleSizeFont;
		glm::mat4* projection = &Engine::getHero().getCamera().getOrthoMatrix();
		glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f);
	public:
		IText();
		IText(std::string text, unsigned int size = 16, glm::vec3 position = glm::vec3(),
			unsigned char r = 0, unsigned char g = 0, unsigned char b = 0, unsigned char a = 255, 
			float scale = 1.0f, unsigned int alignment = LEFT_TOP_CORNER);
		IText(std::wstring wtext, unsigned int size = 16, glm::vec3 position = glm::vec3(),
			unsigned char r = 0, unsigned char g = 0, unsigned char b = 0, unsigned char a = 255, 
			float scale = 1.0f, unsigned int alignment = LEFT_TOP_CORNER);
		~IText();
		
		virtual void render() = 0;
		virtual void init();

		virtual std::string getText();
		virtual void setText(std::string text);
		virtual std::wstring getTextW();
		virtual void setTextW(std::wstring text);
		virtual int getColor();
		virtual void setColor(unsigned int color);
		virtual void setColor(unsigned char r = 0, unsigned char g = 0, unsigned char b = 0, unsigned char a = 0);
		virtual int getSize();
		virtual void setSize(unsigned int size);
		virtual float getScale();
		virtual void setScale(float scale);
		virtual glm::vec3 getPosition();
		virtual void setPosition(glm::vec3 scale);
		virtual glm::mat4* getProjection();
		virtual void setProjection(glm::mat4* projection);
	};


}