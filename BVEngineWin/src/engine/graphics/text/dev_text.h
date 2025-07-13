#pragma once

#include "IText.h"

#include <bcppul/logging.h>

namespace bulka {
	class DevText {
	private:
		static bcppul::Logger* logger;
		bool visible = false;
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
		bool isVisible();
		void setVisible(bool val);
		void toggleVisible();
	};
}