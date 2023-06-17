
# LLCBKv2

LED Lighting Control By K4 - A Multithreaded, GUI Enabled, WS281x Controller written in C++

Designed for the purpose of controlling custom lights in a vehicle

Supports RPI4B OOTB




## Features

- Multithreaded
- GUI Enabled
- Thread Interruption
- Basic Animation Examples


## Installation

**Compile**

1.) Clone this project

2.) Clone [RPI WS281x](https://github.com/jgarff/rpi_ws281x) and compile it as per the instructions in the repo

3.) Make sure the includes in ```main.cpp``` pick up the WS281x repo

4.) Modify PWM Channels if needed

5.) Compile and have fun

**Download**

1.) Download the precompiled binary [HERE](https://github.com/jgarff/rpi_ws281x)

2.) Run and have fun
    
## Documentation

- 2 PWM Channels (0 and 1) (Pin 18/19)

- Supports SK6812/WS2811/WS2812

- NOTE: GUI HAS NOT BEEN ADDED YET, STILL WIP

## Acknowledgements

 - [RPI WS281x](https://github.com/jgarff/rpi_ws281x)

