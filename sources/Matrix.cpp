#include "Matrix.hpp"
#include <iomanip>
#include <sstream>

namespace zich{
    //Setters
    void Matrix::setRow(int r) {
        if(r < 1){
            throw std::runtime_error("SetRow Error: Row must be greater than 0.");
        }
        this->_row = r;
    }
    void Matrix::setColumn(int c) {
        if(c < 1){
            throw std::runtime_error("SetColumn Error: Column must be greater than 0.");
        }
        this->_col = c;
    }
    void Matrix::setSize(int s) {
        // if(s != this->getColumn()*this->getRow()){
        //     throw std::runtime_error("SetSize Error: Size does not match Row*Column value.");
        // }
        this->_size = s;
    }
    void Matrix::setVector(std::vector<double> other) {
        for(int i=0; i<other.size(); i++){
            if(sizeof(other.at(i)) != 8){
                throw std::runtime_error("setVector Error: Vector element is not of type double.");
            }
        }
        this->mat = other;
    }
    void Matrix::setMatrix(std::vector<double> m, int r, int c){
        this->setVector(m);
        this->setRow(r);
        this->setSize(r*c);
        this->setColumn(c);
        
    }
    //Constructors
    Matrix::Matrix(){
        this->setMatrix();
    }
    Matrix::Matrix(std::vector<double> m, int r, int c){
        this->setMatrix(m, r, c);
    }
    Matrix::Matrix(const Matrix& other){
        *this = other;
    }
    //Destructor
    Matrix::~Matrix(){};

    //Functions
    void Matrix::printMatrix() const{
        int r = this->getRow();
        int c = this->getColumn();
        std::string ans;
        for(int i=0; i<r; i++){
            ans += "[";
            for(int j=0; j<c; j++){
                std::stringstream stream;
                stream << std::fixed << std::setprecision(2) << this->getVector()[(i*c)+j];
                // ans += std::to_string(this->getVector()[(i*c)+j]);
                ans += stream.str();
                stream.str("");
                ans += " ";
            }
            ans.pop_back();
            ans += "]\n";
        }
        ans.pop_back();
        std::cout << ans << std::endl;
    }

    //Operators
    Matrix Matrix::operator + (const Matrix& other) const{
        if(this->getRow() != other.getRow() || this->getColumn() != other.getColumn()){
            throw std::runtime_error("Operator (+) Error: Matrixs must be same dimension.");
        }
        std::vector<double> vec;
        for(int i=0; i<this->getSize(); i++){
            vec.push_back(this->getVector().at(i) + other.getVector().at(i));
        }
        return Matrix(vec, this->getRow(), this->getColumn());
    }

    Matrix Matrix::operator - (const Matrix& other) const{
        if(this->getRow() != other.getRow() || this->getColumn() != other.getColumn()){
            throw std::runtime_error("Operator (+) Error: Matrixs must be same dimension.");
        }
        std::vector<double> vec;
        for(int i=0; i<this->getSize(); i++){
            vec.push_back(this->getVector().at(i) - other.getVector().at(i));
        }
        return Matrix(vec, this->getRow(), this->getColumn());
    }

    
}


int main(){
    // zich::Matrix m1;
    // m1.printMatrix();
    // std::cout << m1.getSize() << std::endl;
    std::vector<double> v1 = {1,0,0,0,1,0,0,0,1};
    std::vector<double> v2 = {5,5,5,5,5,5,5,5,5};
    zich::Matrix m1{v1, 3, 3};
    zich::Matrix m2{v2, 3, 3};
    // m2.printMatrix();
    // std::cout << m2.getSize() << std::endl;
    zich::Matrix m3 = m2 + m1;
    zich::Matrix m4 = m2 - m1;
    std::cout << "m1\n";
    m1.printMatrix();
    std::cout << "\nm2\n";
    m2.printMatrix();
    std::cout << "\nm3=m2+m1\n";
    m3.printMatrix();
    std::cout << "\nm4=m2-m1\n";
    m4.printMatrix();

    return 0;
}
