#include<ncurses.h>
#include "git/util.h"
using namespace std;

void initialize_application();
void finalize_application();
void initialize_variables();
void draw_screen();
void initialize_screen();
WINDOW *create_newwin(int height, int width, int starty, int startx);

int main (){
    initialize_application();
    keypad(stdscr, TRUE);
    vector<string> branches = getAllBranches();
    refresh();
    getch();

    finalize_application();
    return 0;
}

void initialize_application(){
    initialize_screen();
    initialize_variables();
    draw_screen();
}

void initialize_screen(){
    initscr();
//    noecho();
    cbreak();   
    keypad(stdscr, TRUE);
}
void finalize_application(){
    endwin();
}

void initialize_variables(){
}

void draw_screen(){
    int maxr,maxc;
    WINDOW *my_win;
    getmaxyx(stdscr,maxr,maxc);
   

    /* Dimentions remaining constant across windows */
    int startC = 3;
    int width = maxc-6;
    /* Initialize input window */
    int inputH = 3; 
    int inputR = maxr-3;
    create_newwin(inputH, width, inputR, startC);
    /* Initialize branch window */
    int branchH = (maxr-6)/2;
    int branchR = maxr - 3 - branchH;
    create_newwin(branchH,width,branchR,startC);
    /* Initialize git status window */
    int statusR = 1;
    int statusH = maxr - inputH - branchH -1;
    create_newwin(statusH,width,1,startC);
}

WINDOW *create_newwin(int height, int width, int starty, int startx)
{       
    refresh();
    WINDOW *local_win;

        local_win = newwin(height, width, starty, startx);
        box(local_win, 0 , 0);          /* 0, 0 gives default characters 
                                         * for the vertical and horizontal
                                         * lines                        */
        wrefresh(local_win);            /* Show that box                */

        return local_win;
}

