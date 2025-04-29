#ifndef _LIB_MONODRAW_
#define _LIB_MONODRAW_ 1

#include <wchar.h>

struct Canvas {
    int width;
    int height;
    int char_width;
    int char_height;
    char* dots;
    wchar_t* chars;
};

struct Canvas* create_canvas(int width, int height);

void destroy_canvas(struct Canvas* canvas);

void print_canvas(struct Canvas* canvas);

void clear_canvas(struct Canvas* canvas);

void draw_dot(struct Canvas* canvas, float x, float y);

void draw_char(struct Canvas* canvas, float x, float y, wchar_t c);

void draw_line(
    struct Canvas* canvas,
    float x_start,
    float y_start,
    float x_end,
    float y_end,
    float width
);

void draw_text(
    struct Canvas* canvas,
    float x_start,
    float y_start,
    float max_width,
    float max_height,
    wchar_t* text
);

void draw_ring(
    struct Canvas* canvas,
    float x_center,
    float y_center,
    float radius,
    float width
);

void draw_circle(
    struct Canvas* canvas,
    float x_center,
    float y_center,
    float radius
);

void draw_rectangle(
    struct Canvas* canvas,
    float x_start,
    float y_start,
    float x_end,
    float y_end
);

void draw_frame(
    struct Canvas* canvas,
    float x_start,
    float y_start,
    float x_end,
    float y_end,
    float width
);

void draw_triangle(
    struct Canvas* canvas,
    float x1,
    float y1,
    float x2,
    float y2,
    float x3,
    float y3
);

void draw_black_hole(
    struct Canvas* canvas,
    float x_center,
    float y_center,
    float radius,
    float width
);

#endif
