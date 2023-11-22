#ifndef _IMAGELOADER_H_
#define _IMAGELOADER_H_

#include <string>
#include <memory>

class ImageData {
public:
	ImageData(int width,int height,int channel,unsigned char* data) {
		_width = width;
		_height = height;
		_channel = channel;
		_data = data;
	}
	~ImageData() {
		free(_data);
	}
	inline int width() const {
		return _width;
	}
	inline int height() const {
		return _height;
	}
	inline int channel() const {
		return _channel;
	}
	inline unsigned char* data() const {
		return _data;
	}
private:
	int _width = 0;
	int _height = 0;
	int _channel = 0;
	unsigned char* _data = NULL;
};

class ImageLoader {
public:
	static std::shared_ptr<ImageData> loadImage(const std::string& path, bool flip = false);
};

#endif // !_IMAGELOADER_H_
