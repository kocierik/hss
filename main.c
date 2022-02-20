#include<ncurses.h>
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
struct machine{
  char *name;
  struct machine *next;
};

int addNodeBottom(char *name, struct machine *head){
    struct machine *newNode = (struct machine*)malloc(sizeof(struct machine));
    newNode->name = (char *) malloc(100);
    strcpy(newNode->name,name);
    newNode->next = NULL; 

    if(head->next == NULL) head->next = newNode;
    else{
      struct machine *current = head;
      while (current->next != NULL) current = current->next;
      current->next = newNode;
    }
    return 0;
}




int main() {
  WINDOW *w;
  
  struct passwd *pw = getpwuid(getuid());
  char *homedir = pw->pw_dir;
  char *line = NULL;
  // bool checkSpace = false;
  strcat(homedir,"/.ssh/known_hosts.old");
  FILE *file = fopen(homedir,"r"); 


  
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

  ssize_t read;
  size_t len = 0;
  char *text = NULL;
  char *text2 = NULL;
  
  struct machine* headList = (struct machine*)malloc(sizeof(struct machine));
  headList->next = NULL;

  

  while ((read = getline(&line, &len, file)) != -1) {
    text = strtok(line,",");
    text2 = strtok(line," ");
    // printf("%s\n",text);
    addNodeBottom(text,headList);
  }
  while (headList != NULL){
    printf("%s\n",headList->name);
    headList = headList->next;
  }

    fclose(file);
}
