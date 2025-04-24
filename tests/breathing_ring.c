#include <locale.h>
#include <monodraw.h>
#include <math.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    setlocale(LC_CTYPE, "");

    struct Canvas* canvas = create_canvas(100, 100);

    for (int i = 0; 1; i++) {
        clear_canvas(canvas);

        float size = fabsf(sinf(i / 100.0));
        draw_ring(canvas, 50, 50, 50 * size, 1);

        system("clear");
        print_canvas(canvas);

        usleep(10000);
    }

    destroy_canvas(canvas);

    return 0;
}
