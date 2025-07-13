#include <ft2build.h>
#include FT_FREETYPE_H

#include "static_text.h"

#include <GL/glew.h>
#include "../../engine.h"
#include "../../hero.h"
#include "../shader_manager.h"

#include <codecvt> 
#include <cmath> 


namespace bulka {
	StaticText::StaticText()
	{
	}
	StaticText::StaticText(
		std::string text, unsigned int size, glm::vec3 position, unsigned char r, unsigned char g, unsigned char b, unsigned char a, float scale, unsigned int alignment) 
		: IText(std::string(""), size, position, r, g, b, a, scale, alignment)
	{
		setText(text);
	}
	StaticText::StaticText(
		std::wstring wtext, unsigned int size, glm::vec3 position, unsigned char r, unsigned char g, unsigned char b, unsigned char a, float scale, unsigned int alignment) 
		: IText(std::wstring(L""), size, position, r, g, b, a, scale, alignment)
	{
		setTextW(wtext);
	}

	StaticText::~StaticText()
	{
		if (VBO != 0) {
			glDeleteBuffers(1, &VBO);
			VBO = 0;
		}
		if (VAO != 0) {
			glDeleteVertexArrays(1, &VAO);
			VAO = 0;
		}
	}
	void StaticText::init()
	{
		singleSizeFont = TextManager::getSingleSize(size);
		changed = true;
		createMesh();
	}
	void StaticText::render()
	{
		if (text.empty()) {
			return;
		}
		ShaderManager::textShader.bind();
		ShaderManager::textShader.uniformMat4f("projection", *projection);
		ShaderManager::textShader.uniform1f("scale", scale);
		ShaderManager::textShader.uniform4fv("textColor", glm::vec4(
			static_cast<float>((color >> 24) & 0xFF) / 256,
			static_cast<float>((color >> 16) & 0xFF) / 256,
			static_cast<float>((color >> 8) & 0xFF) / 256,
			static_cast<float>((color) & 0xFF) / 256
		));
		//std::cout << "1: " << glGetError() << std::endl;
		//std::cout << "2: " << glGetError() << std::endl;
		glActiveTexture(GL_TEXTURE0);
		ShaderManager::textShader.uniform3fv("text_position", position);
		ShaderManager::textShader.uniform2f("char_position", 0, 0);
		//std::cout << VAO << std::endl;
		glBindVertexArray(VAO);
		glBindTexture(GL_TEXTURE_2D, singleSizeFont->getTexture());
		glDrawArrays(GL_TRIANGLES, 0, text.length() * 6);
		glBindTexture(GL_TEXTURE_2D, 0);
		glBindVertexArray(0);
		ShaderManager::textShader.unbind();

	}
	void StaticText::createMesh()
	{
		singleSizeFont = TextManager::getSingleSize(size);
		if (singleSizeFont->getTexture() == 0) {
			singleSizeFont->createTexture();
		}
		if (!changed) {
			return;
		}
		if(VBO != 0){
			glDeleteBuffers(1, &VBO);
		}
		if(VAO != 0){
			glDeleteVertexArrays(1, &VAO);
		}			
		unsigned int* lines_widths = 0;
		unsigned int maxLineWidth = 0;

		unsigned int line_height = singleSizeFont->getLineHeight();
		unsigned int max_glyph_width = singleSizeFont->getMaxGlyphWidth();
		unsigned int length = text.size();
		float onePixelPartTextureX = singleSizeFont->getOnePixelPartOfTextureX();
		float onePixelPartTextureY = singleSizeFont->getOnePixelPartOfTextureY();

		std::string::const_iterator cic;
		std::string::const_iterator ciend;

		glm::vec2 char_position = {0, 0};

		if (alignment & DRAW_LINE_RIGHT_SIDE) {
			lines_widths = new unsigned int[lines] {};
			maxLineWidth = 0;
			cic = text.begin();
			ciend = text.end();
			maxLineWidth = getLinesWidths(cic, ciend, lines, lines_widths);
		}

		unsigned int lineSpace = singleSizeFont->getLineHeight();
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


		float* vertices = new float[length * 4 * 6] {};
		unsigned char c = 0;
		unsigned int line = 0;
		for (unsigned int i = 0; i < length; i++)
		{
			addCharToMesh(text[i], vertices, i, char_position, lines_widths, line, screenWidth, line_height, line_height, max_glyph_width, onePixelPartTextureX, onePixelPartTextureY);
		}

		glGenVertexArrays(1, &VAO);
		glBindVertexArray(VAO);
		glGenBuffers(1, &VBO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float) * 4 * length, vertices, GL_STATIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (GLvoid*)(0 * sizeof(float)));
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
		delete[] lines_widths;
		delete[] vertices;

