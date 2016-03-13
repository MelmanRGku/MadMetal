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
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glTexParameterf(textureTarget, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameterf(textureTarget, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glBindTexture(textureTarget, 0);
		stbi_image_free(data);
		return true;
	}
	else {
		std::cout << "Could not load texture " << fileName << std::endl;
	}

	return false;
}

void Texture::Bind(GLenum TextureUnit)
{
	glActiveTexture(TextureUnit);
	glBindTexture(textureTarget, textureObj);
}

void Texture::unBind(GLenum TextureUnit) {
	glActiveTexture(TextureUnit);
	glBindTexture(textureTarget, 0);
}