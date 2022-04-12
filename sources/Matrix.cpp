#include "Matrix.hpp"
#include <iomanip>
#include <sstream>

namespace zich{
    //Setters
    void Matrix::setMatrix(std::vector<double> m, int r, int c){
        if(r < 1 || c < 1){
            throw std::runtime_error("SetMatrix Error: Row must be greater than 0.");
        }
        for(int i=0; i<m.size(); i++){
            if(sizeof(m.at(i)) != 8){
                throw std::runtime_error("SetMatrix Error: Vector element is not of type double.");
            }
        }
        this->setRow(r);
        this->setColumn(c);
        this->setSize(r*c);
        this->setVector(m);
        
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
    /*This function prints the matrix.*/
    void Matrix::printMatrix() const{
        int r = this->getRow();
        int c = this->getColumn();
        std::string ans;
        for(int i=0; i<r; i++){
            ans += "[";
            for(int j=0; j<c; j++){
                std::stringstream stream;
                stream << std::fixed << std::setprecision(2) << this->getVector()[(i*c)+j];
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

    /*This function returns the sum of the matrix.*/
    double const Matrix::sum() const{
        double ans = 0;
        for(double d : this->getVector()){
            ans += d;
        }
        return ans;
    }

    //Operators
    //Operator (+):
    Matrix Matrix::operator + (const Matrix& other) const{
        if(this->getRow() != other.getRow() || this->getColumn() != other.getColumn()){
            throw std::runtime_error("Operator (+) Error: 'This' Matrix and 'other' Matrix Row/Column do not match.");
        }
        std::vector<double> vec;
        for(int i=0; i<this->getSize(); i++){
            vec.push_back(this->getVector().at(i) + other.getVector().at(i));
        }
        return Matrix(vec, this->getRow(), this->getColumn());
    }

    //Operator (-):
    Matrix Matrix::operator - (const Matrix& other) const{
        if(this->getRow() != other.getRow() || this->getColumn() != other.getColumn()){
            throw std::runtime_error("Operator (-) Error: 'This' Matrix and 'other' Matrix Row/Column do not match.");
        }
        std::vector<double> vec;
        for(int i=0; i<this->getSize(); i++){
            vec.push_back(this->getVector().at(i) - other.getVector().at(i));
        }
        return Matrix(vec, this->getRow(), this->getColumn());
    }

    //Operator (*):
    Matrix Matrix::operator * (const Matrix& other) const{
        if(this->getColumn() != other.getRow()){
            throw std::runtime_error("Operator (*) Error: Matrix1 Column does not equal Matrix2 Row.");
        }
        std::vector<double> vec(this->getRow()*other.getColumn(), 0.0);
        int spot = 0;
        for(int i=0; i<this->getRow(); i++){
            for(int j=0; j<other.getColumn(); j++){
                for(int k=0; k<this->getColumn(); k++){
                    int index1 = (i*this->getColumn()) + k;
                    int index2 = (k*other.getColumn()) + j;
                    vec.at(spot) += this->getVector().at(index1) * other.getVector().at(index2);
                }
                spot++;
            }
        }
        return Matrix(vec, this->getRow(), other.getColumn());
    }

    //Operator (+=):
    Matrix& Matrix::operator += (const Matrix& other){
        if(this->getRow() != other.getRow() || this->getColumn() != other.getColumn()){
            throw std::runtime_error("Operator (+=) Error: 'This' Matrix and 'other' Matrix Row/Column do not match.");
        }
        return (*this = *this + other);
    }
    //Operator (-=):
    Matrix& Matrix::operator -= (const Matrix& other){
        if(this->getRow() != other.getRow() || this->getColumn() != other.getColumn()){
            throw std::runtime_error("Operator (-=) Error: 'This' Matrix and 'other' Matrix Row/Column do not match.");
        }
        return (*this = *this - other);
    }
    //Operator (*=):
    Matrix& Matrix::operator *= (const Matrix& other){
        if(this->getColumn() != other.getRow()){
            throw std::runtime_error("Operator (*=) Error: 'This' Matrix and 'other' Matrix Row/Column do not match.");
        }
        return (*this = *this * other);
    }
    //Operator (==):
    bool Matrix::operator == (const Matrix& other) const{
        if(this->getRow() != other.getRow() || this->getColumn() != other.getColumn()){
            throw std::runtime_error("Operator (==) Error: 'This' Matrix and 'other' Matrix Row/Column do not match.");
        }
        for(int i=0; i<this->getSize(); i++){
            if(this->getVector().at(i) != other.getVector().at(i)){
                return false;
            }
        }
        return true;
    }

    //Operator (!=):
    bool Matrix::operator != (const Matrix& other) const{
        if(this->getRow() != other.getRow() || this->getColumn() != other.getColumn()){
            throw std::runtime_error("Operator (!=) Error: This Matrix and 'other' Matrix Row/Column do not match.");
        }
        return !(*this == other);
    }

    //Operator (>=):
    bool Matrix::operator >= (const Matrix& other) const{
        if(this->getRow() != other.getRow() || this->getColumn() != other.getColumn()){
            throw std::runtime_error("Operator (>=) Error: This Matrix and 'other' Matrix Row/Column do not match.");
        }
        return this->sum() >= other.sum();
    }

    //Operator (<=):
    bool Matrix::operator <= (const Matrix& other) const{
        if(this->getRow() != other.getRow() || this->getColumn() != other.getColumn()){
            throw std::runtime_error("Operator (>=) Error: This Matrix and 'other' Matrix Row/Column do not match.");
        }
        return this->sum() <= other.sum();
    }

    //Operator (>):
    bool Matrix::operator > (const Matrix& other) const{
        if(this->getRow() != other.getRow() || this->getColumn() != other.getColumn()){
            throw std::runtime_error("Operator (>=) Error: This Matrix and 'other' Matrix Row/Column do not match.");
        }
        return this->sum() > other.sum();
    }

    //Operator (<):
    bool Matrix::operator < (const Matrix& other) const{
        if(this->getRow() != other.getRow() || this->getColumn() != other.getColumn()){
            throw std::runtime_error("Operator (>=) Error: This Matrix and 'other' Matrix Row/Column do not match.");
        }
        return this->sum() < other.sum();
    }
    //Unary Operators:
    //Operator (++prefix):
    Matrix& Matrix::operator ++ () {
        std::vector<double> vec;
        for(int i=0; i<this->getSize(); i++){
            vec.push_back(this->getVector().at(i) + 1.0);
        }
        this->setVector(vec);
        return *this;
    }
    //Operator (--prefix):
    Matrix& Matrix::operator -- () {
        std::vector<double> vec;
        for(int i=0; i<this->getSize(); i++){
            vec.push_back(this->getVector().at(i) - 1.0);
        }
        this->setVector(vec);
        return *this;
    }
    //Operator (- prefix):
    Matrix& Matrix::operator - () {
        std::vector<double> vec;
        for(int i=0; i<this->getSize(); i++){
            vec.push_back(this->getVector().at(i) *(-1.0));
        }
        this->setVector(vec);
        return *this;
    }
    //Operator (+ prefix):
    Matrix& Matrix::operator + () {
        return *this;
    }
    //Operator (postfix++)):
    Matrix Matrix::operator ++ (int){
        Matrix temp(*this);
        ++(*this);
        return temp;
    }
    //Operator (postfix--)):
    Matrix Matrix::operator -- (int){
        Matrix temp(*this);
        --(*this);
        return temp;
    }
    
        
        
    
}
    


int main(){
    using namespace std;
    std::vector<double> v1 = {0,0,0,0,0,0};
    std::vector<double> v2 = {1,1,1,1,1,1};
    std::vector<double> v3 = {1,2,0,1,1,1};
    std::vector<double> v4 = {2,1,3,1,2,0};
    zich::Matrix m1{v3, 3, 2};
    zich::Matrix m2{v2, 3, 2};
    cout<<"m2:"<<endl;
    m2.printMatrix();

    cout<<"m3:"<<endl;
    zich::Matrix m3 = m2--;
    m3.printMatrix();

    cout<<"m2:"<<endl;
    m2.printMatrix();

    cout<<"m2--:"<<endl;
    m2--;
    m2.printMatrix();

    
    // cout<<"m3:"<<endl;
    // zich::Matrix m3 = ++m2;
    // m3.printMatrix();

    return 0;
}
