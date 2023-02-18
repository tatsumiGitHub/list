#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sysexits.h>

#define LIST_END -1
#define LIST_BUF 64
#define ACS_SORT 0
#define DESC_SORT 1

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

void initListInt(ListInt *_list);
void freeListInt(ListInt *_list);
int getListInt(ListInt *_list, int _idx);
void addListInt(ListInt *_list, int _element, int _idx);
void removeListInt(ListInt *_list, int _idx);
void pushListInt(ListInt *_list, int _element);
int peekListInt(ListInt *_list);
int popListInt(ListInt *_list);
void qsortListInt(ListInt *_list, int SORT_OPTION);
void showListInt(ListInt *_list);

void initListDouble(ListDouble *_list);
void freeListDouble(ListDouble *_list);
double getListDouble(ListDouble *_list, int _idx);
void addListDouble(ListDouble *_list, double _element, int _idx);
void removeListDouble(ListDouble *_list, int _idx);
void pushListDouble(ListDouble *_list, double _element);
double popListDouble(ListDouble *_list);
void qsortListDouble(ListDouble *_list, int SORT_OPTION);
void showListDouble(ListDouble *_list);