// muovere_palina.cpp : Questo file contiene la funzione 'main', in cui inizia e termina l'esecuzione del programma.
//

#include <iostream>
#include <string>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>

using namespace std;

#define KEY_SEEN     1
#define KEY_RELEASED 2


struct coordinate
{
    double x;
    double y;
};


struct palla {
    coordinate coordinata;
    string colore;
    double raggio;
    bool piena;
};

struct triangolo
{
    coordinate punta;
    coordinate aDestra;
    coordinate aSinistra;
};

struct dim_dysplay {
    int w;
    int h;
};

void init_allegro();        //inizializa la grafica di allegro5
void install_peri();        //installa le periferiche necesarie
void draw_menu(coordinate punta);
void muovi_menu(coordinate& punta, unsigned char key[], palla& p, bool& men);

void draw_triangle(coordinate punta);

void pallina(palla& p);     //disegna la pallina
void muoviPalla(palla& p, unsigned char key[], dim_dysplay dim);    //muovimento della pallina

int main()
{
    bool chiudi = false;
    bool men = true;
    palla p;
    dim_dysplay d;
    coordinate punta;

    punta.x = 300;
    punta.y = 320;
    
    //dimensioni finestra
    d.w = 800;
    d.h = 600;

    //pallina
    p.coordinata.x = 400;
    p.coordinata.y = 300;
    p.raggio = 10;
    p.colore = "red";
    p.piena = true;
    
    
    init_allegro();     //inizializazione allegro
    install_peri();     //installa le periferiche del computer

    //variabili allegro
    ALLEGRO_DISPLAY* display = al_create_display(d.w, d.h);
    ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue();
    ALLEGRO_TIMER* timer = al_create_timer(1.0 / 244.0);
    
    ALLEGRO_EVENT event;

    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_display_event_source(display));
    al_register_event_source(queue, al_get_timer_event_source(timer));


    unsigned char key[ALLEGRO_KEY_MAX];
    memset(key, 0, sizeof(key));

    al_start_timer(timer);
    while (true) {
        al_wait_for_event(queue, &event);
        
        switch (event.type)
        {
        case ALLEGRO_EVENT_TIMER:

            if (key[ALLEGRO_KEY_ESCAPE])
                chiudi = true;
            else if (men)
                muovi_menu(punta, key, p, men);
            else
                muoviPalla(p, key, d);

            for (int i = 0; i < ALLEGRO_KEY_MAX; i++)
                key[i] &= KEY_SEEN;

            break;

        case ALLEGRO_EVENT_KEY_DOWN:
            key[event.keyboard.keycode] = KEY_SEEN | KEY_RELEASED;
            //start = true;
            break;

        case ALLEGRO_EVENT_KEY_UP:
            key[event.keyboard.keycode] &= KEY_RELEASED;
            break;

        case ALLEGRO_EVENT_DISPLAY_CLOSE:
            chiudi = true;
            break;
        }
       
        if (chiudi)
            break;

        al_clear_to_color(al_map_rgb(200, 200, 200));

        if(men)
            draw_menu(punta);
        else
            pallina(p);
        

        al_flip_display();

    }
    
}


void init_allegro() {
    al_init();
    al_init_primitives_addon();

    return;
}

void install_peri() {
    al_install_keyboard();

    return;
}

void pallina(palla& p) {
    int r = 0, g = 0, b = 0;
    
    if (p.colore == "red")
        r = 255;
    else if (p.colore == "green")
        g = 255;
    else if (p.colore == "blue")
        b = 255;

    if(p.piena)
        al_draw_filled_circle(p.coordinata.x, p.coordinata.y, p.raggio, al_map_rgb(r, g, b));
    else
        al_draw_circle(p.coordinata.x, p.coordinata.y, p.raggio, al_map_rgb(r, g, b), 2);
    return;
}
void draw_triangle(coordinate punta) {
    triangolo t;
    t.punta.x = punta.x;
    t.punta.y = punta.y + 20;
    t.aDestra.x = punta.x - 10;
    t.aDestra.y = punta.y + 40;
    t.aSinistra.x = punta.x + 10;
    t.aSinistra.y = punta.y + 40;

    al_draw_filled_triangle(t.punta.x, t.punta.y, t.aDestra.x, t.aDestra.y, t.aSinistra.x, t.aSinistra.y, al_map_rgb(0, 0, 0));
    return;
}
    
void draw_menu(coordinate punta) {
    coordinate p1, p2;
    p1.x = 300;
    p1.y = 300;
    p2.x = 500;
    p2.y = 300;

    al_draw_circle(p1.x, p1.y, 10, al_map_rgb(0, 0, 0), 3);
    al_draw_filled_circle(p2.x, p2.y, 10, al_map_rgb(0, 0, 0));

    draw_triangle(punta);
    
    return;
}
void muovi_menu(coordinate& punta, unsigned char key[], palla &p, bool& men) {
    if (((key[ALLEGRO_KEY_A]) || (key[ALLEGRO_KEY_LEFT])))
        punta.x = 300;
    if (((key[ALLEGRO_KEY_D]) || (key[ALLEGRO_KEY_RIGHT])))
        punta.x = 500;
    if (key[ALLEGRO_KEY_ENTER]) {
        if (punta.x == 300)
            p.piena = false;
        else
            p.piena = true;
        men = false;
    }


    return;
}

void muoviPalla(palla& p, unsigned char key[], dim_dysplay dim) {
    //muovimento sull'asse x
    if (((key[ALLEGRO_KEY_A]) || (key[ALLEGRO_KEY_LEFT])) && p.coordinata.x > p.raggio)
        p.coordinata.x--;
    if (((key[ALLEGRO_KEY_D]) || (key[ALLEGRO_KEY_RIGHT])) && p.coordinata.x < dim.w - p.raggio)
        p.coordinata.x++;
    //muovimento sull'asse y
    if (((key[ALLEGRO_KEY_W]) || (key[ALLEGRO_KEY_UP])) && p.coordinata.y > p.raggio)
        p.coordinata.y--;
    if (((key[ALLEGRO_KEY_S]) || (key[ALLEGRO_KEY_DOWN])) && p.coordinata.y < dim.h - p.raggio)
        p.coordinata.y++;

    return;
}
