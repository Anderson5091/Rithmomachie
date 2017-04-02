
/*
 *    RITHMOMACHIE - Created by Anderson5091 30/Mars/17.
 *
 *    .
 */

#include "Event.h"

#define  BOUTONS_SOURIS 10
#define MAX_KEYBUF   16

int key[ALLEGRO_KEY_MAX];

static  int tableau_souris[BOUTONS_SOURIS];
static  int sx, sy;
static int keybuf[MAX_KEYBUF];
static int keybuf_len = 0;
static ALLEGRO_MUTEX *keybuf_mutex;


bool souris_bouton_presse(int b){
    return tableau_souris[b] & 1;
}

bool souris_bouton_relache(int b) {
    return tableau_souris[b] & 2;
}

int souris_x(void) {
    return sx;
}

int souris_y(void) {
    return sy;
}

void souris_gerer_evenement(ALLEGRO_EVENT *event) {
    switch (event->type) {
        case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
            tableau_souris[event->mouse.button] |= (1 << 0);
            tableau_souris[event->mouse.button] |= (1 << 1);
            break;

        case ALLEGRO_EVENT_MOUSE_BUTTON_UP:
            tableau_souris[event->mouse.button] &= ~(1 << 0);
            tableau_souris[event->mouse.button] |= (1 << 2);
            break;
        case ALLEGRO_EVENT_MOUSE_AXES:
            sx = event->mouse.x;
            sy = event->mouse.y;
            break;
    }
}

void souris_tick(void) {
    // effacer les bits presse/relache
    int i;
    for(i = 0; i < BOUTONS_SOURIS; i++) {
        tableau_souris[i] &= ~(1 << 1);
        tableau_souris[i] &= ~(1 << 2);
    }

}

static void add_key(ALLEGRO_KEYBOARD_EVENT *event)
{
   if ((event->unichar == 0) || (event->unichar > 255))
      return;

   al_lock_mutex(keybuf_mutex);

   if (keybuf_len < MAX_KEYBUF) {
      keybuf[keybuf_len] = event->unichar | ((event->keycode << 8) & 0xff00);
      keybuf_len++;
   }

   al_unlock_mutex(keybuf_mutex);
}

int readkey()
{
   int c = 0;

   poll_input();

   al_lock_mutex(keybuf_mutex);

   if (keybuf_len > 0) {
      c = keybuf[0];
      keybuf_len--;
      memmove(keybuf, keybuf + 1, sizeof(keybuf[0]) * keybuf_len);
   }

   al_unlock_mutex(keybuf_mutex);

   return c;
}

void clear_keybuf()
{
   al_lock_mutex(keybuf_mutex);

   keybuf_len = 0;

   al_unlock_mutex(keybuf_mutex);
}
