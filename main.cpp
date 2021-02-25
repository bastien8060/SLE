#include <iostream>
#include <unistd.h>
#include <functional>
#include <cmath>
#include <stdio.h>
//#include<graphics.h>
#include <math.h>
#include <vector>
#include <sstream>
#include <algorithm>
#include <utility>
#include <sys/types.h>
// Server side implementation of UDP client-server model. Windows not working with this.
#include <sys/socket.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <netinet/in.h>


#include "src/sle_geometry.cpp"

/* A simple server in the internet domain using TCP
   The port number is passed as an argument */
// Server side implementation of UDP client-server model

#define PORT    6770
#define MAXLINE 1024
#define CPS 60

#include "src/sle_proto_parse.cpp"
#include "src/server.cpp"

//Function to convert a variable type in memory to std::string
template <typename T> std::string tostr(const T& t) {
  std::ostringstream os;
  os << t;
  return os.str();
}


//Todo add a or expression in case 0
//handler to alter the sorting function behaviour. sorts in order



void testunit(){

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


  LINE ONE


  */


  int x1, y1, x2, y2;
  x1 = 10;
  y1 = 30;
  x2 = 40;
  y2 = 120;


  std::cout << "\n\n\n DDA Line Drawing Algorithm\n\n\n";

  std::vector<std::vector<int> > lines = line(x1, y1, x2, y2);

  for (int i = 0; i < lines.size(); ++i)
  {
    std::vector<int >  point = lines[i];
    std::cout << "\n\n X:" << point[0] << "  Y:" << point[1];

  }



  /*


  LINE TWO


  */



  std::cout << "\n\n\n Xiaolin Wu's Line Drawing Algorithm\n\n\n";

  std::vector<std::vector<int> > lines2 = linehoriz(x1, y1, x2, y2);

  for (int i = 0; i < lines2.size(); ++i)
  {
    std::vector<int > point = lines2[i];
    std::cout << "\n\n X:" << point[0] << "  Y:" << point[1];

  }




  /*


  LINE THREE


  */


  std::cout << "\n\n\nBresenham's Line Drawing Algorithm\n\n\n";


  std::vector<std::vector<int> > lines3 = linehoriz2(x1, y1, x2, y2);

  for (int i = 0; i < lines3.size(); ++i)
  {
    std::vector<int > point = lines3[i];
    std::cout << "\n\n X:" << point[0] << "  Y:" << point[1];

  }




  /*


  CIRCLE


  */


  std::cout << "\n\n\nBresenham's Cricle Drawing Algorithm\n\n\n";

  int radius = 50;
  int xpos = 60;
  int ypos = 60;
  std::vector<std::vector<int> > lines4 = circle(xpos, ypos, radius);

  for (int i = 0; i < lines4.size(); ++i)
  {
    std::vector<int > point = lines4[i];
    std::cout << "\n\n X:" << point[0] << "  Y:" << point[1];

  }


  /*


  POLYGON


  */


  std::cout << "\n\n\nPolygon Line Joiner\n\n\n";


  std::vector<std::vector<int>> dots;
  std::vector<int> point;
  point.push_back(67);
  point.push_back(44);
  dots.push_back(point);
  point.clear();

  point.push_back(194);
  point.push_back(44);
  dots.push_back(point);
  point.clear();

  point.push_back(170);
  point.push_back(174);
  dots.push_back(point);
  point.clear();

  point.push_back(41);
  point.push_back(95);
  dots.push_back(point);
  point.clear();



  std::vector<std::vector<int>> lines5 = polygon(dots);

  std::cout << "[";
  for (int i = 0; i < lines5.size(); ++i)
  {
    std::vector<int >  point = lines5[i];
    std::cout << "[" << point[0] << "," << point[1] << "],";

  }
  std::cout << "]";

  /*


  OTHER


  */
}

int main() {

  //testunit();
  server_start();

  return 0;
}


