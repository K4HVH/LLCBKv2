#include "animations.h"
#include "definitions.cpp"
#include <thread>
#include <chrono>

iter it;

void anims::mode0(ws2811_t string, int ch)
{
    // clear the LEDs
    for (const int& value : it.LEDS_BOTH(0, 8, 0, 6, 1)) {
        string.channel[ch].leds[value] = 0x000000;
    }

    // Push updated colors
    ws2811_render(&string);
}

void anims::mode1(ws2811_t string, int ch)
{
    // clear the interior LEDs from any residual animations
    for (const int& value : it.LEDS_BOTH(1, 8, 1, 6, 1)) {
        string.channel[ch].leds[value] = 0x000000;
    }

    // outer ring
    for (const int& value : it.LEDS_BOTH(0, 0, 0, 0, 1)) {
        string.channel[ch].leds[value] = globals.ledCol;
    }

    while (!globals.shutdown)
    {

        for (int i = 0; i < 8; i++)
        {

            if (ch == 0) {
                for (const int& value : it.LEDS_LARGE(1, 1, 8)) {
                    string.channel[ch].leds[value + i] = globals.ledCol;
                }

                for (const int& value : it.LEDS_SMALL(1, 1, 8)) {
                    string.channel[ch].leds[value + i] = globals.ledCol;
                }
            } else {
                for (const int& value : it.LEDS_LARGE(1, 1, 8)) {
                    string.channel[ch].leds[value - i + 7] = globals.ledCol;
                }

                for (const int& value : it.LEDS_SMALL(1, 1, 8)) {
                    string.channel[ch].leds[value - i + 7] = globals.ledCol;
                }
            }

            // Push updated colors
            ws2811_render(&string);
            std::this_thread::sleep_for(std::chrono::milliseconds(40));

            if (ch == 0) {
                for (const int& value : it.LEDS_LARGE(1, 1, 8)) {
                    string.channel[ch].leds[value + i] = 0x000000;
                }

                for (const int& value : it.LEDS_SMALL(1, 1, 8)) {
                    string.channel[ch].leds[value + i] = 0x000000;
                }
            } else {
                for (const int& value : it.LEDS_LARGE(1, 1, 8)) {
                    string.channel[ch].leds[value - i + 7] = 0x000000;
                }

                for (const int& value : it.LEDS_SMALL(1, 1, 8)) {
                    string.channel[ch].leds[value - i + 7] = 0x000000;
                }
            }

            if ((ch == 0) && (globals.right.halt)) {
                globals.right.halt = false;
                return;
            } else if ((ch == 1) && (globals.left.halt)) {
                globals.left.halt = false;
                return;
            }
        }
    }
}

void anims::mode15(ws2811_t string, int ch)
{
    // clear the interior LEDs from any residual animations
    for (const int& value : it.LEDS_BOTH(1, 8, 1, 6, 1)) {
        string.channel[ch].leds[value] = 0x000000;
    }

    // outer ring
    for (const int& value : it.LEDS_BOTH(0, 0, 0, 0, 1)) {
        string.channel[ch].leds[value] = globals.ledCol;
    }

    while (!globals.shutdown)
    {

        for (int i = 0; i < 8; i++)
        {
            if (ch == 0) {
                for (const int& value : it.LEDS_LARGE(1, 1, 8)) {
                    string.channel[ch].leds[value + i] = globals.ledCol;
                }

                for (const int& value : it.LEDS_SMALL(8-i, 8-i, 1)) {
                    string.channel[ch].leds[value] = globals.ledCol;
                }
            } else {
                for (const int& value : it.LEDS_LARGE(1, 1, 8)) {
                    string.channel[ch].leds[value - i + 7] = globals.ledCol;
                }

                for (const int& value : it.LEDS_SMALL(8-i, 8-i, 1)) {
                    string.channel[ch].leds[value] = globals.ledCol;
                }
            }

            // Push updated colors
            ws2811_render(&string);
            std::this_thread::sleep_for(std::chrono::milliseconds(40));

            if (ch == 0) {
                for (const int& value : it.LEDS_LARGE(1, 1, 8)) {
                    string.channel[ch].leds[value + i] = 0x000000;
                }

                if (i == 7) {
                    for (const int& value : it.LEDS_SMALL(1, 6, 1)) {
                        string.channel[ch].leds[value] = 0x000000;
                    }
                }
            } else {
                for (const int& value : it.LEDS_LARGE(1, 1, 8)) {
                    string.channel[ch].leds[value - i + 7] = 0x000000;
                }

                if (i == 7) {
                    
                    for (const int& value : it.LEDS_SMALL(1, 6, 1)) {
                        string.channel[ch].leds[value] = 0x000000;
                    }
                }
            }

            if ((ch == 0) && (globals.right.halt)) {
                globals.right.halt = false;
                return;
            } else if ((ch == 1) && (globals.left.halt)) {
                globals.left.halt = false;
                return;
            }
        }
    }
}

