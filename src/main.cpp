#include <iostream>
#include <string>
#include <vector>

#include "game.hpp"

using namespace std;

int main(int argc, char* argv[]) {

    Master master;
    master.WIDTH = 1000;
    master.HEIGHT = 1000;
    master.AGENT_COUNT = 500;
    master.FPS = 60;
    master.MARGIN = 300;
    master.VISUAL_RANGE = 170;
    master.PROTECTED_RANGE = 50;
    master.MAX_SPEED = 5;
    master.MIN_SPEED = 2;
    master.TURN_FACTOR = 0.2;
    master.MATCH_FACTOR = 0.005;
    master.AVOID_FACTOR = 0.0001;
    master.CENTER_FACTOR = 0.0005;
    master.DEBUG = false;

  if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
    cout << "Error initializing SDL: " << SDL_GetError() << endl;
  }
  SDL_Window* window = SDL_CreateWindow(
    "Boids Simulation",
    SDL_WINDOWPOS_CENTERED,
    SDL_WINDOWPOS_CENTERED,
    master.WIDTH,
    master.HEIGHT,
    0
  );
  SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);
  cout << "Game initialized." << endl;

  Agent* agents = spawn_agents(master);

  bool running = true;
  SDL_Event event;
  while (running) {
    Uint32 start_time = SDL_GetTicks();
    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT) {
        running = false;
      }
      if (event.type == SDL_KEYDOWN) {
        // restart
        if (event.key.keysym.sym == SDLK_r) {
          delete[] agents;
          agents = spawn_agents(master);
        }
        // debug mode
        if (event.key.keysym.sym == SDLK_d) {
          master.DEBUG = !master.DEBUG;
        }
        // slow down
        if (event.key.keysym.sym == SDLK_q) {
          if (master.FPS > 4) {
            master.FPS /= 2;
          }
        }
        // speed up
        if (event.key.keysym.sym == SDLK_e) {
          if (master.FPS < 1000) {
            master.FPS *= 2;
          }
        }
      }
    }

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    // BEGIN Game Logic
    if (master.FPS > 4) {
      update_agents(agents, master);
      move_agents(agents, master);
    }
    draw_agents(renderer, agents, master);
    // END Game Logic

    SDL_RenderPresent(renderer);

    Uint32 end_time = SDL_GetTicks();
    if (end_time - start_time < 1000 / master.FPS) {
      SDL_Delay(1000 / master.FPS - (end_time - start_time));
    }
  }

  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
  delete[] agents;
  return 0;
}
