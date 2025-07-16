#pragma once

#include <vector>
#include <string>
#include <glm/glm.hpp>
#include <glm/ext.hpp>

#define TEXTURE_WIDTH 1024.0f
#define TEXTURE_HEIGHT 1024.0f
#define BLOCK_TEXTURE_WIDTH 16.0f
#define BLOCK_TEXTURE_HEIGHT 16.0f
#define ONE_BLOCK_TEXTURE_PART_X (BLOCK_TEXTURE_WIDTH / TEXTURE_WIDTH)
#define ONE_BLOCK_TEXTURE_PART_Y (BLOCK_TEXTURE_HEIGHT / TEXTURE_HEIGHT)

namespace bulka {
	class Block{
	private:
	protected:
	public:
		class Face {
		private:
		protected:
		public:
			static float defaultVerticesBack[];
			static unsigned int defaultVerticesBackLength;
			static unsigned int defaultIndicesBack[];
			static unsigned int defaultIndicesBackLength;
			static float defaultVerticesFront[];
			static unsigned int defaultVerticesFrontLength;
			static unsigned int defaultIndicesFront[];
			static unsigned int defaultIndicesFrontLength;
			static float defaultVerticesLeft[];
			static unsigned int defaultVerticesLeftLength;
			static unsigned int defaultIndicesLeft[];
			static unsigned int defaultIndicesLeftLength;
			static float defaultVerticesRight[];
			static unsigned int defaultVerticesRightLength;
			static unsigned int defaultIndicesRight[];
			static unsigned int defaultIndicesRightLength;
			static float defaultVerticesBottom[];
			static unsigned int defaultVerticesBottomLength;
			static unsigned int defaultIndicesBottom[];
			static unsigned int defaultIndicesBottomLength;
			static float defaultVerticesTop[];
			static unsigned int defaultVerticesTopLength;
			static unsigned int defaultIndicesTop[];
			static unsigned int defaultIndicesTopLength;



			float* vertices = nullptr;
			unsigned int vertices_length = 0;
			unsigned int* indices = nullptr;
			unsigned int indices_length = 0;
			float textureX = 0;
			float textureY = 0;
			float textureWidth = 1;
			float textureHeight = 1;
			glm::vec3 normal;
			Face(float* vertices = nullptr,
				unsigned int vertices_length = 0,
				unsigned int* indices = nullptr,
				unsigned int indices_length = 0,
				float textureX = 0.0f,
				float textureY = 0.0f,
				float textureWidth = 1.0f,
				float textureHeight = 1.0f,
				glm::vec3 normal = glm::vec3()
			);
			Face(const Face& other);
			virtual ~Face();

			Face* setVertices(float* vertices, unsigned int vertices_length);
			Face* setIndices(unsigned int* indices, unsigned int indices_length);
			Face* setTextureX(float val);
			Face* setTextureY(float val);
			Face* setTextureWidth(float val);
			Face* setTextureHeight(float val);

			Face* recalcVertices();
		};
		
		static Face defaultFaceBack;
		static Face defaultFaceFront;
		static Face defaultFaceLeft;
		static Face defaultFaceRight;
		static Face defaultFaceBottom;
		static Face defaultFaceTop;
		Block(unsigned short id, std::string name, bool hasAlpha = false,
			Face back = defaultFaceBack, Face front = defaultFaceFront,
			Face left = defaultFaceLeft, Face right = defaultFaceRight,
			Face bottom = defaultFaceBottom, Face top = defaultFaceTop
			);
		virtual ~Block();

		unsigned short id;
		std::string name;
		bool hasAlpha = false;
		Face back;
		Face front;
		Face left;
		Face right;
		Face bottom;
		Face top;
	};

}

