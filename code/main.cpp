#include <iostream>
#include "layer.h"
#include "opencv2\opencv.hpp"
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>



#include <fstream>
#include <iostream>
#include <time.h>
#include <boost\iostreams\filtering_streambuf.hpp>
#include <boost\iostreams\copy.hpp>
#include <boost\iostreams\filter\zlib.hpp>
#include <boost\iostreams\filter\gzip.hpp>
#include <boost\iostreams\filtering_stream.hpp>

#include <string>
#include "cifar_parser.h"


#include <fstream>
#include <vector>
#include <sstream>
#include <stdio.h>
#include <tchar.h>
#include "weight_parser.h"
#include "layer.h"
#include <math.h>
#include "cifar10_reader.hpp"

const int mini_batch_size = 16;
const double initial_learning_rate = 0.05f;
std::string solver = "adam";
std::string data_path = "";
using namespace cifar;

using namespace cv;


using namespace std;

void make_array_for_out_2d(double* returnarr, int depth);
void make_array_for_out(double*** returnarr, int depth, int col, int row);
void make_array(double**** returnarr, int number, int depth, int col, int row);
void make_array_for_out_vector323232(vector<vector<vector<double>>> &returnarr, int depth, int col, int row);
void make_array_for_out_vector321616(vector<vector<vector<double>>> &returnarr, int depth, int col, int row);
void make_array_for_out_vector3288(vector<vector<vector<double>>> &returnarr, int depth, int col, int row);
void make_array_for_out_vector6488(vector<vector<vector<double>>> &returnarr, int depth, int col, int row);
void make_array_for_out_vector6444(vector<vector<vector<double>>> &returnarr, int depth, int col, int row);
void make_array_for_out_vector512(vector<double> &returnarr, int a);
void make_array_for_out_vector10(vector<double> &returnarr, int a);
void softmax(vector<vector<double>> arr, vector<int> & input);
int maxindex(vector<double> arr);
void make_array_inputdata(vector<vector<vector<vector<double>>>> &arr, int input);
int get_max_pos(vector<double> arr);
void makearr_4(vector<vector<vector<vector<double>>>> &arr);
void makearr_323232_4(vector<vector<vector<vector<double>>>> &arr);
void makearr_321616_4(vector<vector<vector<vector<double>>>> &arr);
void makearr_3288_4(vector<vector<vector<vector<double>>>> &arr);
void makearr_6488_4(vector<vector<vector<vector<double>>>> &arr);
void makearr_512_4(vector<vector<double>> &arr);
void makearr_10_4(vector<vector<double>> &arr);
void make2dvec(vector<vector<double>> &arr);


std::vector<std::vector<double>> test_images;
std::vector<int> test_labels;
std::vector<std::vector<double>> train_images;
std::vector<int> train_labels;





vector<vector<vector<vector<double>>>> input_images_for_net;

