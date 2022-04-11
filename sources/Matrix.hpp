#pragma once
#include<iostream>
#include<vector>

namespace zich{
    class Matrix
    {
    private:
        int _row;
        int _col;
        int _size;
        std::vector<double> mat;

    public:
        //Getters
        int getRow() const {return this->_row;}
        int getColumn() const {return this->_col;}
        int getSize() const {return this->_size;}
        std::vector<double> getVector() const {return this->mat;}

        //Setters
        void setRow(int r);
        void setColumn(int c);
        void setSize(int s);
        void setVector(std::vector<double> other);
        void setMatrix(std::vector<double> m={0}, int r=1, int c=1);

        //Constructors
        Matrix();
        Matrix(std::vector<double> m, int r, int c);
        Matrix(const Matrix& other);

        //Destructor
        ~Matrix();

        //Functions
        void printMatrix() const;

        //Operators
        //Binary Operators
        Matrix operator + (const Matrix& other) const;  //m3 = m1 + m2;
        Matrix operator - (const Matrix& other) const;
        //Unary Operators
    };
}