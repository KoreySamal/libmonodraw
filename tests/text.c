#include <locale.h>
#include <monodraw.h>
#include <stdlib.h>

int main() {
    setlocale(LC_ALL, "");

    struct Canvas* canvas = create_canvas(100, 100);

    draw_frame(canvas, 30.5, 31, 62, 60, 1, 1);
    draw_char(canvas, 32, 32, L'a');
    draw_char(canvas, 60, 32, L'b');
    draw_char(canvas, 60, 58, L'c');
    draw_char(canvas, 32, 58, L'd');

    draw_text(
        canvas,
        36,
        40,
        29,
        10,
        L"Hello, world!\nПривет, мир!\nمرحبا بالعالم!"
    );

    system("clear");
    print_canvas(canvas);

    destroy_canvas(canvas);

    return 0;
}
