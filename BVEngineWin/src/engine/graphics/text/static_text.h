#pragma once

#include <string>
#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include "IText.h"

namespace bulka {
	class StaticText : public IText{
	private:
		unsigned int VAO = 0;
		unsigned int VBO = 0;
		unsigned int lines = 0;
		bool changed = true;
	protected:
	public:
		static constexpr float ONE_GLYPH_TEXTURE_PART_X = 1.0f / 16.0f;
		static constexpr float ONE_GLYPH_TEXTURE_PART_Y = 1.0f / 8.0f;
		StaticText();
		StaticText(std::string text, unsigned int size = 16, glm::vec3 position = glm::vec3(), unsigned char r = 0, unsigned char g = 0, unsigned char b = 0, unsigned char a = 255, float scale = 1.0f, unsigned int alignment = LEFT_TOP_CORNER);
		StaticText(std::wstring wtext, unsigned int size = 16, glm::vec3 position = glm::vec3(), unsigned char r = 0, unsigned char g = 0, unsigned char b = 0, unsigned char a = 255, float scale = 1.0f, unsigned int alignment = LEFT_TOP_CORNER);
		~StaticText();

		virtual void init() override;
		virtual void render() override;
		virtual void createMesh();
		virtual void addCharToMesh(unsigned char c, float* vertices, unsigned int i, glm::vec2& char_position, unsigned int* lines_widths, unsigned int& line, unsigned int screenWidth, unsigned int lineSpace, unsigned int line_height, unsigned int max_glyph_width, float onePixelPartTextureX, float onePixelPartTextureY);
		virtual std::string getText() override;
		virtual void setText(std::string text) override;
		virtual std::wstring getTextW() override;
		virtual void setTextW(std::wstring text) override;
		virtual void setTextWithoutUpdating(std::string text);
		virtual void setTextWWithoutUpdating(std::wstring text);
		virtual unsigned int getVAO();
		virtual unsigned int getVBO();
		virtual bool getChanged();
		virtual void setChanged(bool val);

	};
}
