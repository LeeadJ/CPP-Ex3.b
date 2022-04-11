#include "Matrix.hpp"
using namespace std;
using namespace zich;
int main(){
    Matrix m1;
    vector<double> v{1,0,0,0,1,0,0,0,1};
    Matrix m2{v, 3, 3};
    Matrix m3(m2);

    m1.printMatrix();
    m2.printMatrix();
    m3.printMatrix();

    return 0;
}