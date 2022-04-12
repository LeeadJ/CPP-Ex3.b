
#include <iomanip>
#include <sstream>
#include <iostream>
#include <istream>
#include <string>
#include<vector>

using namespace std;
int main(){
    string s = "[1 2 3], [4 5 6]";
    string s2 = "[7 8 9]";
    string delimiter = ", ";
    std::vector<string> vec;
    while(s.find(delimiter) != string::npos){
        cout << "string:" << s << endl;
        string token = s.substr(0, s.find(delimiter));
        cout << "token:" <<token << endl;
        vec.push_back(token);
        s.erase(0, s.find(delimiter) + delimiter.length());
    }
    cout << "string:" << s << endl;
    vec.push_back(s);
    cout << "\nvec"<<endl;
    for(int i=0; i<vec.size(); i++){
        cout << vec.at(i) <<endl;
    }

    return 0;
}