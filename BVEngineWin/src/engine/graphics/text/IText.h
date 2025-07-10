#pragma once

#include <string>
#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include "../../engine.h"
#include "../../hero.h"
#include "text_manager.h"

namespace bulka {
	class IText{
	private:
	protected:
		std::string text = "";
		unsigned int color = 0;
		unsigned int size = 16;
		float scale = 1.0f;
		TextManager::SingleSize* singleSizeFont;
		glm::mat4* projection = &Engine::getHero().getCamera().getOrthoMatrix();
		glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f);
	public:
		IText();
		IText(std::string text, unsigned int size = 16, glm::vec3 position = glm::vec3(), unsigned char r = 0, unsigned char g = 0, unsigned char b = 0, unsigned char a = 255, float scale = 1.0f);
		~IText();
		
		virtual void render() = 0;

		virtual std::string& getText();
		virtual void setText(std::string& text);
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