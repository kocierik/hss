
#include<ncurses.h>
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>
#include <string.h>
#include <libssh/libssh.h>
#include <stdio.h>
#include <stdlib.h>

struct machine{
  int len;
  char *name;
  char *psw;
  struct machine *next;
  struct machine *prev;
};

int addNodeBottom(char *name, struct machine *head);
int listLen(struct machine *list);
int maxTextLength(struct machine *list);
struct machine* parsePsw(char *pswPath, struct machine *list);
struct machine* parseFile(char* homedir);
void printHost(int lenHostname, WINDOW *w, struct machine *movePt);
int main();