int main(int argc, char** argv)
{


	clock_t before;
	double result;
	before = clock();

	String imageName("d.jpg"); // by default
	if (argc > 1)
	{
		imageName = argv[1];
	}

	Mat image;



	image = imread(imageName);

	if (image.empty())                      // Check for invalid input
	{
		cout << "Could not open or find the image" << std::endl;
		return -1;
	}

	namedWindow("Display window", WINDOW_AUTOSIZE);

	imshow("Display window", image);                // Show our image inside it.

	waitKey(0); // Wait for a keystroke in the window

	
	cv::Mat rgbMat = cv::imread("d.jpg"); // Read original image
	cv::Mat arrayFromRgb = rgbMat.reshape(1, rgbMat.channels()*rgbMat.size().area());

	
	cout << arrayFromRgb.size() << endl;


	
	uint8_t* data = (uint8_t*)arrayFromRgb.data;
	
	int azx = data[0];

	vector<vector<vector<vector<double>>>> testing_oneimage;

	int temp2 = 0;

	make_array_inputdata(testing_oneimage, 1);


	for (int depth = 0; depth < 3; depth++)
	{
		for (int col = 0; col < 32; col++)
		{
			for (int row = 0; row < 32; row++)
			{
				testing_oneimage[0][depth][col][row] = data[temp2];
				temp2++;
			}
		}
	}

	/*
	for (int col = 0; col < 32; col++)
	{
		for (int row = 0; row < 32; row++)
		{
			testing_oneimage[0][2][col][row] = data[temp2];
			temp2++;
		}
	}


	for (int col = 0; col < 32; col++)
	{
		for (int row = 0; row < 32; row++)
		{
			testing_oneimage[0][1][col][row] = data[temp2];
			temp2++;
		}
	}


	for (int col = 0; col < 32; col++)
	{
		for (int row = 0; row < 32; row++)
		{
			testing_oneimage[0][0][col][row] = data[temp2];
			temp2++;
		}
	}


*/


	auto dataset = cifar::read_dataset<std::vector, std::vector, uint8_t, uint8_t>(datanum,datanum);
	//if (!parse_test_data(data_path, test_images, test_labels)) { std::cerr << "error: could not parse data.\n"; return 1; }
	//if (!parse_train_data(data_path, train_images, train_labels)) { std::cerr << "error:could not parse data.\n"; return 1; }

	int temp = 0;

	vector<vector<vector<vector<double>>>> input_images;
	make_array_inputdata(input_images, datanum);
	
	for (int i = 0; i < datanum; i++)
	{
		for (int depth = 0; depth < 3; depth++)
		{
			for (int col = 0; col < 32; col++)
			{
				for (int row = 0; row < 32; row++)
				{
					input_images[i][depth][col][row] = dataset.test_images[i][temp];
					temp++;
				}
			}
		}


		input_images_for_net.push_back(input_images[i]);
		temp = 0;
	}
	int testing_label[datanum];

	for (int i = 0; i < datanum; i++)
	{
		testing_label[i] = dataset.test_labels[i];
	}


	/*vector<vector<vector<double>>> out1v;
	make_array_for_out_vector323232(out1v, 32, 32, 32);*/

	/*vector<vector<vector<double>>> out2v;
	make_array_for_out_vector323232(out2v, 32, 32, 32);*/

	/*vector<vector<vector<double>>> out3v;
	make_array_for_out_vector323232(out3v, 32, 32, 32);*/

	/*vector<vector<vector<double>>> out4v;
	make_array_for_out_vector321616(out4v, 32, 16, 16);*/

	/*vector<vector<vector<double>>> out5v;
	make_array_for_out_vector321616(out5v, 32, 16, 16);*/

	/*vector<vector<vector<double>>> out6v;
	make_array_for_out_vector321616(out6v, 32, 16, 16);*/

	/*vector<vector<vector<double>>> out7v;
	make_array_for_out_vector321616(out7v, 32, 16, 16);*/

	/*vector<vector<vector<double>>> out8v;
	make_array_for_out_vector321616(out8v, 32, 16, 16);*/

	/*vector<vector<vector<double>>> out9v;
	make_array_for_out_vector321616(out9v, 32, 16, 16);*/

	/*vector<vector<vector<double>>> out10v;
	make_array_for_out_vector321616(out10v, 32, 16, 16);*/

	/*vector<vector<vector<double>>> out11v;
	make_array_for_out_vector3288(out11v, 32, 8, 8);*/

	/*vector<vector<vector<double>>> out12v;
	make_array_for_out_vector6488(out12v, 64, 8, 8);*/

	/*vector<vector<vector<double>>> out13v;
	make_array_for_out_vector6488(out13v, 64, 8, 8);*/

	/*vector<vector<vector<double>>> out14v;
	make_array_for_out_vector6488(out14v, 64, 8, 8);*/

	/*vector<vector<vector<double>>> out15v;
	make_array_for_out_vector6488(out15v, 64, 8, 8);*/

	/*vector<vector<vector<double>>> out16v;
	make_array_for_out_vector6488(out16v, 64, 8, 8);*/

	/*vector<vector<vector<double>>> out17v;
	make_array_for_out_vector6488(out17v, 64, 8, 8);*/

	/*vector<vector<vector<double>>> out18v;
	make_array_for_out_vector6444(out18v, 64, 4, 4);*/

	/*vector<double> out19v;
	make_array_for_out_vector512(out19v, 512);*/

	/*vector<double> out19v1;
	make_array_for_out_vector512(out19v1, 512);*/
	
	/*vector<double> out19v2;
	make_array_for_out_vector512(out19v2, 512);*/

	/*vector<double> out20v;
	make_array_for_out_vector10(out20v, 10);*/

	
	vector<vector<vector<vector<double>>>> out1v_4;
	vector<vector<vector<vector<double>>>> out2v_4;
	vector<vector<vector<vector<double>>>> out3v_4;
	vector<vector<vector<vector<double>>>> out4v_4;
	vector<vector<vector<vector<double>>>> out5v_4;
	vector<vector<vector<vector<double>>>> out6v_4;
	vector<vector<vector<vector<double>>>> out7v_4;
	vector<vector<vector<vector<double>>>> out8v_4;
	vector<vector<vector<vector<double>>>> out9v_4;
	vector<vector<vector<vector<double>>>> out10v_4;
	vector<vector<vector<vector<double>>>> out11v_4;
	vector<vector<vector<vector<double>>>> out12v_4;
	vector<vector<vector<vector<double>>>> out13v_4;
	vector<vector<vector<vector<double>>>> out14v_4;
	vector<vector<vector<vector<double>>>> out15v_4;
	vector<vector<vector<vector<double>>>> out16v_4;
	vector<vector<vector<vector<double>>>> out17v_4;
	vector<vector<vector<vector<double>>>> out18v_4;
	vector<vector<double>> out19v_4;
	vector<vector<double>> out20v_4;
	vector<vector<double>> out21v_4;

	makearr_323232_4(out1v_4);
	makearr_323232_4(out2v_4);
	makearr_323232_4(out3v_4);
	makearr_321616_4(out4v_4);
	makearr_321616_4(out5v_4);
	makearr_321616_4(out6v_4);
	makearr_321616_4(out7v_4);
	makearr_321616_4(out8v_4);
	makearr_321616_4(out9v_4);
	makearr_321616_4(out10v_4);
	makearr_3288_4(out11v_4);
	makearr_6488_4(out12v_4);
	makearr_6488_4(out13v_4);
	makearr_6488_4(out14v_4);
	makearr_6488_4(out15v_4);
	makearr_6488_4(out16v_4);
	makearr_6488_4(out17v_4);
	makearr_6488_4(out18v_4);
	makearr_512_4(out19v_4);
	makearr_512_4(out20v_4);
	makearr_10_4(out21v_4);

	
	/*vector<vector<vector<double>>> out1_1v;
	make_array_for_out_vector323232(out1_1v, 32, 32, 32);
	vector<vector<vector<double>>> out2_1v;
	make_array_for_out_vector323232(out2_1v, 32, 32, 32);
	vector<vector<vector<double>>> out3_1v;
	make_array_for_out_vector323232(out3_1v, 32, 32, 32);*/
	
	

	int accnum = 0;
	layer network;

	vector<int> input;
	for (int i = 0; i < numberdata; i++)
	{
		input.push_back(0);
	}


		//network.normal_convolution(input_images_for_net[i], out1v);
		network.normal_convolution_4(testing_oneimage, out1v_4);

		//network.normalization(out1v, out2v);
		//network.Lnormalization(out1v, out2v);
		network.Lnormalization_4(out1v_4, out2v_4);


		//network.relu1(32, 32, 32, out1v,out3v);
		network.relu1_4(32, 32, 32, out2v_4, out3v_4);


		//network.pool(out3v,out4v);
		network.pool_4(out3v_4, out4v_4);


		//network.point_convolution(out4v,out5v);
		network.point_convolution_4(out4v_4, out5v_4);


		////network.normalization1(out5v,out6v);
		//network.Lnormalization1(out5v, out6v);
		network.Lnormalization1_4(out5v_4, out6v_4);



		//network.relu2(32, 16, 16, out5v,out7v);
		network.relu2_4(32, 16, 16, out6v_4, out7v_4);


		//network.depth_convolution(out7v,out8v);
		network.depth_convolution_4(out7v_4, out8v_4);

		//network.Lnormalization1(out8v,out9v);
		network.Lnormalization1_4(out8v_4, out9v_4);

		//network.relu2(32, 16, 16, out8v,out10v);
		network.relu2_4(32, 16, 16, out9v_4, out10v_4);


		//network.pool2(out10v,out11v);
		network.pool2_4(out10v_4, out11v_4);


		//network.point_convolution2(out11v,out12v);
		network.point_convolution2_4(out11v_4, out12v_4);


		//network.Lnormalization2(out12v,out13v);
		network.Lnormalization2_4(out12v_4, out13v_4);


		//network.relu3(64, 8, 8, out12v,out14v);
		network.relu3_4(64, 8, 8, out13v_4, out14v_4);


		//network.depth_convolution2(out14v,out15v);
		network.depth_convolution2_4(out14v_4, out15v_4);


		//network.Lnormalization2(out15v,out16v);
		network.Lnormalization2_4(out15v_4, out16v_4);

		//network.relu3(64, 8, 8, out15v,out17v);
		network.relu3_4(64, 8, 8, out16v_4, out17v_4);

		//network.pool3(out17v,out18v);
		network.pool3_4(out17v_4, out18v_4);


		//network.Affine(out18v,out19v);
		network.Affine_4(out18v_4, out19v_4);

		////network.Lnormalization3(out19v,out19v1);


		//network.relu4(512, out19v, out19v2);
		network.relu4_4(512, out19v_4, out20v_4);


		//network.Affine2(out19v2,out20v);
		network.Affine2_4(out20v_4, out21v_4);

		softmax(out21v_4, input);
		int addaccu = 0;

		float tempacc = numberdata;

		if (input[0] == 0)
		{
			cout << "airplane" << endl;
			return 0;
		}
		else if (input[0] == 1)
		{
			cout << "automobile" << endl;
			return 0;
		}
		else if (input[0] == 2)
		{
			cout << "bird" << endl;
			return 0;
		}
		else if (input[0] == 3)
		{
			cout << "cat" << endl;
			return 0;
		}
		else if (input[0] == 4)
		{
			cout << "deer" << endl;
			return 0;
		}
		else if (input[0] == 5)
		{
			cout << "dog" << endl;
			return 0;
		}
		else if (input[0] == 6)
		{
			cout << "frog" << endl;
			return 0;
		}
		else if (input[0] == 7)
		{
			cout << "horse" << endl;
			return 0;
		}
		else if (input[0] == 8)
		{
			cout << "ship" << endl;
			return 0;
		}
		else if (input[0] == 9)
		{
			cout << "truck" << endl;
			return 0;
		}

		for (int q = 0; q < numberdata; q++)
		{
			cout << input[q] << " " << testing_label[q] << endl;
			if (input[q] == testing_label[q])
			{
				addaccu++;
			}
		}

		double accuracy = ((float)addaccu / tempacc) * 100;

		cout << "Accuracy : " << accuracy << " % " << endl;

		result = (double)(clock() - before) / CLOCKS_PER_SEC;

		cout << "걸린시간 : " << result << endl;

		cout << endl;

		//if (softmax(out20v,i) == testing_label[i])
		//	accnum++;
		//else continue;


	//// dataset 로드

	/*
	1. dataset 을 읽어온다. 3*32*32
	2. dataset을 일반적인 convolution layer를 통과시킨다.(filter:3*3*3 짜리 32개)  -> output: 32*32*32
	3. dataset을 normalization를 통과시킨다.
	4. dataset을 relu 통과시킨다.
	5. dataset을 pool을 통과시킨다. (filter: 2*2 / stride = 2) -> output: 32*16*16
	6. dataset을 pointwise convolution을 통과시킨다.(filter: 1*1*32 짜리 32개)  -> output: 32*16*16
	7. dataset을 normalization을 통과시킨다.
	8. dataset을 relu을 통과시킨다.
	9. dataset을 depthwise convolution을 통과시킨다.(filter: 3*3*1 짜리 32개)  -> output: 32*16*16
	10. dataset을 normalization을 통과시킨다.
	11. dataset을 relu을 통과시킨다.
	12. dataset을 pool을 통과시킨다. (filter: 2*2 / stride = 2)  -> output: 32*8*8
	13. dataset을 pointwise convolution을 통과시킨다. (filter: 1*1*32 짜리 64개)   --> output: 64*8*8
	14. dataset을 normalization을 통과시킨다.
	15. dataset을 relu을 통과시킨다.
	16. dataset을 depthwise convolution을 통과시킨다. (filter: 3*3*1 짜리 64개) --> output: 64*8*8
	17. dataset을 normalization을 통과시킨다.
	18. dataset을 relu을 통과시킨다.
	19. dataset을 pool을 통과시킨다. (filter: 2*2 / stride = 2)  --> output: 4*4*64 = 1024
	20. dataset을 Fully conected를 통과시킨다.(filter: 1024*512) -> output: 1*1*512 (1차원)
	21. dataset을 Fully conected를 통과시킨다. (filter: 512*10) -> output: 1*1*10 (1차원)
	*/

	// normal convolution 통과시키기. 파라미터로 1장 넣고 convolution layer 통과시킨다.

	
	// 1. dataset 을 읽어온다. 32 * 32 * 3




	return 0;
}

