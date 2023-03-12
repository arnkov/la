#include "laTexture.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "log.h"

void laSetupTexture(GLuint* texture) {
	glGenTextures(1, texture);
	glBindTexture(GL_TEXTURE_2D, *texture);
	// set the texture wrapping/filtering options (on the currently bound texture object)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	log_info("Texture created: %d", *texture);
}

void laDeleteTexture(GLuint* texture) {
	glDeleteTextures(1, texture);
	log_info("Texture deleted: %d", *texture);
}

void laTexFromImage(GLuint* texture, const char* path, int format, bool flip) {
	// load the image
	int width, height, nrChannels;
	stbi_set_flip_vertically_on_load(flip);
	unsigned char* data = stbi_load(path, &width, &height, &nrChannels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
		log_info("Texture loaded: %d", *texture);
	}
	else
	{
		log_error("Failed to load texture");
	}
	stbi_image_free(data);
}

void laBindTexture(GLuint* texture, int slot) {
	glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture(GL_TEXTURE_2D, *texture);
}

void laUnbindTexture() {
	glBindTexture(GL_TEXTURE_2D, 0);
}