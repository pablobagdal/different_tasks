#include<stdio.h>
#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<algorithm>

using namespace std;

//program has valuable leek of memory. I'm not sure, 'cause don't use delete[], meanwhile every new instance in vector built by default constructor.
//No, Now I think it's fine. I use pointer newPoint to make new point. But they all kept in vector, so I'm able to delete all of them
struct Point {
    int x;
    int y;
};

int main()
{
    ifstream file ("RL.txt");
 
    if (!file) 
    {
        cout << "Файл не открыт\n\n";  
        return -1;
    }
    cout << "Все ОК! Файл открыт!\n\n";
    
    vector<Point> arrayOfPoints;

    Point *newPoint;
    Point *currentPoint = new Point;
    
    currentPoint->x=0;
    currentPoint->y=0;
    
    arrayOfPoints.push_back(*currentPoint);
 
    vector<Point>::iterator it;
    
    int steps=0;                                                             //used to define which direction is modifying
 
    string s;                                                                //saves current row
    string subStr;                                                           //used to get "steps" from "s"
    
    int i_x;
    int i_y;
    char dir = 'N';

    for(file >> s; !file.eof(); file >> s){
        //choose direction
        switch (dir)
        {
        case 'N':
            if (s[0] == 'R')
            {
                i_x = 1;
                i_y = 0;
                dir = 'E';
            }else{
                i_x = -1;
                i_y = 0;
                dir = 'W';
            }
            break;
        case 'E':
            if (s[0] == 'R')
            {
                i_x = 0;
                i_y = -1;
                dir = 'S';
            }else{
                i_x = 0;
                i_y = 1;
                dir = 'N';
            }
            break;
        case 'S':
            if (s[0] == 'R')
            {
                i_x = -1;
                i_y = 0;
                dir = 'W';
            }else{
                i_x = 1;
                i_y = 0;
                dir = 'E';
            }
            break;
        case 'W':
            if (s[0] == 'R')
            {
                i_x = 0;
                i_y = 1;
                dir = 'N';
            }else{
                i_x = 0;
                i_y = -1;
                dir = 'S';
            }
            break;
        
        default:
            break;
        }
        
        //define how many steps to go 
        subStr = s.substr(1);                                                //cut 1st sign R or L
        if(subStr.back() == ',')
            subStr = subStr.substr(0,subStr.length()-1);
        steps = stoi(subStr); 
        //cout << "Steps: " << steps << endl;

        //main cycle
        for (int i = 0; i < steps; i++)
        {
            newPoint = new Point;
            newPoint->x = currentPoint->x + i_x;
            newPoint->y = currentPoint->y + i_y;
            //cout << "new point made: " << newPoint->x << ' ' << newPoint->y << endl;
            
            for (Point i: arrayOfPoints){             
                if (i.x == newPoint->x && i.y == newPoint->y){
                    cout << "Distance: " << i.x+i.y << endl;
                    cout << "The program finished." << endl;
                    return 1;
                    
                }
            }
            arrayOfPoints.push_back(*newPoint);
            currentPoint = newPoint;            
        }
        
    }

    return 0;
}