void make_array(double**** returnarr, int number, int depth, int col, int row)
{
	for (int i = 0; i < number; i++)
	{
		returnarr[i] = new double**[depth];
	}

	for (int i = 0; i < number; i++)
	{
		for (int j = 0; j < depth; j++)
		{
			returnarr[i][j] = new double*[col];
		}
	}

	for (int i = 0; i < number; i++)
	{
		for (int j = 0; j < depth; j++)
		{
			for (int k = 0; k < col; k++)
			{
				returnarr[i][j][k] = new double[row];
			}
		}
	}

}

void make_array_for_out_vector323232(vector<vector<vector<double>>> &returnarr, int depth, int col, int row)
{


	vector<double> a;
	vector<vector<double>> b;
	vector<vector<vector<double>>> c;

	for (int i = 0; i < 32; i++)
	{
		a.push_back(0);
	}
	for (int i = 0; i < 32; i++)
	{
		b.push_back(a);
	}
	for (int i = 0; i < 32; i++)
	{
		returnarr.push_back(b);
	}
}

void make_array_for_out_vector321616(vector<vector<vector<double>>> &returnarr, int depth, int col, int row)
{
	vector<double> a;
	vector<vector<double>> b;
	vector<vector<vector<double>>> c;

	for (int i = 0; i < 16; i++)
	{
		a.push_back(0);
	}
	for (int i = 0; i < 16; i++)
	{
		b.push_back(a);
	}
	for (int i = 0; i < 32; i++)
	{
		returnarr.push_back(b);
	}
}

