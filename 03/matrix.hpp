#pragma once
#include <iostream>
using namespace std;
	

class Matrix
{
    class ProxyRow
    {
        private:
            int32_t *data_;
            size_t rows;
        public:
            ProxyRow();
            size_t getRows() const;
            ProxyRow(size_t size);
            int32_t& operator[](size_t j);
            ProxyRow& operator =(ProxyRow &array);
            ~ProxyRow();
    };
    public:
        Matrix(size_t i, size_t j);
        Matrix(const Matrix & matrix);
        
        ProxyRow& operator[](size_t i);
        size_t getRows() const;
        size_t getCols() const;
        Matrix& operator *=(int);
        Matrix operator +(const Matrix&) const;
        Matrix& operator =(const Matrix&);
        bool operator ==(const Matrix&) const;
        bool operator !=(const Matrix&) const;
        friend ostream& operator <<(ostream&, const Matrix&);
        ~Matrix();
    

    private:
        ProxyRow *rows_;
		size_t cols;
		
};

