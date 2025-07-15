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
			float textureWidth = ONE_BLOCK_TEXTURE_PART_X;
			float textureHeight = ONE_BLOCK_TEXTURE_PART_Y;
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
			virtual ~Face();

			void recalcVertices();
		};
		Block(unsigned short id, std::string name, bool hasAlpha = false,
			Face back = Face(
							Face::defaultVerticesBack, Face::defaultVerticesBottomLength, 
							Face::defaultIndicesBack, Face::defaultIndicesBackLength,
							0.0f, 0.0f,
							1.0f, 1.0f, 
							glm::vec3{0, 0, -1}
			),
			Face front = Face(
							Face::defaultVerticesFront, Face::defaultVerticesFrontLength,
							Face::defaultIndicesFront, Face::defaultIndicesFrontLength,
							0.0f, 0.0f,
							1.0f, 1.0f,
							glm::vec3{0, 0, 1}
			), 
			Face left = Face(
							Face::defaultVerticesLeft, Face::defaultVerticesLeftLength,
							Face::defaultIndicesLeft, Face::defaultIndicesLeftLength,
							0.0f, 0.0f,
							1.0f, 1.0f,
							glm::vec3{-1, 0, 0}
			), 
			Face right = Face(
							Face::defaultVerticesRight, Face::defaultVerticesRightLength,
							Face::defaultIndicesRight, Face::defaultIndicesRightLength,
							0.0f, 0.0f,
							1.0f, 1.0f,
							glm::vec3{1, 0, 0}
			),
			Face bottom = Face(
							Face::defaultVerticesBottom, Face::defaultVerticesBottomLength,
							Face::defaultIndicesBottom, Face::defaultIndicesBottomLength,
							0.0f, 0.0f,
							1.0f, 1.0f,
							glm::vec3{0, -1, 0}
			), 
			Face top = Face(
							Face::defaultVerticesTop, Face::defaultVerticesTopLength,
							Face::defaultIndicesTop, Face::defaultIndicesTopLength,
							0.0f, 0.0f,
							1.0f, 1.0f,
							glm::vec3{ 0, 1, 0 }
			));
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

