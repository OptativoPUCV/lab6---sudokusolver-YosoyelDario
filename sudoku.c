#include <stdio.h>
#include <stdlib.h>
#include "list.h"


typedef struct{
   int sudo[9][9];
}Node;

Node* createNode(){
  Node* n=(Node*) malloc(sizeof(Node));
  return n;
}

Node* copy(Node* n){
    Node* new=(Node*) malloc(sizeof(Node));
    *new = *n;
    return new;
}

Node* read_file (char* file_name){
  Node* n = createNode();
  FILE* file = fopen (file_name, "r");
  int i,j;
  for(i=0;i<9;i++){
       for(j=0;j<9;j++){
          if(!fscanf (file, "%d", &n->sudo[i][j]))
            printf("failed to read data!");
       }
  }

  fclose (file);
  return n;
}

void print_node(Node* n){
    int i,j;
    for(i=0;i<9;i++){
       for(j=0;j<9;j++)
          printf("%d ", n->sudo[i][j]);
       printf("\n");
    }
    printf("\n");
}

/*
Cree la función int is_valid(Node * n), para validar si un estado/nodo es válido (cumple con las restricciones del problema). Debe validar que:

No se repitan números en las filas
No se repitan números en las columnas
No se repitan números en las submatrices de 3x3

Si el estado es válido la función retorna 1, si no lo es retorna 0.

Para marcar los números que vayan apareciendo en una fila/columna/submatriz puede usar un arreglo de enteros de largo 10 inicializado con 0s. Cada vez que aparezca un número i, verifique que la casilla i del arreglo sea igual a 0, luego márquela con un '1'. Si la casilla es '1' quiere decir que el número ya estaba marcado por lo que la fla/columna/submatriz no es válida.
*/
int is_valid(Node* n)
{
  //verificar filas primero
  for(int i = 0; i < 9; i++)
  {
    int arrF[10] = {0}; //inicializar arreglo con ceros
    for(int j = 0; j < 9; j++)
    {
      int num = n->sudo[i][j];
      if (num != 0)
      {
        if(arrF[num] == 0)
        {
          arrF[num] = 1;
        }
        else{
          return 0;
        }
      }
    }
  }
  //verificar columnas 
  for(int i = 0; i < 9; i++)
  {
    int arrC[10] = {0}; //inicializar arreglo con ceros
    for(int j = 0; j < 9; j++)
    {
      int num = n->sudo[i][j];
      if (num != 0)
      {
        if(arrC[num] == 0)
        {
          arrC[num] = 1;
        }
        else{
          return 0;
        }
      }
    }
  }

  //Verificar sub-matrices de 3x3
  for(int k = 0; k < 9; k++)
  {
    int arrSub[10] = {0};
    for(int l = 0; l < 9; l++)
    {
      /*
      En un Sudoku, el tablero de 9x9 se divide en nueve submatrices de 3x3.
      Cada submatriz tiene índices diferentes en la matriz principal de 9x9.
      
      En base a la siguiente formula se puede Iterar a través de cada celda dentro de la submatriz de 3x3 correspondiente
      */
      int i = 3 *(k/3) + (l/3);
      int j = 3 *(k%3) + (l%3);
      
      int num = n->sudo[i][j];
      if (num != 0)
      {
        if(arrSub[num] == 0)
        {
          arrSub[num] = 1;
        }
        else{
          return 0;
        }
      }
    }
  }
  //Si no se encuentran duplicados el nodo es valido.
  return 1;
}

/*
.Cree una función que a partir de un nodo genere una lista con los nodos adyacentes. Obtenga los nodos adyacentes a n y agréguelos a la lista
Recuerde que los nodos adyacentes son generados aplicando las acciones al estado actual.
Para el caso del ejemplo, la función debería retornar una lista con 9 nodos. 
Cada uno de ellos idéntico al nodo original pero cambiando el valor de la primera casilla vacía, es decir: sudo[0][2], por 1, 2, ..., 9.
Utilice la función Node* copy(Node* n) para copiar nodos.
*/
List* get_adj_nodes(Node* n)
{
  List* list = createList();
  for(int i = 0; i < 9; i++)
  {
    for(int j = 0; j < 9; j++)
    {
      if (n->sudo[i][j] == 0)
      {
        for(int num = 1; num <= 9; num++)
          {
            Node* newNode = copy(n);
            newNode->sudo[i][j] = num;
            pushBack(list, newNode);
          }
        return list;
      }
    }
  } 
  return list;
}


int is_final(Node* n){
    return 0;
}

Node* DFS(Node* initial, int* cont){
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