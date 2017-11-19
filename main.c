#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node{
  struct node *next;
  char word[32];
  int count;
}Node;

Node *words;

void init(){
  words = NULL;
}

void newWord(char *s){
  Node *p = words, *q = NULL;
  while(p != NULL){
    if(strcmp(p->word, s) > 0) break;
    if(strcmp(p->word, s) == 0){
      p->count++;
      return;
    }
    q = p;
    p = p->next;
  }
  Node *new = (Node *)malloc(sizeof(Node));
  new->count = 1;
  strcpy(new->word, s);
  new->next = p;
  if(q == NULL) words = new;
  else q->next = new;
}


int main(int argc, char const *argv[]) {
  FILE *iFile = fopen(argv[1], "r");
  FILE *oFile = fopen(argv[2], "w");
  Node *p;
  char buff[32];
  init();
  while(fscanf(iFile, "%31[A-Za-z']", buff) >= 0) {
    toupper(buff[0]);
    for(int i = 1; buff[i]; i++) buff[i] = tolower(buff[i]);
    newWord(buff);
    fscanf(iFile, "%*[^A-Za-z']");
  }
  printf("%s\n", buff);
  while (words != NULL) {
    fprintf(oFile, "%3i %s\n", words->count, words->word);
    p  = words;
    words = words->next;
    free(p);
  }
  fclose(iFile);
  fclose(oFile);
  return 0;
}
