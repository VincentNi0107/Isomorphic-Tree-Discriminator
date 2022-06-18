# include "myline.h"
myline::myline(int x1,int y1,int x2,int y2):x1(x1),y1(y1),x2(x2),y2(y2),Fl_Widget(x1,y1,x2,y2,""){
}
void myline::draw() {
    fl_begin_line();
    fl_color(FL_BLACK);
    fl_line(x1, y1, x2, y2);
    fl_end_line();
}