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
      ej: int k=4,p; 
for(p=0;p<9;p++){
    int i=3*(k/3) + (p/3) ;
    int j=3*(k%3) + (p%3) ;
    printf("%d ",nodo->sudo[i][j]);
    if(p%3 == 2) printf("\n");
}
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
1.Cree una función que a partir de un nodo genere una lista con los nodos adyacentes. Obtenga los nodos adyacentes a n y agréguelos a la lista
Recuerde que los nodos adyacentes son generados aplicando las acciones al estado actual.
Para el caso del ejemplo, la función debería retornar una lista con 9 nodos. 
Cada uno de ellos idéntico al nodo original pero cambiando el valor de la primera casilla vacía, es decir: sudo[0][2], por 1, 2, ..., 9.
Utilice la función Node* copy(Node* n) para copiar nodos.

3.Modifique la función get_adj_nodes para que sólo los nodos válidos sean retornados (use la función is_valid).
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
          if(is_valid(newNode))
          {
            pushBack(list, newNode);
          } 
        }
        return list;
      }
    }
  } 
  return list;
}

/*
Implemente la función int is_final(Node * n). Esta función retorna 1 si el nodo corresponde a un nodo final (es decir, todos los valores de la matriz son distintos a 0) y 0 en caso contrario.

*/
int is_final(Node* n)
{
  for(int i = 0; i < 9; i++){
    for(int j = 0; j < 9; j++){
      if(n->sudo[i][j] == 0)
      {
        return 0; // existe al menos una celda vacia, el nodo no es final
      }
    }
  }
  return 1; //Si todas las celdas estan llenas, es un nodo final
}

/*
Implemente la función Node* DFS(Node* n, int* cont). Esta función realiza una búsqueda en profundidad a partir del nodo n. El algoritmo es el siguiente:

Cree un stack S (pila) e inserte el nodo.

Mientras el stack S no se encuentre vacío:

a) Saque y elimine el primer nodo de S.

b) Verifique si corresponde a un estado final, si es así retorne el nodo.

c) Obtenga la lista de nodos adyacentes al nodo.

d) Agregue los nodos de la lista (uno por uno) al stack S.

e) Libere la memoria usada por el nodo.

Si terminó de recorre el grafo sin encontrar una solución, retorne NULL.

Almacene en la variable cont, la cantidad de iteraciones que realiza el algoritmo.
*/
Node* DFS(Node* initial, int* cont)
{
  Stack* pila = createStack(); //Crear pila
  push(pila, initial); // insertar el nodo inicial en la pila
  //*cont = 0; // contador de iteraciones

  while(is_empty(pila) == 0)
  {
    Node* aux = top(pila); //se obtiene el primero nodo de la pila
    pop(pila);// se elimina el nodo

    // verificar si el nodo actual es estado final
    if(is_final(aux))
    {
      return aux;
    }

    List* nodosAdyacentes = get_adj_nodes(aux);
    Node* nodoAdy = first(nodosAdyacentes);
    while(nodoAdy != NULL)
    {
      push(pila, nodoAdy);
      nodoAdy = next(nodosAdyacentes);
    }
    //clean(nodosAdyacentes);
    (*cont)++; 
    free(aux);
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