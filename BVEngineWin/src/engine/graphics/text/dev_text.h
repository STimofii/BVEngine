#pragma once

#include "IText.h"

namespace bulka {
	class DevText {
	private:
		IText* left_top_text = nullptr;
		IText* right_top_text = nullptr;
		IText* left_bottom_text = nullptr;
		IText* right_bottom_text = nullptr;
	protected:
	public:
		DevText();
		~DevText();

		void init();
		void update();
		void render();
	};
}