void make_array_for_out_vector3288(vector<vector<vector<double>>> &returnarr, int depth, int col, int row)
{
	vector<double> a;
	vector<vector<double>> b;
	vector<vector<vector<double>>> c;

	for (int i = 0; i < 8; i++)
	{
		a.push_back(0);
	}
	for (int i = 0; i < 8; i++)
	{
		b.push_back(a);
	}
	for (int i = 0; i < 32; i++)
	{
		returnarr.push_back(b);
	}
}

void make_array_for_out_vector6488(vector<vector<vector<double>>> &returnarr, int depth, int col, int row)
{
	vector<double> a;
	vector<vector<double>> b;
	vector<vector<vector<double>>> c;

	for (int i = 0; i < 8; i++)
	{
		a.push_back(0);
	}
	for (int i = 0; i < 8; i++)
	{
		b.push_back(a);
	}
	for (int i = 0; i < 64; i++)
	{
		returnarr.push_back(b);
	}
}

void make_array_for_out_vector6444(vector<vector<vector<double>>> &returnarr, int depth, int col, int row)
{
	vector<double> a;
	vector<vector<double>> b;
	vector<vector<vector<double>>> c;

	for (int i = 0; i < 4; i++)
	{
		a.push_back(0);
	}
	for (int i = 0; i < 4; i++)
	{
		b.push_back(a);
	}
	for (int i = 0; i < 64; i++)
	{
		returnarr.push_back(b);
	}
}

