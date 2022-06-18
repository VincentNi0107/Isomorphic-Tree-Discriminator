# include "Simple_window.h"
# include "Graph.h"
# include "BarChart.h"
# include "std_lib_facilities.h"


int main() {
  Point tl(100, 100);
  Simple_window win(tl, 1010, 600, "BarChart");

  BarChart chart;

  win.attach(chart);

  win.wait_for_button();
  return 0;
}
