#include<stdio.h>
#include<iostream>
#include<fstream>
#include<vector>
#include<algorithm>
#include<set>

using namespace std;

int main(){

    int count = 0;
    set<string> lines;
    string line1;
    string subStr;
    ifstream myfile("09.txt");
    bool inTrash = false;                                      //признак того, что мы находимся в мусоре
    char ch;
    
    
    if (myfile.is_open()){
        while(myfile >> noskipws >> ch){
            if (!inTrash){
                if (ch == '<')
                {
                    inTrash = true;
                }
            }else if (ch == '!')
            {
                myfile >> noskipws >> ch;
            }else if (ch == '>')
            {
                inTrash = false;
            }else{
                count++;
            }
        }  
        cout << "the end" << endl;
        cout << count << endl;
    }
    else 
        cout << "Unable to open file";
    return 1;
}