void make_array_for_out_vector512(vector<double> &returnarr,int a)
{
	for (int i = 0; i < 512; i++)
	{
		returnarr.push_back(0);
	}
}

void make_array_for_out_vector10(vector<double> &returnarr, int a)
{
	for (int i = 0; i < 10; i++)
	{
		returnarr.push_back(0);
	}
}

void make_array_for_out(double*** returnarr, int depth, int col, int row)
{
	for (int j = 0; j < depth; j++)
	{
		returnarr[j] = new double*[col];
	}

	for (int j = 0; j < depth; j++)
	{
		for (int k = 0; k < col; k++)
		{
			returnarr[j][k] = new double[row];
		}
	}
}


void softmax(vector<vector<double>> arr,vector<int> & input)
{
	vector<vector<double>> inputarr;
	make2dvec(inputarr);
	double subarr[numberdata][10];

	vector<int> tmp1;
	for (int i = 0; i < 10; i++)
	{
		tmp1.push_back(0);
	}
	int tmp[numberdata];
	for (int n = 0; n < numberdata; n++)
	{
		tmp[n] = get_max_pos(arr[n]);
	}


	/*for (int i = 0; i < 9; i++) // cifar10 range is 0~10
	{
		if (arr[tmp] > arr[i + 1])
			tmp = tmp;
		else
			tmp = i + 1;

	}*/
	for (int n = 0; n < numberdata; n++)
	{
		for (int i = 0; i < 10; i++)
		{
			subarr[n][i] = arr[n][i] - arr[n][tmp[n]];
		}
	}

	double sum_for_softmax[numberdata];

	for (int n = 0; n < numberdata; n++)
	{
		sum_for_softmax[n] = 0;
	}


	for (int n = 0; n < numberdata; n++)
	{
		for (int i = 0; i < 10; i++)
		{
			sum_for_softmax[n] = sum_for_softmax[n] + exp(subarr[n][i]);
		}
	}

	for (int n = 0; n < numberdata; n++)
	{
		for (int i = 0; i < 10; i++)
		{
			inputarr[n][i] = (exp(subarr[n][i]) / sum_for_softmax[n]);
		}
	}

	

	for (int n = 0; n < numberdata; n++)
	{
		input[n] = get_max_pos(inputarr[n]);
	}

	/*for (int i = 0; i < 9; i++) // cifar10 range is 0~10
	{
		if (inputarr[maxindex] > inputarr[i + 1])
			maxindex = maxindex;
		else
			maxindex = i + 1;
		
	}*/
}

