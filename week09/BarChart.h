# ifndef _BARCHART_H_
# define _BARCHART_H_

# include "Graph.h"
# include <vector>
using namespace std;

class BarChart : public Graph_lib :: Shape {
  private:
    vector <double> newyork, austin;
    void draw_lines() const;

  public:
    BarChart();
    ~ BarChart(){};
};

# endif
