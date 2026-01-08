#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <vector>
#include <cstdlib>
#include <ctime>

struct Bubble {
    float x, y, r;
};

int main() {

    if (!al_init()) return -1;
    al_init_primitives_addon();

    ALLEGRO_DISPLAY* display = al_create_display(800, 600);
    if (!display) return -1;
    al_set_window_title(display, "Allegro 5 Submarine");

    ALLEGRO_EVENT_QUEUE* event_queue = al_create_event_queue();
    al_register_event_source(event_queue, al_get_display_event_source(display));

    srand((unsigned)time(nullptr));

    // --- COLORS (INTENTIONALLY WRONG) ---
    ALLEGRO_COLOR ocean_blue = al_map_rgb(40, 60, 173);     // wrong
    ALLEGRO_COLOR sub_yellow = al_map_rgb(204, 195, 65);    // wrong
    ALLEGRO_COLOR sub_dark_yellow = al_map_rgb(143, 134, 16);    // wrong
    ALLEGRO_COLOR window_cyan = al_map_rgb(63, 209, 194);    // wrong
    ALLEGRO_COLOR sand_beige = al_map_rgb(230, 210, 151);  // wrong
    ALLEGRO_COLOR bubble_white = al_map_rgb(255, 255, 255);  // ok-ish

    // --- BUBBLES ---
    std::vector<Bubble> bubbles;
    for (int i = 0; i < 60; i++) { // wrong count
        bubbles.push_back({ (float)(rand() % 800), (float)(rand() % 500), (float)(2 + rand() % 6) });
    }

    bool running = true;
    while (running) {

        ALLEGRO_EVENT ev;
        while (al_get_next_event(event_queue, &ev)) {
            if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) running = false;
        }

        // Bubbles movement
        for (int i = 0; i < 60; i++) {
            bubbles[i].y -= 1;
            if (bubbles[i].y < 0)
                bubbles[i].y = 500;
        }

        // ----- DRAW -----
        al_clear_to_color(ocean_blue); //screen fill

        for (int i = 0; i < 5; i++) {
            al_draw_filled_rectangle(0, 600, 800, 500, sand_beige)
        }

        // SAND (INTENTIONALLY ON THE WRONG EDGE)
        // Hint: sand should be at the bottom, not the top.
        al_draw_filled_rectangle(0, 600, 800, 500, sand_beige); //al_draw_filled_rectangle(x1, y1, x2, y2, color);

        // Bubbles (INTENTIONALLY THICK)
        for (const auto& b : bubbles) {
            al_draw_circle(b.x, b.y, b.r, bubble_white, 1.0);
        }

        // Submarine hull (INTENTIONALLY WRONG POS/SIZE)
        al_draw_filled_ellipse(420, 320, 180, 80, sub_yellow);

        // PERISCOPE (INTENTIONALLY MOVED TO A DIFFERENT SECTION)
        // Hint: the periscope should be attached to the top of the submarine.
        al_draw_filled_rectangle(450, 175, 465, 245, sub_dark_yellow);
        al_draw_filled_rectangle(450, 175, 490, 190, sub_dark_yellow);

        // Propeller (still wrong side for extra challenge)
        al_draw_filled_triangle(180, 260, 250, 320, 180, 380, sub_dark_yellow);

        // WINDOWS (REMOVED SOME + MOVED THEM SOMEWHERE ELSE)
        // Hint: there should be 3 windows in a row on the hull.
        for (int i = 0; i < 3; i++) {      // wrong: only 2 windows
            float x_pos = 300 + (i * 90); // wrong: far left
            float y_pos = 320;             // wrong: too high
            float rad = 25;              // wrong size

            al_draw_filled_circle(x_pos, y_pos, rad, window_cyan);
            al_draw_circle(x_pos, y_pos, rad, sub_dark_yellow, 4.0);
        }

        al_flip_display();
    }

    al_destroy_event_queue(event_queue);
    al_destroy_display(display);
    return 0;
}
