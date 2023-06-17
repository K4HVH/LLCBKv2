#include <string>
#include <iostream>
#include <iterator>
#include <algorithm>
#include <vector>
#include <cmath>

// I was going to make this scalable but im trash
// and just want to get this working first

// The rings are going to be connect as follows
// RR -> RL
// MR -> ML
// This requires basically 2 of everything cause im lazy and its easier to do that

class iter {
    public:
        std::vector<int> LEDS_BOTH(int r1start, int r1stop, int r2start, int r2stop, int step);
        std::vector<int> LEDS_LARGE(int r1start, int r1stop, int step);
        std::vector<int> LEDS_SMALL(int r1start, int r1stop, int step);
};

struct globals {
    bool rightHalt = false;
    bool leftHalt = false;
    bool shutdown = false;
} globals;

struct rings {

    struct large {
        int totalRings = 9;
        int totalLeds = 241;
        int ringLedCount[9] = {60, 48, 40, 32, 24, 16, 12, 8, 1};
        int ringStartLed[9] = {0, 60, 108, 148, 180, 204, 220, 232, 240};
        int ringEndLed[9] = {60, 108, 148, 180, 204, 220, 232, 240, 241};

        struct relative {
            int ringStartLed[9] = {0, 60, 108, 148, 180, 204, 220, 232, 240};
            int ringEndLed[9] = {60, 108, 148, 180, 204, 220, 232, 240, 241};
        } relative;
    } large;

    struct small {
        int totalRings = 7;
        int totalLeds = 133;
        int ringLedCount[7] = {40, 32, 24, 16, 12, 8, 1};
        int ringStartLed[7] = {0, 40, 72, 96, 112, 124, 132};
        int ringEndLed[7] = {40, 72, 96, 112, 124, 132, 133};

        struct relative {
            int ringStartLed[7] = {241, 281, 313, 337, 353, 365, 373};
            int ringEndLed[7] = {281, 313, 337, 353, 365, 373, 374};
        } relative;
    } small;

} rings;