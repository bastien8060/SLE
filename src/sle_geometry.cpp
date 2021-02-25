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

int _fpart(int x) {
  return x - std::floor(x);
}

int _rfpart(int x) {
  return 1 - _fpart(x);
}


std::vector<std::vector<int> > linehoriz (short X0, short Y0, short X1, short Y1,
    short BaseColor = 0, short NumLevels = 256, unsigned short IntensityBits = 8)
{
  unsigned short IntensityShift, ErrorAdj, ErrorAcc;
  unsigned short ErrorAccTemp, Weighting, WeightingComplementMask;
  short DeltaX, DeltaY, Temp, XDir;
  std::vector<std::vector<int> > points;

  /* Make sure the line runs top to bottom */
  if (Y0 > Y1) {
    Temp = Y0; Y0 = Y1; Y1 = Temp;
    Temp = X0; X0 = X1; X1 = Temp;
  }
  /* Draw the initial pixel, which is always exactly intersected by
     the line and so needs no weighting */

  //DrawPixel(X0, Y0, BaseColor);
  std::vector<int > point;
  point.push_back(X0);
  point.push_back(Y0);
  points.push_back(point);
  point.clear();

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
      //DrawPixel(pDC,X0, Y0, BaseColor);
      //std::vector<int > point;
      point.push_back(X0);
      point.push_back(Y0);
      points.push_back(point);
      point.clear();
    }
    return points;
  }
  if (DeltaX == 0) {
    /* Vertical line */
    do {
      Y0++;
      //DrawPixel(X0, Y0, BaseColor);
      std::vector<int > point;
      point.push_back(X0);
      point.push_back(Y0);
      points.push_back(point);
      point.clear();

    } while (--DeltaY != 0);
    return points;
  }
  if (DeltaX == DeltaY) {
    /* Diagonal line */
    do {
      X0 += XDir;
      Y0++;
      //DrawPixel(X0, Y0, BaseColor);
      std::vector<int > point;
      point.push_back(X0);
      point.push_back(Y0);
      points.push_back(point);
      point.clear();
    } while (--DeltaY != 0);
    return points;
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
      // DrawPixel(pDC,X0, Y0, BaseColor + Weighting);
      //DrawPixel(pDC,X0 + XDir, Y0,
      //      BaseColor + (Weighting ^ WeightingComplementMask));

      std::vector<int > point;
      point.push_back(X0);
      point.push_back(Y0);
      points.push_back(point);
      point.clear();
      //std::vector<int > point;
      point.push_back(X0 + XDir);
      point.push_back(Y0);
      points.push_back(point);
      point.clear();
    }
    /* Draw the final pixel, which is
       always exactly intersected by the line
       and so needs no weighting */
    //DrawPixel(X1, Y1, BaseColor);
    //std::vector<int > point;
    point.push_back(X1);
    point.push_back(Y1);
    points.push_back(point);
    point.clear();

    return points;
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
    //DrawPixel(X0, Y0, BaseColor + Weighting);
    //DrawPixel(X0, Y0 + 1,
    //      BaseColor + (Weighting ^ WeightingComplementMask));

    std::vector<int > point;
    point.push_back(X0);
    point.push_back(Y0);
    points.push_back(point);
    point.clear();

    //std::vector<int > point;
    point.push_back(X0);
    point.push_back(Y0 + 1);
    points.push_back(point);
    point.clear();
  }
  /* Draw the final pixel, which is always exactly intersected by the line
     and so needs no weighting */
  //DrawPixel(pDC,X1, Y1, BaseColor);
  //std::vector<int > point;
  point.push_back(X1);
  point.push_back(Y1);
  points.push_back(point);
  point.clear();

  return points;
}



std::vector<std::vector<int> > linehoriz2(int x0, int y0, int x1, int y1) //bresenham's line algorithm
{
  int dx, dy, p, x, y;
  std::vector<std::vector<int> > points;

  dx = x1 - x0;
  dy = y1 - y0;

  x = x0;
  y = y0;

  p = 2 * dy - dx;

  while (x < x1)
  {
    std::vector<int > point;

    if (p >= 0)
    {
      //putpixel(x, y, 7);

      point.push_back(x);
      point.push_back(y);
      points.push_back(point);

      y = y + 1;
      p = p + 2 * dy - 2 * dx;
    }
    else
    {
      //putpixel(x, y, 7);
      point.push_back(x);
      point.push_back(y);
      points.push_back(point);
      p = p + 2 * dy;
    }
    x = x + 1;
  }
  return points;
}


