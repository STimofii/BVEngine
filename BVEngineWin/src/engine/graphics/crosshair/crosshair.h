#pragma once

namespace bulka {
	class Crosshair {
	private:
		unsigned int VAO = 0;
		unsigned int VBO = 0;
	protected:
	public:
		Crosshair();
		~Crosshair();
		void init();
		void render();
	};
}