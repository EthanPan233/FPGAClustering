# pragma once
#include "Circuit.h"
#include<unistd.h>
#include "graphics.h"


static void delay (void);
static void button_press (float x, float y);
static void drawscreen (void);
extern std::string mode;

void drawInitCircuit();


static void delay (void) {

 unsigned int microsecond = 1000000;
/* A simple delay routine for animation. */
 usleep(0.05 * microsecond);//sleeps for 1 second
}

static void button_press (float x, float y) {

/* Called whenever event_loop gets a button press in the graphics *
 * area.  Allows the user to do whatever he/she wants with button *
 * clicks.                                                        */

//  printf("User clicked a button at coordinates (%f, %f)\n", x, y);
}

void drawCell(int cellId, int x, int y);

void drawAssignment(const vector<vector<Cell>>& assignment);