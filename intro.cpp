#include <ncurses.h>
#include<iostream>
#include <string>
#include "git/util.h"
#include "util/logger.h"
#include "util/system.h"
#include <menu.h>
using namespace std;

// Function definitions
void initialize_application();
void finalize_application();
void initialize_variables();
void draw_screen();
void initialize_screen();
void start_application();
void setBranches(vector <string>);
void remove_search_char();
void set_git_status();
void add_search_char(char c);
void perform_action_on_key(int);
void setStatus();
ITEM** getMenuItemsFromVector(vector<string>);
WINDOW *create_newwin(int height, int width, int starty, int startx);
vector<string> filterVector(vector<string>, string);

// Global variable
WINDOW * statusWin;
WINDOW * branchWin;
WINDOW * branchWinDer;
WINDOW * searchWin;
MENU * branchMenu;
string searchStr;

int main (){

    initialize_application();
    
    start_application();

    // Cleanup!
    finalize_application();
    return 0;
}

void updateBranches(){
       vector<string> branches = GitHelper::getInstance()->getAllBranches();
       vector<string> recentBranches = GitHelper::getInstance()->getRecentBranches();
   
       vector<string> filteredBranches (filterVector(branches,searchStr));
       vector<string> filteredRecentBranches(filterVector(recentBranches,searchStr));
   
       vector <string> displayBranches ;
       displayBranches.insert(displayBranches.end(), filteredRecentBranches.begin(), filteredRecentBranches.end());
       displayBranches.insert(displayBranches.end(), filteredBranches.begin(), filteredBranches.end());
   
       setBranches(displayBranches);
}

void start_application(){
    updateBranches();
    setStatus();
    int c;
    while((c = getch())) {
        perform_action_on_key(c);
    }

}

vector<string> filterVector(vector<string> branches, string searchStr){
    vector<string> filteredVector;
    for(string &br : branches) {
        int searchPos = br.find(searchStr);
        if(searchPos >= 0){
			Logger::instance()->log("Filtering entry: " + br + " for search str " + searchStr);
			Logger::instance()->log(searchPos);
            filteredVector.push_back(br);
        }
    }
    return *(new vector<string>(filteredVector));

}

void setStatus(){
    int i = 0;
    for(string &line : GitHelper::getInstance()->getCurrentStatus()){
        mvwprintw(statusWin,++i,2,line.c_str());
    }
    wrefresh(statusWin);
}

void perform_action_on_key(int c){
            Logger::instance()->log("You have pressed:" );
         Logger::instance()->log(c);
 
         switch(c) {
             case KEY_DOWN:
                 menu_driver(branchMenu, REQ_DOWN_ITEM);
                 break;
             case KEY_UP:
                 menu_driver(branchMenu, REQ_UP_ITEM);
                 break;
             case KEY_BACKSPACE:
                 remove_search_char();
                 break;
             default:
                 add_search_char(c);
         }
         wrefresh(branchWin);
         wrefresh(statusWin);
         wrefresh(searchWin);
 
}

void add_search_char(char c) {
    Logger::instance()->log("Adding cxhAR");
    Logger::instance()->log(c);
    searchStr+=c;
    mvwaddch(searchWin,1,2+searchStr.length(),c);
    updateBranches();
}

void remove_search_char(){
    mvwaddch(searchWin,1,2+searchStr.length(),' ');
    searchStr = searchStr.substr(0, searchStr.size()-1);
    wmove(searchWin,1,2+searchStr.length()+1);
    updateBranches();
}

void setBranches(vector <string> branches){
unpost_menu(branchMenu);
    //setMenuInWindow();
    ITEM** menuItems = getMenuItemsFromVector(branches);
    MENU * my_menu = new_menu((ITEM **)menuItems);
    branchMenu = my_menu;
    set_menu_win(my_menu, branchWin);
    //set_menu_format(my_menu, 10, 1);
    set_menu_mark(my_menu, " * ");
    set_menu_sub(my_menu, branchWinDer);
    post_menu(my_menu);
    refresh();
    wrefresh(branchWin); 
}

ITEM** getMenuItemsFromVector(vector<string> menuItems){
    ITEM **my_items;
    int n_choices = menuItems.size();
    my_items = (ITEM **)calloc(n_choices + 1, sizeof(ITEM *));
     
    for(int i = 0; i < n_choices; ++i){
        Logger::instance()->log("Adding into menu item:");
        Logger::instance()->log(menuItems[i]);
        char* ca = new char[menuItems[i].size()+1];
        std::copy(menuItems[i].begin(), menuItems[i].end(), ca);
        ca[menuItems[i].size()] = '\0';
        my_items[i] = new_item(ca, "");
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

