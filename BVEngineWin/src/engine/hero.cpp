#include "hero.h"


namespace bulka {
	Hero::Hero()
	{
	}
	Hero::~Hero()
	{
	}
	void Hero::init() {
		camera.init();
	}
	void Hero::postInit() {
		camera.postInit();
	}
	void Hero::finalization() {
		camera.finalization();
	}
	void Hero::inputUpdate() {
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
		camera.addRotation(addRotY, addRotX, 0);
		camera.moveInDirection(moveSpeed * x, moveSpeed * y, moveSpeed * z);
		if (moved || rotated) {
			camera.updateViewMatrix();
			camera.updateProjViewMatrix();
		}
	}
	Camera& Hero::getCamera() {
		return camera;
	}
	void Hero::setPosition(float x, float y, float z) {
		camera.setPosition(x, y, z);
		camera.updateViewMatrix();
		camera.updateProjViewMatrix();
	}
	void Hero::addPosition(float x, float y, float z) {
		camera.addPosition(x, y, z);
		camera.updateViewMatrix();
		camera.updateProjViewMatrix();
	}
	void Hero::moveInDirection(float x, float y, float z) {
		camera.moveInDirection(x, y, z);
		camera.updateViewMatrix();
		camera.updateProjViewMatrix();
	}
	void Hero::setRotation(float x, float y, float z) {
		camera.setRotation(x, y, z);
		camera.updateViewMatrix();
		camera.updateProjViewMatrix();
	}
	void Hero::addRotation(float x, float y, float z) {
		camera.addRotation(x, y, z);
		camera.updateViewMatrix();
		camera.updateProjViewMatrix();
	}
	float Hero::getSpeed()
	{
		return speed;
	}
	float Hero::getSensitivity()
	{
		return sensitivity;
	}
	void Hero::setSpeed(float speed)
	{
		this->speed = speed;
	}
	void Hero::setSensitivity(float sensitivity)
	{
		this->sensitivity = sensitivity;
	}
}