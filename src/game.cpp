#include <iostream>
#include <time.h>
#include "game.hpp"

void draw_grid(SDL_Renderer* renderer, Agent* grid, size_t size) {
  return;
}


void update_grid(Agent* grid, size_t size) {
  return;
}


Agent* spawn_agents(int agent_count, int WIDTH, int HEIGHT) {
  srand(time(NULL));
  Agent* agents = new Agent[agent_count];
  for (int i = 0; i < agent_count; i++) {
    int x = rand() % WIDTH;
    int y = rand() % HEIGHT;
    int speed = rand() % 5 + 1;
    int direction = rand() % 360;
    agents[i] = {x, y, speed, direction};
  }
  return agents;
}
