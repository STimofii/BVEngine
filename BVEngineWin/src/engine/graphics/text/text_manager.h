#pragma once

#include <unordered_map>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <bcppul/logging.h>

#define TEXTURE_INTERPOLATION GL_NEAREST

namespace bulka {
	class TextManager {
	private:
		static bcppul::Logger* logger;
	protected:
	public:
		class SingleSize
		{
		protected:
		public:
			struct Character {
				unsigned int texture;
				unsigned int VAO;
				unsigned int VBO;
				glm::ivec2 size;
				glm::ivec2 bearing;
				unsigned int advance;
				bool visible;
				Character(
					unsigned int texture = 0, unsigned int VAO = 0, unsigned int VBO = 0, 
					glm::ivec2 size = glm::vec2(), glm::ivec2 bearing = glm::vec2(), 
					unsigned int advance = 0, bool visible = false);
				~Character();
				void bind();
				void unbind();
			};

			SingleSize();
			SingleSize(unsigned int size);
			~SingleSize();

			void loadChar(unsigned int c);
			void createTexture();

			std::unordered_map<unsigned int, Character>* getCharacters();
			Character& getCharacter(unsigned int c);
			unsigned int getLineHeight();
			unsigned int getLineHeightLoged();
			unsigned int getMaxGlyphWidth();
			unsigned int getMaxGlyphWidthLoged();
			unsigned int getTexture();
			float getOnePixelPartOfTextureX();
			float getOnePixelPartOfTextureY();

		private:
			unsigned int texture = 0;
			unsigned int size = 0;
			unsigned int line_height = 0;
			unsigned int line_height_loged = 0;
			unsigned int max_glyph_width = 0;
			unsigned int max_glyph_width_loged = 0;
			float onePixelPartOfTextureX = 0;
			float onePixelPartOfTextureY = 0;
			std::unordered_map<unsigned int, Character> characters;
		};

		static void init();
		static void finalization();
		static SingleSize* getSingleSize(unsigned int size);
	private:
		static std::unordered_map<unsigned int, SingleSize*> sizes;
	};
}