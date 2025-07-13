#include "dev_text.h"
#include "static_text.h"

#include <string>
#include <sstream>
#include <iomanip>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "../../engine.h"
#include "../../window.h"
#include "../../hero.h"

#include <bcppul/logging.h>

namespace bulka {
	bcppul::Logger* DevText::logger = bcppul::getLogger("DevText");
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
		left_top_text->init();
		right_top_text = new StaticText("", 16, glm::vec3(0, 0, 0), 255, 255, 255, 255, 1.0f, RIGHT_TOP_CORNER);
		right_top_text->init();
		left_bottom_text = new StaticText("", 16, glm::vec3(0, 0, 0), 255, 255, 255, 255, 1.0f, LEFT_BOTTOM_CORNER);
		left_bottom_text->init();
		right_bottom_text = new StaticText("", 16, glm::vec3(0, 0, 0), 255, 255, 255, 255, 1.0f, RIGHT_BOTTOM_CORNER);
		right_bottom_text->init();
		
	}
	void DevText::update() {
		if (visible) {
			std::stringstream ss;
			ss << std::fixed << std::setprecision(3);
			ss << "FPS: " << Engine::getFPS() << "\n";
			glm::vec3 position = Engine::getHero().getCamera().getPosition();
			glm::vec3 rotation = Engine::getHero().getCamera().getRotation();
			ss << "Position XYZ: " << position.x << "; " << position.y << "; " << position.z << "; " << "\n";
			ss << "Rotation XYZ: " << rotation.x << "; " << rotation.y << "; " << rotation.z << "; " << "\n";
			left_top_text->setText(ss.str());

			ss.str("");
			ss.clear();

			ss << "cat" << "\n";
			right_top_text->setText(ss.str());

			ss.str("");
			ss.clear();

			left_bottom_text->setText(ss.str());

			ss.str("");
			ss.clear();

			ss << BVENGINE_VERSION;
			right_bottom_text->setText(ss.str());
		}
	}
	void DevText::render() {
		if(visible){
			left_top_text->render();
			left_bottom_text->render();
			right_top_text->render();
			right_bottom_text->render();
		}
	}
	bool DevText::isVisible()
	{
		return visible;
	}
	void DevText::setVisible(bool val)
	{
		visible = val;
	}
	void DevText::toggleVisible()
	{
		visible = !visible;
	}
}