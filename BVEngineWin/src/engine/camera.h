#pragma once

#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <cmath>
#include <bcppul/bcppul_math.h>
#include "window.h"
#include "graphics/shader_manager.h"


namespace bulka {
	class Camera {
	private:
	protected:
	public:
		glm::vec3 position;
		glm::vec3 rotation;
		glm::vec3 direction;
		float fov = 67 * (bcppul::PI / 180);
		glm::mat4 projectionMatrix = 1.0f;
		glm::mat4 orthoMatrix = 1.0f;
		glm::mat4 normalizedOrthoMatrix = 1.0f;
		glm::mat4 viewMatrix = 1.0f;
		glm::mat4 projViewMatrix = 1.0f;
		float speed = 30.0f;
		float sensitivity = 0.2f;

		Camera();
		Camera(glm::vec3 position);
		Camera(glm::vec3 position, glm::vec3 rotation);
		~Camera();
		void init();
		void postInit();
		void finalization();
		void inputUpdate();
		void setPosition(float x, float y, float z);
		void addPosition(float x, float y, float z);
		void moveInDirection(float x, float y, float z);
		void setRotation(float x, float y, float z);
		void addRotation(float x, float y, float z);
		void updateVectors();
		void updateDirection();
		void updateProjectionMatrix();
		void updateViewMatrix();
		void updateProjViewMatrix();
		void updateOrthoMatrix();
	};
}