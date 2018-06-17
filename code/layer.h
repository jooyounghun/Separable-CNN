#pragma once
#include <time.h>
#include <stdlib.h>
#include <iostream>
#include "weight_parser.h"
#include "cifar10_reader.hpp"

using namespace std;



#define numberdata 1

double input_arr1[3][34][34];
double input_arr1_4[numberdata][3][34][34];
double onedimension_arr[numberdata][1024];



//
//double**** W1filter;
//
//double**** W2filter;
//
//double**** W3filter;
//
//double**** W4filter;
//
//double**** W5filter;
//
//double** W6filter;
//
//double** W7filter;

vector<vector<vector<vector<double>>>> W1filter;
vector<vector<vector<vector<double>>>> W2filter;
vector<vector<vector<vector<double>>>> W3filter;
vector<vector<vector<vector<double>>>> W4filter;
vector<vector<vector<vector<double>>>> W5filter;
vector<vector<double>> W6filter;
vector<vector<double>> W7filter;



class layer {
private:
	weight_parser wp;
	
	
	

public:

	layer()
	{
		/*W1filter = new double***[32];
		W2filter = new double***[32];
		W3filter = new double***[32];
		W4filter = new double***[64];
		W5filter = new double***[64];
		W6filter = new double*[1024];
		W7filter = new double*[512];*/

		
		makew1(W1filter);
		
		makew2(W2filter);
		
		makew3(W3filter);
		
		makew4(W4filter);
		
		makew5(W5filter);
		
		makew6(W6filter);
		
		makew7(W7filter);


	/*	make_array_four(W1filter, 32, 3, 3, 3);
		make_array_four(W2filter, 32, 32, 1, 1);
		make_array_four(W3filter, 32, 1, 3, 3);
		make_array_four(W4filter, 64, 32, 1, 1);
		make_array_four(W5filter, 64, 1, 3, 3);
		make_array_2d(W6filter, 1024, 512);
		make_array_2d(W7filter, 512, 10);*/

		wp.w1parser(W1filter);
		wp.w2parser(W2filter);
		wp.w3parser(W3filter);
		wp.w4parser(W4filter);
		wp.w5parser(W5filter);
		wp.w6parser(W6filter);
		wp.w7parser(W7filter);

		/*wp.w1(W1filter);
		wp.w2(W2filter);
		wp.w3(W3filter);
		wp.w4(W4filter);
		wp.w5(W5filter);
		wp.w6(W6filter);
		wp.w7(W7filter);*/



	}

/*
	void im2col(vector<vector<vector<vector<double>>>> arr, int filter_h, int filter_w, int stride, int pad)
	{
		int n = arr.size();
		int c = arr[0].size();
		int h = arr[0][0].size();
		int w = arr[0][0][0].size();

		int out_h = h + 2 * 1 - filter_h / 1 + 1;
		int out_w = w + 2 * 1 - filter_w / 1 + 1;
		vector<vector<vector<vector<double>>>> input_arr1;
		makearr(input_arr1);
		for (int k = 0; k < 10000; k++)
		{
			for (int j = 0; j < 3; j++)
			{
				for (int i = 0; i < 34; i++)
				{
					input_arr1[k][j][0][i] = 0;
					input_arr1[k][j][i][0] = 0;
					input_arr1[k][j][i][33] = 0;
					input_arr1[k][j][33][i] = 0;
				}
			}
		}

		vector<vector<vector<vector<double>>>> input_arr2;
		makearr(input_arr2);

		int *y_max = new int[filter_h];
		int *x_max = new int[filter_w];

		for (int i = 0; i < filter_h; i++)
		{
			y_max[i] = i + 1 * out_h;
			for (int j = 0; j < filter_w; j++)
			{
				x_max[j];
			}
		}

	}

	void noconv(vector<vector<vector<vector<double>>>> arr, vector<vector<vector<vector<double>>>> out)
	{
		int out_h = 1 + int((arr[0][0].size() + 2 * 2 - W1filter[0][0].size()) / 1);
		int out_w = 1 + int((arr[0][0][0].size() + 2 * 2 - W1filter[0][0][0].size()) / 1);
		



	}
*/


	/*
	@brief	normal convolution layer, filter size is made up as 3*3*3, 32 times
	@pre	dataset is made up as 3*32*32 / 1 image.
	@post	output is made up as 32*32*32
	*/
	void normal_convolution(vector<vector<vector<double>>> arr, vector<vector<vector<double>>> &out)
	{
		//srand(time(NULL));


		// 1. padding step for parameter.
		

		for (int j = 0; j < 3; j++)
		{
			for (int i = 0; i < 34; i++)
			{
				input_arr1[j][0][i] = 0;
				input_arr1[j][i][0] = 0;
				input_arr1[j][i][33] = 0;
				input_arr1[j][33][i] = 0;
			}
		}

		// 2. arr to input_arr by value

		for (int k = 0; k < 3; k++)
		{
			for (int i = 0; i < 32; i++)
			{
				for (int j = 0; j < 32; j++)
				{
					input_arr1[k][j + 1][i + 1] = arr[k][j][i];
				}
			}
		}

		

		//int filter[32][3][3][3];



		// 3.  Make filter through rand function.
		/*for (int number = 0; number < 32; number++)
		{
			for (int i = 0; i < 3; i++)
			{
				for (int j = 0; j < 3; j++)
				{
					for (int k = 0; k < 3; k++)
					{
						filter[number][i][j][k] = rand();
					}
				}
			}
		}*/

		
		// Produce feature map
		/*double*** featureMap;
		featureMap = new double**[32];
		

		make_array(featureMap, 32, 32, 32);*/

		double pointsum = 0;

		// 4. Matrix Multiple
		for (int number = 0; number < 32; number++)
		{
			for (int col = 0; col < 32; col++)
			{
				for (int row = 0; row < 32; row++)
				{

					// depth 0
					pointsum = pointsum + input_arr1[0][0 + col][0 + row] * W1filter[number][0][0][0];
					pointsum = pointsum + input_arr1[0][0 + col][1 + row] * W1filter[number][0][0][1];
					pointsum = pointsum + input_arr1[0][0 + col][2 + row] * W1filter[number][0][0][2];

					pointsum = pointsum + input_arr1[0][1 + col][0 + row] * W1filter[number][0][1][0];
					pointsum = pointsum + input_arr1[0][1 + col][1 + row] * W1filter[number][0][1][1];
					pointsum = pointsum + input_arr1[0][1 + col][2 + row] * W1filter[number][0][1][2];

					pointsum = pointsum + input_arr1[0][2 + col][0 + row] * W1filter[number][0][2][0];
					pointsum = pointsum + input_arr1[0][2 + col][1 + row] * W1filter[number][0][2][1];
					pointsum = pointsum + input_arr1[0][2 + col][2 + row] * W1filter[number][0][2][2];


					// depth 1

					pointsum = pointsum + input_arr1[1][0 + col][0 + row] * W1filter[number][1][0][0];
					pointsum = pointsum + input_arr1[1][0 + col][1 + row] * W1filter[number][1][0][1];
					pointsum = pointsum + input_arr1[1][0 + col][2 + row] * W1filter[number][1][0][2];

					pointsum = pointsum + input_arr1[1][1 + col][0 + row] * W1filter[number][1][1][0];
					pointsum = pointsum + input_arr1[1][1 + col][1 + row] * W1filter[number][1][1][1];
					pointsum = pointsum + input_arr1[1][1 + col][2 + row] * W1filter[number][1][1][2];

					pointsum = pointsum + input_arr1[1][2 + col][0 + row] * W1filter[number][1][2][0];
					pointsum = pointsum + input_arr1[1][2 + col][1 + row] * W1filter[number][1][2][1];
					pointsum = pointsum + input_arr1[1][2 + col][2 + row] * W1filter[number][1][2][2];


					// depth 2

					pointsum = pointsum + input_arr1[2][0 + col][0 + row] * W1filter[number][2][0][0];
					pointsum = pointsum + input_arr1[2][0 + col][1 + row] * W1filter[number][2][0][1];
					pointsum = pointsum + input_arr1[2][0 + col][2 + row] * W1filter[number][2][0][2];

					pointsum = pointsum + input_arr1[2][1 + col][0 + row] * W1filter[number][2][1][0];
					pointsum = pointsum + input_arr1[2][1 + col][1 + row] * W1filter[number][2][1][1];
					pointsum = pointsum + input_arr1[2][1 + col][2 + row] * W1filter[number][2][1][2];

					pointsum = pointsum + input_arr1[2][2 + col][0 + row] * W1filter[number][2][2][0];
					pointsum = pointsum + input_arr1[2][2 + col][1 + row] * W1filter[number][2][2][1];
					pointsum = pointsum + input_arr1[2][2 + col][2 + row] * W1filter[number][2][2][2];









					out[number][col][row] = pointsum;
					
					pointsum = 0;
				}
			}
		}

		

		// I have to pass 3 dimension array by return
	}


