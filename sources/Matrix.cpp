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

    double const Matrix::sum() const{
        double ans = 0;
        for(double d : this->getVector()){
            ans += d;
        }
        return ans;
    }

    //Operators
    //Oerator (+):
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

    //Oerator (-):
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

    //Oerator (*):
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
    //Oerator (+=):
    Matrix& Matrix::operator += (const Matrix& other){
        if(this->getRow() != other.getRow() || this->getColumn() != other.getColumn()){
            throw std::runtime_error("Operator (+=) Error: 'This' Matrix and 'other' Matrix Row/Column do not match.");
        }
        return (*this = *this + other);
    }
    //Oerator (-=):
    Matrix& Matrix::operator -= (const Matrix& other){
        if(this->getRow() != other.getRow() || this->getColumn() != other.getColumn()){
            throw std::runtime_error("Operator (+=) Error: 'This' Matrix and 'other' Matrix Row/Column do not match.");
        }
        return (*this = *this - other);
    }
    //Oerator (==):
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

    //Oerator (!=):
    bool Matrix::operator != (const Matrix& other) const{
        if(this->getRow() != other.getRow() || this->getColumn() != other.getColumn()){
            throw std::runtime_error("Operator (!=) Error: This Matrix and 'other' Matrix Row/Column do not match.");
        }
        return !(*this == other);
    }

    //Oerator (>=):
    bool Matrix::operator >= (const Matrix& other) const{
        if(this->getRow() != other.getRow() || this->getColumn() != other.getColumn()){
            throw std::runtime_error("Operator (>=) Error: This Matrix and 'other' Matrix Row/Column do not match.");
        }
        return this->sum() >= other.sum();
    }

    //Oerator (<=):
    bool Matrix::operator <= (const Matrix& other) const{
        if(this->getRow() != other.getRow() || this->getColumn() != other.getColumn()){
            throw std::runtime_error("Operator (>=) Error: This Matrix and 'other' Matrix Row/Column do not match.");
        }
        return this->sum() <= other.sum();
    }

    //Oerator (>):
    bool Matrix::operator > (const Matrix& other) const{
        if(this->getRow() != other.getRow() || this->getColumn() != other.getColumn()){
            throw std::runtime_error("Operator (>=) Error: This Matrix and 'other' Matrix Row/Column do not match.");
        }
        return this->sum() > other.sum();
    }

    //Oerator (<):
    bool Matrix::operator < (const Matrix& other) const{
        if(this->getRow() != other.getRow() || this->getColumn() != other.getColumn()){
            throw std::runtime_error("Operator (>=) Error: This Matrix and 'other' Matrix Row/Column do not match.");
        }
        return this->sum() < other.sum();
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
    cout << "m1 sum: " <<m1.sum() << endl;
    cout << "m2 sum: " <<m2.sum() << endl;
    cout << "\nm1==m2\n" << endl;
    bool a = m1==m2;
    cout << a << endl;
    cout << "\nm1>=m2\n" << endl;
    bool b = m1>=m2;
    cout << b << endl;
    cout << "\nm1<=m2\n" << endl;
    bool c = m1<=m2;
    cout << c << endl;
    cout << "\nm1!=m2\n" << endl;
    bool d = m1!=m2;
    cout << d << endl;
    cout << "\nm1>m2\n" << endl;
    bool e = m1>m2;
    cout << e << endl;
    cout << "\nm1<m2\n" << endl;
    bool f = m1<m2;
    cout << f << endl;
    // std::cout << "\nm1\n";
    // m1.printMatrix();
    // std::cout << "\nm2\n";
    // m2.printMatrix();
    // std::cout << "\nm5=m2 * m1\n";
    // m5.printMatrix();
    // std::cout << "\nm5+=m5\n";
    // m5 += m5;
    // m5.printMatrix();
    // std::cout << "\nm5-=m5\n";
    // m5 -= m5;
    // m5.printMatrix();

    return 0;
}
