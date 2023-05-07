#include "setup.h"
#include "square.h"
#include "stdlib.h"
#include <cstdio>

extern unsigned long *ekran;

square::square(int x_cor, int y_cor, int lenght, int width) {
    x = x_cor;
    y = y_cor;
    l = lenght + x_cor;
    w = width + y_cor;
    dx = ((rand() & 0x1) ? 1 : -1) * (((rand() & 0x7) + 2) >> 1);
    dy = ((rand() & 0x1) ? 1 : -1) * (((rand() & 0x7) + 2) >> 1);
}

void square::draw_rectangle() {
    int current_y = y;
    for (int current_x = x; current_x <= l; current_x++) {
        for (; current_y <= w; current_y++) {
            SetPixel(ekran, current_x, current_y);
        }
        current_y = y;

    }
}
void square::draw_empty_rectangle() {
    int current_y = y;
    for (int current_x = x; current_x <= l; current_x++) {
        SetPixel(ekran, current_x, current_y);
    }
    current_y = w;
    for (int current_x = x; current_x <= l; current_x++) {
        SetPixel(ekran, current_x, current_y);
    }
    int current_x = x;
    for (int current_y = y; current_y <= w; current_y++) {
        SetPixel(ekran, current_x, current_y);
    }
    current_x = l;
    for (int current_y = y; current_y <= w; current_y++) {
        SetPixel(ekran, current_x, current_y);
    }
}

void square::draw_empty_graph() {
    int current_y = w;
    int p2 = ((w-y)/5);
    int x2;

    for (int i=0;i<3;i++) {
        x2 = x - i;
        SetPixel(ekran, x2, y);
        SetPixel(ekran, x2, (y + p2));
        SetPixel(ekran, x2, (y + 2*p2));
        SetPixel(ekran, x2, (y + 3*p2));
        SetPixel(ekran, x2, (y + 4*p2));
    }
    for (int current_x = x; current_x <= l; current_x++) {
        SetPixel(ekran, current_x, current_y);
    }
    int current_x = x;
    for (int current_y = y; current_y <= w; current_y++) {
        SetPixel(ekran, current_x, current_y);
    }
}

void square::draw_triangle() {
    int current_y = y;
    for (int current_x = x; current_x <= l; current_x++) {
        for (; current_y <= w; current_y++) {
            SetPixel(ekran, current_x, current_y);
        }
        current_y = y++;
    }
}

void square::draw_empty_aquarium() {
    int current_y = w;
    int p1 = (w-y)/5;
    int x1;


    for (int i=0;i<3;i++) {
        x1 = x - i;
        SetPixel(ekran, x1, y);
        SetPixel(ekran, x1, (y + p1));
        SetPixel(ekran, x1, (y+2*p1));
        SetPixel(ekran, x1, (y+3*p1));
        SetPixel(ekran, x1, (y+4*p1));
    }
    for (int current_x = x; current_x <= l; current_x++) {
        SetPixel(ekran, current_x, current_y);
    }
    int current_x = x;
    for (int current_y = y; current_y <= w; current_y++) {
        SetPixel(ekran, current_x, current_y);
    }
    current_x = l;
    for (int current_y = y; current_y <= w; current_y++) {
        SetPixel(ekran, current_x, current_y);
    }
}

void square::changing_water_level(int water_level) {
    int current_y = w - water_level;
    for (int current_x = x; current_x <= l; current_x++) {
        for (; current_y <= w; current_y++) {
            SetPixel(ekran, current_x, current_y);
        }
        current_y = w - water_level;
    }
}