	void normal_convolution_4(vector<vector<vector<vector<double>>>> arr, vector<vector<vector<vector<double>>>> &out)
	{
		//srand(time(NULL));

	

		// 1. padding step for parameter.

		for (int a = 0; a < numberdata; a++)
		{
			for (int j = 0; j < 3; j++)
			{
				for (int i = 0; i < 34; i++)
				{
					input_arr1_4[a][j][0][i] = 0;
					input_arr1_4[a][j][i][0] = 0;
					input_arr1_4[a][j][i][33] = 0;
					input_arr1_4[a][j][33][i] = 0;
				}
			}
		}

		// 2. arr to input_arr by value

		for (int h = 0; h < numberdata; h++)
		{
			for (int k = 0; k < 3; k++)
			{
				for (int i = 0; i < 32; i++)
				{
					for (int j = 0; j < 32; j++)
					{
						input_arr1_4[h][k][i + 1][j + 1] = arr[h][k][i][j];
					}
				}
			}
		}



		//int filter[32][3][3][3];



		// 3.  Make filter through rand function.
		/*for (int number = 0; number < 32; number++)
		{
		for (int i = 0; i < 3; i++)
		{
		for (int j = 0; j < 3; j++)
		{
		for (int k = 0; k < 3; k++)
		{
		filter[number][i][j][k] = rand();
		}
		}
		}
		}*/


		// Produce feature map
		/*double*** featureMap;
		featureMap = new double**[32];


		make_array(featureMap, 32, 32, 32);*/

		double pointsum = 0;

		// 4. Matrix Multiple
		for (int n = 0; n < numberdata; n++)
		{
			for (int number = 0; number < 32; number++)
			{
				for (int col = 0; col < 32; col++)
				{
					for (int row = 0; row < 32; row++)
					{

						// depth 0
						pointsum = pointsum + input_arr1_4[n][0][0 + col][0 + row] * W1filter[number][0][0][0];
						pointsum = pointsum + input_arr1_4[n][0][0 + col][1 + row] * W1filter[number][0][0][1];
						pointsum = pointsum + input_arr1_4[n][0][0 + col][2 + row] * W1filter[number][0][0][2];

						pointsum = pointsum + input_arr1_4[n][0][1 + col][0 + row] * W1filter[number][0][1][0];
						pointsum = pointsum + input_arr1_4[n][0][1 + col][1 + row] * W1filter[number][0][1][1];
						pointsum = pointsum + input_arr1_4[n][0][1 + col][2 + row] * W1filter[number][0][1][2];

						pointsum = pointsum + input_arr1_4[n][0][2 + col][0 + row] * W1filter[number][0][2][0];
						pointsum = pointsum + input_arr1_4[n][0][2 + col][1 + row] * W1filter[number][0][2][1];
						pointsum = pointsum + input_arr1_4[n][0][2 + col][2 + row] * W1filter[number][0][2][2];


						// depth 1

						pointsum = pointsum + input_arr1_4[n][1][0 + col][0 + row] * W1filter[number][1][0][0];
						pointsum = pointsum + input_arr1_4[n][1][0 + col][1 + row] * W1filter[number][1][0][1];
						pointsum = pointsum + input_arr1_4[n][1][0 + col][2 + row] * W1filter[number][1][0][2];

						pointsum = pointsum + input_arr1_4[n][1][1 + col][0 + row] * W1filter[number][1][1][0];
						pointsum = pointsum + input_arr1_4[n][1][1 + col][1 + row] * W1filter[number][1][1][1];
						pointsum = pointsum + input_arr1_4[n][1][1 + col][2 + row] * W1filter[number][1][1][2];

						pointsum = pointsum + input_arr1_4[n][1][2 + col][0 + row] * W1filter[number][1][2][0];
						pointsum = pointsum + input_arr1_4[n][1][2 + col][1 + row] * W1filter[number][1][2][1];
						pointsum = pointsum + input_arr1_4[n][1][2 + col][2 + row] * W1filter[number][1][2][2];


						// depth 2

						pointsum = pointsum + input_arr1_4[n][2][0 + col][0 + row] * W1filter[number][2][0][0];
						pointsum = pointsum + input_arr1_4[n][2][0 + col][1 + row] * W1filter[number][2][0][1];
						pointsum = pointsum + input_arr1_4[n][2][0 + col][2 + row] * W1filter[number][2][0][2];

						pointsum = pointsum + input_arr1_4[n][2][1 + col][0 + row] * W1filter[number][2][1][0];
						pointsum = pointsum + input_arr1_4[n][2][1 + col][1 + row] * W1filter[number][2][1][1];
						pointsum = pointsum + input_arr1_4[n][2][1 + col][2 + row] * W1filter[number][2][1][2];

						pointsum = pointsum + input_arr1_4[n][2][2 + col][0 + row] * W1filter[number][2][2][0];
						pointsum = pointsum + input_arr1_4[n][2][2 + col][1 + row] * W1filter[number][2][2][1];
						pointsum = pointsum + input_arr1_4[n][2][2 + col][2 + row] * W1filter[number][2][2][2];









						out[n][number][col][row] = pointsum;

						pointsum = 0;
					}

				}
			}
		}



		// I have to pass 3 dimension array by return
	}

	



	/*
	@brief	light normalization
	*/
	void Lnormalization(vector<vector<vector<double>>> arr, vector<vector<vector<double>>> &out)
	{
		vector<vector<vector<double>>> temp;
		makeLN323232(temp);

		vector<vector<vector<double>>> temp1;
		makeLN323232(temp1);

		for (int h = 0; h < 32; h++)
		{
			for (int j = 0; j < 32; j++)
			{
				for (int i = 0; i < 32; i++)
				{
					temp[j][i][h] = arr[h][j][i];
				}
			}
		}



		double sum_for_mean = 0;
		

		double sum_for_meanarr[32];

		for (int k = 0; k < 32; k++)
		{
			for (int i = 0; i < 32; i++)
			{
				for (int j = 0; j < 32; j++)
				{
					sum_for_mean = sum_for_mean + temp[i][j][k];
				}

			}

			sum_for_meanarr[k] = sum_for_mean;
			sum_for_mean = 0;
		}

		double mean1[32];
		for (int i = 0; i < 32; i++)
		{

			mean1[i] = sum_for_meanarr[i] / 1024;
		}


		for (int k = 0; k < 32; k++)
		{
			for (int i = 0; i < 32; i++)
			{
				for (int j = 0; j < 32; j++)
				{
					temp[i][j][k] = temp[i][j][k] - mean1[k];
				}

			}

		}


		for (int k = 0; k < 32; k++)
		{
			for (int i = 0; i < 32; i++)
			{
				for (int j = 0; j < 32; j++)
				{
					temp1[i][j][k] = temp[i][j][k] * temp[i][j][k];
				}

			}

		}

		double var_for_mean=0;
		double var_for_meanarr[32];

		for (int k = 0; k < 32; k++)
		{
			for (int i = 0; i < 32; i++)
			{
				for (int j = 0; j < 32; j++)
				{
					var_for_mean = var_for_mean + temp1[i][j][k];
				}

			}

			var_for_meanarr[k] = var_for_mean;
			var_for_mean = 0;
		}

		double varmean1[32];
		for (int i = 0; i < 32; i++)
		{

			varmean1[i] = var_for_meanarr[i] / 1024;
		}

		for (int i = 0; i < 32; i++)
		{

			varmean1[i] = sqrt(varmean1[i]+10e-7);
		}


		for (int k = 0; k < 32; k++)
		{
			for (int i = 0; i < 32; i++)
			{
				for (int j = 0; j < 32; j++)
				{
					temp[i][j][k] = temp[i][j][k]/varmean1[k];
				}

			}

		}

		for (int h = 0; h < 32; h++)
		{
			for (int j = 0; j < 32; j++)
			{
				for (int i = 0; i < 32; i++)
				{
					out[i][h][j] = temp[h][j][i];
				}
			}
		}




/*

		double mean = sum_for_mean;


		

		double sum_for_variance = 0;

		for (int i = 0; i < 32; i++)
		{
			for (int j = 0; j < 32; j++)
			{
				for (int k = 0; k < 32; k++)
				{
					sum_for_variance = sum_for_variance + (out[i][j][k] - mean) * (out[i][j][k] - mean);
				}
			}
		}

		double variance = sum_for_variance / 32768;

		for (int i = 0; i < 32; i++)
		{
			for (int j = 0; j < 32; j++)
			{
				for (int k = 0; k < 32; k++)
				{
					out[i][j][k] = ((out[i][j][k] - mean) / sqrt(variance));
				}
			}
		}

*/

	}


	void Lnormalization_4(vector<vector<vector<vector<double>>>> arr, vector<vector<vector<vector<double>>>> &out)
	{
		vector<vector<vector<vector<double>>>> temp;
		makearr(temp);

		vector<vector<vector<vector<double>>>> temp1;
		makearr(temp1);

		

		for (int a = 0; a < numberdata; a++)
		{
			for (int h = 0; h < 32; h++)
			{
				for (int j = 0; j < 32; j++)
				{
					for (int i = 0; i < 32; i++)
					{
						temp[a][j][i][h] = arr[a][h][j][i];
					}
				}
			}
		}



		double sum_for_mean = 0;

		
		double sum_for_meanarr[32];


		for (int k = 0; k < 32; k++)
		{
			for (int a = 0; a < numberdata; a++)
			{
				for (int i = 0; i < 32; i++)
				{
					for (int j = 0; j < 32; j++)
					{
						sum_for_mean = sum_for_mean + temp[a][i][j][k];
					}
					
				}
				
			}
			sum_for_meanarr[k] = sum_for_mean / (32*32*numberdata);
			sum_for_mean = 0;
		}


		for (int k = 0; k < 32; k++)
		{
			for (int a = 0; a < numberdata; a++)
			{
				for (int i = 0; i < 32; i++)
				{
					for (int j = 0; j < 32; j++)
					{
						temp[a][i][j][k] = temp[a][i][j][k] - sum_for_meanarr[k];
					}

				}

			}
		}



		double sum_for_mean2 = 0;


		double sum_for_meanarr2[32];



		for (int k = 0; k < 32; k++)
		{
			for (int a = 0; a < numberdata; a++)
			{
				for (int i = 0; i < 32; i++)
				{
					for (int j = 0; j < 32; j++)
					{
						sum_for_mean2 = sum_for_mean2 + (temp[a][i][j][k]* temp[a][i][j][k]);
					}
					
				}

			}
			sum_for_meanarr2[k] = sum_for_mean2 / (32*32* numberdata);
			sum_for_mean2 = 0;
		}



		for (int i = 0; i < 32; i++)
		{
			sum_for_meanarr2[i] = sqrt(sum_for_meanarr2[i] + 10e-7);
		}



		for (int k = 0; k < 32; k++)
		{
			for (int a = 0; a < numberdata; a++)
			{
				for (int i = 0; i < 32; i++)
				{
					for (int j = 0; j < 32; j++)
					{
						temp[a][i][j][k] = temp[a][i][j][k] / sum_for_meanarr2[k];
					}

				}

			}
		}





		for (int a = 0; a < numberdata; a++)
		{
			for (int h = 0; h < 32; h++)
			{
				for (int j = 0; j < 32; j++)
				{
					for (int i = 0; i < 32; i++)
					{
						out[a][i][h][j] = temp[a][h][j][i];
					}
				}
			}
		}


		


		/*

		double mean = sum_for_mean;




		double sum_for_variance = 0;

		for (int i = 0; i < 32; i++)
		{
		for (int j = 0; j < 32; j++)
		{
		for (int k = 0; k < 32; k++)
		{
		sum_for_variance = sum_for_variance + (out[i][j][k] - mean) * (out[i][j][k] - mean);
		}
		}
		}

		double variance = sum_for_variance / 32768;

		for (int i = 0; i < 32; i++)
		{
		for (int j = 0; j < 32; j++)
		{
		for (int k = 0; k < 32; k++)
		{
		out[i][j][k] = ((out[i][j][k] - mean) / sqrt(variance));
		}
		}
		}

		*/

	}



