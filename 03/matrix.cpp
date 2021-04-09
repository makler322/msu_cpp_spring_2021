#include <iostream>
#include "matrix.hpp"
using namespace std;



Matrix::ProxyRow::ProxyRow(size_t size)
{
	rows2 = size;
	data_ = new int32_t [size];
	for (size_t index = 0; index < size; index++)
	{
		data_[index] = 0;
	}
}

Matrix::ProxyRow::ProxyRow()
{
	data_ = new int32_t [2];
}

size_t Matrix::ProxyRow::getRows() const
{
	return rows2;
}

int32_t& Matrix::ProxyRow::operator[](size_t j)
{
	if (j < rows2)
	{
		return data_[j];
	}
	throw std::out_of_range("rows index out of range");
}
Matrix::ProxyRow::~ProxyRow()
{
	delete[] data_;
}

Matrix::ProxyRow& Matrix::ProxyRow::operator =(ProxyRow &array)
{
	delete[] data_;
	rows2 = array.getRows();
	data_ = new int32_t [rows2];
	for (size_t index = 0; index < rows2; index++)
	{
		data_[index] = array[index];
	}
	return *this;
}
Matrix::ProxyRow& Matrix::operator[](size_t i)
{   
	if (i < rows)
	{
		return rows_[i];
	}
	throw std::out_of_range("cols index out of range");
}



Matrix::Matrix(size_t i, size_t j)
{
	rows = i;
	cols = j;
	rows_ = new ProxyRow[i];
	for (size_t index = 0; index < i; index++)
	{
		ProxyRow array(j);
		rows_[index] = array;
	}
}


size_t Matrix::getRows() const {return rows;}


size_t Matrix::getCols() const {return cols;}



Matrix& Matrix::operator *=(int a)
{
	for (size_t i = 0; i < rows; i++)
	{
		for(size_t j = 0; j < cols; j++)
		{
			rows_[i][j] *= a;
		}
	}
	return *this;
}


Matrix Matrix::operator +(const Matrix& SecondMatrix) const
{
	if ((rows != SecondMatrix.getRows()) || (cols != SecondMatrix.getCols()))
	{
		throw out_of_range("Input arrays must have same dimensions");
	}	
	Matrix ResultMatrix = Matrix(rows, cols);
	for (size_t i = 0; i < rows; i++)
	{
		for(size_t j = 0; j < cols; j++)
		{
			ResultMatrix[i][j] = rows_[i][j] + SecondMatrix.rows_[i][j];
		}
	}
	return ResultMatrix;
}


bool Matrix::operator ==(const Matrix& SecondMatrix) const
{
	if ((rows != SecondMatrix.getRows()) || (cols != SecondMatrix.getCols()))
	{
		return false;
	}
	else
	{
		for (size_t i = 0; i < rows; i++)
		{
			for(size_t j = 0; j < cols; j++)
			{
				if (rows_[i][j] != SecondMatrix.rows_[i][j])
				{
					return false;
				}
			}
		}
		return true;
	}
}


Matrix& Matrix::operator =(const Matrix& SecondMatrix)
{
	if (this == &SecondMatrix) 
		return *this;
	if ((rows != SecondMatrix.getRows()) || (cols != SecondMatrix.getCols()))
	{
		throw out_of_range("Input arrays must have same dimensions");
	}
	for (unsigned int i = 0; i < rows; i++)
	{
		for(unsigned int j = 0; j < cols; j++)
		{
			rows_[i][j] = SecondMatrix.rows_[i][j];
		}
	}
	return *this;
}


bool Matrix::operator !=(const Matrix& SecondMatrix) const
{
	return !(*this == SecondMatrix);
}


Matrix::~Matrix()
{
	delete[] rows_;
}


ostream & operator <<(ostream & out, const Matrix& matrix)
{
	size_t rows = matrix.getRows();
	size_t cols = matrix.getCols();
	for (size_t i = 0; i < rows; i++)
	{
		for(size_t j = 0; j < cols; j++)
		{
			out << matrix.rows_[i][j] << " ";
		}
		out << '\n';
	}
	return out;
}