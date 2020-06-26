#include "TextureLoader.h"

#define STB_IMAGE_IMPLEMENTATION // a library dedicated to load and write images

#include "Dependencies/stb-master/stb_image.h"

TextureLoader::TextureLoader()
{

}

TextureLoader::~TextureLoader()
{

}

GLuint TextureLoader::getTextureID(std::string textFileName)
{
	int width;
	int height;
	int channels;
	stbi_uc* image = stbi_load(textFileName.c_str(), &width, &height, &channels, STBI_rgb);
	GLuint mTexture;
	glGenTextures(1, &mTexture);
	glBindTexture(GL_TEXTURE_2D, mTexture);
	
	// sets the texture parameters fro wrapping around
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	
	// sets the parameters for filtering the image
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// sets mipmap profile description
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);

	//creating the texture
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);

	// here the bindin is close and the memori fo the texture is released
	glBindTexture(GL_TEXTURE_2D, 0);
	stbi_image_free(image);

	// returning the texture reference, not the image.
	return mTexture;
}