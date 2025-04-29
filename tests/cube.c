#include <locale.h>
#include <monodraw.h>
#include <stdlib.h>

int main() {
    setlocale(LC_ALL, "");

    struct Canvas* canvas = create_canvas(100, 100);
    float x = 50;
    float y = 50;
    draw_triangle(canvas, x, y + 10, x + 10, y, x + 25, y + 10, 1);
    draw_triangle(canvas, x, y + 10, x + 15, y + 20, x + 25, y + 10, 1);
    draw_triangle(canvas, x, y + 10, x, y + 25, x + 15, y + 35, 1);
    draw_triangle(canvas, x, y + 10, x + 15, y + 20, x + 15, y + 35, 1);
    draw_triangle(canvas, x + 25, y + 10, x + 15, y + 20, x + 15, y + 35, 1);
    draw_triangle(canvas, x + 25, y + 10, x + 25, y + 25, x + 15, y + 35, 1);

    system("clear");
    print_canvas(canvas);

    destroy_canvas(canvas);

    return 0;
}
