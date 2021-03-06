#include <abi.h>
#include <fudge.h>
#include "box.h"
#include "element.h"

void print_insertfill(struct ring *ring, struct event_header *header, struct element_fill *fill)
{

    element_set(&fill->element, header->destination, ELEMENT_DAMAGE_UPDATE, sizeof (struct element_fill));
    ring_write(ring, fill, sizeof (struct element_fill));

}

void print_insertmouse(struct ring *ring, struct event_header *header, struct element_mouse *mouse)
{

    element_set(&mouse->element, header->destination, ELEMENT_DAMAGE_UPDATE, sizeof (struct element_mouse));
    ring_write(ring, mouse, sizeof (struct element_mouse));

}

void print_insertpanel(struct ring *ring, struct event_header *header, struct element_panel *panel)
{

    element_set(&panel->element, header->destination, ELEMENT_DAMAGE_UPDATE, sizeof (struct element_panel));
    ring_write(ring, panel, sizeof (struct element_panel));

}

void print_inserttext(struct ring *ring, struct event_header *header, struct element_text *text, unsigned int count)
{

    element_set(&text->element, header->destination, ELEMENT_DAMAGE_UPDATE, sizeof (struct element_text) + count);
    ring_write(ring, text, sizeof (struct element_text));

}

void print_insertwindow(struct ring *ring, struct event_header *header, struct element_window *window)
{

    element_set(&window->element, header->destination, ELEMENT_DAMAGE_UPDATE, sizeof (struct element_window));
    ring_write(ring, window, sizeof (struct element_window));

}

void print_removefill(struct ring *ring, struct event_header *header, struct element_fill *fill)
{

    element_set(&fill->element, header->destination, ELEMENT_DAMAGE_REMOVE, sizeof (struct element_fill));
    ring_write(ring, fill, sizeof (struct element_fill));

}

void print_removemouse(struct ring *ring, struct event_header *header, struct element_mouse *mouse)
{

    element_set(&mouse->element, header->destination, ELEMENT_DAMAGE_REMOVE, sizeof (struct element_mouse));
    ring_write(ring, mouse, sizeof (struct element_mouse));

}

void print_removepanel(struct ring *ring, struct event_header *header, struct element_panel *panel)
{

    element_set(&panel->element, header->destination, ELEMENT_DAMAGE_REMOVE, sizeof (struct element_panel));
    ring_write(ring, panel, sizeof (struct element_panel));

}

void print_removetext(struct ring *ring, struct event_header *header, struct element_text *text)
{

    element_set(&text->element, header->destination, ELEMENT_DAMAGE_REMOVE, sizeof (struct element_text));
    ring_write(ring, text, sizeof (struct element_text));

}

void print_removewindow(struct ring *ring, struct event_header *header, struct element_window *window)
{

    element_set(&window->element, header->destination, ELEMENT_DAMAGE_REMOVE, sizeof (struct element_window));
    ring_write(ring, window, sizeof (struct element_window));

}