	void Lnormalization1(vector<vector<vector<double>>> arr, vector<vector<vector<double>>> &out)
	{
		vector<vector<vector<double>>> temp;
		makeLN323232(temp);

		vector<vector<vector<double>>> temp1;
		makeLN323232(temp1);

		for (int h = 0; h < 32; h++)
		{
			for (int j = 0; j < 16; j++)
			{
				for (int i = 0; i < 16; i++)
				{
					temp[j][i][h] = arr[h][j][i];
				}
			}
		}



		double sum_for_mean = 0;


		double sum_for_meanarr[32];

		for (int k = 0; k < 32; k++)
		{
			for (int i = 0; i < 16; i++)
			{
				for (int j = 0; j < 16; j++)
				{
					sum_for_mean = sum_for_mean + temp[i][j][k];
				}

			}

			sum_for_meanarr[k] = sum_for_mean;
			sum_for_mean = 0;
		}

		double mean1[32];
		for (int i = 0; i < 32; i++)
		{

			mean1[i] = sum_for_meanarr[i] / 256;
		}


		for (int k = 0; k < 32; k++)
		{
			for (int i = 0; i < 16; i++)
			{
				for (int j = 0; j < 16; j++)
				{
					temp[i][j][k] = temp[i][j][k] - mean1[k];
				}

			}

		}


		for (int k = 0; k < 32; k++)
		{
			for (int i = 0; i < 16; i++)
			{
				for (int j = 0; j < 16; j++)
				{
					temp1[i][j][k] = temp[i][j][k] * temp[i][j][k];
				}

			}

		}

		double var_for_mean = 0;
		double var_for_meanarr[32];

		for (int k = 0; k < 32; k++)
		{
			for (int i = 0; i < 16; i++)
			{
				for (int j = 0; j < 16; j++)
				{
					var_for_mean = var_for_mean + temp1[i][j][k];
				}

			}

			var_for_meanarr[k] = var_for_mean;
			var_for_mean = 0;
		}

		double varmean1[32];
		for (int i = 0; i < 32; i++)
		{

			varmean1[i] = var_for_meanarr[i] / 256;
		}

		for (int i = 0; i < 32; i++)
		{

			varmean1[i] = sqrt(varmean1[i] + 10e-7);
		}


		for (int k = 0; k < 32; k++)
		{
			for (int i = 0; i < 16; i++)
			{
				for (int j = 0; j < 16; j++)
				{
					temp[i][j][k] = temp[i][j][k] / varmean1[k];
				}

			}

		}

		for (int h = 0; h < 32; h++)
		{
			for (int j = 0; j < 16; j++)
			{
				for (int i = 0; i < 16; i++)
				{
					out[h][j][i] = temp[j][i][h];
				}
			}
		}




		/*

		double mean = sum_for_mean;




		double sum_for_variance = 0;

		for (int i = 0; i < 32; i++)
		{
		for (int j = 0; j < 32; j++)
		{
		for (int k = 0; k < 32; k++)
		{
		sum_for_variance = sum_for_variance + (out[i][j][k] - mean) * (out[i][j][k] - mean);
		}
		}
		}

		double variance = sum_for_variance / 32768;

		for (int i = 0; i < 32; i++)
		{
		for (int j = 0; j < 32; j++)
		{
		for (int k = 0; k < 32; k++)
		{
		out[i][j][k] = ((out[i][j][k] - mean) / sqrt(variance));
		}
		}
		}

		*/

	}

	void Lnormalization1_4(vector<vector<vector<vector<double>>>> arr, vector<vector<vector<vector<double>>>> &out)
	{
		vector<vector<vector<vector<double>>>> temp;
		makearr(temp);

		vector<vector<vector<vector<double>>>> temp1;
		makearr(temp1);

		for (int a = 0; a < numberdata; a++)
		{
			for (int h = 0; h < 32; h++)
			{
				for (int j = 0; j < 16; j++)
				{
					for (int i = 0; i < 16; i++)
					{
						temp[a][j][i][h] = arr[a][h][j][i];
					}
				}
			}
		}



		double sum_for_mean = 0;


		double sum_for_meanarr[32];


		for (int k = 0; k < 32; k++)
		{
			for (int a = 0; a < numberdata; a++)
			{
				for (int i = 0; i < 16; i++)
				{
					for (int j = 0; j < 16; j++)
					{
						sum_for_mean = sum_for_mean + temp[a][i][j][k];
					}

				}

			}
			sum_for_meanarr[k] = sum_for_mean / (16 * 16 * numberdata);
			sum_for_mean = 0;
		}


		for (int k = 0; k < 32; k++)
		{
			for (int a = 0; a < numberdata; a++)
			{
				for (int i = 0; i < 16; i++)
				{
					for (int j = 0; j < 16; j++)
					{
						temp[a][i][j][k] = temp[a][i][j][k] - sum_for_meanarr[k];
					}

				}

			}
		}



		double sum_for_mean2 = 0;


		double sum_for_meanarr2[32];



		for (int k = 0; k < 32; k++)
		{
			for (int a = 0; a < numberdata; a++)
			{
				for (int i = 0; i < 16; i++)
				{
					for (int j = 0; j < 16; j++)
					{
						sum_for_mean2 = sum_for_mean2 + (temp[a][i][j][k] * temp[a][i][j][k]);
					}

				}

			}
			sum_for_meanarr2[k] = sum_for_mean2 / (16 * 16 * numberdata);
			sum_for_mean2 = 0;
		}



		for (int i = 0; i < 32; i++)
		{
			sum_for_meanarr2[i] = sqrt(sum_for_meanarr2[i] + 10e-7);
		}



		for (int k = 0; k < 32; k++)
		{
			for (int a = 0; a < numberdata; a++)
			{
				for (int i = 0; i < 16; i++)
				{
					for (int j = 0; j < 16; j++)
					{
						temp[a][i][j][k] = temp[a][i][j][k] / sum_for_meanarr2[k];
					}

				}

			}
		}





		for (int a = 0; a < numberdata; a++)
		{
			for (int h = 0; h < 16; h++)
			{
				for (int j = 0; j < 16; j++)
				{
					for (int i = 0; i < 32; i++)
					{
						out[a][i][h][j] = temp[a][h][j][i];
					}
				}
			}
		}



	}




	/*
	@brief	normalization layer
	@pre	input is made up as 32*32*32
	@post	output size is same to input
	*/
	void normalization(vector<vector<vector<double>>> arr, vector<vector<vector<double>>> &out)
	{
		double sum_for_mean =0;
		for (int i = 0; i < 32; i++)
		{
			for (int j = 0; j < 32; j++)
			{
				for (int k = 0; k < 32; k++)
				{
					sum_for_mean = sum_for_mean + arr[i][j][k];
				}
			}
		}

		double mean = sum_for_mean / 32768;


		double sum_for_variance = 0;

		for (int i = 0; i < 32; i++)
		{
			for (int j = 0; j < 32; j++)
			{
				for (int k = 0; k < 32; k++)
				{
					sum_for_variance = sum_for_variance +(arr[i][j][k] - mean) * (arr[i][j][k] - mean);
				}
			}
		}

		double variance = sum_for_variance / 32768;

		for (int i = 0; i < 32; i++)
		{
			for (int j = 0; j < 32; j++)
			{
				for (int k = 0; k < 32; k++)
				{
					out[i][j][k] = ((arr[i][j][k] - mean) / sqrt(variance));
				}
			}
		}
		
	}

	/*
	@brief	normalization layer
	@pre	input is made up as 32*16*16
	@post	output size is same to input
	*/
	void normalization1(vector<vector<vector<double>>> arr, vector<vector<vector<double>>> &out)
	{
		double sum_for_mean = 0;
		for (int i = 0; i < 32; i++)
		{
			for (int j = 0; j < 16; j++)
			{
				for (int k = 0; k < 16; k++)
				{
					sum_for_mean = sum_for_mean + arr[i][j][k];
				}
			}
		}

		double mean = sum_for_mean / 8192;

		double sum_for_variance = 0;

		for (int i = 0; i < 32; i++)
		{
			for (int j = 0; j < 16; j++)
			{
				for (int k = 0; k < 16; k++)
				{
					sum_for_variance = sum_for_variance + (arr[i][j][k] - mean) * (arr[i][j][k] - mean);
				}
			}
		}

		double variance = sum_for_variance / 8192;

		for (int i = 0; i < 32; i++)
		{
			for (int j = 0; j < 16; j++)
			{
				for (int k = 0; k < 16; k++)
				{
					out[i][j][k] = ((arr[i][j][k] - mean) / sqrt(variance));
				}
			}
		}
	}

	/*
	@brief	normalization layer
	@pre	input is made up as 64*8*8
	@post	output size is same to input
	*/
	void normalization2(vector<vector<vector<double>>> arr, vector<vector<vector<double>>> &out)
	{
		double sum_for_mean = 0;
		for (int i = 0; i <64; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				for (int k = 0; k < 8; k++)
				{
					sum_for_mean = sum_for_mean + arr[i][j][k];
				}
			}
		}

		double mean = sum_for_mean / 4096;

		double sum_for_variance = 0;

