#pragma once
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <cmath>
#include "camera.h"


namespace bulka {
	//class Camera;
	class Hero {
	private:
		Camera camera;
		float speed = 30.0f;
		float sensitivity = 0.2f;
	protected:
	public:
		Hero();
		~Hero();
		void init();
		void postInit();
		void finalization();
		void inputUpdate();
		Camera& getCamera();
		void setPosition(float x, float y, float z);
		void addPosition(float x, float y, float z);
		void moveInDirection(float x, float y, float z);
		void setRotation(float x, float y, float z);
		void addRotation(float x, float y, float z);
		float getSpeed();
		float getSensitivity();
		void setSpeed(float speed);
		void setSensitivity(float sensitivity);
	};
}