# include "righttriangle.h"

RightTriangle :: RightTriangle(Point c, double a, double b, double angle) :c(c), a(a), b(b), angle(angle) {
  double beta = atan(a / b);
  points.push_back(Point(static_cast <int>(c.x), static_cast <int>(c.y)));
  points.push_back(Point(static_cast <int>(c.x + a * cos(angle - beta)), static_cast <int>(c.y + a * sin(angle - beta))));
  points.push_back(Point(static_cast <int>(c.x + b * cos(angle - beta + M_PI / 2)),static_cast <int>(c.y + b * sin(angle - beta + M_PI / 2))));
  }

void RightTriangle :: draw_lines() const {
  for (int i = 0; i <= 2; ++ i) {
    int j = i + 1;
    if(j == 3) j = 0;
    fl_line(points[i].x, points[i].y, points[j].x, points[j].y);
  }
}
