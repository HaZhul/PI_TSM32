#ifndef square_CL
#define square_CL

class square {
public:
    int x, y, l, w, dx, dy, s;
    square(int, int, int, int);
    void draw_rectangle();
    void draw_empty_rectangle();
    void draw_triangle();
    void draw_empty_aquarium();
    void changing_water_level(int water_level);
    void draw_empty_graph();

};

#endif
