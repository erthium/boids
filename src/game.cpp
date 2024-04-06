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


Agent* spawn_agents(Master master) {
  srand(time(NULL));
  Agent* agents = new Agent[master.AGENT_COUNT];
  for (int i = 0; i < master.AGENT_COUNT; i++) {
    // create x y and speed values considering margin as well
    agents[i].x = rand() % (master.WIDTH - 2 * master.MARGIN) + master.MARGIN;
    agents[i].y = rand() % (master.HEIGHT - 2 * master.MARGIN) + master.MARGIN;
    agents[i].speed_x = (rand() % (int)master.MAX_SPEED) + master.MIN_SPEED;
    agents[i].speed_y = (rand() % (int)master.MAX_SPEED) + master.MIN_SPEED;
  }
  return agents;
}

