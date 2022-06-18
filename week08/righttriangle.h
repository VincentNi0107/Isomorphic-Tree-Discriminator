# ifndef _RIGHT_TRIANGLE_H_
# define _RIGHT_TRIANGLE_H_

# include "Graph.h"
# include <vector>
# include <cmath>

using namespace Graph_lib;
using namespace std;

class RightTriangle : public Shape {
  private:
    vector <Point> points;
    double a, b;
    Point c;
    double angle;
    void draw_lines() const;

  public:
    RightTriangle(Point c, double a, double b, double angle = 0.0);

    ~ RightTriangle() { }
};

# endif
