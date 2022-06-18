# ifndef _HYPERELLIPTIC_H_
# define _HYPERELLIPTIC_H_

# include "Graph.h"
# include <vector>
# include <cmath>

using namespace Graph_lib;
using namespace std;

class Hyperelliptic : public Shape {
  private:
    double a, b, m, n;
    int N;

    vector <Point> points;

    Point getPoint(double ox, double oy);
    void draw_lines() const;

  public:
    Hyperelliptic(double a, double b, double m, double n, int N);

    ~ Hyperelliptic() { };
};

# endif
