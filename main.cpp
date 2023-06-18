// Rewriting this in c++ cause python is shit and slow and shit

// Includes
#include <iostream>
#include <signal.h>
#include <string>
#include <cstring>
#include <thread>
#include <pigpio.h>

#include "rpi_ws281x-master/ws2811.h"
#include "animations.cpp"

// Global Vars
static ws2811_t ledString;
anims an;

// Signal Handler
static void signalHandler(int signum)
{
    if (signum == SIGINT || signum == SIGTERM)
    {
        ws2811_fini(&ledString);
        exit(signum);
    }
}

// Init LEDS
void ledInit()
{
    ledString.freq = WS2811_TARGET_FREQ;
    ledString.dmanum = 10;

    ledString.channel[0].gpionum = 18;
    ledString.channel[0].count = 482;
    ledString.channel[0].invert = 0;
    ledString.channel[0].brightness = 10;
    ledString.channel[0].strip_type = WS2811_STRIP_GRB;

    ledString.channel[1].gpionum = 19;
    ledString.channel[1].count = 482;
    ledString.channel[1].invert = 0;
    ledString.channel[1].brightness = 10;
    ledString.channel[1].strip_type = WS2811_STRIP_GRB;

    if (ws2811_init(&ledString) != WS2811_SUCCESS)
    {
        std::cerr << "Failed to init LED strip\n";
        exit(EXIT_FAILURE);
    }

    signal(SIGINT, signalHandler);
    signal(SIGTERM, signalHandler);
}

void gpioInit()
{
    if (gpioInitialise() < 0) {
        std::cerr << "Failed to init pigpio\n";
        exit(EXIT_FAILURE);
    }

    gpioSetMode(17, PI_INPUT);
    gpioSetMode(27, PI_INPUT);
    gpioSetMode(22, PI_INPUT);
}

/*
--- GPIO
18 - Channel 0
19 - Channel 1
17 - Brakes
27 - Indi Right
22 - Indi Left

--- Modes of operation
1.) No condition
15.) Indi 
2.) Brakes down
25.) Indi
3.) Brakes up    <-- Maybe idk yet
35.) Indi
*/

void rightRun()
{
    while (!globals.shutdown)
    {

        switch (globals.right.desired)
        {
        case 1:
            globals.right.running = 1;
            globals.right.compBrakeAnim = false;
            an.mode1(ledString, 0);
            break;
        case 15:
            globals.right.running = 15;
            globals.right.compBrakeAnim = false;
            an.mode15(ledString, 0);
            break;
        case 2:
            globals.right.running = 2;
            an.mode2(ledString, 0);
            break;
        case 25:
            globals.right.running = 25;
            an.mode25(ledString, 0);
            break;
        }
    }
}

void leftRun()
{
    while (!globals.shutdown)
    {
        switch (globals.left.desired)
        {
        case 1:
            globals.left.running = 1;
            globals.left.compBrakeAnim = false;
            an.mode1(ledString, 1);
            break;
        case 15:
            globals.left.running = 15;
            globals.left.compBrakeAnim = false;
            an.mode15(ledString, 1);
            break;
        case 2:
            globals.left.running = 2;
            an.mode2(ledString, 1);
            break;
        case 25:
            globals.left.running = 25;
            an.mode25(ledString, 1);
            break;
        }
    }
}

// Run functions for LEDS
void ledRun()
{
    std::thread right_thread(rightRun);
    std::thread left_thread(leftRun);

    right_thread.join();
    left_thread.join();
}

void test()
{
    std::cout << "Press enter to exit\n";
    if (std::cin.ignore()) {
        globals.shutdown = true;
    }
}

void inputHandler()
{
    while (!globals.shutdown)
    {   
        if (gpioRead(17) == 0)  // Not Braking
        {
            if (gpioRead(27) == 1) {
                // Indi Right
                globals.right.desired = 15;
                globals.left.desired = 1;
            } else if (gpioRead(22) == 1) {
                // Indi Left
                globals.right.desired = 1;
                globals.left.desired = 15;
            } else {
                // None
                globals.right.desired = 1;
                globals.left.desired = 1;
            }

        } else if (gpioRead(17) == 1) {  // Braking
            if (gpioRead(27) == 1) {
                // Indi Right
                globals.right.desired = 25;
                globals.left.desired = 2;
            } else if (gpioRead(22) == 1) {
                // Indi Left
                globals.right.desired = 2;
                globals.left.desired = 25;
            } else {
                // None
                globals.right.desired = 2;
                globals.left.desired = 2;
            }
        }

        if (globals.right.desired != globals.right.running) {
            globals.right.halt = true;
        } else if (globals.left.desired != globals.left.running) {
            globals.left.halt = true;
        }
    }
}

int main()
{
    ledInit();
    gpioInit();

    std::thread run_thread(ledRun);
    std::thread con_thread(test);
    std::thread handler_thread(inputHandler);

    con_thread.join();
    run_thread.join();
    handler_thread.join();

    an.mode0(ledString, 0);
    an.mode0(ledString, 1);

    //Clean up and exit
    //ws2811_fini(&ledString);
    gpioTerminate();
    return 0;
}