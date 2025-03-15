#pragma once

class Clock{
public:
  Clock(){};
  static void update_time();
  static float get_time_since_last_frame();
private:
  static float last_frame_time;
  static float delta_time;
};