		for (int i = 0; i < 64; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				for (int k = 0; k < 8; k++)
				{
					sum_for_variance = sum_for_variance + (arr[i][j][k] - mean) * (arr[i][j][k] - mean);
				}
			}
		}

		double variance = sum_for_variance / 4096;

		for (int i = 0; i < 64; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				for (int k = 0; k < 8; k++)
				{
					out[i][j][k] = ((arr[i][j][k] - mean) / sqrt(variance));
				}
			}
		}
	}


	void Lnormalization2(vector<vector<vector<double>>> arr, vector<vector<vector<double>>> &out)
	{
		vector<vector<vector<double>>> temp;
		makeLN646464(temp);

		vector<vector<vector<double>>> temp1;
		makeLN646464(temp1);

		for (int h = 0; h < 64; h++)
		{
			for (int j = 0; j < 8; j++)
			{
				for (int i = 0; i < 8; i++)
				{
					temp[j][i][h] = arr[h][j][i];
				}
			}
		}



		double sum_for_mean = 0;


		double sum_for_meanarr[64];

		for (int k = 0; k < 64; k++)
		{
			for (int i = 0; i < 8; i++)
			{
				for (int j = 0; j < 8; j++)
				{
					sum_for_mean = sum_for_mean + temp[i][j][k];
				}

			}

			sum_for_meanarr[k] = sum_for_mean;
			sum_for_mean = 0;
		}

		double mean1[64];
		for (int i = 0; i < 64; i++)
		{

			mean1[i] = sum_for_meanarr[i] / 64;
		}


		for (int k = 0; k < 64; k++)
		{
			for (int i = 0; i < 8; i++)
			{
				for (int j = 0; j < 8; j++)
				{
					temp[i][j][k] = temp[i][j][k] - mean1[k];
				}

			}

		}


		for (int k = 0; k < 64; k++)
		{
			for (int i = 0; i < 8; i++)
			{
				for (int j = 0; j < 8; j++)
				{
					temp1[i][j][k] = temp[i][j][k] * temp[i][j][k];
				}

			}

		}

		double var_for_mean = 0;
		double var_for_meanarr[64];

		for (int k = 0; k < 64; k++)
		{
			for (int i = 0; i < 8; i++)
			{
				for (int j = 0; j < 8; j++)
				{
					var_for_mean = var_for_mean + temp1[i][j][k];
				}

			}

			var_for_meanarr[k] = var_for_mean;
			var_for_mean = 0;
		}

		double varmean1[64];
		for (int i = 0; i < 64; i++)
		{

			varmean1[i] = var_for_meanarr[i] / 64;
		}

		for (int i = 0; i < 64; i++)
		{

			varmean1[i] = sqrt(varmean1[i] + 10e-7);
		}


		for (int k = 0; k < 64; k++)
		{
			for (int i = 0; i < 8; i++)
			{
				for (int j = 0; j < 8; j++)
				{
					temp[i][j][k] = temp[i][j][k] / varmean1[k];
				}

			}

		}

		for (int h = 0; h < 64; h++)
		{
			for (int j = 0; j < 8; j++)
			{
				for (int i = 0; i < 8; i++)
				{
					out[h][j][i] = temp[j][i][h];
				}
			}
		}




		/*

		double mean = sum_for_mean;




		double sum_for_variance = 0;

		for (int i = 0; i < 32; i++)
		{
		for (int j = 0; j < 32; j++)
		{
		for (int k = 0; k < 32; k++)
		{
		sum_for_variance = sum_for_variance + (out[i][j][k] - mean) * (out[i][j][k] - mean);
		}
		}
		}

		double variance = sum_for_variance / 32768;

		for (int i = 0; i < 32; i++)
		{
		for (int j = 0; j < 32; j++)
		{
		for (int k = 0; k < 32; k++)
		{
		out[i][j][k] = ((out[i][j][k] - mean) / sqrt(variance));
		}
		}
		}

		*/

	}


	void Lnormalization2_4(vector<vector<vector<vector<double>>>> arr, vector<vector<vector<vector<double>>>> &out)
	{
		vector<vector<vector<vector<double>>>> temp;
		makearr646464(temp);

		vector<vector<vector<vector<double>>>> temp1;
		makearr646464(temp1);

		for (int a = 0; a < numberdata; a++)
		{
			for (int h = 0; h < 64; h++)
			{
				for (int j = 0; j < 8; j++)
				{
					for (int i = 0; i < 8; i++)
					{
						temp[a][j][i][h] = arr[a][h][j][i];
					}
				}
			}
		}



		double sum_for_mean = 0;


		double sum_for_meanarr[64];


		for (int k = 0; k < 64; k++)
		{
			for (int a = 0; a < numberdata; a++)
			{
				for (int i = 0; i < 8; i++)
				{
					for (int j = 0; j < 8; j++)
					{
						sum_for_mean = sum_for_mean + temp[a][i][j][k];
					}

				}

			}
			sum_for_meanarr[k] = sum_for_mean / (8 * 8 * numberdata);
			sum_for_mean = 0;
		}


		for (int k = 0; k < 64; k++)
		{
			for (int a = 0; a < numberdata; a++)
			{
				for (int i = 0; i < 8; i++)
				{
					for (int j = 0; j < 8; j++)
					{
						temp[a][i][j][k] = temp[a][i][j][k] - sum_for_meanarr[k];
					}

				}

			}
		}



		double sum_for_mean2 = 0;


		double sum_for_meanarr2[64];



		for (int k = 0; k < 64; k++)
		{
			for (int a = 0; a < numberdata; a++)
			{
				for (int i = 0; i < 8; i++)
				{
					for (int j = 0; j < 8; j++)
					{
						sum_for_mean2 = sum_for_mean2 + (temp[a][i][j][k] * temp[a][i][j][k]);
					}

				}

			}
			sum_for_meanarr2[k] = sum_for_mean2 / (8 * 8 * numberdata);
			sum_for_mean2 = 0;
		}



		for (int i = 0; i < 64; i++)
		{
			sum_for_meanarr2[i] = sqrt(sum_for_meanarr2[i] + 10e-7);
		}



		for (int k = 0; k < 64; k++)
		{
			for (int a = 0; a < numberdata; a++)
			{
				for (int i = 0; i < 8; i++)
				{
					for (int j = 0; j < 8; j++)
					{
						temp[a][i][j][k] = temp[a][i][j][k] / sum_for_meanarr2[k];
					}

				}

			}
		}





		for (int a = 0; a < numberdata; a++)
		{
			for (int h = 0; h < 8; h++)
			{
				for (int j = 0; j < 8; j++)
				{
					for (int i = 0; i < 64; i++)
					{
						out[a][i][h][j] = temp[a][h][j][i];
					}
				}
			}
		}



	}



	void Lnormalization3(vector<double> arr, vector<double> &out)
	{
		vector<vector<vector<double>>> temp;
		makeLN512(temp);

		vector<vector<vector<double>>> temp1;
		makeLN512(temp1);

		vector<vector<vector<double>>> temp2;
		makeLN512(temp2);

		for (int i = 0; i < 512; i++)
		{
			temp[i][0][0] = arr[i];
		}

		for (int h = 0; h < 512; h++)
		{
			for (int j = 0; j < 1; j++)
			{
				for (int i = 0; i < 1; i++)
				{
					temp1[j][i][h] = temp[h][j][i];
				}
			}
		}




		double sum_for_mean = 0;


		double sum_for_meanarr[512];

		for (int k = 0; k < 512; k++)
		{
			for (int i = 0; i < 1; i++)
			{
				for (int j = 0; j < 1; j++)
				{
					sum_for_mean = sum_for_mean + temp1[i][j][k];
				}

			}

			sum_for_meanarr[k] = sum_for_mean;
			sum_for_mean = 0;
		}

		double mean1[512];
		for (int i = 0; i < 512; i++)
		{

			mean1[i] = sum_for_meanarr[i] / 1;
		}


		for (int k = 0; k < 512; k++)
		{
			for (int i = 0; i < 1; i++)
			{
				for (int j = 0; j < 1; j++)
				{
					temp1[i][j][k] = temp1[i][j][k] - mean1[k];
				}

			}

		}


		for (int k = 0; k < 512; k++)
		{
			for (int i = 0; i < 1; i++)
			{
				for (int j = 0; j < 1; j++)
				{
					temp2[i][j][k] = temp1[i][j][k] * temp1[i][j][k];
				}

			}

		}

		double var_for_mean = 0;
		double var_for_meanarr[512];

		for (int k = 0; k < 512; k++)
		{
			for (int i = 0; i < 1; i++)
			{
				for (int j = 0; j < 1; j++)
				{
					var_for_mean = var_for_mean + temp2[i][j][k];
				}

			}

			var_for_meanarr[k] = var_for_mean;
			var_for_mean = 0;
		}

		double varmean1[512];
		for (int i = 0; i < 512; i++)
		{

			varmean1[i] = var_for_meanarr[i] / 1;
		}

		for (int i = 0; i < 512; i++)
		{

			varmean1[i] = sqrt(varmean1[i] + 10e-7);
		}


		for (int k = 0; k < 512; k++)
		{
			for (int i = 0; i < 1; i++)
			{
				for (int j = 0; j < 1; j++)
				{
					temp1[i][j][k] = temp1[i][j][k] / varmean1[k];
				}

			}

		}

		for (int h = 0; h < 512; h++)
		{
			for (int j = 0; j < 1; j++)
			{
				for (int i = 0; i < 1; i++)
				{
					out[h] = temp1[j][i][h];
				}
			}
		}

		/*

		double mean = sum_for_mean;




		double sum_for_variance = 0;

		for (int i = 0; i < 32; i++)
		{
		for (int j = 0; j < 32; j++)
		{
		for (int k = 0; k < 32; k++)
		{
		sum_for_variance = sum_for_variance + (out[i][j][k] - mean) * (out[i][j][k] - mean);
		}
		}
		}

		double variance = sum_for_variance / 32768;

		for (int i = 0; i < 32; i++)
		{
		for (int j = 0; j < 32; j++)
		{
		for (int k = 0; k < 32; k++)
		{
		out[i][j][k] = ((out[i][j][k] - mean) / sqrt(variance));
		}
		}
		}

		*/

	}



	/*
	@brief	normalization layer
	@pre	input is made up as 512
	@post	output size is same to input
	*/
	void normalization3(vector<double> arr, vector<double> &out)
	{
		
		vector<vector<vector<double>>> temp;
		makeLN512(temp);


		double sum_for_mean = 0;
		for (int i = 0; i <512; i++)
		{
			sum_for_mean = sum_for_mean + arr[i];
		}

		double mean = sum_for_mean / 512;

		double sum_for_variance = 0;

		for (int i = 0; i < 512; i++)
		{
			sum_for_variance = sum_for_variance + (arr[i] - mean) * (arr[i] - mean);

		}

		double variance = sum_for_variance / 512;

		for (int i = 0; i < 512; i++)
		{
			out[i] = ((arr[i] - mean) / sqrt(variance));

		}
	}



	/*
	@brief	relu layer/ but I have to change by input matrix, as 32*32*32 case like this.
	*/
	void relu1(int depth, int col, int row, vector<vector<vector<double>>> arr, vector<vector<vector<double>>> &out)
	{
		for (int k = 0; k < depth; k++)
		{
			for (int i = 0; i < col; i++)
			{
				for (int j = 0; j < row; j++)
				{
					if (arr[k][i][j] < 0)
					{
						out[k][i][j] = 0;
					}
					else
					{
						out[k][i][j] = arr[k][i][j];
					}
				}
			}
		}

		

	}

	void relu1_4(int depth, int col, int row, vector<vector<vector<vector<double>>>> arr, vector<vector<vector<vector<double>>>> &out)
	{
		for (int n = 0; n < numberdata; n++)
		{
			for (int k = 0; k < depth; k++)
			{
				for (int i = 0; i < col; i++)
				{
					for (int j = 0; j < row; j++)
					{
						if (arr[n][k][i][j] < 0)
						{
							out[n][k][i][j] = 0;
						}
						else
						{
							out[n][k][i][j] = arr[n][k][i][j];
						}
					}
				}
			}
		}



	}




	/*
	@brief	relu layer/ but I have to change by input matrix, as 32*16*16 like this.
	*/
	void relu2(int depth, int col, int row, vector<vector<vector<double>>> arr, vector<vector<vector<double>>> &out)
	{
		for (int k = 0; k < depth; k++)
		{
			for (int i = 0; i < col; i++)
			{
				for (int j = 0; j < row; j++)
				{
					if (arr[k][i][j] < 0)
					{
						out[k][i][j] = 0;
					}
					else
					{
						out[k][i][j] = arr[k][i][j];
					}
				}
			}
		}
	}


	void relu2_4(int depth, int col, int row, vector<vector<vector<vector<double>>>> arr, vector<vector<vector<vector<double>>>> &out)
	{
		for (int n = 0; n < numberdata; n++)
		{
			for (int k = 0; k < depth; k++)
			{
				for (int i = 0; i < col; i++)
				{
					for (int j = 0; j < row; j++)
					{
						if (arr[n][k][i][j] < 0)
						{
							out[n][k][i][j] = 0;
						}
						else
						{
							out[n][k][i][j] = arr[n][k][i][j];
						}
					}
				}
			}
		}

	}


	/*
	@brief	relu layer/ but I have to change by input matrix, as 64*8*8 like this.
	*/
	void relu3(int depth, int col, int row, vector<vector<vector<double>>> arr, vector<vector<vector<double>>> &out)
	{
		for (int k = 0; k < depth; k++)
		{
			for (int i = 0; i < col; i++)
			{
				for (int j = 0; j < row; j++)
				{
					if (arr[k][i][j] < 0)
					{
						out[k][i][j] = 0;
					}
					else
					{
						out[k][i][j] = arr[k][i][j];
					}
				}
			}
		}

	}

	void relu3_4(int depth, int col, int row, vector<vector<vector<vector<double>>>> arr, vector<vector<vector<vector<double>>>> &out)
	{
		for (int n = 0; n < numberdata; n++)
		{
			for (int k = 0; k < depth; k++)
			{
				for (int i = 0; i < col; i++)
				{
					for (int j = 0; j < row; j++)
					{
						if (arr[n][k][i][j] < 0)
						{
							out[n][k][i][j] = 0;
						}
						else
						{
							out[n][k][i][j] = arr[n][k][i][j];
						}
					}
				}
			}
		}


	}



	/*
	@brief	relu layer/ but I have to change by input matrix, as 512 like this.
	*/
	void relu4(int depth, vector<double> arr, vector<double> &out)
	{
		for (int k = 0; k < depth; k++)
		{
			if (arr[k] < 0)
			{
				out[k] = 0;
			}
			else
			{
				out[k] = arr[k];
			}
		}

	}

	void relu4_4(int depth, vector<vector<double>> arr, vector<vector<double>> &out)
	{
		for (int n = 0; n < numberdata; n++)
		{
			for (int k = 0; k < depth; k++)
			{
				if (arr[n][k] < 0)
				{
					out[n][k] = 0;
				}
				else
				{
					out[n][k] = arr[n][k];
				}
			}
		}

	}



	/*
	@brief	pooling layer, filter size is made up as 2*2 / stride = 2
	@pre	input size is made up as 32*32*32
	@post	output size is made up as 32*16*16
	*/
	void pool(vector<vector<vector<double>>> arr, vector<vector<vector<double>>> &out)
	{

		/*double*** return_arr;
		return_arr = new double**[32];

		make_array(return_arr, 32, 16, 16);*/


		for (int depth = 0; depth < 32; depth++)
		{
			for (int col = 0; col < 16; col++)
			{
				for (int row = 0; row < 16; row++)
				{
					if (arr[depth][0 + (col * 2)][0 + (row * 2)] >= arr[depth][0 + (col * 2)][1 + (row * 2)] && arr[depth][0 + (col * 2)][0 + (row * 2)] >= arr[depth][1 + (col * 2)][0 + (row * 2)] && arr[depth][0 + (col * 2)][0 + (row * 2)] >= arr[depth][1 + (col * 2)][1 + (row * 2)])
						out[depth][0 + col][0 + row] = arr[depth][0 + (col * 2)][0 + (row * 2)];

					else if (arr[depth][0 + (col * 2)][1 + (row * 2)] >= arr[depth][0 + (col * 2)][0 + (row * 2)] && arr[depth][0 + (col * 2)][1 + (row * 2)] >= arr[depth][1 + (col * 2)][0 + (row * 2)] && arr[depth][0 + (col * 2)][1 + (row * 2)] >= arr[depth][1 + (col * 2)][1 + (row * 2)])
						out[depth][0 + col][0 + row] = arr[depth][0 + (col * 2)][1 + (row * 2)];

					else if (arr[depth][1 + (col * 2)][0 + (row * 2)] >= arr[depth][0 + (col * 2)][0 + (row * 2)] && arr[depth][1 + (col * 2)][0 + (row * 2)] >= arr[depth][0 + (col * 2)][1 + (row * 2)] && arr[depth][1 + (col * 2)][0 + (row * 2)] >= arr[depth][1 + (col * 2)][1 + (row * 2)])
						out[depth][0 + col][0 + row] = arr[depth][1 + (col * 2)][0 + (row * 2)];

					else if (arr[depth][1 + (col * 2)][1 + (row * 2)] >= arr[depth][0 + (col * 2)][0 + (row * 2)] && arr[depth][1 + (col * 2)][1 + (row * 2)] >= arr[depth][0 + (col * 2)][1 + (row * 2)] && arr[depth][1 + (col * 2)][1 + (row * 2)] >= arr[depth][1 + (col * 2)][0 + (row * 2)])
						out[depth][0 + col][0 + row] = arr[depth][1 + (col * 2)][1 + (row * 2)];
				}
			}
		
		}

		// I have to pass return 3 dimension array.
	}



	void pool_4(vector<vector<vector<vector<double>>>> arr, vector<vector<vector<vector<double>>>> &out)
	{

		/*double*** return_arr;
		return_arr = new double**[32];

		make_array(return_arr, 32, 16, 16);*/

		for (int n = 0; n < numberdata; n++)
		{
			for (int depth = 0; depth < 32; depth++)
			{
				for (int col = 0; col < 16; col++)
				{
					for (int row = 0; row < 16; row++)
					{
						if (arr[n][depth][0 + (col * 2)][0 + (row * 2)] >= arr[n][depth][0 + (col * 2)][1 + (row * 2)] && arr[n][depth][0 + (col * 2)][0 + (row * 2)] >= arr[n][depth][1 + (col * 2)][0 + (row * 2)] && arr[n][depth][0 + (col * 2)][0 + (row * 2)] >= arr[n][depth][1 + (col * 2)][1 + (row * 2)])
							out[n][depth][0 + col][0 + row] = arr[n][depth][0 + (col * 2)][0 + (row * 2)];

						else if (arr[n][depth][0 + (col * 2)][1 + (row * 2)] >= arr[n][depth][0 + (col * 2)][0 + (row * 2)] && arr[n][depth][0 + (col * 2)][1 + (row * 2)] >= arr[n][depth][1 + (col * 2)][0 + (row * 2)] && arr[n][depth][0 + (col * 2)][1 + (row * 2)] >= arr[n][depth][1 + (col * 2)][1 + (row * 2)])
							out[n][depth][0 + col][0 + row] = arr[n][depth][0 + (col * 2)][1 + (row * 2)];

						else if (arr[n][depth][1 + (col * 2)][0 + (row * 2)] >= arr[n][depth][0 + (col * 2)][0 + (row * 2)] && arr[n][depth][1 + (col * 2)][0 + (row * 2)] >= arr[n][depth][0 + (col * 2)][1 + (row * 2)] && arr[n][depth][1 + (col * 2)][0 + (row * 2)] >= arr[n][depth][1 + (col * 2)][1 + (row * 2)])
							out[n][depth][0 + col][0 + row] = arr[n][depth][1 + (col * 2)][0 + (row * 2)];

						else if (arr[n][depth][1 + (col * 2)][1 + (row * 2)] >= arr[n][depth][0 + (col * 2)][0 + (row * 2)] && arr[n][depth][1 + (col * 2)][1 + (row * 2)] >= arr[n][depth][0 + (col * 2)][1 + (row * 2)] && arr[n][depth][1 + (col * 2)][1 + (row * 2)] >= arr[n][depth][1 + (col * 2)][0 + (row * 2)])
							out[n][depth][0 + col][0 + row] = arr[n][depth][1 + (col * 2)][1 + (row * 2)];
					}
				}

			}
		}

		// I have to pass return 3 dimension array.
	}




	/*
	@brief	point wise convolution layer, filter size is made up as 32*32*1*1
	@pre	input size is made up as 32*16*16
	@post	output size is made up as 32*16*16
	*/
	void point_convolution(vector<vector<vector<double>>> arr, vector<vector<vector<double>>> &out)
	{
		//srand(time(NULL));

		//1. Make filter.
		//double**** filter = new double***[32];

		//make_array_four(filter, 32, 32, 1, 1);


		


		//for (int i = 0; i < 32; i++)
		//{
		//	// 'i' is  how many filter
		//	for (int j = 0; j < 32; j++)
		//	{
		//		// 'j' is filter depth.
		//		filter[j][i][0][0] = rand()%10;
		//	}
		//}



		/*double*** featureMap;
		featureMap = new double**[32];

		make_array(featureMap, 32, 16, 16);*/

		double pointsum = 0;

		//2. pointwise convolution.

		for (int number = 0; number < 32; number++)
		{
			
			for (int col = 0; col < 16; col++)
			{
				for (int row = 0; row < 16; row++)
				{
					for (int depth = 0; depth < 32; depth++)
					{
						pointsum = pointsum + arr[depth][col][row] * W2filter[number][depth][0][0];

						
					}
					out[number][col][row] = pointsum;
					pointsum = 0;
				}

			}
				
		}

		// I have to pass 3 array dimension return value

		
	}



	void point_convolution_4(vector<vector<vector<vector<double>>>> arr, vector<vector<vector<vector<double>>>> &out)
	{
		//srand(time(NULL));

		//1. Make filter.
		//double**** filter = new double***[32];

		//make_array_four(filter, 32, 32, 1, 1);





		//for (int i = 0; i < 32; i++)
		//{
		//	// 'i' is  how many filter
		//	for (int j = 0; j < 32; j++)
		//	{
		//		// 'j' is filter depth.
		//		filter[j][i][0][0] = rand()%10;
		//	}
		//}



		/*double*** featureMap;
		featureMap = new double**[32];

		make_array(featureMap, 32, 16, 16);*/

		double pointsum = 0;

		//2. pointwise convolution.

		for (int n = 0; n < numberdata; n++)
		{
			for (int number = 0; number < 32; number++)
			{

				for (int col = 0; col < 16; col++)
				{
					for (int row = 0; row < 16; row++)
					{
						for (int depth = 0; depth < 32; depth++)
						{
							pointsum = pointsum + arr[n][depth][col][row] * W2filter[number][depth][0][0];


						}
						out[n][number][col][row] = pointsum;
						pointsum = 0;
					}

				}

			}
		}

		// I have to pass 3 array dimension return value


	}



	/*
	@brief	depth wise convolution layer, filter size is made up as 3*3*1, 32(°³)
	@pre	input size is made up as 32*16*16
	@post	output size is made up as 32*16*16
	*/
	void depth_convolution(vector<vector<vector<double>>> arr, vector<vector<vector<double>>> &out)
	{
		//srand(time(NULL));
		// 1. make filter.
		//double**** filter = new double***[32];

		//make_array_four(filter, 32, 1, 3, 3);

		/*for (int number = 0; number < 32; number++)
		{
			for (int i = 0; i < 3; i++)
			{
				for (int j = 0; j < 3; j++)
				{
					filter[number][0][i][j] = rand()%10;
				}
			}
		}*/
		


		// 2. padding
		double input_arr[32][18][18];

		for (int j = 0; j < 32; j++)
		{
			for (int i = 0; i < 18; i++)
			{
				input_arr[j][0][i] = 0;
				input_arr[j][i][0] = 0;
				input_arr[j][i][17] = 0;
				input_arr[j][17][i] = 0;
			}
		}

		// 3. arr to input_arr by value

		for (int k = 0; k < 32; k++)
		{
			for (int i = 0; i < 16; i++)
			{
				for (int j = 0; j < 16; j++)
				{
					input_arr[k][j + 1][i + 1] = arr[k][j][i];
				}
			}
		}



		/*double*** featureMap;
		featureMap = new double**[32];

		make_array(featureMap, 32, 16, 16);*/

		double pointsum = 0;

		// 4. depthwise convolution
		for (int depth = 0; depth < 32; depth++)
		{
			for (int col = 0; col < 16; col++)
			{
				for (int row = 0; row < 16; row++)
				{
					// matrix mul.
					pointsum = pointsum + input_arr[depth][0 + col][0 + row] * W3filter[depth][0][0][0];
					pointsum = pointsum + input_arr[depth][0 + col][1 + row] * W3filter[depth][0][0][1];
					pointsum = pointsum + input_arr[depth][0 + col][2 + row] * W3filter[depth][0][0][2];

					pointsum = pointsum + input_arr[depth][1 + col][0 + row] * W3filter[depth][0][1][0];
					pointsum = pointsum + input_arr[depth][1 + col][1 + row] * W3filter[depth][0][1][1];
					pointsum = pointsum + input_arr[depth][1 + col][2 + row] * W3filter[depth][0][1][2];

					pointsum = pointsum + input_arr[depth][2 + col][0 + row] * W3filter[depth][0][2][0];
					pointsum = pointsum + input_arr[depth][2 + col][1 + row] * W3filter[depth][0][2][1];
					pointsum = pointsum + input_arr[depth][2 + col][2 + row] * W3filter[depth][0][2][2];


					
					out[depth][col][row] = pointsum;
					pointsum = 0;
				}
				
			}
		}

		// I have to pass 3 dimensional array by return.

	
	}


	void depth_convolution_4(vector<vector<vector<vector<double>>>> arr, vector<vector<vector<vector<double>>>> &out)
	{
		//srand(time(NULL));
		// 1. make filter.
		//double**** filter = new double***[32];

		//make_array_four(filter, 32, 1, 3, 3);

		/*for (int number = 0; number < 32; number++)
		{
		for (int i = 0; i < 3; i++)
		{
		for (int j = 0; j < 3; j++)
		{
		filter[number][0][i][j] = rand()%10;
		}
		}
		}*/



		// 2. padding
		double input_arr[numberdata][32][18][18];

		for (int n = 0; n < numberdata; n++)
		{
			for (int j = 0; j < 32; j++)
			{
				for (int i = 0; i < 18; i++)
				{
					input_arr[n][j][0][i] = 0;
					input_arr[n][j][i][0] = 0;
					input_arr[n][j][i][17] = 0;
					input_arr[n][j][17][i] = 0;
				}
			}
		}

		// 3. arr to input_arr by value

		for (int n = 0; n < numberdata; n++)
		{
			for (int k = 0; k < 32; k++)
			{
				for (int i = 0; i < 16; i++)
				{
					for (int j = 0; j < 16; j++)
					{
						input_arr[n][k][j + 1][i + 1] = arr[n][k][j][i];
					}
				}
			}
		}



		/*double*** featureMap;
		featureMap = new double**[32];

		make_array(featureMap, 32, 16, 16);*/

		double pointsum = 0;

		// 4. depthwise convolution
		for (int n = 0; n < numberdata; n++)
		{
			for (int depth = 0; depth < 32; depth++)
			{
				for (int col = 0; col < 16; col++)
				{
					for (int row = 0; row < 16; row++)
					{
						// matrix mul.
						pointsum = pointsum + input_arr[n][depth][0 + col][0 + row] * W3filter[depth][0][0][0];
						pointsum = pointsum + input_arr[n][depth][0 + col][1 + row] * W3filter[depth][0][0][1];
						pointsum = pointsum + input_arr[n][depth][0 + col][2 + row] * W3filter[depth][0][0][2];

						pointsum = pointsum + input_arr[n][depth][1 + col][0 + row] * W3filter[depth][0][1][0];
						pointsum = pointsum + input_arr[n][depth][1 + col][1 + row] * W3filter[depth][0][1][1];
						pointsum = pointsum + input_arr[n][depth][1 + col][2 + row] * W3filter[depth][0][1][2];

						pointsum = pointsum + input_arr[n][depth][2 + col][0 + row] * W3filter[depth][0][2][0];
						pointsum = pointsum + input_arr[n][depth][2 + col][1 + row] * W3filter[depth][0][2][1];
						pointsum = pointsum + input_arr[n][depth][2 + col][2 + row] * W3filter[depth][0][2][2];



						out[n][depth][col][row] = pointsum;
						pointsum = 0;
					}

				}
			}
		}

		// I have to pass 3 dimensional array by return.


	}



	/*
	@brief	pooling layer, filter size is made up as 2*2 / stirde = 2
	@pre	input size is made up as 32*16*16
	@post	output size is made up as 32*8*8
	*/
	void pool2(vector<vector<vector<double>>> arr, vector<vector<vector<double>>> &out)
	{

		/*double*** return_arr;
		return_arr = new double**[32];

		make_array(return_arr, 32, 8, 8);*/

		for (int depth = 0; depth < 32; depth++)
		{
			for (int col = 0; col < 8; col++)
			{
				for (int row = 0; row < 8; row++)
				{
					if (arr[depth][0 + (col * 2)][0 + (row * 2)] >= arr[depth][0 + (col * 2)][1 + (row * 2)] && arr[depth][0 + (col * 2)][0 + (row * 2)] >= arr[depth][1 + (col * 2)][0 + (row * 2)] && arr[depth][0 + (col * 2)][0 + (row * 2)] >= arr[depth][1 + (col * 2)][1 + (row * 2)])
						out[depth][0 + col][0 + row] = arr[depth][0 + (col * 2)][0 + (row * 2)];

					else if (arr[depth][0 + (col * 2)][1 + (row * 2)] >= arr[depth][0 + (col * 2)][0 + (row * 2)] && arr[depth][0 + (col * 2)][1 + (row * 2)] >= arr[depth][1 + (col * 2)][0 + (row * 2)] && arr[depth][0 + (col * 2)][1 + (row * 2)] >= arr[depth][1 + (col * 2)][1 + (row * 2)])
						out[depth][0 + col][0 + row] = arr[depth][0 + (col * 2)][1 + (row * 2)];

					else if (arr[depth][1 + (col * 2)][0 + (row * 2)] >= arr[depth][0 + (col * 2)][0 + (row * 2)] && arr[depth][1 + (col * 2)][0 + (row * 2)] >= arr[depth][0 + (col * 2)][1 + (row * 2)] && arr[depth][1 + (col * 2)][0 + (row * 2)] >= arr[depth][1 + (col * 2)][1 + (row * 2)])
						out[depth][0 + col][0 + row] = arr[depth][1 + (col * 2)][0 + (row * 2)];

					else if (arr[depth][1 + (col * 2)][1 + (row * 2)] >= arr[depth][0 + (col * 2)][0 + (row * 2)] && arr[depth][1 + (col * 2)][1 + (row * 2)] >= arr[depth][0 + (col * 2)][1 + (row * 2)] && arr[depth][1 + (col * 2)][1 + (row * 2)] >= arr[depth][1 + (col * 2)][0 + (row * 2)])
						out[depth][0 + col][0 + row] = arr[depth][1 + (col * 2)][1 + (row * 2)];
				}
			}
		}

	}


	void pool2_4(vector<vector<vector<vector<double>>>> arr, vector<vector<vector<vector<double>>>> &out)
	{

		/*double*** return_arr;
		return_arr = new double**[32];

		make_array(return_arr, 32, 8, 8);*/

		for (int n = 0; n < numberdata; n++)
		{
			for (int depth = 0; depth < 32; depth++)
			{
				for (int col = 0; col < 8; col++)
				{
					for (int row = 0; row < 8; row++)
					{
						if (arr[n][depth][0 + (col * 2)][0 + (row * 2)] >= arr[n][depth][0 + (col * 2)][1 + (row * 2)] && arr[n][depth][0 + (col * 2)][0 + (row * 2)] >= arr[n][depth][1 + (col * 2)][0 + (row * 2)] && arr[n][depth][0 + (col * 2)][0 + (row * 2)] >= arr[n][depth][1 + (col * 2)][1 + (row * 2)])
							out[n][depth][0 + col][0 + row] = arr[n][depth][0 + (col * 2)][0 + (row * 2)];

						else if (arr[n][depth][0 + (col * 2)][1 + (row * 2)] >= arr[n][depth][0 + (col * 2)][0 + (row * 2)] && arr[n][depth][0 + (col * 2)][1 + (row * 2)] >= arr[n][depth][1 + (col * 2)][0 + (row * 2)] && arr[n][depth][0 + (col * 2)][1 + (row * 2)] >= arr[n][depth][1 + (col * 2)][1 + (row * 2)])
							out[n][depth][0 + col][0 + row] = arr[n][depth][0 + (col * 2)][1 + (row * 2)];

						else if (arr[n][depth][1 + (col * 2)][0 + (row * 2)] >= arr[n][depth][0 + (col * 2)][0 + (row * 2)] && arr[n][depth][1 + (col * 2)][0 + (row * 2)] >= arr[n][depth][0 + (col * 2)][1 + (row * 2)] && arr[n][depth][1 + (col * 2)][0 + (row * 2)] >= arr[n][depth][1 + (col * 2)][1 + (row * 2)])
							out[n][depth][0 + col][0 + row] = arr[n][depth][1 + (col * 2)][0 + (row * 2)];

						else if (arr[n][depth][1 + (col * 2)][1 + (row * 2)] >= arr[n][depth][0 + (col * 2)][0 + (row * 2)] && arr[n][depth][1 + (col * 2)][1 + (row * 2)] >= arr[n][depth][0 + (col * 2)][1 + (row * 2)] && arr[n][depth][1 + (col * 2)][1 + (row * 2)] >= arr[n][depth][1 + (col * 2)][0 + (row * 2)])
							out[n][depth][0 + col][0 + row] = arr[n][depth][1 + (col * 2)][1 + (row * 2)];
					}
				}
			}
		}

	}



	/*
	@brief	point wise convolution layer, filter size is made up as 64*32*1*1
	@pre	input size is made up as 32*8*8
	@post	output size is made up as 64*8*8
	*/
	void point_convolution2(vector<vector<vector<double>>> arr, vector<vector<vector<double>>> &out)
	{
		//srand(time(NULL));

		//1. Make filter.
		//double filter[64][32][1][1];

		//for (int i = 0; i < 64; i++)
		//{
		//	// 'i' is  how many filter
		//	for (int j = 0; j < 32; j++)
		//	{
		//		// 'j' is filter depth.
		//		filter[i][j][0][0] = rand();
		//	}
		//}


		



		/*double*** featureMap;
		featureMap = new double**[64];

		make_array(featureMap, 64, 8, 8);*/

		double pointsum = 0;

		//2. pointwise convolution.
		for (int number = 0; number < 64; number++)
		{
			for (int col = 0; col < 8; col++)
			{
				for (int row = 0; row < 8; row++)
				{
					for (int depth = 0; depth < 32; depth++)
					{
						pointsum = pointsum + arr[depth][col][row] * W4filter[number][depth][0][0];
					}
					out[number][col][row] = pointsum;
					pointsum = 0;
				}
			}
		}

		// I have to pass 3 array dimension return value

	}


	void point_convolution2_4(vector<vector<vector<vector<double>>>> arr, vector<vector<vector<vector<double>>>> &out)
	{
		//srand(time(NULL));

		//1. Make filter.
		//double filter[64][32][1][1];

		//for (int i = 0; i < 64; i++)
		//{
		//	// 'i' is  how many filter
		//	for (int j = 0; j < 32; j++)
		//	{
		//		// 'j' is filter depth.
		//		filter[i][j][0][0] = rand();
		//	}
		//}






		/*double*** featureMap;
		featureMap = new double**[64];

		make_array(featureMap, 64, 8, 8);*/

		double pointsum = 0;

		//2. pointwise convolution.
		for (int n = 0; n < numberdata; n++)
		{
			for (int number = 0; number < 64; number++)
			{
				for (int col = 0; col < 8; col++)
				{
					for (int row = 0; row < 8; row++)
					{
						for (int depth = 0; depth < 32; depth++)
						{
							pointsum = pointsum + arr[n][depth][col][row] * W4filter[number][depth][0][0];
						}
						out[n][number][col][row] = pointsum;
						pointsum = 0;
					}
				}
			}
		}

		// I have to pass 3 array dimension return value

	}



	/*
	@brief	depth wise convolution layer, filter size is made up as 3*3*1, 64(°³)
	@pre	input size is made up as 64*8*8
	@post	output size is made up as 64*8*8
	*/
	void depth_convolution2(vector<vector<vector<double>>> arr, vector<vector<vector<double>>> &out)
	{
		//srand(time(NULL));
		// 1. make filter.
		/*double filter[64][1][3][3];

		for (int number = 0; number < 64; number++)
		{
			for (int i = 0; i < 3; i++)
			{
				for (int j = 0; j < 3; j++)
				{
					filter[number][0][i][j] = rand()%10;
				}
			}
		}*/


		


		// 2. padding

		double input_arr[64][10][10];

		for (int j = 0; j < 64; j++)
		{
			for (int i = 0; i < 10; i++)
			{
				input_arr[j][0][i] = 0;
				input_arr[j][i][0] = 0;
				input_arr[j][i][9] = 0;
				input_arr[j][9][i] = 0;
			}
		}

		// 3. arr to input_arr by value

		for (int k = 0; k < 64; k++)
		{
			for (int i = 0; i < 8; i++)
			{
				for (int j = 0; j < 8; j++)
				{
					input_arr[k][j + 1][i + 1] = arr[k][j][i];
				}
			}
		}



		/*double*** featureMap;
		featureMap = new double**[64];

		make_array(featureMap, 64, 8, 8);*/

		double pointsum = 0;


		// 4. depthwise convolution
		for (int depth = 0; depth < 64; depth++)
		{
			for (int col = 0; col < 8; col++)
			{
				for (int row = 0; row < 8; row++)
				{
					// matrix mul.
					pointsum = pointsum + input_arr[depth][0 + col][0 + row] * W5filter[depth][0][0][0];
					pointsum = pointsum + input_arr[depth][0 + col][1 + row] * W5filter[depth][0][0][1];
					pointsum = pointsum + input_arr[depth][0 + col][2 + row] * W5filter[depth][0][0][2];

					pointsum = pointsum + input_arr[depth][1 + col][0 + row] * W5filter[depth][0][1][0];
					pointsum = pointsum + input_arr[depth][1 + col][1 + row] * W5filter[depth][0][1][1];
					pointsum = pointsum + input_arr[depth][1 + col][2 + row] * W5filter[depth][0][1][2];

					pointsum = pointsum + input_arr[depth][2 + col][0 + row] * W5filter[depth][0][2][0];
					pointsum = pointsum + input_arr[depth][2 + col][1 + row] * W5filter[depth][0][2][1];
					pointsum = pointsum + input_arr[depth][2 + col][2 + row] * W5filter[depth][0][2][2];

					out[depth][col][row] = pointsum;
					pointsum = 0;
				}
			}
		}

		// I have to pass 3 dimensional array by return.

	}


	void depth_convolution2_4(vector<vector<vector<vector<double>>>> arr, vector<vector<vector<vector<double>>>> &out)
	{
		//srand(time(NULL));
		// 1. make filter.
		/*double filter[64][1][3][3];

		for (int number = 0; number < 64; number++)
		{
		for (int i = 0; i < 3; i++)
		{
		for (int j = 0; j < 3; j++)
		{
		filter[number][0][i][j] = rand()%10;
		}
		}
		}*/





		// 2. padding

		double input_arr[numberdata][64][10][10];

		for (int n = 0; n < numberdata; n++)
		{
			for (int j = 0; j < 64; j++)
			{
				for (int i = 0; i < 10; i++)
				{
					input_arr[n][j][0][i] = 0;
					input_arr[n][j][i][0] = 0;
					input_arr[n][j][i][9] = 0;
					input_arr[n][j][9][i] = 0;
				}
			}
		}

		// 3. arr to input_arr by value

		for (int n = 0; n < numberdata; n++)
		{
			for (int k = 0; k < 64; k++)
			{
				for (int i = 0; i < 8; i++)
				{
					for (int j = 0; j < 8; j++)
					{
						input_arr[n][k][j + 1][i + 1] = arr[n][k][j][i];
					}
				}
			}
		}



		/*double*** featureMap;
		featureMap = new double**[64];

		make_array(featureMap, 64, 8, 8);*/

		double pointsum = 0;


		// 4. depthwise convolution

		for (int n = 0; n < numberdata; n++)
		{
			for (int depth = 0; depth < 64; depth++)
			{
				for (int col = 0; col < 8; col++)
				{
					for (int row = 0; row < 8; row++)
					{
						// matrix mul.
						pointsum = pointsum + input_arr[n][depth][0 + col][0 + row] * W5filter[depth][0][0][0];
						pointsum = pointsum + input_arr[n][depth][0 + col][1 + row] * W5filter[depth][0][0][1];
						pointsum = pointsum + input_arr[n][depth][0 + col][2 + row] * W5filter[depth][0][0][2];

						pointsum = pointsum + input_arr[n][depth][1 + col][0 + row] * W5filter[depth][0][1][0];
						pointsum = pointsum + input_arr[n][depth][1 + col][1 + row] * W5filter[depth][0][1][1];
						pointsum = pointsum + input_arr[n][depth][1 + col][2 + row] * W5filter[depth][0][1][2];

						pointsum = pointsum + input_arr[n][depth][2 + col][0 + row] * W5filter[depth][0][2][0];
						pointsum = pointsum + input_arr[n][depth][2 + col][1 + row] * W5filter[depth][0][2][1];
						pointsum = pointsum + input_arr[n][depth][2 + col][2 + row] * W5filter[depth][0][2][2];

						out[n][depth][col][row] = pointsum;
						pointsum = 0;
					}
				}
			}
		}

		// I have to pass 3 dimensional array by return.

	}



	/*
	@brief	pooling layer, filter size is made up as 2*2 / stride = 2
	@pre	input size is made up as 64*8*8
	@post	output size is made up as 64*4*4
	*/

	void pool3_4(vector<vector<vector<vector<double>>>> arr, vector<vector<vector<vector<double>>>> &out)
	{
		/*double*** return_arr;
		return_arr = new double**[64];

		make_array(return_arr, 64, 4, 4);*/

		for (int n = 0; n < numberdata; n++)
		{
			for (int depth = 0; depth < 64; depth++)
			{
				for (int col = 0; col < 4; col++)
				{
					for (int row = 0; row < 4; row++)
					{
						if (arr[n][depth][0 + (col * 2)][0 + (row * 2)] >= arr[n][depth][0 + (col * 2)][1 + (row * 2)] && arr[n][depth][0 + (col * 2)][0 + (row * 2)] >= arr[n][depth][1 + (col * 2)][0 + (row * 2)] && arr[n][depth][0 + (col * 2)][0 + (row * 2)] >= arr[n][depth][1 + (col * 2)][1 + (row * 2)])
							out[n][depth][0 + col][0 + row] = arr[n][depth][0 + (col * 2)][0 + (row * 2)];

						else if (arr[n][depth][0 + (col * 2)][1 + (row * 2)] >= arr[n][depth][0 + (col * 2)][0 + (row * 2)] && arr[n][depth][0 + (col * 2)][1 + (row * 2)] >= arr[n][depth][1 + (col * 2)][0 + (row * 2)] && arr[n][depth][0 + (col * 2)][1 + (row * 2)] >= arr[n][depth][1 + (col * 2)][1 + (row * 2)])
							out[n][depth][0 + col][0 + row] = arr[n][depth][0 + (col * 2)][1 + (row * 2)];

						else if (arr[n][depth][1 + (col * 2)][0 + (row * 2)] >= arr[n][depth][0 + (col * 2)][0 + (row * 2)] && arr[n][depth][1 + (col * 2)][0 + (row * 2)] >= arr[n][depth][0 + (col * 2)][1 + (row * 2)] && arr[n][depth][1 + (col * 2)][0 + (row * 2)] >= arr[n][depth][1 + (col * 2)][1 + (row * 2)])
							out[n][depth][0 + col][0 + row] = arr[n][depth][1 + (col * 2)][0 + (row * 2)];

						else if (arr[n][depth][1 + (col * 2)][1 + (row * 2)] >= arr[n][depth][0 + (col * 2)][0 + (row * 2)] && arr[n][depth][1 + (col * 2)][1 + (row * 2)] >= arr[n][depth][0 + (col * 2)][1 + (row * 2)] && arr[n][depth][1 + (col * 2)][1 + (row * 2)] >= arr[n][depth][1 + (col * 2)][0 + (row * 2)])
							out[n][depth][0 + col][0 + row] = arr[n][depth][1 + (col * 2)][1 + (row * 2)];
					}
				}
			}
		}
	}



	/*
	@brief	Affine layer(FC layer), filter size is made up as 1024*512
	@pre	input size is made up as 64*4*4 = 1*1*1024
	@post	output size is made up as 1*1*512
	*/
