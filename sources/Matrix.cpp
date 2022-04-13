#include "Matrix.hpp"
#include <iomanip>
#include <sstream>
#include <iostream>
#include <istream>
#include <string>

const int DOUBLE_SIZE = 8;
namespace zich{
    //Constructors
    Matrix::Matrix(){
        std::vector<double> vec = {0};
        this->_col = 1;
        this->_row = 1;
        this->_mat = vec;
        this->_size = 1;
    }
    Matrix::Matrix(const std::vector<double> &m, int r, int c){
        if(r < 1 || c < 1){
            throw std::runtime_error("Matrix Constructor Error: Row must be greater than 0.");
        }
        if(r*c != m.size()){
            throw std::runtime_error("Matrix Constructor Error: Vector size does not match row*column input.");
        }
        if(m.empty()){
            throw std::runtime_error("Matrix Constructor Error: Vector is empty.");
        }
        for(int i=0; i<(m.size()); i++){
            if(sizeof(m.at(i)) != DOUBLE_SIZE){
                throw std::runtime_error("Matrix Constructor Error: Vector element is not of type double.");
            }
        }
        this->_row = r;
        this->_col = c;
        this->_size = r*c;
        this->setVector(m);
    }
    Matrix::Matrix(const Matrix& other){
        this->_col = other.getColumn();
        this->_row = other.getRow();
        this->_size = other.getSize();
        this->_mat = other.getVector();
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
                stream << std::fixed << std::setprecision(2) << this->getVector()[(unsigned int)(i*c)+(unsigned int)j];
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
    double Matrix::sum() const{
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
        vec.resize((unsigned int)this->getSize());
        for(int i=0; i<this->getSize(); i++){
            vec[(unsigned int)i] = this->getVector().at((unsigned int)i) + other.getVector().at((unsigned int)i);
        }
        return Matrix(vec, this->getRow(), this->getColumn());
    }

    //Operator (-):
    Matrix Matrix::operator - (const Matrix& other) const{
        if(this->getRow() != other.getRow() || this->getColumn() != other.getColumn()){
            throw std::runtime_error("Operator (-) Error: 'This' Matrix and 'other' Matrix Row/Column do not match.");
        }
        std::vector<double> vec;
        vec.resize((unsigned int)this->getSize());
        for(int i=0; i<this->getSize(); i++){
            vec[(unsigned int)i] = this->getVector().at((unsigned int)i) - other.getVector().at((unsigned int)i);
        }
        return Matrix(vec, this->getRow(), this->getColumn());
    }

    //Operator (mat*mat):
    Matrix Matrix::operator * (const Matrix& other) const{
        if(this->getColumn() != other.getRow()){
            throw std::runtime_error("Operator (*) Error: Matrix1 Column does not equal Matrix2 Row.");
        }
        std::vector<double> vec((unsigned long)(this->getRow()*other.getColumn()), 0.0);
        int spot = 0;
        for(int i=0; i<this->getRow(); i++){
            for(int j=0; j<other.getColumn(); j++){
                for(int k=0; k<this->getColumn(); k++){
                    int index1 = (i*this->getColumn()) + k;
                    int index2 = (k*other.getColumn()) + j;
                    vec.at((unsigned long)spot) += this->getVector().at((unsigned long)index1) * other.getVector().at((unsigned long)index2);
                }
                spot++;
            }
        }
        return Matrix(vec, this->getRow(), other.getColumn());
    }

    //Operator (mat*num):
    Matrix Matrix::operator * (const double num) const{
        std::vector<double> vec;
        vec.resize((unsigned int)this->getSize());
        for(int i=0; i<this->getSize(); i++){
            vec[(unsigned int)i] = this->getVector().at((unsigned int)i) * num;
        }
        return Matrix(vec, this->getRow(), this->getColumn());
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
    //Operator (*= num):
    Matrix& Matrix::operator *= (const double num){
        return (*this = num * (*this));
    }
    //Operator (==):
    bool Matrix::operator == (const Matrix& other) const{
        if(this->getRow() != other.getRow() || this->getColumn() != other.getColumn()){
            throw std::runtime_error("Operator (==) Error: 'This' Matrix and 'other' Matrix Row/Column do not match.");
        }
        for(int i=0; i<this->getSize(); i++){
            if(this->getVector().at((unsigned long)i) != other.getVector().at((unsigned long)i)){
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
        vec.resize((unsigned int)this->getSize());
        for(int i=0; i<this->getSize(); i++){
            vec[(unsigned int)i] = this->getVector().at((unsigned int)i) + 1.0;
        }
        this->setVector(vec);
        return *this;
    }
    //Operator (--prefix):
    Matrix& Matrix::operator -- () {
        std::vector<double> vec;
        vec.resize((unsigned int)this->getSize());
        for(int i=0; i<this->getSize(); i++){
            vec[(unsigned int)i] = this->getVector().at((unsigned int)i) - 1.0;
        }
        this->setVector(vec);
        return *this;
    }
    //Operator (- prefix):
    Matrix& Matrix::operator - () {
        std::vector<double> vec;
        vec.resize((unsigned int)this->getSize());
        for(int i=0; i<this->getSize(); i++){
            vec[(unsigned int)i] = this->getVector().at((unsigned int)i) * -1.0;
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

    //Friend Operators:
    //Operator (num*Matrix)):
    Matrix operator * (double num, const Matrix& other){
        std::vector<double> vec;
        vec.resize((unsigned int)other.getSize());
        for(int i=0; i<other.getSize(); i++){
            vec[(unsigned int)i] = other.getVector().at((unsigned int)i) * num;
        }
        return Matrix(vec, other.getRow(), other.getColumn());
    }
    //Operator (cout)):
    std::ostream& operator << (std::ostream& out, const Matrix& other){
        int r = other.getRow();
        int c = other.getColumn();
        int counter = 0;
        std::string ans;
        for(int i=0; i<r; i++){
            ans += "[";
            for(int j=0; j<c; j++){
                std::stringstream stream;
                stream << other.getVector().at((unsigned int)(counter++));
                ans += stream.str();
                stream.str("");
                ans += " ";
            }
            ans.pop_back();
            ans += "]\n";
        }
        ans.pop_back();
        out << ans;
        return out;
    }

    //Operator (cin)):
    std::istream& operator >> (std::istream& in,  Matrix& other){
        //Initializing the final Variables for the setters:
        std::vector<double> vec_final;
        int row_final=0;
        int col_final=0;

        //Using 'std::getline' to convert the instream input to type String:
        std::string input; //for combining the lines
        std::getline(in, input);
        std::cout << "\ninput:" << input <<std::endl;/////////////////////////////////////////////////////////////////////////

        //Test 1) Checking if the string starts with '[' and ends with ']':
        if(input[0] != '[' || input.back() != ']'){
            throw std::runtime_error("Operator (cin) Error: Input missing '[' or ']' character on start/end.");
        }
        //Test 2) Checking if the input is not empty:
        std::string test2 = input;
        std::string nums = "0123456789";
        int test2Count = 0;
        test2.erase(test2.length()-1, 1); //erasing the last character ']'
        test2.erase(0, 1); //erasing the first character '['
        for(int i=0; i<test2.length(); i++){
            if(nums.find(test2.at((unsigned long)i)) != std::string::npos){
                test2Count++;
            }
        }
        if(test2Count==0){
            throw std::runtime_error("Operator (cin) Error: Input does not contain values.");
        }
        

        //Using a <string>vector to store the rows of the input:
        std::vector<std::string> vec_str;

        //Looping through each index of 'ves_str' to extract the information:
        std::string delimiter = ", [";
        while(input.find(delimiter) != std::string::npos){
            std::cout << "\nIteration: "<< (row_final+1) << std::endl;/////////////////////////////////////////////////////////////////////////
            std::cout << "input: "<< input << std::endl;/////////////////////////////////////////////////////////////////////////
            //'token' represents a row from the input. Each token will be stored in 'vec_str':
            std::string token = input.substr(0, input.find(delimiter));/////////////////////////////////////////////////////////////////////////
            std::cout << "token:: "<< token << std::endl;/////////////////////////////////////////////////////////////////////////
            vec_str.push_back(token);
            row_final++;
            //After storing the token in 'vec_str', erase and update the input string:
            input.erase(0, input.find(delimiter) + (delimiter.length()-1));
            std::cout << "input after erase: "<< input << std::endl;/////////////////////////////////////////////////////////////////////////
        }

        //Inserting the remaining row from input in 'vec_str':
        std::cout << "input after WHILE: "<< input << std::endl;/////////////////////////////////////////////////////////////////////////
        // if(input.length() > 0){
        vec_str.push_back(input);
        row_final++;
        // }
        
        std::cout << "\nUPDATEING VEC\n" << std::endl;/////////////////////////////////////////////////////////////////////////
        //These 2 variables will help check if the columns are equal between each row:
        int columnCheck=0;
        bool first = true;
        //Looping through 'vec_str', checking that each row is valid and updating final variables:
        for(int i=0; i<row_final; i++){
            std::cout << "\n\n";/////////////////////////////////////////////////////////////////////////
            std::string temp_row = vec_str.at((unsigned long)i);
            //Test 3) Checking if each row starts with '[' and ends with ']':
            if(temp_row[0] != '[' || temp_row.back() != ']'){
                throw std::runtime_error("Operator (cin) Error: Input Row missing '[' or ']' character on start/end.");
            }
            std::cout<< "temp:" << temp_row << std::endl;/////////////////////////////////////////////////////////////////////////
            temp_row.erase(temp_row.length()-1, 1); //erasing the last character ']'
            std::cout<< "temp after erasing last:" << temp_row << std::endl;/////////////////////////////////////////////////////////////////////////
            temp_row.erase(0, 1); //erasing the first character '['
            std::cout<< "temp after erasing first:" << temp_row << std::endl;/////////////////////////////////////////////////////////////////////////

            std::string allowedChar = "0123456789. "; //These are the allowed characters inbetween each '[ ]' characters per row.
            //Test 4) Checking if the current row contains invalid characters:
            for(int i=0; i<temp_row.length(); i++){
                if(allowedChar.find(temp_row.at((unsigned long)i)) == std::string::npos){
                    throw std::runtime_error("Operator (cin) Error: Input Row contains invalid Character.");
                }
            }
            //Test 5) Checking if there are double-spaces between each number:
            std::string double_space = "  ";
            if(temp_row.find(double_space) != std::string::npos){
                throw std::runtime_error("Operator (cin) Error: Input row contains Double-Space.");
            }
            //Converting the string-numbers into type double:
            std::stringstream Y(temp_row); // Y is an object of stringstream that references 'temp_row' string.
            std::string single_num;
            double currD=0;
            int columnCount=0;
            while(getline(Y, single_num, ' ')){
            //Test 6) Checking that each string-number can be converted into type double:
                try{
                    currD = std::stod(single_num);
                }
                catch(...){
                    throw std::runtime_error("Operator (cin) Error: Unable to convert string-number into type double.");
                }
                std::cout << "Inserting currD: " <<currD<<std::endl;/////////////////////////////////////////////////////////////////////////
                vec_final.push_back(currD);
                columnCount++;
                if(first){
                    columnCheck++;
                }
            }
            first=false;
            //Test 7) Checking that each column contains the same amount of numbers:
            if(columnCount != columnCheck){
                throw std::runtime_error("Operator (cin) Error: Input Columns are not equal.");
            }
        }
        // col_final = vec_final.size()/row_final;

        //Updating the final variables:
        other.setRow(row_final);
        std::cout <<"Set Row: " << other.getRow()<<std::endl;/////////////////////////////////////////////////////////////////////////
        other.setColumn(columnCheck);
        std::cout <<"Set Col: " << other.getColumn()<<std::endl;/////////////////////////////////////////////////////////////////////////
        other.setVector(vec_final);
        std::cout <<"Set Vec: ";/////////////////////////////////////////////////////////////////////////
        for(double d : other.getVector()){
            std::cout << d << " ";
        }
        
        other.setSize(row_final*col_final);
        std::cout <<"\nSet Size: " << other.getSize()<<std::endl;/////////////////////////////////////////////////////////////////////////
        return in;
    }
    
        
        
    
}
    


// int main(){
//     using namespace std;
//     std::vector<double> v1 = {0,0,0,0,0,0};
//     std::vector<double> v2 = {1,1,1,1,1,1};
//     std::vector<double> v3 = {1,2,0,1,1,1};
//     std::vector<double> v4 = {2,1,3,1,2,0};
//     zich::Matrix m1{v3, 3, 2};
//     zich::Matrix m2({1,1,1,1,1,1}, 3, 2);
    
//     m2.printMatrix();
//     // cout<<"m2:"<<endl;
//     // m2.printMatrix();

//     // cout<<"m3:"<<endl;
//     // zich::Matrix m3 = 3.9*m2;
//     // cout << m3;
//     string vec = "[1 2.2 3], [4.98 5 6], [77.5 8 9], [0 11 12]";
//     zich::Matrix m4;
//     // cout << m4.getColumn()<<endl;
//     // cout << m4.getRow()<<endl;
//     // cout << m4.getSize()<<endl;
//     // m4.printMatrix();
    
//     // cout << "Enter string:";
//     // cin >> m4;
//     // cout <<m4;
//     // string temp = "[1 2.2 3]";
//     // std::string allowedChar = "0123456789. ";
//     // std::cout<< "temp:" << temp << std::endl;
//     // temp.erase(temp.length()-1, 1); //erasing the last character ']'
//     // std::cout<< "temp after erasing last:" << temp << std::endl;
//     // temp.erase(0, 1); //erasing the first character '['
//     // std::cout<< "temp after erasing first:" << temp << std::endl;
//     // for(int i=0; i<temp.length(); i++){
//     //     if(allowedChar.find(temp.at(i)) == std::string::npos){
//     //         throw std::runtime_error("Operator (cin) Error: Invalid Input.");
//     //     }
//     // }
//     // cout<<"COMPLETE"<<endl;
    


    
//     // cout<<"m3:"<<endl;
//     // zich::Matrix m3 = ++m2;
//     // m3.printMatrix();

//     return 0;
// }
