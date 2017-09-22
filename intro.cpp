#include <ncurses.h>
#include<iostream>
#include <string>
#include "git/util.h"
#include "util/logger.h"
#include "util/system.h"
#include <menu.h>
using namespace std;


void initialize_application();
void finalize_application();
void initialize_variables();
void draw_screen();
void initialize_screen();
void start_application();
void setBranches(vector <string>);
ITEM** getMenuItemsFromVector(vector<string>);
WINDOW *create_newwin(int height, int width, int starty, int startx);
WINDOW * statusWin;
WINDOW * branchWin;
WINDOW * branchWinDer;
WINDOW * searchWin;
MENU * branchMenu;

int main (){

    initialize_application();
    vector<string> branches = getAllBranches();
    
	start_application();

    // Cleanup!
    finalize_application();
    return 0;
}

void start_application(){
    vector<string> branches ;
    branches.push_back("asdf");
    branches.push_back("hasdfsdf");
    branches.push_back("lartsdf");
    branches.push_back("gayujtsdf");
    branches.push_back("weqasdf");
    branches.push_back("weqasdf");
    branches.push_back("weqasdf");
    branches.push_back("weqasdf");
    branches.push_back("weqasdf");
    branches.push_back("weqasdf");
    branches.push_back("weqasdf");
    branches.push_back("weqasdf");
    branches.push_back("weqasdf");
    branches.push_back("weqasdf");
    branches.push_back("weqasdf");
    branches.push_back("weqasdf");
    branches.push_back("weqasdf");
    branches.push_back("weqasdf");
    branches.push_back("weqasdf");
    branches.push_back("weqasdf");
    branches.push_back("weqasdf");
    branches.push_back("weqasdf");
    branches.push_back("weqasdf");
    branches.push_back("weqasdf");
    branches.push_back("weqasdf");
    branches.push_back("weqasdf");
    branches.push_back("weqasdf");
    branches.push_back("weqasdf");
    branches.push_back("weqasdf");
    branches.push_back("weqasdf");
    branches.push_back("weqasdf");
    branches.push_back("weqasdf");
    branches.push_back("weqasdf");
    branches.push_back("weqasdf");
    branches.push_back("weqasdf");
    branches.push_back("weqasdf");
    branches.push_back("weqasdf");
    branches.push_back("weqasdf");
    branches.push_back("weqasdf");
    branches.push_back("weqasdf");
    branches.push_back("weqasdf");
    branches.push_back("weqasdf");
    branches.push_back("weqasdf");
    branches.push_back("weqasdf");
    branches.push_back("weqasdf");
    branches.push_back("weqasdf");
    branches.push_back("weqasdf");
    branches.push_back("weqasdf");
    branches.push_back("weqasdf");
    branches.push_back("weqasdf");
    branches.push_back("weqasdf");
    branches.push_back("weqasdf");
    branches.push_back("weqasdf");
    branches.push_back("weqasdf");
    branches.push_back("weqasdf");
    branches.push_back("weqasdf");
    branches.push_back("weqasdf");
    branches.push_back("weqasdf");
    branches.push_back("weqasdf");
    branches.push_back("weqasdf");
    setBranches(branches);
	getch();
int c;
	while((c = getch()) != KEY_F(1))

	{
Logger::instance()->log("You have pressed:" );
Logger::instance()->log((c));

       switch(c)
	        {	case KEY_DOWN:
				menu_driver(branchMenu, REQ_DOWN_ITEM);
				break;
			case KEY_UP:
				menu_driver(branchMenu, REQ_UP_ITEM);
				break;
		}
                wrefresh(branchWin);
	}	


}

void setBranches(vector <string> branches){
	//setMenuInWindow();
     ITEM** menuItems = getMenuItemsFromVector(branches);
     MENU * my_menu = new_menu((ITEM **)menuItems);
branchMenu = my_menu;
        set_menu_win(my_menu, branchWin);
    //set_menu_format(my_menu, 10, 1);
            set_menu_mark(my_menu, std::itoa(addch(ACS_PI)));

                WINDOW* my_menu_win = branchWin;
//                    set_menu_sub(my_menu, derwin(my_menu_win, 5, 5, 1, 1));
                    set_menu_sub(my_menu, branchWinDer);
//        mvwaddch(my_menu_win, 2, 0, ACS_LTEE);
//                mvwhline(my_menu_win, 2, 1, ACS_HLINE, 38);
//                    mvwaddch(my_menu_win, 2, 39, ACS_RTEE);
                        //box(branchWin, 0, 0);

            post_menu(my_menu);
        refresh();
wrefresh(branchWin); 
}

ITEM** getMenuItemsFromVector(vector<string> menuItems){
    ITEM **my_items;
    int n_choices = menuItems.size();
    my_items = (ITEM **)calloc(n_choices + 1, sizeof(ITEM *));
     
    for(int i = 0; i < n_choices; ++i)
	{/*const char * branch = menuItems[i].c_str();*/
        
        char* ca = new char[menuItems[i].size()+1];
        std::copy(menuItems[i].begin(), menuItems[i].end(), ca);
ca[menuItems[i].size()] = '\0';
        my_items[i] = new_item(ca, "");
		/* Set the user pointer */
//		set_item_userptr(my_items[i], func);
	}	
    my_items[n_choices] = (ITEM *)NULL;
    return my_items;
}
void initialize_application(){
	Logger::instance()->enableLogs();
    Logger::instance()->log("\n\n\n========Application starting!!!========");
    Logger::instance()->log(GetStdoutFromCommand("date"));
    Logger::instance()->log(GetStdoutFromCommand("git status"));

    initialize_screen();
    initialize_variables();
    draw_screen();
    keypad(stdscr, TRUE);
    refresh();

}

void initialize_screen(){
    initscr();
    noecho();
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
    getmaxyx(stdscr,maxr,maxc);

    /* Dimentions remaining constant across windows */
    int startC = 3;
    int width = maxc-6;
    /* Initialize input window */
    int inputH = 3; 
    int inputR = maxr-3;
    searchWin = create_newwin(inputH, width, inputR, startC);
    /* Initialize branch window */
    int branchH = (maxr-6)/2;
    int branchR = maxr - 3 - branchH;
    branchWin = create_newwin(branchH,width,branchR,startC);
    branchWinDer = derwin(branchWin,branchH-2,width-2,1,1);
    /* Initialize git status window */
    int statusR = 1;
    int statusH = maxr - inputH - branchH -1;
    statusWin = create_newwin(statusH,width,statusR,startC);
}

WINDOW *create_newwin(int height, int width, int starty, int startx)
{       
    Logger::instance()->log("Creating window of height" + to_string(height) + 
            ", width: " + to_string(width) +
            " at (x:" + to_string(startx) + 
            ", y:" + to_string(starty) + ")");
    refresh();
    WINDOW *local_win;

    local_win = newwin(height, width, starty, startx);
    box(local_win, 0 , 0);          /* 0, 0 gives default characters 
                                     * for the vertical and horizontal
                                     * lines                        */
    wrefresh(local_win);            /* Show that box                */

    return local_win;
}