void anims::mode2(ws2811_t string, int ch)
{
    // clear the interior LEDs from any residual animations
    if (ch == 0) {
        if (!globals.right.compBrakeAnim) {
            for (const int& value : it.LEDS_LARGE(1, 8, 1)) {
                string.channel[ch].leds[value] = 0x000000;
            }
        }
    } else {
        if (!globals.left.compBrakeAnim) {
            for (const int& value : it.LEDS_LARGE(1, 8, 1)) {
                string.channel[ch].leds[value] = 0x000000;
            }
        }
    }

    for (const int& value : it.LEDS_SMALL(1, 6, 1)) {
        string.channel[ch].leds[value] = 0x000000;
    }

    // outer ring
    for (const int& value : it.LEDS_BOTH(0, 0, 0, 0, 1)) {
        string.channel[ch].leds[value] = globals.ledCol;
    }

    while (!globals.shutdown)
    {        
        for (int i = 0; i < 8; i++)
        {
            if (ch == 0) {
                for (const int& value : it.LEDS_LARGE(8-i, 8-i, 1)) {
                    string.channel[ch].leds[value] = globals.ledCol;
                }

                for (const int& value : it.LEDS_SMALL(1, 1, 8)) {
                    string.channel[ch].leds[value + i] = globals.ledCol;
                }
            } else {
                for (const int& value : it.LEDS_LARGE(8-i, 8-i, 1)) {
                    string.channel[ch].leds[value] = globals.ledCol;
                }

                for (const int& value : it.LEDS_SMALL(1, 1, 8)) {
                    string.channel[ch].leds[value - i + 7] = globals.ledCol;
                }
            }

            // Push updated colors
            ws2811_render(&string);
            std::this_thread::sleep_for(std::chrono::milliseconds(40));

            if (ch == 0) {
                if (i == 7) {
                    globals.right.compBrakeAnim = true;
                }

                for (const int& value : it.LEDS_SMALL(1, 1, 8)) {
                    string.channel[ch].leds[value + i] = 0x000000;
                }

            } else {
                if (i == 7) {
                    globals.left.compBrakeAnim = true;
                }

                for (const int& value : it.LEDS_SMALL(1, 1, 8)) {
                    string.channel[ch].leds[value - i + 7] = 0x000000;
                }
            }

            if ((ch == 0) && (globals.right.halt)) {
                globals.right.halt = false;
                return;
            } else if ((ch == 1) && (globals.left.halt)) {
                globals.left.halt = false;
                return;
            }
        }
    }
}

void anims::mode25(ws2811_t string, int ch)
{
    // clear the interior LEDs from any residual animations
    if (ch == 0) {
        if (!globals.right.compBrakeAnim) {
            for (const int& value : it.LEDS_BOTH(1, 8, 1, 6, 1)) {
                string.channel[ch].leds[value] = 0x000000;
            }
        }
    } else {
        if (!globals.left.compBrakeAnim) {
            for (const int& value : it.LEDS_BOTH(1, 8, 1, 6, 1)) {
                string.channel[ch].leds[value] = 0x000000;
            }
        }
    }

    // outer ring
    for (const int& value : it.LEDS_BOTH(0, 0, 0, 0, 1)) {
        string.channel[ch].leds[value] = globals.ledCol;
    }

    while (!globals.shutdown)
    {        
        for (int i = 0; i < 8; i++)
        {
            if (ch == 0) {
                for (const int& value : it.LEDS_LARGE(8-i, 8-i, 1)) {
                    string.channel[ch].leds[value] = globals.ledCol;
                }

                for (const int& value : it.LEDS_SMALL(8-i, 8-i, 1)) {
                    string.channel[ch].leds[value] = globals.ledCol;
                }
            } else {
                for (const int& value : it.LEDS_LARGE(8-i, 8-i, 1)) {
                    string.channel[ch].leds[value] = globals.ledCol;
                }

                for (const int& value : it.LEDS_SMALL(8-i, 8-i, 1)) {
                    string.channel[ch].leds[value] = globals.ledCol;
                }
            }

            // Push updated colors
            ws2811_render(&string);
            std::this_thread::sleep_for(std::chrono::milliseconds(40));

            if (ch == 0) {
                if (i == 7) {
                    globals.right.compBrakeAnim = true;

                    for (const int& value : it.LEDS_SMALL(1, 6, 1)) {
                        string.channel[ch].leds[value] = 0x000000;
                    }
                }

            } else {
                if (i == 7) {
                    globals.left.compBrakeAnim = true;
                    
                    for (const int& value : it.LEDS_SMALL(1, 6, 1)) {
                        string.channel[ch].leds[value] = 0x000000;
                    }
                }
            }

            if ((ch == 0) && (globals.right.halt)) {
                globals.right.halt = false;
                return;
            } else if ((ch == 1) && (globals.left.halt)) {
                globals.left.halt = false;
                return;
            }
        }
    }
}