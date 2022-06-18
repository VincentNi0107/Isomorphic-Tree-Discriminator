# include "Simple_window.h"
# include "AnalogClock.h"
# include "std_lib_facilities.h"
int main() {
  Point tl(100, 100);
  Simple_window win(tl, 600, 500, "Analog Clock");

  AnalogClock cl;
  
  while(true){
  win.attach(cl);
  Fl::wait();
  Sleep(1000);
  win.detach(cl);
  Fl::redraw();
  }
  win.wait_for_button();
  return 0;
}
