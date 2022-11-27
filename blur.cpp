#include "iosyn.h"
#include<fstream>
#include<regex>
#include<algorithm>
#include<string>
#include<string.h>

using namespace std;


int main(int argc, char *argv[]){
    if(argc==1){
        cout<<"Error! You have not entered your file name!"<<endl;
    }
    else if(argc == 2){
        string fileName = argv[1];
        ofstream interTarget("__interTarget.cpp");
        ifstream readFile(fileName);
        ifstream header("header.temp");
        string __line;
        while (getline (header, __line)) {
            interTarget << __line << endl;
        }
        while (getline (readFile, __line)) {
            while (1) {
                if(__line[0] != '\t' && __line[0] != ' ')   break;
                __line.erase(0,1);
                
            }
            if(__line.substr(0,4) == "var "){
                __line.erase(0,3);
                __line = "auto" + __line;
            }
            if(__line.substr(0,6) == "const "){
                __line.erase(0,5);
                __line = "const auto" + __line;
            }
            if(__line.substr(0,3) == "in("){
                int index = 3;
                __line.insert(index,"&");
                while(index<__line.size()){
                    if(__line[index] == ','){
                        index++;
                        __line.insert(index,"&");
                    }
                    index++;
                }
            }
            if(__line.substr(0,3) == "if "){
                __line.insert(3,"(");
                __line.insert(__line.size()-1,")");
                
            }
            if(__line.substr(0,6) == "while "){
                __line.insert(6,"(");
                __line.insert(__line.size()-1,")");
                
            }
            interTarget << __line << ";" << endl;
            
        }
        interTarget << "return 0;\n}\n";

        readFile.close();
        header.close();
        interTarget.close();
        
        system("g++ ./__interTarget.cpp -o interTarget");
        system("./interTarget");
    }
    
}