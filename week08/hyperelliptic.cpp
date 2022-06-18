# include "hyperelliptic.h"

Hyperelliptic :: Hyperelliptic(double a, double b, double m, double n, int N) :a(a), b(b), m(m), n(n), N(N) {
  double x = -a, step = a * 2 / (N >> 1);
  for (int i = 0; i <= (N >> 1); ++ i) {
    double y1 = pow(1 - pow(fabs(x / a), n), 1.0 / m) * b;
    double y2 = -y1;
    points.push_back(getPoint(x, y1));
    if(i != 0 && i != (N >> 1)) points.push_back(getPoint(x, y2));
    x += step;
  }
  }

Point Hyperelliptic :: getPoint(double ox, double oy) {
  int x = static_cast <int> (ox);
  int y = static_cast <int> (oy);
  x += 400;
  y += 300;
  return Point(x, y);
}


void Hyperelliptic :: draw_lines() const {
  for (int i = 0; i < points.size(); ++ i)
    for (int j = i + 1; j < points.size(); ++ j)
      fl_line(points[i].x, points[i].y, points[j].x, points[j].y);
}


