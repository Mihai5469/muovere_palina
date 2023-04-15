// muovere_palina.cpp : Questo file contiene la funzione 'main', in cui inizia e termina l'esecuzione del programma.
//

#include <iostream>
#include <string>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>

using namespace std;

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

void init_allegro();        //inizializa la grafica di allegro5
void install_peri();        //installa le periferiche necesarie
void inp(ALLEGRO_EVENT event, bool& chiudi);

void pallina(palla& p);     //disegna la pallina

int main()
{
    bool chiudi = false;
    palla p;

    p.coordinata.x = 400;
    p.coordinata.y = 300;
    p.raggio = 10;
    p.colore = "red";
    p.piena = false;
    
    
    init_allegro();     //inizializazione allegro
    install_peri();     //installa le periferiche del computer

    

    //variabili allegro
    ALLEGRO_DISPLAY* display = al_create_display(800, 600);
    ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue();
    ALLEGRO_TIMER* timer = al_create_timer(1.0 / 244.0);
    
    ALLEGRO_EVENT event;

    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_display_event_source(display));
    al_register_event_source(queue, al_get_timer_event_source(timer));


    al_start_timer(timer);
    while (true) {
        al_wait_for_event(queue, &event);

        inp(event, chiudi);
       
        if (chiudi)
            break;

        al_clear_to_color(al_map_rgb(200, 200, 200));

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

void inp(ALLEGRO_EVENT event, bool& chiudi) {
    switch (event.type)
    {
    case ALLEGRO_EVENT_TIMER:
        break;

    case ALLEGRO_KEY_DOWN:

        break;

    case ALLEGRO_EVENT_DISPLAY_CLOSE:
        chiudi = true;
        break;
    }
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
