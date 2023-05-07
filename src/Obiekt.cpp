#include "setup.h"
#include "stdlib.h"
#include <cstdio>

class Obiekt {
public:
    float I = 0;
    float K;
    float T;
    float E;
    float Y = 0;
    Obiekt(float K_, float T_) {
        K = K_;
        T = T_;
    }
    float calculate(float U) {
        Y = Y + (K / T) * (U * K - Y) * 0.10;
        return (Y);
    }

};
