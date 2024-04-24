#include <SDL.h>
#include <SDL_image.h>
#include <SDL_timer.h>
#include "agent.hpp"
#include "master.hpp"

using namespace std;

void draw_agents(SDL_Renderer* renderer, Agent* agents, Master master);

Agent* spawn_agents(Master master);

bool is_in_visual(Agent agent, Agent other, Master master);

bool is_in_protected_range(Agent agent, Agent other, Master master);

void update_agents(Agent* agents, Master master);

void move_agents(Agent* agents, Master master);
