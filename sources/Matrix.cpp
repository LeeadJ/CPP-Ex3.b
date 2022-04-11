#include "Matrix.hpp"

namespace zich{
    void Matrix::printMatrix() const{
        int r = this->getRow();
        int c = this->getColumn();
        for(int i=0; i<r; i++){
            std::cout << "[";
            for(int j=0; j<c; j++){
                std::cout << " " << this->getVector()[(i*c)+j];
            }
            std::cout << "]" << std::endl;
        }
    }
    void Matrix::setMatrix(std::vector<double> m={0}, int r=0, int c=0){
        this->setVector(m);
        this->setRow(r);
        this->setColumn(c);
    }
    Matrix::Matrix(){
        this->setMatrix();
    }
    Matrix::Matrix(std::vector<double> m, int r, int c){
        this->setMatrix(m, r, c);
    }
    Matrix::Matrix(const zich::Matrix& other){
        *this = other;
    }
    Matrix::~Matrix(){};
}
