#pragma once

#include <string>
#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include "IText.h"

namespace bulka {
	class DynamicText : public IText{
	private:
	protected:
	public:
		DynamicText();
		DynamicText(std::string text, unsigned int size = 16, glm::vec3 position = glm::vec3(), unsigned char r = 0, unsigned char g = 0, unsigned char b = 0, unsigned char a = 255, float scale = 1.0f);
		~DynamicText();

		virtual void init();
		virtual void render() override;
	};
}
