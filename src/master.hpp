#pragma once

struct Master {
  int WIDTH;
  int HEIGHT;
  int AGENT_COUNT;
  int FPS;
  int MARGIN;
  float TURN_FACTOR;
  float MATCH_FACTOR;
  float AVOID_FACTOR;
  float CENTER_FACTOR;
  float VISUAL_RANGE;
  float PROTECTED_RANGE;
  float MAX_SPEED;
  float MIN_SPEED;
};