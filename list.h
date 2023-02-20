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

typedef struct
{
    long size;
    long capacity;
    char **ptr;
} ListString;

void init_ListInt(ListInt *_list);
void asList_ListInt(ListInt *_list, const int *_array, long _size);
void free_ListInt(ListInt *_list);
void copy_ListInt(ListInt *_list_dst, const ListInt *_list_src);
int get_ListInt(const ListInt *_list, long _idx);
void set_ListInt(ListInt *_list, int _element, long _idx);
long indexOf_ListInt(const ListInt *_list, int _element);
void add_ListInt(ListInt *_list, int _element, long _idx);
void remove_ListInt(ListInt *_list, long _idx);
void push_ListInt(ListInt *_list, int _element);
int peek_ListInt(const ListInt *_list);
int pop_ListInt(ListInt *_list);
void qsort_ListInt(ListInt *_list, long _left, long _right, int SORT_OPTION);
void toArray_ListInt(int *_array, const ListInt *_list);
void show_ListInt(ListInt *_list);

void init_ListDouble(ListDouble *_list);
void asList_ListDouble(ListDouble *_list, const double *_array, long _size);
void free_ListDouble(ListDouble *_list);
void copy_ListDouble(ListDouble *_list_dst, const ListDouble *_list_src);
double get_ListDouble(const ListDouble *_list, long _idx);
void set_ListDouble(ListDouble *_list, double _element, long _idx);
long indexOf_ListDouble(const ListDouble *_list, double _element);
void add_ListDouble(ListDouble *_list, double _element, long _idx);
void remove_ListDouble(ListDouble *_list, long _idx);
void push_ListDouble(ListDouble *_list, double _element);
double peek_ListDouble(const ListDouble *_list);
double pop_ListDouble(ListDouble *_list);
void qsort_ListDouble(ListDouble *_list, long _left, long _right, int SORT_OPTION);
void toArray_ListDouble(double *_array, const ListDouble *_list);
void show_ListDouble(ListDouble *_list);

void init_ListString(ListString *_list);
void asList_ListString(ListString *_list, char **_string_array, long _size);
void free_ListString(ListString *_list);
void copy_ListString(ListString *_list_dst, const ListString *_list_src);
void inputFile_ListString(ListString *_list, const char *_file_name);
char *get_ListString(const ListString *_list, long _idx);
void set_ListString(ListString *_list, char *_string, long _idx);
long indexOf_ListString(const ListString *_list, const char *_string);
void add_ListString(ListString *_list, char *_string, long _idx);
void remove_ListString(ListString *_list, long _idx);
void push_ListString(ListString *_list, char *_string);
char *peek_ListString(const ListString *_list);
char *pop_ListString(ListString *_list);
void qsort_ListString(ListString *_list, long _left, long _right, int SORT_OPTION);
void show_ListString(ListString *_list);