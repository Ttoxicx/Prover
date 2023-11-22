#include "IO/Image/ImageLoader.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image/stb_image.h>

std::shared_ptr<ImageData> ImageLoader::loadImage(const std::string& path, bool flip) {
	stbi_set_flip_vertically_on_load(flip);
	int width, height, channel;
	unsigned char* data = stbi_load(path.c_str(), &width, &height, &channel, 0);
	return std::make_shared<ImageData>(width, height, channel, data);
}