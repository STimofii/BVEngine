#include "camera.h"

#include <cmath>
#include <iostream>
#include "window.h"
#include "engine.h"
#include "graphics/shader_manager.h"

namespace bulka {
	Camera::Camera()
	{
	}
	Camera::Camera(glm::vec3 position, glm::vec3 rotation) : position(position), rotation(rotation)
	{
		updateDirection();
	}
	Camera::Camera(glm::vec3 position) : position(position)
	{
		
	}
	Camera::~Camera()
	{
	}
	void Camera::init() {
		
		
	}
	void Camera::postInit() {
		updateOrthoMatrix();
	}
	void Camera::finalization() {

	}
	void Camera::setPosition(float x, float y, float z)
	{
		position.x = x;
		position.y = y;
		position.z = z;
	}
	void Camera::inputUpdate()
	{

	}
	void Camera::addPosition(float x, float y, float z)
	{
		position.x += x;
		position.y += y;
		position.z += z;
	}
	void Camera::moveInDirection(float x, float y, float z)
	{
		position.x += direction.x * x - direction.z * z;
		position.y += y;
		position.z += direction.z * x + direction.x * z;
	}
	void Camera::moveInDirectionWithVertical(float x, float y, float z)
	{
		//TODO: MAYBE NOT CORRECT
		position.x += direction.x * x - direction.z * z;
		position.y += direction.y * x + direction.y * z;
		position.z += direction.z * x + direction.x * z;
	}
	void Camera::setRotation(float x, float y, float z)
	{
		rotation.x = x;
		rotation.y = y;
		rotation.z = z;
		updateDirection();
	}
	void Camera::addRotation(float x, float y, float z)
	{
		rotation.x += x;
		rotation.y += y;
		rotation.z += z;
		if(rotation.y < 0 || rotation.y > 360){
			rotation.y = std::fmod(rotation.y, 360);
		}
		if (rotation.z < 0 || rotation.z > 360) {
			rotation.z = std::fmod(rotation.z, 360);
		}

		if(rotation.x < -90){
			rotation.x = -90;
		}
		else if (rotation.x > 90) {
			rotation.x = 90;
		}
		updateDirection();
	}
	glm::vec3& Camera::getPosition()
	{
		return position;
	}
	glm::vec3& Camera::getRotation()
	{
		return rotation;
	}
	glm::vec3& Camera::getDirection()
	{
		return direction;
	}
	float Camera::getFOV()
	{
		return fov;
	}
	void Camera::setFOV(float fov)
	{
		fov = bcppul::degreesToRadians(fov);
		if (this->fov != fov){
			this->fov = fov;
			updateProjectionMatrix();
			updateProjViewMatrix();
		}
	}
	void Camera::updateDirection()
	{
		float pitch = bcppul::degreesToRadians(rotation.x);
		float yaw = bcppul::degreesToRadians(rotation.y);
		float roll = bcppul::degreesToRadians(rotation.z);
		direction.x = std::cos(yaw);
		direction.y = std::sin(pitch);
		direction.z = std::sin(yaw);

	}
	void Camera::updateProjectionMatrix()
	{
		projectionMatrix = glm::perspective(fov, Window::getAspect(), 0.01f, 1000.0f);
	}
	void Camera::updateViewMatrix()
	{
		viewMatrix = glm::mat4(1.0f);
		viewMatrix = glm::rotate(viewMatrix, static_cast<float>(bcppul::degreesToRadians(rotation.x)), glm::vec3(1, 0, 0));
		viewMatrix = glm::rotate(viewMatrix, static_cast<float>(bcppul::degreesToRadians(rotation.y)), glm::vec3(0, 1, 0));
		viewMatrix = glm::rotate(viewMatrix, static_cast<float>(bcppul::degreesToRadians(rotation.z)), glm::vec3(0, 0, 1));
		viewMatrix = glm::translate(viewMatrix, -position);
	}
	void Camera::updateProjViewMatrix()
	{
		projViewMatrix = projectionMatrix * viewMatrix;
		if(Engine::getIsGLInitialized()){
			if (ShaderManager::mainShader.programID != 0) {
				ShaderManager::mainShader.bind();
				ShaderManager::mainShader.uniformMat4f("projViewMat", projViewMatrix);
			}

			ShaderManager::mainShader.unbind();
		}
	}
	void Camera::updateOrthoMatrix()
	{
		float as = Window::getAspect();
		normalizedOrthoMatrix = glm::ortho(-1.0f * as, 1.0f * as, -1.0f, 1.0f, 0.0f, 1000.0f);
		orthoMatrix = glm::ortho(0.0f, static_cast<float>(Window::getRealWidth()), 0.0f, static_cast<float>(Window::getRealHeight()), 0.0f, 1000.0f);
	}

	glm::mat4& Camera::getProjectionMatrix()
	{
		return projectionMatrix;
	}
	glm::mat4& Camera::getViewMatrix()
	{
		return viewMatrix;
	}
	glm::mat4& Camera::getProjViewMatrix()
	{
		return projViewMatrix;
	}
	glm::mat4& Camera::getOrthoMatrix()
	{
		return orthoMatrix;
	}
	glm::mat4& Camera::getNormalizedOrthoMatrix()
	{
		return normalizedOrthoMatrix;
	}
}