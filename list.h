#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sysexits.h>

#define LIST_BUF 64
#define ACS_SORT 0
#define DECS_SORT 1

typedef struct
{
    long size;
    long capacity;
    int *ptr;
} ListInt;

typedef struct
{
    long size;
    long capacity;
    double *ptr;
} ListDouble;

void init_ListInt(ListInt *_list);
void asList_ListInt(ListInt *_list, const int *_array, long _size);
void free_ListInt(ListInt *_list);
void copy_ListInt(ListInt *_list_dst, const ListInt *_list_src);
int get_ListInt(ListInt *_list, long _idx);
void set_ListInt(ListInt *_list, int _element, long _idx);
void add_ListInt(ListInt *_list, int _element, long _idx);
void remove_ListInt(ListInt *_list, long _idx);
void push_ListInt(ListInt *_list, int _element);
int peek_ListInt(ListInt *_list);
int pop_ListInt(ListInt *_list);
void qsort_ListInt(ListInt *_list, long _left, long _right, int SORT_OPTION);
void toArray_ListInt(int *_array, const ListInt *_list);
void show_ListInt(ListInt *_list);

void init_ListDouble(ListDouble *_list);
void asList_ListDouble(ListDouble *_list, const double *_array, long _size);
void free_ListDouble(ListDouble *_list);
void copy_ListDouble(ListDouble *_list_dst, const ListDouble *_list_src);
double get_ListDouble(ListDouble *_list, long _idx);
void set_ListDouble(ListDouble *_list, double _element, long _idx);
void add_ListDouble(ListDouble *_list, double _element, long _idx);
void remove_ListDouble(ListDouble *_list, long _idx);
void push_ListDouble(ListDouble *_list, double _element);
double peek_ListDouble(ListDouble *_list);
double pop_ListDouble(ListDouble *_list);
void qsort_ListDouble(ListDouble *_list, long _left, long _right, int SORT_OPTION);
void toArray_ListDouble(double *_array, const ListDouble *_list);
void show_ListDouble(ListDouble *_list);