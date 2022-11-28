#include "iosyn.h"
#include<fstream>
#include<regex>
#include<algorithm>
#include<vector>
#include<string>
#include<string.h>

using namespace std;


int main(int argc, char *argv[]){
    vector<string> funcs;
    vector<string> mainBody;
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
            if(__line.substr(0,5) == "func "){
                __line.erase(0,4);
                __line = "int" + __line;
                string func = __line;
                
                int openedP = 1;
                while(openedP > 0){
                    getline (readFile, __line);
                    while (1) {
                if(__line[0] != '\t' && __line[0] != ' ')   break;
                __line.erase(0,1);
                
            }
                        if(__line.substr(0,4) == "var "){
                        bool isString = false;
                        for(int i = 0;i<__line.size();i++){
                            if(__line[i] == '"'){
                                isString = true;
                                __line.erase(0,3);
                                __line = "string" + __line;
                                break;
                            }
                            
                        }
                            
                        if(!isString){
                            __line.erase(0,3);
                            __line = "auto" + __line;
                        }
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
                    if(__line.substr(0,5) == "elif "){
                        __line.insert(5,"(");
                        __line.insert(__line.size()-1,")");
                        
                    }
                    if(__line.substr(0,6) == "while "){
                        __line.insert(6,"(");
                        __line.insert(__line.size()-1,")");
                        
                    }
                    for(auto c: __line){
                        if(c == '}')    openedP--;
                        if(c == '{')    openedP++;
                    }
                    func+="\n"+__line + ";";
                }
                funcs.push_back(func);
                continue;
            }
            if(__line.substr(0,4) == "var "){
                bool isString = false;
                for(int i = 0;i<__line.size();i++){
                    if(__line[i] == '"'){
                        isString = true;
                        __line.erase(0,3);
                        __line = "string" + __line;
                        break;
                    }
                    
                }
                    
                if(!isString){
                    __line.erase(0,3);
                    __line = "auto" + __line;
                }
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
            if(__line.substr(0,5) == "elif "){
                __line.insert(5,"(");
                __line.insert(__line.size()-1,")");
                
            }
            if(__line.substr(0,6) == "while "){
                __line.insert(6,"(");
                __line.insert(__line.size()-1,")");
                
            }
            if(__line[__line.size()-1] != '}')  mainBody.push_back(__line+';'+'\n');
            else    mainBody.push_back(__line+'\n');
            
        }
        for(auto s: funcs){
            interTarget << s << endl;
        }
        interTarget << "\n int main() {\n";
        for(auto s: mainBody){
            interTarget << s ;
        }

        interTarget << "return 0;\n}\n";

        readFile.close();
        header.close();
        interTarget.close();
        
        system("g++ ./__interTarget.cpp -o interTarget");
        system("./interTarget");
    }
    
}