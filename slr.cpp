#include <iostream>
#include <unistd.h>
#include <functional>
#include <cmath>
#include <stdio.h>
//#include<graphics.h>
#include <math.h>
#include <vector>
#include <sstream>
#include <string>


template <typename T> std::string tostr(const T& t) {
    std::ostringstream os;
    os << t;
    return os.str();
}

//Function for finding absolute value




int sort_handler1(int a, int b) {
    return a - b;
}

int sort_handler2(int a, int b) {
    return a - b;
}

// C++ port of JS's array.prototype.sort() function. Supports handler to change the sorting behaviour.
std::vector<int> sort(std::vector<int> p, int arrsize, std::function<int (int, int)> handler) {

    int max = arrsize;
    int index = 1;
    while (index < max) {
        int result = handler(p[index - 1], p[index]);
        if (result <= 0) {
            index = ++index;
        } else {

            int tmp1 = p[index - 1];
            int tmp2 = p[index];

            std::swap(p[index - 1], p[index]);
            index = 1;

        }
    }

    return p;
}










int reducehandler1(int total, int i) {
    return total + i;
}
// JS port of Reduce function from array prototype.reduce(). Supports handler to change the behaviour.
int reduce(std::function<int (int, int)> handler, std::vector<int> iter, int arrsize, int initial = 0) {

    int total = initial;
    for (int i = 0; i <= arrsize; ++i)
    {
        total = handler(total, i);
    }

    return total;
}







int _ROUND(double a) {
    double b = a + 0.5;
    return (int)b;
}








//DDA Function for line generation
std::vector<std::vector<int> > line(int X0, int Y0, int X1, int Y1)
{
    // calculate dx & dy
    int dx = X1 - X0;
    int dy = Y1 - Y0;

    // calculate steps required for generating pixels
    int steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);

    // calculate increment in x & y for each steps
    float Xinc = dx / (float) steps;
    float Yinc = dy / (float) steps;

    // Put pixel for each step
    float X = X0;
    float Y = Y0;
    std::vector<std::vector<int> > points;

    for (int i = 0; i <= steps; i++)
    {
        std::vector<int > point;
        point.push_back(X);
        point.push_back(Y);
        points.push_back(point);
        //putpixel (round(X),round(Y),RED);  // put pixel at (X,Y)
        points[i][0] = (int)round(X);
        points[i][1] = (int)round(Y);

        //points[i](point);
        X += Xinc;           // increment in x at each step
        Y += Yinc;           // increment in y at each step
        //delay(100);          // for visualization of line-
        // generation step by step
    }
    //std::cout << "\n\n\nprewarmed: " << points[6][0] << "\n\n\n";

    return points;
}







int abs (int n)
{
    return ( (n > 0) ? n : ( n * (-1)));
}


int main() {


    /*


    INIT


    */

    std::ostringstream ss;
    //windows size. Number of pixels
    int x_size = 200;
    int y_size = 200;

    int pixel[y_size * x_size] = { 0 };
    int pixel_size = y_size * x_size;

    std::vector< int > pixel_demo; //smaller array for testing purposes

    pixel_demo.push_back(1);
    pixel_demo.push_back(7);
    pixel_demo.push_back(5);
    pixel_demo.push_back(2);
    pixel_demo.push_back(6);
    pixel_demo.push_back(3);
    pixel_demo.push_back(8);
    pixel_demo.push_back(4);
    pixel_demo.push_back(10);
    pixel_demo.push_back(9);

    int pixel_demo_size = pixel_demo.size();

    /*


    SORT


    */



    std::vector<int> resultsort = sort(pixel_demo, pixel_demo_size, sort_handler1);



    /*


    REDUCE


    */

    int resultreduce = reduce(reducehandler1, pixel_demo, pixel_demo_size);


    /*


    ROUND


    */

    double x = 55.49;
    int resultround = _ROUND(x);


    /*


    LINE


    */


    int x1, y1, x2, y2;
    x1 = 10;
    y1 = 30;
    x2 = 40;
    y2 = 120;

    std::vector<std::vector<int> > lines = line(x1, y1, x2, y2);

    for (int i = 0; i < lines.size(); ++i)
    {
        std::vector<int >  point = lines[i];
        std::cout << "\n\n X:" << point[0] << "  Y:" << point[1];

    }


    /*


    OTHER


    */

    return 0;
}


