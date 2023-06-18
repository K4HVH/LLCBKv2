#include "rpi_ws281x-master/ws2811.h"

class anims {
    public:
        void mode0(ws2811_t string, int ch);
        void mode1(ws2811_t string, int ch);
        void mode15(ws2811_t string, int ch);
        void mode2(ws2811_t string, int ch);
        void mode25(ws2811_t string, int ch);

};