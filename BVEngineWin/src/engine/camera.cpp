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
		updateVectors();
	}
	Camera::Camera(glm::vec3 position) : position(position)
	{
		updateVectors();
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
		float pitch = rotation.x * (bcppul::PI / 180);
		float yaw = rotation.y * (bcppul::PI / 180);
		float roll = rotation.z * (bcppul::PI / 180);
		position.x += std::sin(yaw) * -z + std::sin(yaw - bcppul::HALF_PI) * -x;
		position.y += y;
		position.z += std::cos(yaw) * z + std::cos(yaw - bcppul::HALF_PI) * x;
	}
	void Camera::setRotation(float x, float y, float z)
	{
		rotation.x = x;
		rotation.y = y;
		rotation.z = z;
	}
	void Camera::addRotation(float x, float y, float z)
	{
		rotation.x += x;
		rotation.y += y;
		rotation.z += z;
		if(rotation.y <= 0 || rotation.y >= 360){
			rotation.y = std::fmod(rotation.y, 360);
		}
		if (rotation.z <= 0 || rotation.z >= 360) {
			rotation.z = std::fmod(rotation.z, 360);
		}

		if(rotation.x < -90){
			rotation.x = -90;
		}
		else if (rotation.x > 90) {
			rotation.x = 90;
		}
	}
	glm::vec3& Camera::getPosition()
	{
		return position;
	}
	glm::vec3& Camera::getRotation()
	{
		return rotation;
	}
	float Camera::getFOV()
	{
		return fov;
	}
	void Camera::setFOV(float fov)
	{
		fov = fov * (bcppul::PI / 180);
		if (this->fov != fov){
			this->fov = fov;
			updateProjectionMatrix();
			updateProjViewMatrix();
		}
	}
	void Camera::updateVectors()
	{

	}
	void Camera::updateDirection()
	{

	}
	void Camera::updateProjectionMatrix()
	{
		projectionMatrix = glm::perspective(fov, Window::getAspect(), 0.01f, 1000.0f);
	}
	void Camera::updateViewMatrix()
	{
		viewMatrix = glm::mat4(1.0f);
		viewMatrix = glm::rotate(viewMatrix, static_cast<float>(rotation.x * (bcppul::PI / 180)), glm::vec3(1, 0, 0));
		viewMatrix = glm::rotate(viewMatrix, static_cast<float>(rotation.y * (bcppul::PI / 180)), glm::vec3(0, 1, 0));
		viewMatrix = glm::rotate(viewMatrix, static_cast<float>(rotation.z * (bcppul::PI / 180)), glm::vec3(0, 0, 1));
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
		//orthoMatrix = glm::ortho(0.0f * as, 1.0f * as, 0.0f, 1.0f, 0.0f, 1000.0f);
		//orthoMatrix = glm::ortho(-1.0f * as, 1.0f * as, -1.0f, 1.0f, 0.0f, 1000.0f);
		
		if (ShaderManager::textShader.programID != 0) {
			ShaderManager::textShader.bind();
			ShaderManager::textShader.uniformMat4f("projection", orthoMatrix);
			ShaderManager::textShader.unbind();
		}
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