int maxindex(vector<double> arr)
{
	int maxindex = 0;

	for (int i = 0; i < 9; i++) // cifar10 range is 0~10
	{
		if (arr[maxindex] > arr[i + 1])
			maxindex = maxindex;
		else
			maxindex = i + 1;

	}

	return maxindex;
}

void make_array_inputdata(vector<vector<vector<vector<double>>>> &arr, int input)
{
	vector<double> a;
	vector<vector<double>> b;
	vector<vector<vector<double>>> c;
	for (int i = 0; i < 32; i++)
	{
		a.push_back(0);
	}

	for (int j = 0; j < 32; j++)
	{
		b.push_back(a);
	}

	for (int j = 0; j < 3; j++)
	{
		c.push_back(b);
	}
	for (int j = 0; j < input; j++)
	{
		arr.push_back(c);
	}

}


int get_max_pos(vector<double> arr)
{
	double max = arr[0];
	int max_pos = 0;

	int i;
	for (i = 1; i<10; i++)
	{
		if (max<arr[i])
		{
			max = arr[i];
			max_pos = i;
		}
	}

	return max_pos;
}


void makearr_4(vector<vector<vector<vector<double>>>> &arr)
{
	vector<double> a;
	vector<vector<double>> b;
	vector<vector<vector<double>>> c;
	vector<vector<vector<vector<double>>>> d;


	for (int j = 0; j < 32; j++)
	{
		a.push_back(0);
	}
	for (int i = 0; i < 32; i++)
	{
		b.push_back(a);
	}

	for (int i = 0; i < 3; i++)
	{
		c.push_back(b);
	}
	for (int i = 0; i < numberdata; i++)
	{
		arr.push_back(c);
	}

}