// Function for circle-generation
// using Bresenham's algorithm
std::vector<std::vector<int> > circle(int xc, int yc, int r)
{
  std::vector<int > point;
  std::vector<std::vector<int> > points;

  int x = 0, y = r;
  int d = 3 - 2 * r;
  point.push_back(xc + x);
  point.push_back(yc + y);
  points.push_back(point);
  point.clear();

  point.push_back(xc - x);
  point.push_back(yc + y);
  points.push_back(point);
  point.clear();

  point.push_back(xc + x);
  point.push_back(yc - y);
  points.push_back(point);
  point.clear();

  point.push_back(xc - x);
  point.push_back(yc - y);
  points.push_back(point);
  point.clear();

  point.push_back(xc + y);
  point.push_back(yc + x);
  points.push_back(point);
  point.clear();

  point.push_back(xc - y);
  point.push_back(yc + x);
  points.push_back(point);
  point.clear();

  point.push_back(xc + y);
  point.push_back(yc - x);
  points.push_back(point);
  point.clear();

  point.push_back(xc - y);
  point.push_back(yc - x);
  points.push_back(point);
  point.clear();

  /*putpixel(xc+x, yc+y, RED);
  putpixel(xc-x, yc+y, RED);
  putpixel(xc+x, yc-y, RED);
  putpixel(xc-x, yc-y, RED);
  putpixel(xc+y, yc+x, RED);
  putpixel(xc-y, yc+x, RED);
  putpixel(xc+y, yc-x, RED);
  putpixel(xc-y, yc-x, RED);
  */
  while (y >= x)
  {
    // for each pixel we will
    // draw all eight pixels

    x++;

    // check for decision parameter
    // and correspondingly
    // update d, x, y
    if (d > 0)
    {
      y--;
      d = d + 4 * (x - y) + 10;
    }
    else
      d = d + 4 * x + 6;
    //drawCircle(xc, yc, x, y);
    point.push_back(xc + x);
    point.push_back(yc + y);
    points.push_back(point);
    point.clear();

    point.push_back(xc - x);
    point.push_back(yc + y);
    points.push_back(point);
    point.clear();

    point.push_back(xc + x);
    point.push_back(yc - y);
    points.push_back(point);
    point.clear();

    point.push_back(xc - x);
    point.push_back(yc - y);
    points.push_back(point);
    point.clear();

    point.push_back(xc + y);
    point.push_back(yc + x);
    points.push_back(point);
    point.clear();

    point.push_back(xc - y);
    point.push_back(yc + x);
    points.push_back(point);
    point.clear();

    point.push_back(xc + y);
    point.push_back(yc - x);
    points.push_back(point);
    point.clear();

    point.push_back(xc - y);
    point.push_back(yc - x);
    points.push_back(point);
    point.clear();
    //point.clear();
    //delay(50);
  }
  return points;
}


std::vector<std::vector<int> > polygon(std::vector<std::vector<int> > dots) {

  std::vector<std::vector<int> > points;
  for (int i = 1; i < dots.size(); ++i)
  {

    std::vector<int> xy1 = dots[i - 1];
    std::vector<int> xy2 = dots[i];

    int x1 = xy1[0];
    int y1 = xy1[1];
    int x2 = xy2[0];
    int y2 = xy2[1];

    //std::cout << "\n\n x1:" << x1 << "  y1" << y1 << "\n\n x2:" << x2 << "  y2:" << y2;

    std::vector<std::vector<int> > result = line(x1, y1, x2, y2);
    for (int i = 0; i < result.size(); ++i)
    {
      points.push_back(result[i]);
    }
  }

  std::vector<int> xy1 = dots[dots.size() - 1];
  std::vector<int> xy2 = dots[0];

  int x1 = xy1[0];
  int y1 = xy1[1];
  int x2 = xy2[0];
  int y2 = xy2[1];

  std::vector<std::vector<int> > result = line(x1, y1, x2, y2);

  for (int i = 0; i < result.size(); ++i)
  {
    points.push_back(result[i]);
  }

  return points;
}


