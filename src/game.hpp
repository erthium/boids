#include <SDL.h>
#include <SDL_image.h>
#include <SDL_timer.h>
#include "agent.hpp"

using namespace std;

void draw_grid(SDL_Renderer* renderer, Agent* agents, int WIDTH, int HEIGHT);

void update_agents(Agent* agents, int WIDTH, int HEIGHT);

Agent* spawn_agents(int agent_count, int WIDTH, int HEIGHT);
