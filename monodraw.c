#include <stdlib.h>
#include <math.h>
#include <wchar.h>
#include "monodraw.h"

const wchar_t canvas_symbols[] = {
    L' ',
    L'🬀',
    L'🬁',
    L'🬂',
    L'🬃',
    L'🬄',
    L'🬅',
    L'🬆',
    L'🬇',
    L'🬈',
    L'🬉',
    L'🬊',
    L'🬋',
    L'🬌',
    L'🬍',
    L'🬎',
    L'🬏',
    L'🬐',
    L'🬑',
    L'🬒',
    L'🬓',
    L'▌',
    L'🬔',
    L'🬕',
    L'🬖',
    L'🬗',
    L'🬘',
    L'🬙',
    L'🬚',
    L'🬛',
    L'🬜',
    L'🬝',
    L'🬞',
    L'🬟',
    L'🬠',
    L'🬡',
    L'🬢',
    L'🬣',
    L'🬤',
    L'🬥',
    L'🬦',
    L'🬧',
    L'▐',
    L'🬨',
    L'🬩',
    L'🬪',
    L'🬫',
    L'🬬',
    L'🬭',
    L'🬮',
    L'🬯',
    L'🬰',
    L'🬱',
    L'🬲',
    L'🬳',
    L'🬴',
    L'🬵',
    L'🬶',
    L'🬷',
    L'🬸',
    L'🬹',
    L'🬺',
    L'🬻',
    L'█',
};

const float aspect = 4.0 / 3.0;

struct Canvas* create_canvas(int width, int height) {
    if (width < 0 || height < 0) {
        return NULL;
    }

    struct Canvas* canvas = malloc(sizeof(struct Canvas));
    if (canvas == NULL) {
        return NULL;
    }

    canvas->width = width;
    canvas->height = height;
    canvas->char_width = ceil(width * aspect / 2.0);
    canvas->char_height = ceil(height / 3.0);

    canvas->dots = calloc(
        canvas->char_width * canvas->char_height,
        sizeof(char)
    );
    if (canvas->dots == NULL) {
        free(canvas);
        return NULL;
    }

    return canvas;
}

void destroy_canvas(struct Canvas* canvas) {
    free(canvas->dots);
    free(canvas);
}

void set_canvas_dot(struct Canvas* canvas, int x, int y, int state) {
    if (
        x < 0 ||
        y < 0 ||
        x > canvas->width * aspect ||
        y > canvas->height
    ) {
        return;
    }

    int char_x = x / 2;
    int char_y = y / 3;
    int char_index = canvas->char_width * char_y + char_x;

    int inner_x = x % 2;
    int inner_y = y % 3;
    char bit_mask = 1 << (inner_y * 2 + inner_x);

    if (state) {
        canvas->dots[char_index] |= bit_mask;
    } else {
        canvas->dots[char_index] &= ~bit_mask;
    }
}

void print_canvas(struct Canvas* canvas) {
    int c;
    for (int y = 0; y < canvas->char_height; y++) {
        for (int x = 0; x < canvas->char_width; x++) {
            c = canvas->dots[y * canvas->char_width + x];
            putwchar(canvas_symbols[c]);
        }
        putwchar('\n');
    }
}

void clear_canvas(struct Canvas* canvas) {
    for (int y = 0; y < canvas->char_height; y++) {
        for (int x = 0; x < canvas->char_width; x++) {
            canvas->dots[y * canvas->char_width + x] = 0;
        }
    }
}

void draw_dot(struct Canvas* canvas, int x, int y) {
    set_canvas_dot(canvas, x * aspect, y, 1);
}

void draw_line(
    struct Canvas* canvas,
    float x_start,
    float y_start,
    float x_end,
    float y_end,
    float width
) {
    float cathesus1 = x_end - x_start;
    float cathesus2 = y_end - y_start;
    float hypot = hypotf(cathesus1, cathesus2);
    float angle = atan2f(cathesus2, cathesus1);

    x_start *= aspect;

    float x;
    float y;
    float half_width = width / 2.0;
    const float step = 0.5;
    for (float j = -half_width; j <= half_width; j += 0.5) {
        for (float i = hypot; i >= 0; i -= step) {
            x = roundf(x_start + i * cosf(angle) * aspect + j * sinf(-angle) * aspect);
            y = roundf(y_start + i * sinf(angle) + j * cosf(-angle));
            set_canvas_dot(canvas, x, y, 1);
        }
    }
}

