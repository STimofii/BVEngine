#include "dev_text.h"
#include "static_text.h"

#include <string>
#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include "../../engine.h"
#include "../../hero.h"

namespace bulka {
	DevText::DevText()
	{
	}
	DevText::~DevText()
	{
	}

	void DevText::init() {
		delete left_top_text;
		delete left_bottom_text;
		delete right_top_text;
		delete right_bottom_text;

		left_top_text = new StaticText("", 16, glm::vec3(0, 0, 0), 255, 255, 255, 255, 1.0f, LEFT_TOP_CORNER);
		left_bottom_text = new StaticText("", 16, glm::vec3(0, 0, 0), 255, 255, 255, 255, 1.0f, LEFT_BOTTOM_CORNER);
		right_top_text = new StaticText("", 16, glm::vec3(0, 0, 0), 255, 255, 255, 255, 1.0f, RIGHT_TOP_CORNER);
		right_bottom_text = new StaticText("", 16, glm::vec3(0, 0, 0), 255, 255, 255, 255, 1.0f, RIGHT_BOTTOM_CORNER);
		
	}
	void DevText::update() {
		left_top_text->setText("BulkaLT");
		left_bottom_text->setText("BulkaLB");
		right_top_text->setText("cat");
		right_bottom_text->setText(BVENGINE_VERSION);
	}
	void DevText::render() {
		left_top_text->render();
		left_bottom_text->render();
		right_top_text->render();
		right_bottom_text->render();
	}
}