#include "setup.h"
#include "stdlib.h"
#include <cstdio>

class Regulator {
public:
    float K;
    float Pi;
    float I = 0;
    float E;
    float U;
    float Smin;
    float Y_I;
    float Smax;
    Regulator(float K_, float Pi_, float Smin_, float Smax_) {
        K = K_;
        Pi = Pi_;
        Smin = Smin_;
        Smax = Smax_;
    }

    float calculate(float Uzad, float U) {
        E = Uzad - U;
        float Y_Kp = K * E;
        I = I + E / (Pi * 10);
        if (I > 100)
            I = 100;
        if (I < -100)
            I = -100;
        Y_I = I;
        float Y = Y_Kp + Y_I;
        if (Y > Smax)
            Y = Smax;
        if (Y < Smin)
            Y = Smin;
        return (Y);
    }

};