void draw_ring(
    struct Canvas* canvas,
    float x_center,
    float y_center,
    float radius,
    float width
) {
    x_center *= aspect;

    int x_start = floor(x_center - radius * aspect - width);
    int x_end = ceil(x_center + radius * aspect + width);
    int y_start = floor(y_center - radius - width);
    int y_end = ceil(y_center + radius + width);

    float cathesus1;
    float cathesus2;
    float distance;
    for (int y = y_start; y <= y_end; y++) {
        for (int x = x_start; x <= x_end; x++) {
            cathesus1 = fabsf(x_center - x) / aspect;
            cathesus2 = fabsf(y_center - y);
            distance = hypotf(cathesus1, cathesus2);

            if (fabsf(distance - radius) < width) {
                set_canvas_dot(canvas, x, y, 1);
            }
        }
    }
}

void draw_circle(
    struct Canvas* canvas,
    float x_center,
    float y_center,
    float radius
) {
    x_center *= aspect;

    int x_start = floor(x_center - radius * aspect);
    int x_end = ceil(x_center + radius * aspect);
    int y_start = floor(y_center - radius);
    int y_end = ceil(y_center + radius);

    float cathesus1;
    float cathesus2;
    float distance;
    for (int y = y_start; y <= y_end; y++) {
        for (int x = x_start; x <= x_end; x++) {
            cathesus1 = fabsf(x_center - x) / aspect;
            cathesus2 = fabsf(y_center - y);
            distance = hypotf(cathesus1, cathesus2);

            if (distance <= radius) {
                set_canvas_dot(canvas, x, y, 1);
            }
        }
    }
}

void draw_rectangle(
    struct Canvas* canvas,
    float x_start,
    float y_start,
    float x_end,
    float y_end
) {
    x_start *= aspect;
    x_end *= aspect;

    float temp;
    if (x_start > x_end) {
        temp = x_end;
        x_end = x_start;
        x_start = temp;
    }
    if (y_start > y_end) {
        temp = y_end;
        y_end = y_start;
        y_start = temp;
    }

    for (float y = y_start; y <= y_end; y++) {
        for (float x = x_start; x <= x_end; x++) {
            set_canvas_dot(canvas, x, y, 1);
        }
    }
}

void draw_frame(
    struct Canvas* canvas,
    float x_start,
    float y_start,
    float x_end,
    float y_end,
    float width
) {
    float half_width = width / 2.0;
    draw_line(canvas, x_start, y_start, x_end, y_start, width);
    draw_line(canvas, x_end, y_start - half_width, x_end, y_end + half_width, width);
    draw_line(canvas, x_start, y_end, x_end, y_end, width);
    draw_line(canvas, x_start, y_start - half_width, x_start, y_end + half_width, width);
}

void draw_black_hole(
    struct Canvas* canvas,
    float x_center,
    float y_center,
    float radius,
    float width
) {
    x_center *= aspect;

    int x_start = floor(x_center - radius * aspect * 3 - width);
    int x_end = ceil(x_center + radius * aspect * 3 + width);
    int y_start = floor(y_center - radius - width);
    int y_end = ceil(y_center + radius + width);

    float cathesus1;
    float cathesus2;
    float distance;
    for (int y = y_start; y <= y_end; y++) {
        for (int x = x_start; x <= x_end; x++) {
            cathesus1 = fabsf(x_center - x) / aspect;
            cathesus2 = fabsf(y_center - y);
            distance = hypotf(cathesus1, cathesus2);

            if (fabsf(distance - radius) < width + width * (cathesus1 / cathesus2)) {
                set_canvas_dot(canvas, x, y, 1);
            }
        }
    }
}
