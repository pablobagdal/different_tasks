#include<stdio.h>
#include<iostream>
#include<fstream>
#include<string>
#include<cmath>

using namespace std;

void DefineCoordinate(string line, int comma, int &coord, int one){
    string a = "";
    if (one < 0)
    {
        for (int i = 3; i > 0; i--){
            if (isdigit(line[comma-i]))
                {            
                    a += line[comma+ i*one];
                    coord = stoi(a);
                }
        }
    }else{
        for (int i = 1; i < 4; i++){
            if (isdigit(line[comma+i]))
                {            
                    a += line[comma+ i];
                    coord = stoi(a);
                }
        }
    }
    
    
}
void Foo(int matr[1000][1000], int val, int x1,int y1,int x2,int y2){
    for (int i = x1; i <= x2; i++)
    {
        for (int j = y1; j <= y2; j++)
        {
            if (!(val == -1 && matr[i][j] == 0))
            {
                matr[i][j] += val;
            }
            
        }
        
    }
    
}
int main()
{
    int matr[1000][1000];
    for (int i = 0; i < 1000; i++)
    {
        for (int j = 0; j < 1000; j++)
        {
            matr[i][j] = 0;
        }
        
    }
    
    string line;
    string subStr;
    int count = 0;
    int x1,y1,x2,y2;
    int comma, comma2;
    string a;

    ifstream myfile ("06.txt");
    if (myfile.is_open())
    {
        while ( getline (myfile,line) )
        {
            //cout << line << '\n';
            //распознаём части строки
            subStr = line.substr(0,7);// toggle/turn on/turn off
            comma = line.find(',');
            comma2 = line.find(',',18);
            x1=0;
            x2=0;
            y1=0;
            y2=0;

            DefineCoordinate(line, comma, x1, -1);
            DefineCoordinate(line, comma, y1, 1);
            DefineCoordinate(line, comma2, x2, -1);
            DefineCoordinate(line, comma2, y2, 1);
            

            
            if (subStr == "toggle ")
            {
                // cout << "this is toggle" << endl;
                Foo(matr, 2, x1,y1,x2,y2);

            }else if (subStr == "turn on")
            {
                // cout << "this is turn on" << endl;
                Foo(matr, 1, x1,y1,x2,y2);
            }else if (subStr == "turn of")
            {
                // cout << "this is turn off" << endl;
                Foo(matr, -1, x1,y1,x2,y2);
            }


             cout << "(" << x1 << ',' << y1 << "), (" << x2 << ',' << y2 << ')' << endl;
            
        }
        for (int i = 0; i < 1000; i++){
            for (int j = 0; j < 1000; j++){
                count += matr[i][j];
                //cout << matr[i][j];
            }
            // cout << endl;
        }
        cout << "Result: " << count << endl;
        myfile.close();
    }

    else cout << "Unable to open file";

    return 1;
}
