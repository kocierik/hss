#include<ncurses.h>
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>
#include <stdio.h>
#include <string.h>

int main() {
  WINDOW *w;
  
  struct passwd *pw = getpwuid(getuid());
  char *homedir = pw->pw_dir;
  char c;
  strcat(homedir,"/.ssh/known_hosts");
  FILE *file = fopen(homedir,"r"); 

  do {
    c = fgetc(file);
    printf("%c", c);
  } while (c != EOF);
 
    fclose(file);
  
  char list[5][7] = { "One", "Two", "Three", "Four", "Five" };
  char item[8];
  int ch, i = 0;
  initscr(); 
  w = newwin(10, 30, 1, 1); 
  box(w, 0, 0); 
  
  for( i=0; i<5; i++ ) {
    if( i == 0 ) 
    wattron( w, A_STANDOUT ); // highlights the first item.
    else
      wattroff( w, A_STANDOUT );
    sprintf(item, "%-7s",  list[i]);
    mvwprintw( w, i+1, 2, "%s", item );
    }
  
  wrefresh(w);
  i = 0;
  noecho(); 
  keypad(w, TRUE); 
  curs_set( 0 ); 

  while(( ch = wgetch(w)) != 'q'){ 
    // right pad with spaces to make the items appear with even width.
    sprintf(item, "%-7s",  list[i]); 
    mvwprintw( w, i+1, 2, "%s", item ); 

    switch( ch ) {
      case KEY_UP:
        i--;
        i = ( i<0 ) ? 4 : i;
        break;
      case KEY_DOWN:
        i++;
        i = ( i>4 ) ? 0 : i;
        break;
    }
    wattron( w, A_STANDOUT );
    sprintf(item, "%-7s",  list[i]);
    mvwprintw( w, i+1, 2, "%s", item);
    wattroff( w, A_STANDOUT );
  }
  delwin(w);
  endwin();
}
