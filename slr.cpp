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

#include <algorithm>
#include <utility>

//Function to convert a variable type in memory to std::string
template <typename T> std::string tostr(const T& t) {
    std::ostringstream os;
    os << t;
    return os.str();
}


//Todo add a or expression in case 0
//handler to alter the sorting function behaviour. sorts in order

int sort_handler1(int a, int b) {
    return a - b;
}

//handler to alter the sorting function behaviour. sorts backward.

int sort_handler2(int a, int b) {
    return b - a;
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









//handler function run in loop. it adds i to the total recursively.
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






//Round down a number like std::floor by converting the number to an int.
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

    //TODO when other functions implemented.
    //Check if steps is too low. if so then switch to next algorithm int* linehoriz

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

int _fpart(int x){
    return x - std::floor(x);
}

int _rfpart(int x){
    return 1 - _fpart(x);
}


std::vector<std::vector<int> > linehoriz (short X0, short Y0, short X1, short Y1,
         short BaseColor, short NumLevels, unsigned short IntensityBits)
{
   unsigned short IntensityShift, ErrorAdj, ErrorAcc;
   unsigned short ErrorAccTemp, Weighting, WeightingComplementMask;
   short DeltaX, DeltaY, Temp, XDir;

   /* Make sure the line runs top to bottom */
   if (Y0 > Y1) {
      Temp = Y0; Y0 = Y1; Y1 = Temp;
      Temp = X0; X0 = X1; X1 = Temp;
   }
   /* Draw the initial pixel, which is always exactly intersected by
      the line and so needs no weighting */
   DrawPixel(X0, Y0, BaseColor);

   if ((DeltaX = X1 - X0) >= 0) {
      XDir = 1;
   } else {
      XDir = -1;
      DeltaX = -DeltaX; /* make DeltaX positive */
   }
   /* Special-case horizontal, vertical, and diagonal lines, which
      require no weighting because they go right through the center of
      every pixel */
   if ((DeltaY = Y1 - Y0) == 0) {
      /* Horizontal line */
      while (DeltaX-- != 0) {
         X0 += XDir;
         DrawPixel(pDC,X0, Y0, BaseColor);
      }
      return;
   }
   if (DeltaX == 0) {
      /* Vertical line */
      do {
         Y0++;
         DrawPixel(X0, Y0, BaseColor);
      } while (--DeltaY != 0);
      return;
   }
   if (DeltaX == DeltaY) {
      /* Diagonal line */
      do {
         X0 += XDir;
         Y0++;
         DrawPixel(X0, Y0, BaseColor);
      } while (--DeltaY != 0);
      return;
   }
   /* Line is not horizontal, diagonal, or vertical */
   ErrorAcc = 0;  /* initialize the line error accumulator to 0 */
   /* # of bits by which to shift ErrorAcc to get intensity level */
   IntensityShift = 16 - IntensityBits;
   /* Mask used to flip all bits in an intensity weighting, producing the
      result (1 - intensity weighting) */
   WeightingComplementMask = NumLevels - 1;
   /* Is this an X-major or Y-major line? */
   if (DeltaY > DeltaX) {
      /* Y-major line; calculate 16-bit fixed-point fractional part of a
         pixel that X advances each time Y advances 1 pixel, truncating the
         result so that we won't overrun the endpoint along the X axis */
      ErrorAdj = ((unsigned long) DeltaX << 16) / (unsigned long) DeltaY;
      /* Draw all pixels other than the first and last */
      while (--DeltaY) {
         ErrorAccTemp = ErrorAcc;   /* remember current accumulated error */
         ErrorAcc += ErrorAdj;      /* calculate error for next pixel */
         if (ErrorAcc <= ErrorAccTemp) {
            /* The error accumulator turned over, so advance the X coord */
            X0 += XDir;
         }
         Y0++; /* Y-major, so always advance Y */
         /* The IntensityBits most significant bits of ErrorAcc give us the
            intensity weighting for this pixel, and the complement of the
            weighting for the paired pixel */
         Weighting = ErrorAcc >> IntensityShift;
         DrawPixel(pDC,X0, Y0, BaseColor + Weighting);
         DrawPixel(pDC,X0 + XDir, Y0,
               BaseColor + (Weighting ^ WeightingComplementMask));
      }
      /* Draw the final pixel, which is 
         always exactly intersected by the line
         and so needs no weighting */
      DrawPixel(X1, Y1, BaseColor);
      return;
   }
   /* It's an X-major line; calculate 16-bit fixed-point fractional part of a
      pixel that Y advances each time X advances 1 pixel, truncating the
      result to avoid overrunning the endpoint along the X axis */
   ErrorAdj = ((unsigned long) DeltaY << 16) / (unsigned long) DeltaX;
   /* Draw all pixels other than the first and last */
   while (--DeltaX) {
      ErrorAccTemp = ErrorAcc;   /* remember current accumulated error */
      ErrorAcc += ErrorAdj;      /* calculate error for next pixel */
      if (ErrorAcc <= ErrorAccTemp) {
         /* The error accumulator turned over, so advance the Y coord */
         Y0++;
      }
      X0 += XDir; /* X-major, so always advance X */
      /* The IntensityBits most significant bits of ErrorAcc give us the
         intensity weighting for this pixel, and the complement of the
         weighting for the paired pixel */
      Weighting = ErrorAcc >> IntensityShift;
      DrawPixel(X0, Y0, BaseColor + Weighting);
      DrawPixel(X0, Y0 + 1,
            BaseColor + (Weighting ^ WeightingComplementMask));
   }
   /* Draw the final pixel, which is always exactly intersected by the line
      and so needs no weighting */
   DrawPixel(pDC,X1, Y1, BaseColor);
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