//	void Affine(vector<vector<vector<double>>> arr,vector<double> &out)
//	{
//		// 1. make [4][4][64] -> [1][1][1024]
//		
//
//		int numbering = 0;
//
//		for (int depth = 0; depth < 64; depth++)
//		{
//			for (int col = 0; col < 4; col++)
//			{
//				for (int row = 0; row < 4; row++)
//				{
//					onedimension_arr[numbering] = arr[depth][col][row];
//					numbering++;
//				}
//			}
//		}
//
//		
//
//		// 2. make filter [1024] [512]
//		//srand(time(NULL));
//
//		/*for (int i = 0; i < 512; i++)
//		{
//			for (int j = 0; j < 1024; j++)
//			{
//				filter1[i][j] = rand()%10;
//			}
//		}
//*/
//		
//
//		// 3. filtering.
//
//		/*double* returnarr = new double[512];*/
//
//
//		double returnvalue = 0;
//		for (int j = 0; j < 512; j++)
//		{
//			for (int i = 0; i < 1024; i++)
//			{
//				returnvalue = returnvalue +  onedimension_arr[i] * W6filter[i][j];
//			}
//			out[j] = returnvalue;
//			returnvalue = 0;
//		}
//
//		// I have to pass 1 dimension parameter by return value
//		
//
//
//	}
//

	void Affine_4(vector<vector<vector<vector<double>>>> arr, vector<vector<double>> &out)
	{
		// 1. make [4][4][64] -> [1][1][1024]


		int numbering = 0;
		for (int n = 0; n < numberdata; n++)
		{
			for (int depth = 0; depth < 64; depth++)
			{
				for (int col = 0; col < 4; col++)
				{
					for (int row = 0; row < 4; row++)
					{
						onedimension_arr[n][numbering] = arr[n][depth][col][row];
						numbering++;
					}
				}
			}
			numbering = 0;
		}



		// 2. make filter [1024] [512]
		//srand(time(NULL));

		/*for (int i = 0; i < 512; i++)
		{
		for (int j = 0; j < 1024; j++)
		{
		filter1[i][j] = rand()%10;
		}
		}
		*/


		// 3. filtering.

		/*double* returnarr = new double[512];*/


		double returnvalue = 0;
		for (int n = 0; n < numberdata; n++)
		{
			for (int j = 0; j < 512; j++)
			{
				for (int i = 0; i < 1024; i++)
				{
					returnvalue = returnvalue + onedimension_arr[n][i] * W6filter[i][j];
				}
				out[n][j] = returnvalue;
				returnvalue = 0;
			}
		}

		// I have to pass 1 dimension parameter by return value



	}



	/*
	@brief	Affine layer(FC layer), filter size is made up as 512*10
	@pre	input size is made up as 1*1*512
	@post	output size is made up as 1*1*10
	*/
	void Affine2(vector<double> arr, vector<double> &out)
	{
		// 1. make filter [512][10]
		//double filter[512][10];

		//srand(time(NULL));

		/*for (int i = 0; i < 512; i++)
		{
			for (int j = 0; j < 10; j++)
			{
				filter[i][j] = rand();
			}
		}
*/

		// 2. filtering. affine layer.
		
		/*double returnarr[10];*/


		double returnvalue = 0;

		for (int j = 0; j < 10; j++)
		{
			for (int i = 0; i < 512; i++)
			{
				returnvalue = returnvalue + arr[i] * W7filter[i][j];
			}

			out[j] = returnvalue;
			returnvalue = 0;
		}

		// I have to pass 1 dimension array by return.

	}

	void Affine2_4(vector<vector<double>> arr, vector<vector<double>> &out)
	{
		// 1. make filter [512][10]
		//double filter[512][10];

		//srand(time(NULL));

		/*for (int i = 0; i < 512; i++)
		{
		for (int j = 0; j < 10; j++)
		{
		filter[i][j] = rand();
		}
		}
		*/

		// 2. filtering. affine layer.

		/*double returnarr[10];*/


		double returnvalue = 0;

		for (int n = 0; n < numberdata; n++)
		{
			for (int j = 0; j < 10; j++)
			{
				for (int i = 0; i < 512; i++)
				{
					returnvalue = returnvalue + arr[n][i] * W7filter[i][j];
				}

				out[n][j] = returnvalue;
				returnvalue = 0;
			}
		}

		// I have to pass 1 dimension array by return.

	}


	void make_array_2d(double** arr,int col, int row)
	{
		for (int i = 0; i < col; i++)
		{
			arr[i] = new double[row];
		}
	}

	void make_array(double*** returnarr, int depth, int col, int row)
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

	void make_array_four(double**** returnarr, int number, int depth, int col, int row)
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

	void makew1(vector<vector<vector<vector<double>>>> &arr)
	{
		vector<double> a;
		vector<vector<double>> b;
		vector<vector<vector<double>>> c;
		vector<vector<vector<vector<double>>>> d;

		for (int i = 0; i < 3; i++)
		{
			a.push_back(0);
		}

		for (int i = 0; i < 3; i++)
		{
			b.push_back(a);
		}

		for (int i = 0; i < 3; i++)
		{
			c.push_back(b);
		}

		for (int i = 0; i < 32; i++)
		{
			arr.push_back(c);
		}
	}

	void makew1_1(vector<vector<vector<vector<double>>>> &arr)
	{
		vector<double> a;
		vector<vector<double>> b;
		vector<vector<vector<double>>> c;
		vector<vector<vector<vector<double>>>> d;

		for (int i = 0; i < 3; i++)
		{
			a.push_back(0);
		}

		for (int i = 0; i < 3; i++)
		{
			b.push_back(a);
		}

		for (int i = 0; i < 32; i++)
		{
			c.push_back(b);
		}

		for (int i = 0; i < 32; i++)
		{
			arr.push_back(c);
		}
	}


	void makew2(vector<vector<vector<vector<double>>>> &arr)
	{
		vector<double> a;
		vector<vector<double>> b;
		vector<vector<vector<double>>> c;
		vector<vector<vector<vector<double>>>> d;

		a.push_back(0);
		b.push_back(a);

		for (int j = 0; j < 32; j++)
		{
			for (int i = 0; i < 32; i++)
			{
				c.push_back(b);
			}
		}
		for (int i = 0; i < 32; i++)
		{
			arr.push_back(c);
		}
	}

	void makew3(vector<vector<vector<vector<double>>>> &arr)
	{
		vector<double> a;
		vector<vector<double>> b;
		vector<vector<vector<double>>> c;
		vector<vector<vector<vector<double>>>> d;


		for (int j = 0; j < 3; j++)
		{
			a.push_back(0);
		}
		for (int i = 0; i < 3; i++)
		{
			b.push_back(a);
		}

		for (int i = 0; i < 1; i++)
		{
			c.push_back(b);
		}
		for (int i = 0; i < 32; i++)
		{
			arr.push_back(c);
		}
	}

	void makew4(vector<vector<vector<vector<double>>>> &arr)
	{
		vector<double> a;
		vector<vector<double>> b;
		vector<vector<vector<double>>> c;
		vector<vector<vector<vector<double>>>> d;


		
		a.push_back(0);
		
		b.push_back(a);
		

		for (int i = 0; i < 32; i++)
		{
			c.push_back(b);
		}
		for (int i = 0; i < 64; i++)
		{
			arr.push_back(c);
		}
	}

	void makew5(vector<vector<vector<vector<double>>>> &arr)
	{
		vector<double> a;
		vector<vector<double>> b;
		vector<vector<vector<double>>> c;
		vector<vector<vector<vector<double>>>> d;


		for (int j = 0; j < 3; j++)
		{
			a.push_back(0);
		}
		for (int i = 0; i < 3; i++)
		{
			b.push_back(a);
		}

		for (int i = 0; i < 1; i++)
		{
			c.push_back(b);
		}
		for (int i = 0; i < 64; i++)
		{
			arr.push_back(c);
		}
	}

	void makew6(vector<vector<double>> &arr)
	{
		vector<double> a;
		vector<vector<double>> b;
		vector<vector<vector<double>>> c;
		vector<vector<vector<vector<double>>>> d;



		for (int i = 0; i < 512; i++)
		{
			a.push_back(0);
		}
		for (int i = 0; i < 1024; i++)
		{
			arr.push_back(a);
		}
	}

	void makew7(vector<vector<double>> &arr)
	{
		vector<double> a;
		vector<vector<double>> b;
		vector<vector<vector<double>>> c;
		vector<vector<vector<vector<double>>>> d;



		for (int i = 0; i < 10; i++)
		{
			a.push_back(0);
		}
		for (int i = 0; i < 512; i++)
		{
			arr.push_back(a);
		}
	}

	void makeLN323232(vector<vector<vector<double>>> &arr)
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
			arr.push_back(b);
		}
	}


	void makeLN321616(vector<vector<vector<double>>> &arr)
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
			arr.push_back(b);
		}
	}

	void makeLN646464(vector<vector<vector<double>>> &arr)
	{
		vector<double> a;
		vector<vector<double>> b;
		vector<vector<vector<double>>> c;




		for (int i = 0; i < 64; i++)
		{
			a.push_back(0);
		}


		for (int i = 0; i < 64; i++)
		{
			b.push_back(a);
		}
		for (int i = 0; i < 64; i++)
		{
			arr.push_back(b);
		}
	}

	void makeLN512(vector<vector<vector<double>>> &arr)
	{
		vector<double> a;
		vector<vector<double>> b;
		vector<vector<vector<double>>> c;




		for (int i = 0; i < 512; i++)
		{
			a.push_back(0);
		}


		for (int i = 0; i < 512; i++)
		{
			b.push_back(a);
		}
		for (int i = 0; i < 512; i++)
		{
			arr.push_back(b);
		}
	}

	void makearr(vector<vector<vector<vector<double>>>> &arr)
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


	void makearr646464(vector<vector<vector<vector<double>>>> &arr)
	{
		vector<double> a;
		vector<vector<double>> b;
		vector<vector<vector<double>>> c;
		vector<vector<vector<vector<double>>>> d;


		for (int j = 0; j < 64; j++)
		{
			a.push_back(0);
		}
		for (int i = 0; i < 64; i++)
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


};