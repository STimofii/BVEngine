#pragma once

#include <string>
#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include "IText.h"

namespace bulka {
	class StaticText : public IText{
	private:
	protected:
	public:
		StaticText();
		StaticText(std::string text, unsigned int size = 16, glm::vec3 position = glm::vec3(), unsigned char r = 0, unsigned char g = 0, unsigned char b = 0, unsigned char a = 255, float scale = 1.0f, unsigned int alignment = LEFT_TOP_CORNER);
		StaticText(std::wstring wtext, unsigned int size = 16, glm::vec3 position = glm::vec3(), unsigned char r = 0, unsigned char g = 0, unsigned char b = 0, unsigned char a = 255, float scale = 1.0f, unsigned int alignment = LEFT_TOP_CORNER);
		~StaticText();

		virtual void init() override;
		virtual void render() override;
		virtual std::string getText() override;
		virtual void setText(std::string text) override;
		virtual std::wstring getTextW() override;
		virtual void setTextW(std::wstring text) override;

	};
}
