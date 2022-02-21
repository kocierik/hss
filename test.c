#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>
#include <stdio.h>
#include <string.h>
int main(){
  struct passwd *pw = getpwuid(getuid());
  const char *homedir = pw->pw_dir;
  char test[50];
  strcpy(test,homedir);
  strcat(homedir,"/.ssh/ps.old");
  FILE *file = fopen(homedir,"r"); 
  printf("%s\n",test);
  printf("%s",homedir);

  return 0;
}
