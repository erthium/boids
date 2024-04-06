#include <iostream>
#include <time.h>
#include "game.hpp"


void draw_agents(SDL_Renderer* renderer, Agent* agents, Master master) {
  // draw a triangle for each agent according to where they are facing, long part of the triangle will face there
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
  SDL_RenderClear(renderer);
  
  // render every agent
  for (int i = 0; i < master.AGENT_COUNT; i++) {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderDrawLine(renderer, agents[i].x, agents[i].y, agents[i].x + 10, agents[i].y + 10);
    SDL_RenderDrawLine(renderer, agents[i].x, agents[i].y, agents[i].x - 10, agents[i].y + 10);
    SDL_RenderDrawLine(renderer, agents[i].x + 10, agents[i].y + 10, agents[i].x - 10, agents[i].y + 10);
  }

  SDL_RenderPresent(renderer);
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
