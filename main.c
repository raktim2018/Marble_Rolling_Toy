#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include "dfa.h"

#define LANG_MAX_LENGTH 1000

void readFile(char * filename);

int main(int argc, char ** argv){
  int i;
  int now;
  int len;

  char str[LANG_MAX_LENGTH+1];

  initDFA();
  if (argc>1) readFile(argv[1]);
  else readFile("description.dat");

  printf("Write an input string, maximum %d characters:\n", LANG_MAX_LENGTH);
  fgets(str, LANG_MAX_LENGTH+1, stdin);
  len = strlen(str);

  now = startState;

  printf("->%s\n", idElement[startState]);

  for(i = 0; i < len-1; i++){
    now = next(now,str[i]);
    printf("Getting input '%c', now in state %s\n", str[i], idElement[now]);
  }

  if (isFinal[now]){
    printf("Ended at Final State,that is %s. String received\n", idElement[now]);
  }
  else{
    printf("Ended not in Final State,that is %s. String rejected\n", idElement[now]);
  }
}

void readFile(char * filename){
  FILE *f;
  int n,i,j;
  char *inp = malloc(MAX_LENGTH+5);

  f = fopen(filename, "r");
  assert(f!=NULL);

  /*(Number of states)*/
  fscanf(f, "%d", &n);
  assert(n <= MAX_ELEMENT);
  nElement = n;

  /*(List of states, separated by a space)*/
  for(i=0;i<nElement;i++){
    fscanf(f,"%s", inp);

    for(j=0;j<i;j++){
      assert(strcmp(inp,idElement[j])!=0);
    }

    setIdElement(i,inp);
  }

  /*(List of symbols, not spaces separated)*/
  fscanf(f, "%s", inp);
  assert(strlen(inp)<=MAX_SYMBOL);
  nSymbol = strlen(inp);

  for(i = 0; i < nSymbol; i++){
    for(j = 0; j < i; j++){
      assert(inp[i]!=inp[j]);
    }

    setIdSymbol(i, inp[i]);
  }

  /*(Initial state)*/
  fscanf(f, "%s", inp);
  startState = getIdElement(inp);

  /*(Final state amount)*/
  fscanf(f, "%d", &n);
  assert(n <= nElement);
  nFinal = n;

  /*(Final state list, separated by space)*/
  for(i=0;i<nFinal;i++){
    fscanf(f, "%s", inp);

    j = getIdElement(inp);
    assert(!(isFinal[j]));
    isFinal[j] = true;
  }

  /*(Table-shaped transition function)*/
  for(i=0;i<nElement;i++){
    for(j=0;j<nSymbol;j++){
      fscanf(f,"%s",inp);
      toWhere[i][j] = getIdElement(inp);
    }
  }
}
