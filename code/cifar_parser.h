#pragma once

#include <iostream>
#include <sstream>
#include <fstream>
#include <iomanip> // setw
#include <random>

#include <stdio.h>

#define datanum 1

namespace cifar
{
	std::string data_name() { return std::string("CIFAR-10"); }

	bool parse_cifar_data(const std::string& cifar_file,
		std::vector<std::vector<double>> * images,
		std::vector<int> *labels,
		double scale_min = -1.0, double scale_max = 1.0, // <-- what does this mean?
		int x_padding = 0, int y_padding = 0)
	{
		std::ifstream ifs(cifar_file.c_str(), std::ios::in | std::ios::binary);

		if (ifs.bad() || ifs.fail())
		{
			return false;
		}

		for (size_t i = 0; i < datanum; i++)
		{
			unsigned char label;
			ifs.read((char*)&label, 1);
			labels->push_back((int)label);

			std::vector<unsigned char> image_c(32 * 32 * 3);
			ifs.read((char*)&image_c[0], 32 * 32 * 3);
			int width = 32 + 2 * x_padding;
			int height = 32 + 2 * y_padding;
			std::vector<double> image(height*width * 3);

			for (size_t c = 0; c < 3; c++)
				for (size_t y = 0; y < 32; y++)
					for (size_t x = 0; x < 32; x++)
						image[width*(y + y_padding) + x + x_padding + (3 - c - 1)*width*height] =
						(image_c[y * 32 + x + c * 32 * 32] / 255.0f)*(scale_max - scale_min) + scale_min;
			images->push_back(image);
		}
		return true;
	}

	bool parse_test_data(std::string &data_path, std::vector<std::vector<double>> &test_images, std::vector<int> &test_labels,
		double min_val = -1.f, double max_val = 1.f, int padx = 0, int pady = 0)
	{
		return parse_cifar_data(data_path + "cifar10-test", &test_images, &test_labels, min_val, max_val, padx, pady);
	}

	bool parse_train_data(std::string &data_path, std::vector<std::vector<double>> &train_images, std::vector<int> &train_labels,
		double min_val = -1.f, double max_val = 1.f, int padx = 0, int pady = 0)
	{
		if (!parse_cifar_data(data_path + "cifar10-train", &train_images, &train_labels, min_val, max_val, padx, pady)) return false;
		return true;
	}


} // namespace