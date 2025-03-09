#pragma once

struct Agent {
  float x;
  float y;
  float speed_x;
  float speed_y;
  short class_id;
};

enum AgentClass {
  RED,
  GREEN,
  BLUE
};
