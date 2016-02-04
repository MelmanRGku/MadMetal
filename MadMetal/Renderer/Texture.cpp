#define STB_IMAGE_IMPLEMENTATION
#include "Texture.h"


Texture::Texture(GLenum TextureTarget, const std::string& FileName)
{
	textureTarget = TextureTarget;
	fileName = FileName;
}


bool Texture::Load()
{
	int width, height, n;
	unsigned char* data = stbi_load(fileName.c_str(), &width, &height, &n, 4); // request RGBA
	if (data != NULL)
	{
		glGenTextures(1, &textureObj);
		glBindTexture(textureTarget, textureObj);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glTexParameterf(textureTarget, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameterf(textureTarget, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glBindTexture(textureTarget, 0);
		std::cout << width << " " << height << " " << sizeof(data) << std::endl;
		stbi_image_free(data);

		return true;
	}

	return false;
}

void Texture::Bind(GLenum TextureUnit)
{
	glActiveTexture(TextureUnit);
	glBindTexture(textureTarget, textureObj);
}