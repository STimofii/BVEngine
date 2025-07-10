#pragma once

#include <unordered_map>
#include <glm/glm.hpp>
#include <glm/ext.hpp>

namespace bulka {
	class TextRenderer {
	protected:
	public:
		class SingleSize
		{
		protected:
		public:
			class Character {
			private:
			protected:
			public:
				unsigned int texture;
				unsigned int VAO;
				unsigned int VBO;
				glm::ivec2 size;
				glm::ivec2 bearing;
				unsigned int advance;
				Character(unsigned int texture = 0, unsigned int VAO = 0, unsigned int VBO = 0, glm::ivec2 size = glm::vec2(), glm::ivec2 bearing = glm::vec2(), unsigned int advance = 0);
				~Character();
				void bind();
				void unbind();
			};

			SingleSize();
			SingleSize(unsigned int size);
			~SingleSize();

			Character* getCharacters();
			Character& getCharacter(unsigned char c);

		private:
			Character* characters;
		};

		static void init();
		static void finalization();
		static SingleSize* getSingleSize(unsigned int size);
	private:
		static std::unordered_map<unsigned int, SingleSize*> sizes;
	};
}