		changed = false;
	}
	void StaticText::addCharToMesh(
		unsigned char c, float* vertices, unsigned int i, glm::vec2& char_position, unsigned int* lines_widths, unsigned int& line, 
		unsigned int screenWidth, unsigned int lineSpace, unsigned int line_height, unsigned int max_glyph_width, float onePixelPartTextureX, float onePixelPartTextureY)
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
		float x = char_position.x + character.bearing.x;

		float glyph_width = character.size.x;
		float glyph_height = character.size.y;

		float y_bottom = char_position.y + character.bearing.y - glyph_height;
		float y_top = char_position.y + character.bearing.y;

		float u1 = static_cast<float>(c % 16) * ONE_GLYPH_TEXTURE_PART_X;
		float v1 = static_cast<float>(std::floor(c / 16.0f)) * ONE_GLYPH_TEXTURE_PART_Y;
		float u2 = u1 + glyph_width * onePixelPartTextureX;
		float v2 = v1 + (glyph_height) * onePixelPartTextureY;

		vertices[i * 24 + 0] = x;
		vertices[i * 24 + 1] = y_top;
		vertices[i * 24 + 2] = u1;
		vertices[i * 24 + 3] = v1;

		vertices[i * 24 + 4] = x;
		vertices[i * 24 + 5] = y_bottom;
		vertices[i * 24 + 6] = u1;
		vertices[i * 24 + 7] = v2;

		vertices[i * 24 + 8] = x + glyph_width;
		vertices[i * 24 + 9] = y_bottom;
		vertices[i * 24 + 10] = u2;
		vertices[i * 24 + 11] = v2;

		vertices[i * 24 + 12] = x;
		vertices[i * 24 + 13] = y_top;
		vertices[i * 24 + 14] = u1;
		vertices[i * 24 + 15] = v1;

		vertices[i * 24 + 16] = x + glyph_width;
		vertices[i * 24 + 17] = y_bottom;
		vertices[i * 24 + 18] = u2;
		vertices[i * 24 + 19] = v2;

		vertices[i * 24 + 20] = x + glyph_width;
		vertices[i * 24 + 21] = y_top;
		vertices[i * 24 + 22] = u2;
		vertices[i * 24 + 23] = v1;

		char_position.x += (static_cast<float>(character.advance >> 6));
	}
	std::string StaticText::getText()
	{
		return text;
	}
	void StaticText::setText(std::string text)
	{
		if (this->text.compare(text) == 0) {
			return;
		}
		this->text = text;
		changed = true;

		lines = text.empty() ? 0 : 1;
		char& c = text[0];
		for (unsigned int i = 0; ; ++i) {
			c = text[i];
			if (c == '\n') {
				++lines;
			}
			if (c == '\0') {
				break;
			}
			if (c < 32) {
				c = ' ';
			}
		}
		createMesh();
	}
	std::wstring StaticText::getTextW()
	{
		std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
		return converter.from_bytes(text);
	}
	void StaticText::setTextW(std::wstring text)
	{
		std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
		setText(converter.to_bytes(text));
	}

	void StaticText::setTextWithoutUpdating(std::string text)
	{
		if (this->text.compare(text) == 0) {
			return;
		}
		this->text = text;
		changed = true;
	}
	void StaticText::setTextWWithoutUpdating(std::wstring text)
	{
		std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
		setTextWithoutUpdating(converter.to_bytes(text));
	}
	unsigned int StaticText::getVAO()
	{
		return VAO;
	}
	unsigned int StaticText::getVBO()
	{
		return VBO;
	}
}