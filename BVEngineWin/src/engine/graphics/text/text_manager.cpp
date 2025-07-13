#include <ft2build.h>
#include FT_FREETYPE_H

#include "text_manager.h"


#include "../../settings.h"
#include "../../engine.h"
#include <exception>
#include <cmath>


namespace bulka {
	bcppul::Logger* TextManager::logger = bcppul::getLogger("TextManager");
	std::unordered_map<unsigned int, TextManager::SingleSize*> TextManager::sizes;


	TextManager::SingleSize::SingleSize()
	{

	}

	TextManager::SingleSize::SingleSize(unsigned int size) : size(size)
	{
		//for (unsigned int c = 0; c < 128; c++)
		//{
		//	loadChar(c);
		//}
	}

	TextManager::SingleSize::~SingleSize()
	{
		glDeleteTextures(1, &texture);
		texture = 0;
	}
	void TextManager::SingleSize::loadChar(unsigned int c)
	{
		FT_Set_Pixel_Sizes(Engine::getMainFont(), 0, size);
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
		FT_Face& face = Engine::getMainFont();
		if (FT_Load_Char(face, c, FT_LOAD_RENDER))
		{
			*logger << bcppul::ERROR << "ERROR::FREETYPE: Failed to load Glyph " << c;
			return;
		}
		line_height = face->size->metrics.height >> 6;
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
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, TEXTURE_INTERPOLATION);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, TEXTURE_INTERPOLATION);
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
			advance, (width > 0) && (height > 0)
		);
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	void TextManager::SingleSize::createTexture()
	{
		*logger << bcppul::TRACE << ("Loading font texture for size ") << size;
		FT_Set_Pixel_Sizes(Engine::getMainFont(), 0, size);
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
		FT_Face& face = Engine::getMainFont();
		max_glyph_width = 0;
		for (unsigned int c = 32; c < 128; ++c) {
			unsigned int glyphWidth = getCharacter(c).size.x;
			if (glyphWidth > max_glyph_width) {
				max_glyph_width = glyphWidth;
			}
		}
		line_height = face->size->metrics.height >> 6;
		line_height_loged = std::pow(2, std::ceil(std::log2(line_height)));
		max_glyph_width_loged = std::pow(2, std::ceil(std::log2(max_glyph_width)));
		//std::cout << "width: " << max_glyph_width_loged << "; height: " << line_height_loged << std::endl;
		unsigned int glyphSize = line_height_loged * max_glyph_width_loged;
		unsigned int width = 16 * max_glyph_width_loged;
		unsigned int height = 8 * line_height_loged;
		unsigned char* bitmap = new unsigned char[width * height] {};
		onePixelPartOfTextureX = 1.0f / width;
		onePixelPartOfTextureY = 1.0f / height;
		try {
			for (unsigned int yc = 2; yc < 8; ++yc) {
				for (unsigned int xc = 0; xc < 16; ++xc) {
					unsigned char c = (yc * 16 + xc);
					unsigned int beginY = yc * line_height_loged;
					unsigned int beginX = xc * max_glyph_width_loged;
					if (FT_Load_Char(face, c, FT_LOAD_RENDER))
					{
						*logger << bcppul::ERROR << "ERROR::FREETYPE: Failed to load Glyph " << c;
						return;
					}
					for (unsigned int y = 0; y < face->glyph->bitmap.rows; ++y)
					{
						for (unsigned int x = 0; x < face->glyph->bitmap.width; ++x)
						{
							bitmap[(beginY + y) * width + (beginX + x)] = face->glyph->bitmap.buffer[y * face->glyph->bitmap.width + x];
						}
					}
				}
			}
		}
		catch (std::exception e) {
			*logger << bcppul::ERROR << "Error in creating font texture: " << e.what();
		}

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
			bitmap
		);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, TEXTURE_INTERPOLATION);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, TEXTURE_INTERPOLATION);
		glBindTexture(GL_TEXTURE_2D, 0);

		delete[] bitmap;
		*logger << bcppul::TRACE << ("Loaded font texture for size ") << size;
	}
	std::unordered_map<unsigned int, TextManager::SingleSize::Character>* TextManager::SingleSize::getCharacters()
	{
		return &characters;
	}
	TextManager::SingleSize::Character& TextManager::SingleSize::getCharacter(unsigned int c)
	{
		auto pointer = characters.find(c);
		if (pointer == characters.end()) {
			loadChar(c);
			return characters[c];
		}
		return characters[c];
	}
	unsigned int TextManager::SingleSize::getLineHeight()
	{
		return line_height;
	}
	unsigned int TextManager::SingleSize::getLineHeightLoged()
	{
		return line_height_loged;
	}
	unsigned int TextManager::SingleSize::getMaxGlyphWidth()
	{
		return max_glyph_width;
	}
	unsigned int TextManager::SingleSize::getMaxGlyphWidthLoged()
	{
		return max_glyph_width_loged;
	}
	unsigned int TextManager::SingleSize::getTexture()
	{
		if (texture == 0) {
			createTexture();
		}
		return texture;
	}
	float TextManager::SingleSize::getOnePixelPartOfTextureX()
	{
		return onePixelPartOfTextureX;
	}
	float TextManager::SingleSize::getOnePixelPartOfTextureY()
	{
		return onePixelPartOfTextureY;
	}
	TextManager::SingleSize::Character::Character(
		unsigned int texture, unsigned int VAO, unsigned int VBO, 
		glm::ivec2 size, glm::ivec2 bearing, 
		unsigned int advance, bool visible
	) :
		texture(texture), VAO(VAO), VBO(VBO), size(size), bearing(bearing), advance(advance), visible(visible)
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