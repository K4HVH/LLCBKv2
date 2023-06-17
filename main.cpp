// Rewriting this in c++ cause python is shit and slow and shit

// Includes
#include <iostream>
#include <signal.h>
#include <string>
#include <cstring>
#include <thread>

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
void led_init()
{
    ledString.freq = WS2811_TARGET_FREQ;
    ledString.dmanum = 10;

    ledString.channel[0].gpionum = 18;
    ledString.channel[0].count = 482;
    ledString.channel[0].invert = 0;
    ledString.channel[0].brightness = 255;
    ledString.channel[0].strip_type = WS2811_STRIP_GRB;

    ledString.channel[1].gpionum = 19;
    ledString.channel[1].count = 266;
    ledString.channel[1].invert = 0;
    ledString.channel[1].brightness = 255;
    ledString.channel[1].strip_type = WS2811_STRIP_GRB;

    if (ws2811_init(&ledString) != WS2811_SUCCESS)
    {
        std::cerr << "Failed to init LED strip\n";
        exit(EXIT_FAILURE);
    }

    signal(SIGINT, signalHandler);
    signal(SIGTERM, signalHandler);
}

// Modes of operation
// 1.) No condition
//  15.) Indi Right
//  16.) Indi Left
// 2.) Brakes down
//  25.) Indi Right
//  26.) Indi Left
// 3.) Brakes up    
//  35.) Indi Right    <-- Maybe idk yet
//  36.) Indi Left

void right_run()
{
    while (!globals.shutdown)
    {
        an.mode1(ledString, 0);
        an.mode15(ledString, 0);
    }
}

void left_run()
{
    while (!globals.shutdown)
    {
        an.mode1(ledString, 1);
        an.mode15(ledString, 1);
    }
}


//std::vector<int> result = it.LEDS_OUT(0, 0, 0, 0, 1);
//for (const int& value : result) {
//    string.channel[0].leds[value] = 0x100005;
//}
// Leaving this here in case


// Run functions for LEDS
void led_run()
{
    std::thread right_thread(right_run);
    std::thread left_thread(left_run);

    right_thread.join();
    left_thread.join();

    std::cout << "here\n";
}

void test()
{
    std::cout << "Press enter to exit\n";
    if (std::cin.ignore()) {
        globals.rightHalt = true;
        globals.leftHalt = true;
        globals.shutdown = true;

        std::cout << "here\n";
    }
}

int main()
{
    led_init();

    std::thread run_thread(led_run);
    std::thread con_thread(test);

    con_thread.join();
    //run_thread.join();

    an.mode0(ledString, 0);
    an.mode0(ledString, 1);

    //Clean up and exit
    //ws2811_fini(&ledString);
    return 0;
}