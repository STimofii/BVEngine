#include "hero.h"

#include <cmath>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "input.h"
#include "engine.h"
#include "server/world/chunks/chunk.h"
#include "server/world/world.h"
#include "server/game.h"



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
		bool accelerated = false;
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
		if (Input::isKeyPressed(GLFW_KEY_F4)) {
			accelerated = true;
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
		if (accelerated) {
			moveSpeed *= 10;
		}
		camera.addRotation(addRotY, addRotX, 0);
		camera.moveInDirection(moveSpeed * x, moveSpeed * y, moveSpeed * z);
		//camera.moveInDirectionWithVertical(moveSpeed * x, moveSpeed * y, moveSpeed * z);
		if (moved || rotated) {
			chunksPosition.y = std::floor(camera.getPosition().y / SUB_CHUNK_SIZE_Y);
			glm::ivec2 moveChunks(0, 0);
			if (camera.getPosition().x >= CHUNK_SIZE_X) {
				moveChunks.x = camera.getPosition().x / CHUNK_SIZE_X;
				camera.getPosition().x = std::fmod(camera.getPosition().x, CHUNK_SIZE_X);
			} else if (camera.getPosition().x < 0) {
				moveChunks.x = std::floor(camera.getPosition().x / CHUNK_SIZE_X);
				camera.getPosition().x = CHUNK_SIZE_X + std::fmod(camera.getPosition().x, CHUNK_SIZE_X);
			}
			if (camera.getPosition().z >= CHUNK_SIZE_Z) {
				moveChunks.y = camera.getPosition().z / CHUNK_SIZE_Z;
				camera.getPosition().z = std::fmod(camera.getPosition().z, CHUNK_SIZE_Z);
			} else if (camera.getPosition().z < 0) {
				moveChunks.y = std::floor(camera.getPosition().z / CHUNK_SIZE_Z);
				camera.getPosition().z = CHUNK_SIZE_X + std::fmod(camera.getPosition().z, CHUNK_SIZE_Z);
			}

			chunksPosition.x += moveChunks.x;
			chunksPosition.z += moveChunks.y;
			Game::getWorld()->moveChunks(moveChunks.x, moveChunks.y);

			camera.updateViewMatrix();
			camera.updateProjViewMatrix();
		}
	}

	glm::ivec3 Hero::getChunksPosition() {
		return chunksPosition;
	}

	glm::ivec3 Hero::getWorldPosition()
	{
		glm::ivec3 out(camera.getPosition());
		out.x += chunksPosition.x * CHUNK_SIZE_X;
		out.z += chunksPosition.z * CHUNK_SIZE_Z;
		return out;
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