void makearr_323232_4(vector<vector<vector<vector<double>>>> &arr)
{
	vector<double> a;
	vector<vector<double>> b;
	vector<vector<vector<double>>> c;
	vector<vector<vector<vector<double>>>> d;


	for (int j = 0; j < 32; j++)
	{
		a.push_back(0);
	}
	for (int i = 0; i < 32; i++)
	{
		b.push_back(a);
	}

	for (int i = 0; i < 32; i++)
	{
		c.push_back(b);
	}
	for (int i = 0; i < numberdata; i++)
	{
		arr.push_back(c);
	}

}

void makearr_321616_4(vector<vector<vector<vector<double>>>> &arr)
{
	vector<double> a;
	vector<vector<double>> b;
	vector<vector<vector<double>>> c;
	vector<vector<vector<vector<double>>>> d;


	for (int j = 0; j < 16; j++)
	{
		a.push_back(0);
	}
	for (int i = 0; i < 16; i++)
	{
		b.push_back(a);
	}

	for (int i = 0; i < 32; i++)
	{
		c.push_back(b);
	}
	for (int i = 0; i < numberdata; i++)
	{
		arr.push_back(c);
	}

}

void makearr_3288_4(vector<vector<vector<vector<double>>>> &arr)
{
	vector<double> a;
	vector<vector<double>> b;
	vector<vector<vector<double>>> c;
	vector<vector<vector<vector<double>>>> d;


	for (int j = 0; j < 8; j++)
	{
		a.push_back(0);
	}
	for (int i = 0; i < 8; i++)
	{
		b.push_back(a);
	}

	for (int i = 0; i < 32; i++)
	{
		c.push_back(b);
	}
	for (int i = 0; i < numberdata; i++)
	{
		arr.push_back(c);
	}

}

void makearr_6488_4(vector<vector<vector<vector<double>>>> &arr)
{
	vector<double> a;
	vector<vector<double>> b;
	vector<vector<vector<double>>> c;
	vector<vector<vector<vector<double>>>> d;


	for (int j = 0; j < 8; j++)
	{
		a.push_back(0);
	}
	for (int i = 0; i < 8; i++)
	{
		b.push_back(a);
	}

	for (int i = 0; i < 64; i++)
	{
		c.push_back(b);
	}
	for (int i = 0; i < numberdata; i++)
	{
		arr.push_back(c);
	}

}


void makearr_512_4(vector<vector<double>> &arr)
{
	vector<double> a;
	vector<vector<double>> b;
	vector<vector<vector<double>>> c;
	vector<vector<vector<vector<double>>>> d;


	for (int j = 0; j < 512; j++)
	{
		a.push_back(0);
	}
	for (int i = 0; i < numberdata; i++)
	{
		arr.push_back(a);
	}

}


void makearr_10_4(vector<vector<double>> &arr)
{
	vector<double> a;
	vector<vector<double>> b;
	vector<vector<vector<double>>> c;
	vector<vector<vector<vector<double>>>> d;


	for (int j = 0; j < 10; j++)
	{
		a.push_back(0);
	}
	for (int i = 0; i < numberdata; i++)
	{
		arr.push_back(a);
	}

}

void make2dvec(vector<vector<double>> &arr)
{
	vector<double> a;
	vector<vector<double>> b;

	for (int j = 0; j < 10; j++)
	{
		a.push_back(0);
	}
	for (int i = 0; i < numberdata; i++)
	{
		arr.push_back(a);
	}
}