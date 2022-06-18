# ifndef _MYLINE_H_
# define _MYLINE_H_

#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/fl_draw.H>
# include <map>


class myline : public Fl_Widget {
  private:
    int x1,x2,y1,y2;
  public:
    myline(int x1,int y1,int x2,int y2);
    virtual void draw();
    ~ myline() { };
};





# endif
