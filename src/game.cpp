#include <iostream>
#include <time.h>
#include <vector>
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


bool is_in_visual(Agent agent, Agent other, Master master) {
  int dx = agent.x - other.x;
  int dy = agent.y - other.y;
  return sqrt(dx * dx + dy * dy) < master.VISUAL_RANGE;
}


bool is_in_protected_range(Agent agent, Agent other, Master master) {
  int dx = agent.x - other.x;
  int dy = agent.y - other.y;
  return sqrt(dx * dx + dy * dy) < master.PROTECTED_RANGE;
}


void update_agents(Agent* agents, Master master) {
  return;
}


void move_agents(Agent* agents, Master master) {
  // move agent according to its speed
  for (int i = 0; i < master.AGENT_COUNT; i++)  {
    agents[i].x += agents[i].speed_x;
    agents[i].y += agents[i].speed_y;
    // min max speed clamping
    // min max speed represents the minimum and maximum velocity an agent can have, direction included
    float total_speed = sqrt(agents[i].speed_x * agents[i].speed_x + agents[i].speed_y * agents[i].speed_y);
    if (total_speed > master.MAX_SPEED) {
      agents[i].speed_x = agents[i].speed_x / total_speed * master.MAX_SPEED;
      agents[i].speed_y = agents[i].speed_y / total_speed * master.MAX_SPEED;
    }
    if (total_speed < master.MIN_SPEED) {
      agents[i].speed_x = agents[i].speed_x / total_speed * master.MIN_SPEED;
      agents[i].speed_y = agents[i].speed_y / total_speed * master.MIN_SPEED;
    }
  }
}
