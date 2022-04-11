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
        void setRow(int r){this->_row = r;}
        void setColumn(int c){this->_col = c;}
        void setSize(int s){this->_size = s;}
        void setVector(std::vector<double> other={0}){this->mat = other;}
        void setMatrix(std::vector<double> m={0}, int r=1, int c=1);

        //Constructors
        Matrix();
        Matrix(std::vector<double> m, int r, int c);
        Matrix(const Matrix& other);

        //Destructor
        ~Matrix();

        //Functions
        /*This function prints the matrix.*/
        void printMatrix() const;
        /*This function returns the sum of the matrix.*/
        double const sum() const; 

        //Operators
        //Binary Operators
        Matrix operator + (const Matrix& other) const;  //m3 = m1 + m2;
        Matrix operator - (const Matrix& other) const;
        Matrix operator * (const Matrix& other) const;
        

        Matrix& operator += (const Matrix& other);
        Matrix& operator -= (const Matrix& other);

        bool operator == (const Matrix& other) const;
        bool operator != (const Matrix& other) const;
        bool operator >= (const Matrix& other) const;
        bool operator <= (const Matrix& other) const;
        bool operator > (const Matrix& other) const;
        bool operator < (const Matrix& other) const;
        //Unary Operators
    };
}