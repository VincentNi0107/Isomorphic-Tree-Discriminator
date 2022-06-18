# include "AnalogClock.h"

void AnalogClock :: draw_lines() const {

  // get the time from system  ( windows )
  time_t timer;
  time(&timer);
  struct tm *cur_time = localtime(&timer);
  int year = cur_time -> tm_year + 1900, month = cur_time -> tm_mon + 1, day = cur_time -> tm_mday;
  int hour = cur_time -> tm_hour, minute = cur_time -> tm_min, second = cur_time -> tm_sec;
  int wday = cur_time -> tm_wday;

  // Clear the screen
  // Graph_lib :: Rectangle background(Point(0, 0), 600, 500);
  // background.set_color(Graph_lib :: Color :: white);
  // background.set_fill_color(Graph_lib :: Color :: white);
  // background.draw();

  // Print the current time in screen
  string cur_time_string = "";
  if(hour < 10) cur_time_string += "0";
  cur_time_string += to_string(hour) + ":";
  if(minute < 10) cur_time_string += "0";
  cur_time_string += to_string(minute) + ":";
  if(second < 10) cur_time_string += "0";
  cur_time_string += to_string(second);
  Graph_lib :: Text t_time(Point(265, 340), cur_time_string);
  t_time.set_font(Graph_lib :: Font(FL_COURIER));
  t_time.set_font_size(15);
  t_time.draw();

  // Print the current date in screen
  string cur_date_string = "";
  cur_date_string += to_string(year) + "/";
  if(month < 10) cur_date_string += "0";
  cur_date_string += to_string(month) + "/";
  if(day < 10) cur_date_string += "0";
  cur_date_string += to_string(day);
  Graph_lib :: Text t_date(Point(255, 325), cur_date_string);
  t_date.set_font(Graph_lib :: Font(FL_COURIER));
  t_date.set_font_size(15);
  t_date.draw();

  // Draw the circle
  Graph_lib :: Circle c_circle(Point(300, 250), 200);
  c_circle.set_color(Graph_lib :: Color :: black);
  c_circle.set_style(Graph_lib :: Line_style(Graph_lib :: Line_style :: solid, 3));
  c_circle.draw();

  // Draw the clock
  for (int deg = 0; deg < 60; deg ++) {
    double angle = deg / 30.0 * M_PI;
    if(deg % 5 == 0) {
      // Clock Line
      Graph_lib :: Line l(Point(300 + 175 * cos(angle), 250 + 175 * sin(angle)), Point(300 + 200 * cos(angle), 250 + 200 * sin(angle)));
      l.set_color(Graph_lib :: Color :: black);
      l.set_style(Graph_lib :: Line_style(Graph_lib :: Line_style :: solid, 3));
      l.draw();

      // Clock num
      int num = deg / 5 - 9; num = (num + 12) % 12;
      if(num == 0) num = 12;
      Graph_lib :: Text t(Point(300 + 165 * cos(angle) - 7, 250 + 165 * sin(angle) + 5), to_string(num));
      t.set_color(Graph_lib :: Color :: black);
      t.set_font(Graph_lib :: Font(Graph_lib :: Font(FL_COURIER_BOLD)));
      t.set_font_size(20);
      t.draw();
    } 
  }

  // Draw the dot
  Graph_lib :: Circle c_dot(Point(300, 250), 2);
  c_dot.set_fill_color(Graph_lib :: Color :: black);
  c_dot.set_style(Graph_lib :: Line_style(Graph_lib :: Line_style :: solid, 3));
  c_dot.draw();

  // Draw pointers
  double hour_angle = (hour % 12) / 6.0 * M_PI, minute_angle = (minute % 60) / 30.0 * M_PI, second_angle = (second % 60) / 30.0 * M_PI;
  minute_angle += second_angle / 60;
  hour_angle += minute_angle / 12;

  Graph_lib :: Line l_hour(Point(300, 250), Point(300 + 75 * sin(hour_angle), 250 - 75 * cos(hour_angle)));
  l_hour.set_color(Graph_lib :: Color :: black);
  l_hour.set_style(Graph_lib :: Line_style(Graph_lib :: Line_style :: solid, 5));
  l_hour.draw();

  Graph_lib :: Line l_minute(Point(300, 250), Point(300 + 130 * sin(minute_angle), 250 - 130 * cos(minute_angle)));
  l_minute.set_color(Graph_lib :: Color :: black);
  l_minute.set_style(Graph_lib :: Line_style(Graph_lib :: Line_style :: solid, 2));
  l_minute.draw();

  Graph_lib :: Line l_second(Point(300, 250), Point(300 + 150 * sin(second_angle), 250 - 150 * cos(second_angle)));
  l_second.set_color(Graph_lib :: Color :: black);
  l_second.set_style(Graph_lib :: Line_style(Graph_lib :: Line_style :: solid, 1));
  l_second.draw();
  
}
