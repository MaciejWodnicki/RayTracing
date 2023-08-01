#pragma once

#include "pch.h"

class OutputFile {
private:
	int _width;
	int _height;

	std::string _data;
	std::vector<std::vector<glm::vec3>> _pixelArray;

public:
	OutputFile(int width, int height);
	OutputFile(OutputFile& file);

	void ColorPixel(int x, int y, glm::vec3 Color);

	void saveFile();

	int getWidth();
	int getHeight();
};

