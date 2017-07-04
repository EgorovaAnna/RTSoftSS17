#include <iostream>
#include <string>
#include <fstream>
#include <cmath>
//#include <cstdlib>

template <typename T> class Matrix
{
	T **matrix;
	int M;
public:
	Matrix(int N);
	T get(int i, int j);
	T determinant();
	void set(int i, int j, T data);
	int getMM();
	T minor();
	void load(std::string fl);
	~Matrix();
};
template <typename T> Matrix<T>::Matrix(int N)
{
	int i, j;
	matrix = new T*[N];
	for(i = 0; i < N; i++)
		matrix[i] = new T[N];
	for(i = 0; i < N; i++)
		for(j = 0; j < N; j++)
			matrix[i][j] = T();
	M = N;
}
template <typename T> Matrix<T>::~Matrix()
{
	int i, j;
	for(j = 0; j < M; j++)
		delete []matrix[j];
	delete []matrix;
}
template <typename T> T Matrix<T>::get(int i, int j)
{
	if (i < M && j < M)
		return matrix[i][j];
	else
		return -180;
}
template <typename T> int Matrix<T>::getMM()
{
	//MM = M - 1;
	return M - 1;
}
template <typename T> void Matrix<T>::set(int i, int j, T data)
{
	if (i < M && j < M)
		matrix[i][j] = data;
}
template <typename T> T Matrix<T>::minor()
{
	if(M >= 2)
	{
		T det = 0;
		int i, j, k, l;
		Matrix<T> minor[M](getMM());
		for (k = 0; k < M; k++)
		{
			for (i = 1; i < M; i++)
			{
				l = 0;
				for (j = 0; j < M; j++)
				{		
					if (j != k)
					{
						minor[k].set(i - 1, l, matrix[i][j]);
						l++;
					}
				}
			}
			det += pow(-1, k)*matrix[0][k]*minor[k].minor();
		}
		return det;
	}
	else
		return matrix[0][0];
}
template <typename T> void Matrix<T>::load(std::string fl)
{
	std::ifstream fin(fl.c_str());
	int i, j;
	for(i = 0; i < M; i++)
	{
		for(j = 0; j < M; j++)
		{
			fin >> matrix[i][j];
			std::cout << matrix[i][j] <<" ";
		}
		std::cout<< std::endl;
	}
	fin.close();
}

int main()
{
	Matrix<int> mat(4);
	mat.load("matrixinit.txt");
	std::cout << mat.minor() << std::endl;
}






