#pragma once
#include<iostream>
#include<vector>

namespace zich{
    class Matrix
    {
    private:
        int _row;
        int _col;
        std::vector<double> mat;

    public:
        //Getters
        int getRow() const {return this->_row;}
        int getColumn() const {return this->_col;}
        std::vector<double> getVector() const {return this->mat;}

        //Setters
        void setRow(int r) {this->_row = r;}
        void setColumn(int c) {this->_col = c;}
        void setVector(std::vector<double> other) {this->mat = other;}
        void setMatrix(std::vector<double> m={0}, int r=0, int c=0);

        //Constructors
        Matrix();
        Matrix(std::vector<double> m, int r, int c);
        Matrix(const zich::Matrix& other);

        //Destructor
        ~Matrix();

        //Functions
        void printMatrix() const;
        
        //Operators

    };
}