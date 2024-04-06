# Boids

Simple simulation of **Boid** artificial life program initially developed by Craig Reynolds in 1986.

---

<p align="left">
  <img width="600" height="330" src="https://raw.githubusercontent.com/ErtyumPX/boids/main/assets/images/general.gif">
</p>

---

The main source that I followed while developing the simulation is [Boids - Cornell ECE](https://people.ece.cornell.edu/land/courses/ece4760/labs/s2021/Boids/Boids.html), I appreciate the detailed explanation and the code provided.

## License

This project is licensed under the [GNU GPL-3.0](https://github.com/ErtyumPX/boids/blob/main/LICENSE) license.

Feel free to use the source code. Referring to the repository would be very much appreciated.

## Setup

Project is currently compiled with `GNU G++ 13.2.1`.

The only third-party dependency is `SDL2`. Used version of SDL2 in project is `2.28.5`, should work as long as it is **SDL2** and not **SDL**.

For compiling and linking rules `GNU Make 4.4.1` was used. After downloading dependencies, make sure to change the include paths inside the Makefile.

```
# change the paths for '-I' 
CC := g++
CFLAGS := -Wall -std=c++11 -I/usr/include/SDL2           # here
TEST_CFLAGS := -Wall -std=c++11 -Iinclude/SDL2 -Isrc/    # and here
LDFLAGS := -lSDL2 -lSDL2_image
...
```

After fulfilling dependencies, download or clone the project and use Makefile to easily compile:

```
> make all
> make run
```

Since SDL2 is a cross-platform media library, output should work on Windows, MacOS and Linux.

## Rules

As with most artificial life simulations, Boids is an example of emergent behavior; that is, the complexity of Boids arises from the interaction of individual agents (the boids, in this case) adhering to a set of simple rules. The rules applied in the simplest Boids world are as follows:

- **Separation**: steer to avoid crowding local flockmates
- **Alignment**: steer towards the average heading of local flockmates
- **Cohesion**: steer to move towards the average position (center of mass) of local flockmates

Source: [Wikipedia Boids](https://en.wikipedia.org/wiki/Boids)

## Simulation

The simulation allows you to:
- Speed up/down the simulation using `q` and `e` keys
- Toggle the debug mode for seeing each agents' visual and protected range using `d` key
- Restart the simulation using `r` key

**Speeding Up/Down**

<p align="left">
  <img width="600" height="330" src="https://raw.githubusercontent.com/ErtyumPX/boids/main/assets/images/speed_up_down.gif">
</p>


**Debug Mode**

<p align="left">
  <img width="600" height="330" src="https://raw.githubusercontent.com/ErtyumPX/boids/main/assets/images/debug_mode.gif">
</p>

## General Structure

### Directory Structure and Files

- `src/` directory contains the source code
  - `src/main.cpp` is the entry point of the program
  - `src/game.hpp` contains the declarations of the core functions
  - `src/game.cpp` contains the implementation of core functions
  - `src/agent.hpp` has the struct of the boid agents
  - `src/master.cpp` has the struct of all the configurations for the simulation
- `stable/` directory contains the stable output
  - `stable/boids.follow` is the executable

### How It Goes

Will be updated soon.
