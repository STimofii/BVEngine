#pragma once

#include <unordered_map>
#include <glm/glm.hpp>
#include <glm/ext.hpp>

namespace bulka {
	class TextManager {
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

			std::unordered_map<unsigned int, Character>* getCharacters();
			Character& getCharacter(unsigned int c);

		private:
			unsigned int size;
			std::unordered_map<unsigned int, Character> characters;
		};

		static void init();
		static void finalization();
		static SingleSize* getSingleSize(unsigned int size);
	private:
		static std::unordered_map<unsigned int, SingleSize*> sizes;
	};
}