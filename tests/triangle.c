#include <locale.h>
#include <monodraw.h>
#include <stdlib.h>

int main() {
    setlocale(LC_ALL, "");

    struct Canvas* canvas = create_canvas(100, 100);
    draw_triangle(canvas, 35, 45, 35, 65, 55, 65, 1);
    draw_triangle(canvas, 45, 35, 65, 35, 65, 55, 1);
    draw_triangle(canvas, 10, 10, 45, 25, 90, 10, 1);
    draw_triangle(canvas, 20, 20, 10, 80, 30, 50, 1);

    system("clear");
    print_canvas(canvas);

    destroy_canvas(canvas);

    return 0;
}
