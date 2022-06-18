#include "Simple_window.h"
#include "Graph.h"
#include "std_lib_facilities.h"
#include "righttriangle.h"
#include <iostream>

int main() {
    Point tl(100, 100);
    Simple_window win(tl, 800, 600, "RightTriangle");
    double A = 100.0, B = 50.0;
    Color colors[8] = {Color :: dark_red, Color :: dark_blue, Color :: dark_green, Color :: dark_yellow, Color :: white, Color :: black, Color :: dark_magenta, Color :: dark_cyan};


    double C = sqrt(A * A + B * B);
    double Ar = C / 2 / tan(M_PI / 8);
    double beta = M_PI / 2 - 2 * atan(A / B);
    double dCx = C / 2 * cos(beta), dCy = C / 2 * sin(beta);
    double px = Ar - dCx, py = -dCy;
    double R = sqrt(px * px + py * py);
    double theta = atan(fabs(py) / px);
    if(py < 0) theta = -theta;
    double angle = 0, angle_step = M_PI / 4;


    Shape *tri[8];
    for (int i = 0; i < 8; ++ i) {
        Point p(static_cast <int> (R * cos(theta) + 400), static_cast <int> (R * sin(theta) + 300));
        tri[i] = new RightTriangle(p, A, B, angle);
        tri[i] -> set_color(colors[i]);
        win.attach(*tri[i]);
        angle += angle_step;
        theta += angle_step;
    }

    win.wait_for_button();

    for (int i = 0; i < 8; ++ i) delete tri[i];
    return 0;
}
