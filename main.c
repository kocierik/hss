#include<ncurses.h>
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAXLEN 50
struct machine{
  int len;
  char *name;
  struct machine *next;
  struct machine *prev;
};

int addNodeBottom(char *name, struct machine *head){
    struct machine *newNode = (struct machine*)malloc(sizeof(struct machine));
    newNode->name = (char *) malloc(100);
    strcpy(newNode->name,name);
    newNode->next = NULL; 

    if(head->next == NULL){
       head->next = newNode;
       head->prev = NULL;
    }
    else{
      struct machine *current = head;
      while (current->next != NULL) current = current->next;
      current->next = newNode;
      newNode->prev = current;
    }
    return 0;
}


int listLen(struct machine *list){
  int i = 0;
  while (list != NULL){
    i++;
    list = list->next;
  }
  return i;
}

int maxTextLength(struct machine *list){
  int i = 0, max = 0;
  while (list != NULL){  
    while (list->name[i] != '\0'){
      i++;
    }
    if(i>max) max = i;
    i = 0;
    list = list->next;
  }
  return max;
}

struct machine* parseFile(){
  struct passwd *pw = getpwuid(getuid());
  char *homedir = pw->pw_dir;
  strcat(homedir,"/.ssh/known_hosts.old");
  FILE *file = fopen(homedir,"r"); 

  ssize_t read;
  char *line = NULL;
  size_t len = 0;
  char *text = NULL;  
  struct machine* headList = (struct machine*)malloc(sizeof(struct machine));
  headList->next = NULL;

  while ((read = getline(&line, &len, file)) != -1) {
    text = strtok(line,","); 
    strtok(line," ");
    addNodeBottom(text,headList);
  }
  fclose(file);
  return headList;
}


int main() {
  WINDOW *w;
  struct machine *temp = parseFile();
  struct machine *headList = temp;
  headList = headList->next;
  free(temp);
  int lenHostname = listLen(headList);
  struct machine *movePt = headList;
  int maxLen = maxTextLength(movePt);



  int ch, i = 0;
  initscr(); 
  w = newwin(lenHostname+2, maxLen+5, 1, 1); 
  box(w, 0, 0); 
  
  for( i=0; i<lenHostname; i++ ) {
    if( i == 0 ) 
    wattron( w, A_STANDOUT ); // highlights the first item.
    else
      wattroff( w, A_STANDOUT );
    mvwprintw( w, i+1, 2, "%s", movePt->name );
    movePt = movePt->next;
    }
  
  wrefresh(w);
  i = 0;
  noecho(); 
  keypad(w, TRUE); 
  curs_set( 0 ); 
  movePt = headList;
  while(( ch = wgetch(w)) != 'q'){ 
    // right pad with spaces to make the items appear with even width.
    mvwprintw( w, i+1, 2, "%s", movePt->name ); 

    switch( ch ) {
      case KEY_UP:
        if(i>0){
            i--;
            movePt = movePt->prev;
            break;
          }
      case KEY_DOWN:
        if(i<lenHostname-1){
          i++;
          movePt = movePt->next;
          break;
        }
    }
    wattron( w, A_STANDOUT );
    mvwprintw( w, i+1, 2, "%s", movePt->name);
    wattroff( w, A_STANDOUT );
  }
  delwin(w);
  endwin();
  return 0;
}
