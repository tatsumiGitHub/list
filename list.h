#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sysexits.h>

#define LIST_BUF 64
#define ACS_SORT 0
#define DECS_SORT 1

typedef struct
{
    unsigned long size;
    unsigned long capacity;
    int *ptr;
} ListInt;

typedef struct
{
    unsigned long size;
    unsigned long capacity;
    double *ptr;
} ListDouble;

void initListInt(ListInt *_list);
void freeListInt(ListInt *_list);
int getListInt(ListInt *_list, unsigned long _idx);
void setListInt(ListInt *_list, int _element, unsigned long _idx);
void addListInt(ListInt *_list, int _element, unsigned long _idx);
void removeListInt(ListInt *_list, unsigned long _idx);
void pushListInt(ListInt *_list, int _element);
int peekListInt(ListInt *_list);
int popListInt(ListInt *_list);
void qsortListInt(ListInt *_list, unsigned long _left, unsigned long _right, int SORT_OPTION);
void showListInt(ListInt *_list);

void initListDouble(ListDouble *_list);
void freeListDouble(ListDouble *_list);
double getListDouble(ListDouble *_list, unsigned long _idx);
void setListDouble(ListDouble *_list, double _element, unsigned long _idx);
void addListDouble(ListDouble *_list, double _element, unsigned long _idx);
void removeListDouble(ListDouble *_list, unsigned long _idx);
void pushListDouble(ListDouble *_list, double _element);
double peekListDouble(ListDouble *_list);
double popListDouble(ListDouble *_list);
void qsortListDouble(ListDouble *_list, unsigned long _left, unsigned long _right, int SORT_OPTION);
void showListDouble(ListDouble *_list);