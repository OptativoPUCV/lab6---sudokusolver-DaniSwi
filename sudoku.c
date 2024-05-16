#include "list.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct {
  int sudo[9][9];
} Node;

Node *createNode() {
  Node *n = (Node *)malloc(sizeof(Node));
  return n;
}

Node *copy(Node *n) {
  Node *new = (Node *)malloc(sizeof(Node));
  *new = *n;
  return new;
}

Node *read_file(char *file_name) {
  Node *n = createNode();
  FILE *file = fopen(file_name, "r");
  int i, j;
  for (i = 0; i < 9; i++) {
    for (j = 0; j < 9; j++) {
      if (!fscanf(file, "%d", &n->sudo[i][j]))
        printf("failed to read data!");
    }
  }

  fclose(file);
  return n;
}

void print_node(Node *n) {
  int i, j;
  for (i = 0; i < 9; i++) {
    for (j = 0; j < 9; j++)
      printf("%d ", n->sudo[i][j]);
    printf("\n");
  }
  printf("\n");
}

int is_valid(Node *n) {
  int i, j;
  for (i = 0; i < 9; ++i) {
    for (j = 0; j < 9; ++j) {
      if (n->sudo[i][j] == 0)
        continue;
      for (int k = 0; k < 9; ++k) {
        if (k != j && n->sudo[i][k] == n->sudo[i][j]) {
          return 0;
        }
      }
    }
  }
  return 1;
}

List *get_adj_nodes(Node *n) {
  if(n == NULL)
    return NULL;
  List *list = createList();
  int i, j;
  for (i = 0; i < 9; ++i) {
    for (j = 0; j < 9; ++j) {
      if (n->sudo[i][j] == 0) {
        int k;
        for (k = 1; k <= 9; ++k) {
          Node *new = copy(n);
          new->sudo[i][j] = k;
          pushBack(list, new);
          if(is_valid(new) == 0)
            popBack(list);
        }
      }
    }
  }
  return list;
}

int is_final(Node *n) {
  int i, j;
  for (i = 0; i < 9; ++i){
    for(j = 0; j < 9; ++j){
      if(n->sudo[i][j] == 0)
        return 0;
    }
  }
  return 1;
}

Node *DFS(Node *initial, int *cont) {
  Stack *S = createStack();
  push(S, initial);
  while (get_size(S) != 0){
    Node *n = pop(S);
    pop(S);
    if(is_final(n))
      return n;
    List *adj = get_adj_nodes(n);
    Node *aux = first(adj);
    while(aux != NULL) {
      push(S, aux);
      aux = next(adj);
    }
    free(n);
    (*cont)++;
  }
  return NULL;
}

/*
int main( int argc, char *argv[] ){

  Node* initial= read_file("s12a.txt");;

  int cont=0;
  Node* final = DFS(initial, &cont);
  printf("iterations:%d\n",cont);
  print_node(final);

  return 0;
}*/