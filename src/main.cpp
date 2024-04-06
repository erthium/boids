#include <iostream>
#include <string>
#include <vector>

#include "game.hpp"

using namespace std;

#define FPS 60
#define WIDTH 1024
#define HEIGHT 768
#define MARGIN 10

#define AGENT_COUNT 20

// agents configuration
#define VISUAL_RANGE 50
#define PROTECTED_RANGE 10
#define MAX_SPEED 5
#define MIN_SPEED 2
#define TURN_FACTOR 0.2
#define MATCH_FACTOR 0.1
#define AVOID_FACTOR 0.1
#define CENTER_FACTOR 0.1

int main(int argc, char* argv[]) {

  if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
    cout << "Error initializing SDL: " << SDL_GetError() << endl;
  }
  SDL_Window* window = SDL_CreateWindow(
    "Boids Simulation",
    SDL_WINDOWPOS_CENTERED,
    SDL_WINDOWPOS_CENTERED,
    WIDTH,
    HEIGHT,
    0
  );
  SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);
  cout << "Game initialized." << endl;

  Master master = {
    WIDTH,
    HEIGHT,
    AGENT_COUNT,
    FPS,
    MARGIN,
    TURN_FACTOR,
    MATCH_FACTOR,
    AVOID_FACTOR,
    CENTER_FACTOR,
    VISUAL_RANGE,
    PROTECTED_RANGE,
    MAX_SPEED,
    MIN_SPEED
  };

  Agent* agents = spawn_agents(master);

  bool running = true;
  SDL_Event event;
  while (running) {
    Uint32 start_time = SDL_GetTicks();
    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT) {
        running = false;
      }
    }

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    // BEGIN Game Logic
  
    update_agents(agents, master);
    move_agents(agents, master);
    draw_agents(renderer, agents, master);

    // END Game Logic

    SDL_RenderPresent(renderer);

    Uint32 end_time = SDL_GetTicks();
    if (end_time - start_time < 1000 / FPS) {
      SDL_Delay(1000 / FPS - (end_time - start_time));
    }
  }

  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();

  return 0;
}
