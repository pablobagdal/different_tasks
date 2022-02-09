#include<stdio.h>
#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<algorithm>

using namespace std;

struct Point {
    int x;
    int y;
};

int main()
{
    string fileName = "Santa.txt";

    ifstream file (fileName);
 
    if (!file) 
    {
        cout << "Файл не открыт\n\n";  
        return -1;
    }
    cout << "Все ОК! Файл открыт!\n\n";
    

    int i_x;
    int i_y;
    char ch;
    bool flagRepeat = false;

    vector<Point> arrayOfPoints;

    Point *newPoint;
    Point *currentPoint = new Point;
    currentPoint->x = 0;
    currentPoint->y = 0;
    
    arrayOfPoints.push_back(*currentPoint);
 
    vector<Point>::iterator it;

    int count = 1;
    cout << "real Santa" << endl;
    while(file >> noskipws >> ch){
        if (count % 2 == 1)
        {
            //cout << ch << ' ';
        //choose direction
        switch (ch)
        {
        case '^':
            i_x = 0;
            i_y = 1;
            break;
        case '>':
            i_x = 1;
            i_y = 0;
            break;
        case 'v':
            i_x = 0;
            i_y = -1;
            break;
        case '<':
            i_x = -1;
            i_y = 0;
            break;
        
        default:
            break;
        }

        newPoint = new Point;
        newPoint->x = currentPoint->x + i_x;
        newPoint->y = currentPoint->y + i_y;
        //cout << "new " << newPoint->x << ' ' << newPoint->y;
        for (Point i: arrayOfPoints){          
            if (i.x == newPoint->x && i.y == newPoint->y){
                flagRepeat = true;
                // cout << " repeat heppend" << endl;
                break;
                }
        }
        if(!flagRepeat){
            arrayOfPoints.push_back(*newPoint); 
        }
        flagRepeat = false;
        currentPoint = newPoint;        
        
        //cout << endl;
        }
        count++;
        
    }

    file.close();
    file.open(fileName);
 
    if (!file) 
    {
        cout << "Файл не открыт\n\n";  
        return -1;
    }
    cout << "Все ОК! Файл открыт!\n\n";

    count = 1;
    currentPoint = new Point;
    currentPoint->x = 0;
    currentPoint->y = 0;

    cout << "robot Santa" << endl;
    while(file >> noskipws >> ch){
        if (count % 2 == 0)
        {
            //cout << ch << ' ';
        //choose direction
        switch (ch)
        {
        case '^':
            i_x = 0;
            i_y = 1;
            break;
        case '>':
            i_x = 1;
            i_y = 0;
            break;
        case 'v':
            i_x = 0;
            i_y = -1;
            break;
        case '<':
            i_x = -1;
            i_y = 0;
            break;
        
        default:
            break;
        }

        newPoint = new Point;
        newPoint->x = currentPoint->x + i_x;
        newPoint->y = currentPoint->y + i_y;
        //cout << "new " << newPoint->x << ' ' << newPoint->y;
        for (Point i: arrayOfPoints){          
            if (i.x == newPoint->x && i.y == newPoint->y){
                flagRepeat = true;
                // cout << " repeat heppend" << endl;
                break;
                }
        }
        if(!flagRepeat){
            arrayOfPoints.push_back(*newPoint); 
        }
        flagRepeat = false;
        currentPoint = newPoint;        
        
        //cout << endl;
        }
        count++;
        
        
    }

    cout << count << ' ';
        
    cout << "Count: " << arrayOfPoints.size() << endl;


    // for (it = arrayOfPoints.begin(); it != arrayOfPoints.end(); ++it) {
    //     cout << it->x << ' ' << it->y << endl;
    // }

    return 1;
}
