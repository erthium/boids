#include <iostream>
#include <time.h>
#include <vector>
#include "game.hpp"


void draw_agents(SDL_Renderer* renderer, Agent* agents, Master master) {
  // render every agent
  for (size_t i = 0; i < master.AGENT_COUNT; i++) {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    // find 3 points of the triangle, make the one that is in the direction of the agent longer
    float angle = atan2(agents[i].speed_y, agents[i].speed_x);
    float x1 = agents[i].x + 13 * cos(angle);
    float y1 = agents[i].y + 13 * sin(angle);
    float x2 = agents[i].x + 5 * cos(angle + 3.14 / 2);
    float y2 = agents[i].y + 5 * sin(angle + 3.14 / 2);
    float x3 = agents[i].x + 5 * cos(angle - 3.14 / 2);
    float y3 = agents[i].y + 5 * sin(angle - 3.14 / 2);
    // draw the triangle
    SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
    SDL_RenderDrawLine(renderer, x2, y2, x3, y3);
    SDL_RenderDrawLine(renderer, x3, y3, x1, y1);

    // debug mode
    if (master.DEBUG) {
      SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
      SDL_Rect protected_range = {
        agents[i].x - master.PROTECTED_RANGE,
        agents[i].y - master.PROTECTED_RANGE,
        2 * master.PROTECTED_RANGE,
        2 * master.PROTECTED_RANGE
      };
      SDL_RenderDrawRect(renderer, &protected_range);
      SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
      SDL_Rect visual_range = {
        agents[i].x - master.VISUAL_RANGE,
        agents[i].y - master.VISUAL_RANGE,
        2 * master.VISUAL_RANGE,
        2 * master.VISUAL_RANGE
      };
      SDL_RenderDrawRect(renderer, &visual_range);
    }
  }
}


Agent* spawn_agents(Master master) {
  srand(time(NULL));
  Agent* agents = new Agent[master.AGENT_COUNT];
  for (size_t i = 0; i < master.AGENT_COUNT; i++) {
    // create x y and speed values considering margin as well
    agents[i].x = rand() % (master.WIDTH - 2 * master.MARGIN) + master.MARGIN;
    agents[i].y = rand() % (master.HEIGHT - 2 * master.MARGIN) + master.MARGIN;
    // random speed values
    agents[i].speed_x = (rand() % 100) / 100.0 - 0.5;
    agents[i].speed_y = (rand() % 100) / 100.0 - 0.5;
  }
  return agents;
}


bool is_in_visual(Agent agent, Agent other, Master master) {
  int dx = agent.x - other.x;
  int dy = agent.y - other.y;
  return (dx * dx + dy * dy) < master.VISUAL_RANGE * master.VISUAL_RANGE;
}


bool is_in_protected_range(Agent agent, Agent other, Master master) {
  int dx = agent.x - other.x;
  int dy = agent.y - other.y;
  return (dx * dx + dy * dy) < master.PROTECTED_RANGE * master.PROTECTED_RANGE;
}


void update_agents(Agent* agents, Master master) {
  for (size_t i = 0; i < master.AGENT_COUNT; i++) {
    // find all neighbors of agent i
    vector<int> in_protected_range = {};
    vector<int> in_visual_range = {};
    for (size_t j = 0; j < master.AGENT_COUNT; j++) {
      if (i != j) {
        if (is_in_protected_range(agents[i], agents[j], master)) {
          in_protected_range.push_back(j);
        }
        if (is_in_visual(agents[i], agents[j], master)) {
          in_visual_range.push_back(j);
        }
      }
    }

    // separation
    float close_dx = 0;
    float close_dy = 0;
    for (size_t j = 0; j < in_protected_range.size(); j++) {
      int neighbor = in_protected_range[j];
      close_dx += agents[i].x - agents[neighbor].x;
      close_dy += agents[i].y - agents[neighbor].y;
    }
    agents[i].speed_x += master.AVOID_FACTOR * close_dx;
    agents[i].speed_y += master.AVOID_FACTOR * close_dy;

    // alignment
    float avg_x_speed = 0;
    float avg_y_speed = 0;
    if (in_visual_range.size() > 0) {
      for (size_t j = 0; j < in_visual_range.size(); j++) {
        int neighbor = in_visual_range[j];
        avg_x_speed += agents[neighbor].speed_x;
        avg_y_speed += agents[neighbor].speed_y;
      }
      avg_x_speed /= in_visual_range.size();
      avg_y_speed /= in_visual_range.size();
      agents[i].speed_x += master.MATCH_FACTOR * (avg_x_speed - agents[i].speed_x);
      agents[i].speed_y += master.MATCH_FACTOR * (avg_y_speed - agents[i].speed_y);
    }

    // cohesion
    float avg_x = 0;
    float avg_y = 0;
    if (in_visual_range.size() > 0) {
      for (size_t j = 0; j < in_visual_range.size(); j++) {
        int neighbor = in_visual_range[j];
        avg_x += agents[neighbor].x;
        avg_y += agents[neighbor].y;
      }
      avg_x /= in_visual_range.size();
      avg_y /= in_visual_range.size();
      agents[i].speed_x += master.CENTER_FACTOR * (avg_x - agents[i].x);
      agents[i].speed_y += master.CENTER_FACTOR * (avg_y - agents[i].y);
    }

    // avoiding screen edges
    if (agents[i].x < master.MARGIN) {
      agents[i].speed_x += master.TURN_FACTOR;
    }
    if (agents[i].x > master.WIDTH - master.MARGIN) {
      agents[i].speed_x -= master.TURN_FACTOR;
    }
    if (agents[i].y < master.MARGIN) {
      agents[i].speed_y += master.TURN_FACTOR;
    }
    if (agents[i].y > master.HEIGHT - master.MARGIN) {
      agents[i].speed_y -= master.TURN_FACTOR;
    }
  }   
}


void move_agents(Agent* agents, Master master) {
  // move agent according to its speed
  for (size_t i = 0; i < master.AGENT_COUNT; i++)  {
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
