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
        

        //Constructors
        Matrix();
        Matrix(const std::vector<double> &m, const int r, const int c);
        Matrix(const Matrix& other);

        //Destructor
        ~Matrix();

        //Functions
        /*This function prints the matrix.*/
        void printMatrix() const;
        /*This function returns the sum of the matrix.*/
        double sum() const; 
        

        //Operators
        //Binary Operators
        Matrix operator + (const Matrix& other) const;  
        Matrix operator - (const Matrix& other) const;
        Matrix operator * (const Matrix& other) const;
        Matrix operator * (const double num) const;
        
        
        Matrix& operator += (const Matrix& other);
        Matrix& operator -= (const Matrix& other);
        Matrix& operator *= (const Matrix& other);
        Matrix& operator *= (const double num);

        bool operator == (const Matrix& other) const;
        bool operator != (const Matrix& other) const;
        bool operator >= (const Matrix& other) const;
        bool operator <= (const Matrix& other) const;
        bool operator > (const Matrix& other) const;
        bool operator < (const Matrix& other) const;

        //Unary Operators:
        Matrix& operator ++ ();
        Matrix& operator -- ();
        Matrix operator ++ (int); //postfix
        Matrix operator -- (int); //postfix

        Matrix& operator - ();
        Matrix& operator + ();

        //Friend Operators:
        friend Matrix operator * (const double num, const Matrix& other);
        friend std::ostream& operator << (std::ostream& out, const Matrix& other);
        friend std::istream& operator >> (std::istream& in,  Matrix& other);
        
    };
    

    
}