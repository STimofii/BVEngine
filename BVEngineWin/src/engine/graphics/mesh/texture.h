#pragma once


namespace bulka{
	class Texture{
	private:
	protected:
	public:
		unsigned int texture = 0;
		Texture(const char* path = nullptr);
		~Texture();
		void loadTexture(const char* path);
		void loadTexture(unsigned char* data, int width, int height, int alpha);

		void bind();
		void unbind();
	};


}
