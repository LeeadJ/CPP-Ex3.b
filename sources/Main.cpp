// #include "Matrix.hpp"
// #include <iomanip>
// #include <sstream>
// #include <iostream>
// #include <istream>
// #include <string>


// int main(){
//     std::vector<double> vec1 = {1,0,0,0,1,0,0,0,1};
//     std::vector<double> vec2 = {1,1,1,1,1,1,1,1,1};
//     std::vector<double> vec3 = {5,5,5,5,5,5,5,5,5};
//     std::vector<double> vec4 = {1};
//     std::vector<double> vec5 = {1,1,1,1,2,2,2,2,3,3,3,3,4,4,4,4,5,5,5,5,6,6,6,6,7,7,7,7,8,8,8,8,9,9,9,9,10,10,10,10};

//     zich::Matrix m1{vec1, 3, 3};
//     zich::Matrix m2{vec2, 3, 3};
//     zich::Matrix m3{vec3, 3, 3};
//     zich::Matrix m4{vec4, 1, 1};
//     zich::Matrix m5{vec5, 10, 4};
//     zich::Matrix m6{vec5, 4, 10};

//     std::cout<<"\nM1: 3x3"<<std::endl;
//     std::cout << m1 << std::endl;
//     std::cout<<"\nM2: 3x3"<<std::endl;
//     std::cout << m2 << std::endl;
//     std::cout<<"\nM3: 3x3"<<std::endl;
//     std::cout << m3 << std::endl;
//     std::cout<<"\nM4: 1x1"<<std::endl;
//     std::cout << m4 << std::endl;
//     std::cout<<"\nM5: 10x4"<<std::endl;
//     std::cout << m5 << std::endl;
//     std::cout<<"\nM6: 4x10"<<std::endl;
//     std::cout << m6 << std::endl;

//     std::cout<<"\nM1 + M2"<<std::endl;
//     std::cout << (m1+m2) << std::endl;
//     std::cout<<"\nM1 * M2"<<std::endl;
//     std::cout << (m1*m2) << std::endl;
//     std::cout<<"\nM5*0"<<std::endl;
//     std::cout << (m5*0) << std::endl;

//     std::cout<<"\nM4 += M4 (10 iterations)"<<std::endl;
//     for(int i=0; i<10; i++){
//         std::cout << m4 << " ";
//         m4+=m4;
//     }

//     std::cout<<"\nM5 *= M6 (10 iterations)"<<std::endl;
//     for(int i=0; i<10; i++){
//         std::cout << m5 << std::endl;
//         m5*=m6;
//     }

    

//     return 0;
// }