#include "OutputFile.h"

#include "pch.h"
#include <fstream>
#include <glm/gtx/string_cast.hpp>

OutputFile::OutputFile(int width, int height)
{
	_width = width;
	_height = height;

	_data = "P3\n" + std::to_string(width) + ' ' + std::to_string(height) + '\n' + std::to_string(255) + '\n';
	std::vector<std::vector<glm::vec3>> pixelArray(width, std::vector<glm::vec3>(height, glm::vec3(0.0f)));
	_pixelArray = pixelArray;

}

OutputFile::OutputFile(OutputFile& file)
{
	_pixelArray = std::move(file._pixelArray);
	_width = file._width;
	_height = file._height;
}

void OutputFile::ColorPixel(int x, int y, glm::vec3 color)
{
	_pixelArray[x][y] = color;
}

void OutputFile::saveFile()
{
	//parse array to string
	for (int j = _height-1; j >=0; j--)
	{
		for (int i = 0; i < _width; i++)
		{
			std::string r = std::to_string(static_cast<int>(255.999 * _pixelArray[i][j].r));
			std::string g = std::to_string(static_cast<int>(255.999 * _pixelArray[i][j].g));
			std::string b = std::to_string(static_cast<int>(255.999 * _pixelArray[i][j].b));
			std::string colorString = r + ", " + g + ", " + b + "\n";
			_data.append(colorString);

		}
	}


	//write to file

	std::ofstream file;

	file.open("image.ppm");

	if (!file)
	{
		std::cerr << "error creating file";
		exit(1);
	}

	file << _data;

	file.close();
	
}

int OutputFile::getWidth()
{
	return _width;
}

int OutputFile::getHeight()
{
	return _height;
}
