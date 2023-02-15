#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LIST_END -1
#define LIST_BUF 64

typedef struct
{
    int size;
    long capacity;
    int *ptr;
} ListInt;

typedef struct
{
    int size;
    long capacity;
    double *ptr;
} ListDouble;

int initListInt(ListInt *_list);
int freeListInt(ListInt *_list);
int getListInt(ListInt *_list, int _idx);
int addListInt(ListInt *_list, int _element, int _idx);
int removeListInt(ListInt *_list, int _idx);

int initListDouble(ListDouble *_list);
int freeListDouble(ListDouble *_list);
double getListDouble(ListDouble *_list, int _idx);
int addListDouble(ListDouble *_list, double _element, int _idx);
int removeListDouble(ListDouble *_list, int _idx);