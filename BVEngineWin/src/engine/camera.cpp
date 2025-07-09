#include "camera.h"

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
		normalizedOrthoMatrix = glm::ortho(-1, 1, -1, 1);
		
	}
	void Camera::postInit() {
		ShaderManager::mainShader.bind();
		ShaderManager::mainShader.uniformMat4f("projViewMat", projViewMatrix);
		ShaderManager::mainShader.unbind();
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
		bool moved = false;
		bool rotated = false;
		float x = 0;
		float y = 0;
		float z = 0;
		float addRotX = 0;
		float addRotY = 0;
		if (Input::isKeyPressed(GLFW_KEY_W)) {
			z = -1;
			moved = true;
		}
		if (Input::isKeyPressed(GLFW_KEY_A)) {
			x = -1;
			moved = true;
		}
		if (Input::isKeyPressed(GLFW_KEY_S)) {
			z = 1;
			moved = true;
		}
		if (Input::isKeyPressed(GLFW_KEY_D)) {
			x = 1;
			moved = true;
		}
		if (Input::isKeyPressed(GLFW_KEY_SPACE)) {
			y = 1;
			moved = true;
		}
		if (Input::isKeyPressed(GLFW_KEY_LEFT_SHIFT)) {
			y = -1;
			moved = true;
		}
		if (Input::getMouseDeltaX != 0) {
			addRotX = -sensitivity * Input::getMouseDeltaX();
			rotated = true;
		}
		if (Input::getMouseDeltaY != 0) {
			addRotY = -sensitivity * Input::getMouseDeltaY();
			rotated = true;
		}
		float moveSpeed = Engine::getDeltaTime() * speed;
		addRotation(addRotY, addRotX, 0);
		moveInDirection(moveSpeed * x, moveSpeed * y, moveSpeed * z);
		if (moved || rotated) {
			updateViewMatrix();
			updateProjViewMatrix();
		}
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
	void Camera::updateVectors()
	{

	}
	void Camera::updateDirection()
	{
		float pitch = rotation.x * (bcppul::PI / 180);
		float yaw = rotation.y * (bcppul::PI / 180);
		float roll = rotation.z * (bcppul::PI / 180);
		direction.x = std::sin(pitch) * std::cos(yaw);
		direction.y = -std::sin(pitch);
		direction.z = -(std::cos(pitch) * std::cos(yaw));
	}
	void Camera::updateProjectionMatrix()
	{
		projectionMatrix = glm::perspective(fov, Window::getAspect(), 0.01f, 100.0f);
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
		if(ShaderManager::mainShader.programID != 0){
			ShaderManager::mainShader.bind();
			ShaderManager::mainShader.uniformMat4f("projViewMat", projViewMatrix);
			ShaderManager::mainShader.unbind();
		}
	}
	void Camera::updateOrthoMatrix()
	{
		orthoMatrix = glm::ortho(0, Window::getRealWidth(), Window::getRealHeight(), 0);
	}
}