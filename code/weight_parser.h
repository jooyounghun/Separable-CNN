#pragma once
#include <iostream>
#include <sstream>
#include <fstream>
#include <iomanip> // setw
#include <random>
#include <list>
#include <vector>
#include <algorithm>
#include <string>

#include <stdio.h>

using namespace std;
class weight_parser
{

public:
	weight_parser(){}

	void w1parser(vector<vector<vector<vector<double>>>> & arr)
	{
		string line;
		ifstream fin;
		fin.open(("w1.txt"));


		if (fin.is_open())
		{
			while (getline(fin, line))
			{
				string input;
				stringstream ss(line);
				for (int h = 0; h < 32; h++)
				{
					for (int i = 0; i < 3; i++)
					{
						for (int j = 0; j < 3; j++)
						{
							
							for (int k = 0; k < 3; k++)
							{
								
								getline(ss, input, '/');
								arr[h][i][j][k] = stod(input);
								
							}
						
						}
					}
				}
			}
		}

		

	}

	

	void w2parser(vector<vector<vector<vector<double>>>> &arr)
	{
		string line;
		ifstream fin;
		fin.open(("w2.txt"));
		if (fin.is_open())
		{
			while (getline(fin, line))
			{
				stringstream ss(line);
				string input;
				for (int i = 0; i < 32; i++)
				{
					for (int j = 0; j < 32; j++)
					{
						getline(ss, input, '/');
						arr[i][j][0][0] = stod(input);
					}
				}
			}

		}
	}

	void w3parser(vector<vector<vector<vector<double>>>> &arr)
	{
		string line;
		ifstream fin;
		fin.open(("w3.txt"));
		if (fin.is_open())
		{
			while (getline(fin, line))
			{
				stringstream ss(line);
				string input;
				for (int i = 0; i < 32; i++)
				{
					for (int j = 0; j < 3; j++)
					{
						for (int k = 0; k < 3; k++)
						{
							getline(ss, input, '/');
							arr[i][0][j][k] = stod(input);
						}
					}
				}
			}

		}
	}

	void w4parser(vector<vector<vector<vector<double>>>> & arr)
	{
		string line;
		ifstream fin;
		fin.open(("w4.txt"));
		if (fin.is_open())
		{
			while (getline(fin, line))
			{
				stringstream ss(line);
				string input;
				for (int i = 0; i < 64; i++)
				{
					for (int j = 0; j < 32; j++)
					{

						getline(ss, input, '/');
						arr[i][j][0][0] = stod(input);

					}
				}
			}

		}
	}


	void w5parser(vector<vector<vector<vector<double>>>> & arr)
	{
		string line;
		ifstream fin;
		fin.open(("w5.txt"));
		if (fin.is_open())
		{
			while (getline(fin, line))
			{
				stringstream ss(line);
				string input;
				for (int i = 0; i < 64; i++)
				{
					for (int j = 0; j < 3; j++)
					{
						for (int k = 0; k < 3; k++)
						{
							getline(ss, input, '/');
							arr[i][0][j][k] = stod(input);
						}
					}
				}
			}

		}
	}


	void w6parser(vector<vector<double>> & arr)
	{
		string line;
		ifstream fin;
		fin.open(("w6.txt"));
		if (fin.is_open())
		{
			while (getline(fin, line))
			{
				string input;
				stringstream ss(line);
				for (int i = 0; i < 1024; i++)
				{
					for (int j = 0; j < 512; j++)
					{
						getline(ss, input, '/');
						arr[i][j] = stod(input);

					}
				}
			}
		}
	}

