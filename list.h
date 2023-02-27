#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sysexits.h>

#define LIST_BUF_SIZE 4
#define ACS_SORT  0
#define DECS_SORT 1
#define LINE_SPLIT_TRUE  1
#define LINE_SPLIT_FALSE 0

typedef struct
{
    bool is_string;
    unsigned long size;
    unsigned long data_size;
    unsigned long capacity;
    unsigned long allocated;
    void *base_addr;
} List;

void init_List(List *_list, const int _data_size, const bool _is_string);
void asList_List(List *_list, const void *_array, const long _size, const long _data_size, const int _is_string);
void free_List(List *_list);
void copy_List(List *_list_dst, const List *_list_src);
void *get_List(const List *_list, const long _idx);
void set_List(List *_list, const void *_element, const long _idx);
void add_List(List *_list, const void *_elements, const long _idx);
void remove_List(List *_list, const long _idx);
void push_List(List *_list, const void *_elements);
void *peek_List(const List *_list);
void *pop_List(List *_list);
void qsort_List(List *_list, const long _left, const long _right, int (*compare)(const void*, const void*));
long indexOf_List(const List *_list, const void * _elements, int (*_compare)(const void *, const void *));
void inputFile_List(List *_list, const char *_file_name, const char *_token, const unsigned _LINE_SPLIT);