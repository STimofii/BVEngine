#include <ft2build.h>
#include FT_FREETYPE_H

#include "text_manager.h"


#include "../../settings.h"
#include "../../engine.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>


namespace bulka {
	std::unordered_map<unsigned int, TextManager::SingleSize*> TextManager::sizes;


	TextManager::SingleSize::SingleSize()
	{

	}

	TextManager::SingleSize::SingleSize(unsigned int size)
	{
		characters = new Character[255];
		FT_Set_Pixel_Sizes(Engine::getMainFont(), 0, size);
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
		FT_Face& face = Engine::getMainFont();
		for (unsigned int c = 0; c < 255; c++)
		{
			if (FT_Load_Char(face, c, FT_LOAD_RENDER))
			{
				std::cerr << "ERROR::FREETYPE: Failed to load Glyph " << c << std::endl;
				continue;
			}
			float width = face->glyph->bitmap.width;
			float height = face->glyph->bitmap.rows;
			float left = face->glyph->bitmap_left;
			float top = face->glyph->bitmap_top;
			unsigned int advance = face->glyph->advance.x;

			unsigned int texture;
			glGenTextures(1, &texture);
			glBindTexture(GL_TEXTURE_2D, texture);
			glTexImage2D(
				GL_TEXTURE_2D,
				0,
				GL_RED,
				width,
				height,
				0,
				GL_RED,
				GL_UNSIGNED_BYTE,
				face->glyph->bitmap.buffer
			);
			

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			float vertices[] = {
					0.0f, height, 0.0f, 0.0f,
					0.0f, 0.0f, 0.0f, 1.0f,
					width, 0.0f, 1.0f, 1.0f,

					0.0f, height, 0.0f, 0.0f,
					width, 0.0f, 1.0f, 1.0f,
					width, height, 1.0f, 0.0f
			};
			unsigned int VAO, VBO;
			glGenVertexArrays(1, &VAO);
			glBindVertexArray(VAO);
			glGenBuffers(1, &VBO);
			glBindBuffer(GL_ARRAY_BUFFER, VBO);
			glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float) * 4, vertices, GL_STATIC_DRAW);
			glEnableVertexAttribArray(0);
			glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (GLvoid*)(0 * sizeof(float)));
			glBindBuffer(GL_ARRAY_BUFFER, 0);
			glBindVertexArray(0);

			new(&characters[c]) Character(
				texture, VAO, VBO,
				glm::ivec2(width, height),
				glm::ivec2(left, top),
				advance
			);
		}
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	TextManager::SingleSize::~SingleSize()
	{
		delete[] characters;
	}
	TextManager::SingleSize::Character* TextManager::SingleSize::getCharacters()
	{
		return characters;
	}
	TextManager::SingleSize::Character& TextManager::SingleSize::getCharacter(unsigned char c)
	{
		return characters[c];
	}
	TextManager::SingleSize::Character::Character(unsigned int texture, unsigned int VAO, unsigned int VBO, glm::ivec2 size, glm::ivec2 bearing, unsigned int advance) :
		texture(texture), VAO(VAO), VBO(VBO), size(size), bearing(bearing), advance(advance)
	{
	}
	TextManager::SingleSize::Character::~Character()
	{
		glDeleteTextures(1, &texture);
		glDeleteBuffers(1, &VBO);
		glDeleteVertexArrays(1, &VAO);
	}
	void TextManager::SingleSize::Character::bind() {
		glBindTexture(GL_TEXTURE_2D, texture);
	}
	void TextManager::SingleSize::Character::unbind() {
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	void TextManager::init() {
		getSingleSize(16);
	}
	void TextManager::finalization() {
		for (auto& pair : sizes)
		{
			delete pair.second;
		}
	}
	TextManager::SingleSize* TextManager::getSingleSize(unsigned int size)
	{
		auto it = sizes.find(size);
		if (it == sizes.end()) {
			SingleSize* newSingleSize = new SingleSize(size);
			sizes[size] = newSingleSize;
			return newSingleSize;
		}
		else {
			return it->second;
		}
	}
}