	void w7parser(vector<vector<double>> & arr)
	{
		string line;
		ifstream fin;
		fin.open(("w7.txt"));
		if (fin.is_open())
		{
			while (getline(fin, line))
			{
				string input;
				stringstream ss(line);
				for (int i = 0; i < 512; i++)
				{
					for (int j = 0; j < 10; j++)
					{
						getline(ss, input, '/');
						arr[i][j] = stod(input);

					}
				}
			}
		}
	}

/*
	void w1parser(double**** returnarr, int number, int depth, int col, int row)
	{
		for (int h = 0; h < number; h++)
		{
			returnarr[h] = new double**[depth];
		}

		for (int h = 0; h < number; h++)
		{
			for (int j = 0; j < depth; j++)
			{
				returnarr[h][j] = new double*[col];
			}
		}

		for (int h = 0; h < number; h++)
		{
			for (int j = 0; j < depth; j++)
			{
				for (int k = 0; k < col; k++)
				{
					returnarr[h][j][k] = new double[row];
				}
			}
		}


		string line;
		ifstream fin;
		fin.open(("w1.txt"));
		if (fin.is_open())
		{
			while (getline(fin, line))
			{
				string input;
				stringstream ss(line);
				for (int h = 0; h < 32; h++)
				{
					for (int i = 0; i < 3; i++)
					{
						for (int j = 0; j < 3; j++)
						{
							for (int k = 0; k < 3; k++)
							{
								getline(ss, input, '/');
								returnarr[h][i][j][k] = stof(input);
							}
						}
					}
				}
			}
		}
	}
	void w2parser(double**** returnarr, int number, int depth, int col, int row)
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

		string line;
		ifstream fin;
		fin.open(("w2.txt"));
		if (fin.is_open())
		{
			while (getline(fin, line))
			{
				stringstream ss(line);
				string input;
				for (int i = 0; i < 32; i++)
				{
					for (int j = 0; j < 32; j++)
					{

						getline(ss, input, '/');
						returnarr[i][j][0][0] = stof(input);

					}
				}
			}

		}
	}
	void w3parser(double**** returnarr, int number, int depth, int col, int row)
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

		string line;
		ifstream fin;
		fin.open(("w3.txt"));
		if (fin.is_open())
		{
			while (getline(fin, line))
			{
				stringstream ss(line);
				string input;
				for (int i = 0; i < 32; i++)
				{
					for (int j = 0; j < 3; j++)
					{
						for (int k = 0; k < 3; k++)
						{
							getline(ss, input, '/');
							returnarr[i][0][j][k] = stof(input);
						}
					}
				}
			}

		}
	}
	void w4parser(double**** returnarr, int number, int depth, int col, int row)
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

		string line;
		ifstream fin;
		fin.open(("w4.txt"));
		if (fin.is_open())
		{
			while (getline(fin, line))
			{
				stringstream ss(line);
				string input;
				for (int i = 0; i < 64; i++)
				{
					for (int j = 0; j < 32; j++)
					{

						getline(ss, input, '/');
						returnarr[i][j][0][0] = stof(input);

					}
				}
			}

		}
	}
	void w5parser(double**** returnarr, int number, int depth, int col, int row)
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

		string line;
		ifstream fin;
		fin.open(("w5.txt"));
		if (fin.is_open())
		{
			while (getline(fin, line))
			{
				stringstream ss(line);
				string input;
				for (int i = 0; i < 64; i++)
				{
					for (int j = 0; j < 3; j++)
					{
						for (int k = 0; k < 3; k++)
						{
							getline(ss, input, '/');
							returnarr[i][0][j][k] = stof(input);
						}
					}
				}
			}

		}
	}
	void w6parser(double** returnarr, int number, int depth)
	{
		for (int i = 0; i < number; i++)
		{
			returnarr[i] = new double[depth];
		}

		string line;
		ifstream fin;
		fin.open(("w6.txt"));
		if (fin.is_open())
		{
			while (getline(fin, line))
			{
				string input;
				stringstream ss(line);
				for (int i = 0; i < 1024; i++)
				{
					for (int j = 0; j < 512; j++)
					{
						getline(ss, input, '/');
						returnarr[i][j] = stof(input);
					
					}
				}
			}
		}
	}
	void w7parser(double** returnarr, int number, int depth)
	{
		for (int i = 0; i < number; i++)
		{
			returnarr[i] = new double[depth];
		}

		string line;
		ifstream fin;
		fin.open(("w7.txt"));
		if (fin.is_open())
		{
			while (getline(fin, line))
			{
				string input;
				stringstream ss(line);
				for (int i = 0; i < 512; i++)
				{
					for (int j = 0; j < 10; j++)
					{
						getline(ss, input, '/');
						returnarr[i][j] = stof(input);

					}
				}
			}
		}
	}
*/
};