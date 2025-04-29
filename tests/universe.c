#include <time.h>
#include <locale.h>
#include <monodraw.h>
#include <stdlib.h>
#include <unistd.h>

const int canvas_width = 100;
const int canvas_height = 100;
const int stars_count = 200;

int main() {
    setlocale(LC_CTYPE, "");
    srand(time(NULL));

    struct Canvas* canvas = create_canvas(canvas_width, canvas_height);

    int star_positions[stars_count][2];

    for (int i = 0; i < stars_count; i++) {
        star_positions[i][0] = rand() % canvas_width;
        star_positions[i][1] = rand() % canvas_height;
    }

    for (int j = 0; j < stars_count; j++) {
        draw_dot(
            canvas,
            star_positions[j][0],
            star_positions[j][1],
            1
        );
    }

    draw_black_hole(canvas, 50, 50, 10, 0.5, 1);

    draw_circle(canvas, 20, 30, 5, 1);
    draw_circle(canvas, 80, 90, 20, 1);

    system("clear");
    print_canvas(canvas);

    destroy_canvas(canvas);

    return 0;
}
