#include "draw.h"
#include <stdio.h>
#include "graphics.h"
#include <string>
#include <cstring>
#include <iostream>

void drawInitCircuit() {
    init_graphics("Clustering -- Ethan Pan");
    clearscreen();
    update_message("Clustering");
    init_world (0.,0.,2500.,2500.);

    flushinput();
}


void drawCell(int cellId, int x, int y) {
    setcolor(LIGHTGREY);
    fillrect ((x+2)*50.,y*50.,(x+3)*50.,(y+1)*50.);

    std::string str = to_string(cellId);
    char *cstr = new char[str.length() + 1];
    strcpy(cstr, str.c_str());
    setcolor(BLACK);
    setfontsize(24);
    drawtext((x+2)*50.,y*50.,cstr,150.);
    delete [] cstr;
    flushinput();
}


void drawAssignment(const vector<vector<Cell>>& assignment) {
    clearscreen();
    int x = 0;
    int y = 2;
    int count = 0;
    for (const auto& cell : assignment[0]) {
        count++;
        if(count>20) {x += 2; count = 0; y = 2;}
        drawCell(cell.cellId, x , y);
        y += 2;
    }
    x = 15;
    y = 2;
    count = 0;
    for (const auto& cell : assignment[1]) {
        count++;
        if(count>20) {x += 2; count = 0; y = 2;}
        drawCell(cell.cellId, x , y);
        y += 2;
    }
}