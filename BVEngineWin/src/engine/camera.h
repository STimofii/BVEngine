#pragma once

#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <bcppul/bcppul_math.h>


namespace bulka {
	class Camera {
	private:
		float fov = bcppul::degreesToRadians(70);
	protected:
	public:
		glm::vec3 position;
		glm::vec3 rotation;
		glm::mat4 projectionMatrix = 1.0f;
		glm::mat4 orthoMatrix = 1.0f;
		glm::mat4 normalizedOrthoMatrix = 1.0f;
		glm::mat4 viewMatrix = 1.0f;
		glm::mat4 projViewMatrix = 1.0f;

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
		glm::vec3& getPosition();
		glm::vec3& getRotation();
		float getFOV();
		void setFOV(float fov);
		void updateVectors();
		void updateDirection();
		void updateProjectionMatrix();
		void updateViewMatrix();
		void updateProjViewMatrix();
		void updateOrthoMatrix();

		glm::mat4& getProjectionMatrix();
		glm::mat4& getViewMatrix();
		glm::mat4& getProjViewMatrix();
		glm::mat4& getOrthoMatrix();
		glm::mat4& getNormalizedOrthoMatrix();
	};
}