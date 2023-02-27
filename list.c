#include "list.h"

void init_List(List *_list, const int _data_size, const bool _is_string)
{
    if (_list == NULL)
    {
        printf("Error: Cannot invoke \"init_List(List *_list, const int _data_size, const bool _is_string)\" because \"<local1>\" is null\n");
        exit(EX_USAGE);
    }
    _list->size = 0;
    if (_is_string == true)
    {
        _list->is_string = true;
        _list->data_size = sizeof(char *);
    }
    else
    {
        _list->is_string = false;
        _list->data_size = _data_size;
    }
    _list->capacity = _list->data_size * LIST_BUF_SIZE;
    _list->allocated = 0;
    if ((_list->base_addr = (void *)malloc(_list->capacity)) == NULL)
    {
        printf("Error: unable to allocate new heap space\n");
        exit(EX_OSERR);
    }
    return;
}
void asList_List(List *_list, const void *_array, const long _size, const long _data_size, const int _is_string)
{
    if (_list == NULL)
    {
        printf("Error: Cannot invoke \"asList_List(List *_list, const void *_array, const long _size, const long _data_size, const int _is_string)\" because \"<local1>\" is null\n");
        exit(EX_USAGE);
    }
    if (_array == NULL)
    {
        printf("Error: Cannot invoke \"asList_List(List *_list, const void *_array, const long _size, const long _data_size, const int _is_string)\" because \"<local2>\" is null\n");
        exit(EX_USAGE);
    }
    _list->size = _size;
    if (_is_string == true)
    {
        _list->is_string = true;
        _list->data_size = sizeof(char *);
    }
    else
    {
        _list->is_string = false;
        _list->data_size = _data_size;
    }
    _list->capacity = (_size / LIST_BUF_SIZE + 1) * LIST_BUF_SIZE * _list->data_size;
    if (_list->is_string == true)
    {
        long i;
        char *str_tmp;
        if ((_list->base_addr = (char **)malloc(_list->capacity)) == NULL)
        {
            printf("Error: unable to allocate new heap space\n");
            exit(EX_OSERR);
        }
        for (i = 0; i < _size; i++)
        {
            str_tmp = *((char **)_array + i);
            if ((*((char **)_list->base_addr + i) = (char *)calloc((strlen(str_tmp) + 1), sizeof(char))) == NULL)
            {
                printf("Error: unable to allocate new heap space\n");
                exit(EX_OSERR);
            }
            strcpy(*((char **)_list->base_addr + i), str_tmp);
            _list->allocated += strlen(str_tmp) + 1;
        }
    }
    else
    {
        if ((_list->base_addr = (void *)malloc(_list->capacity)) == NULL)
        {
            printf("Error: unable to allocate new heap space\n");
            exit(EX_OSERR);
        }
        memcpy(_list->base_addr, _array, _size * _data_size);
        _list->allocated = _list->capacity;
    }
    return;
}
void free_List(List *_list)
{
    if (_list == NULL)
    {
        printf("Error: Cannot invoke \"free_List(List *_list)\" because \"<local1>\" is null\n");
        exit(EX_USAGE);
    }
    if (_list->is_string == true)
    {
        int i;
        for (i = 0; i < _list->size; i++)
        {
            free(*((char **)_list->base_addr + i));
        }
    }
    _list->is_string = false;
    _list->size = 0;
    _list->data_size = 0;
    _list->capacity = 0;
    _list->allocated = 0;
    free(_list->base_addr);
    _list->base_addr = NULL;
    return;
}
void copy_List(List *_list_dst, const List *_list_src)
{
    if (_list_dst == NULL)
    {
        printf("Error: Cannot invoke \"copy_List(List *_list_dst, const List *_list_src)\" because \"<local1>\" is null\n");
        exit(EX_USAGE);
    }
    if (_list_src == NULL)
    {
        printf("Error: Cannot invoke \"copy_List(List *_list_dst, const List *_list_src)\" because \"<local2>\" is null\n");
        exit(EX_USAGE);
    }
    _list_dst->is_string = _list_src->is_string;
    _list_dst->size = _list_src->size;
    _list_dst->data_size = _list_src->data_size;
    _list_dst->capacity = _list_src->capacity;
    _list_dst->allocated = _list_src->allocated;
    if ((_list_dst->base_addr = (void *)malloc(_list_dst->capacity)) == NULL)
    {
        printf("Error: unable to allocate new heap space\n");
        exit(EX_OSERR);
    }
    if (_list_dst->is_string == true)
    {
        long i;
        char *str_tmp;
        if ((_list_dst->base_addr = (char **)malloc(_list_dst->capacity)) == NULL)
        {
            printf("Error: unable to allocate new heap space\n");
            exit(EX_OSERR);
        }
        for (i = 0; i < _list_dst->size; i++)
        {
            str_tmp = *((char **)_list_src->base_addr + i);
            if ((*((char **)_list_dst->base_addr + i) = (char *)calloc((strlen(str_tmp) + 1), sizeof(char))) == NULL)
            {
                printf("Error: unable to allocate new heap space\n");
                exit(EX_OSERR);
            }
            strcpy(*((char **)_list_dst->base_addr + i), str_tmp);
        }
    }
    else
    {
        memcpy(_list_dst->base_addr, _list_src->base_addr, _list_dst->capacity);
        _list_dst->allocated = _list_src->allocated;
    }
    return;
}
void *get_List(const List *_list, const long _idx)
{
    if (_list == NULL)
    {
        printf("Error: Cannot invoke \"get_List(const List *_list, const long _idx)\" because \"<local1>\" is null\n");
        exit(EX_USAGE);
    }
    if (_idx < 0 || _list->size < _idx)
    {
        printf("Error: Index %ld out of bounds for length %ld\n", _idx, _list->size);
        exit(EX_USAGE);
    }
    void *return_ptr = NULL;
    if (_list->is_string == true)
    {
        char *str_ptr = *((char **)_list->base_addr + _idx);
        if ((return_ptr = (char *)calloc((strlen(str_ptr) + 1), sizeof(char))) == NULL)
        {
            printf("Error: unable to allocate new heap space\n");
            exit(EX_OSERR);
        }
        strcpy(return_ptr, str_ptr);
    }
    else
    {
        if ((return_ptr = calloc(_list->data_size, 0)) == NULL)
        {
            printf("Error: unable to allocate new heap space\n");
            exit(EX_OSERR);
        }
        memcpy(return_ptr, (_list->base_addr + _idx * _list->data_size), _list->data_size);
    }
    return return_ptr;
}
void set_List(List *_list, const void *_elements, const long _idx)
{
    if (_list == NULL)
    {
        printf("Error: Cannot invoke \"set_List(List *_list, const void *_elements, const long _idx)\" because \"<local1>\" is null\n");
        exit(EX_USAGE);
    }
    if (_elements == NULL)
    {
        printf("Error: Cannot invoke \"set_List(List *_list, const void *_elements, const long _idx)\" because \"<local2>\" is null\n");
        exit(EX_USAGE);
    }
    if (_idx < 0 || _list->size < _idx)
    {
        printf("Error: Index %ld out of bounds for length %ld\n", _idx, _list->size);
        exit(EX_USAGE);
    }
    void *tmp;
    if (_list->is_string == true)
    {
        _list->allocated -= strlen(*((char **)_list->base_addr + _idx));
        if ((tmp = (char *)realloc(*((char **)_list->base_addr + _idx), (strlen(_elements) + 1) * sizeof(char))) == NULL)
        {
            free(*((char **)_list->base_addr + _idx));
            printf("Error: unable to allocate new heap space\n");
            exit(EX_OSERR);
        }
        else
        {
            *((char **)_list->base_addr + _idx) = tmp;
        }
        _list->allocated += strlen(_elements);
        strcpy(*((char **)_list->base_addr + _idx), _elements);
        *((char *)*((char **)_list->base_addr + _idx) + strlen(_elements)) = '\0';
    }
    else
    {
        memmove((_list->base_addr + _idx * _list->data_size), _elements, _list->data_size);
    }
    return;
}
void add_List(List *_list, const void *_elements, const long _idx)
{
    if (_list == NULL)
    {
        printf("Error: Cannot invoke \"add_ListString(ListString *_list, char *_string, long _idx)\" because \"<local1>\" is null\n");
        exit(EX_USAGE);
    }
    if (_elements == NULL)
    {
        printf("Error: Cannot invoke \"add_ListString(ListString *_list, char *_string, long _idx)\" because \"<local2>\" is null\n");
        exit(EX_USAGE);
    }
    if (_idx < 0 || _list->size < _idx)
    {
        printf("Error: Index %ld out of bounds for length %ld\n", _idx, _list->size);
        exit(EX_USAGE);
    }
    if (_list->capacity <= _list->size * _list->data_size)
    {
        void *tmp;
        _list->capacity += LIST_BUF_SIZE * _list->data_size;
        if ((tmp = (void *)realloc(_list->base_addr, _list->capacity)) == NULL)
        {
            free(_list->base_addr);
            printf("Error: unable to allocate new heap space\n");
            exit(EX_OSERR);
        }
        else
        {
            _list->base_addr = tmp;
        }
    }
    memmove((_list->base_addr + (_idx + 1) * _list->data_size), (_list->base_addr + _idx * _list->data_size), (_list->size - _idx) * _list->data_size);
    if (_list->is_string == true)
    {
        if ((*((char **)_list->base_addr + _idx) = (char *)calloc((strlen(_elements) + 1), sizeof(char))) == NULL)
        {
            printf("Error: unable to allocate new heap space\n");
            exit(EX_OSERR);
        }
        _list->allocated += strlen(_elements) + 1;
        strcpy(*((char **)_list->base_addr + _idx), _elements);
    }
    else
    {
        _list->allocated += _list->data_size;
        memmove((_list->base_addr + _idx * _list->data_size), _elements, _list->data_size);
    }
    _list->size++;
    return;
}
void remove_List(List *_list, const long _idx)
{
    if (_list == NULL)
    {
        printf("Error: Cannot invoke \"remove_ListString(ListString *_list, long _idx)\" because \"<local1>\" is null\n");
        exit(EX_USAGE);
    }
    if (_idx < 0 || _list->size <= _idx)
    {
        printf("Error: Index %ld out of bounds for length %ld\n", _idx, _list->size);
        exit(EX_USAGE);
    }
    if (_list->is_string == true)
    {
        _list->allocated -= strlen(*((char **)_list->base_addr + _idx)) + 1;
        free(*((char **)_list->base_addr + _idx));
    }
    memmove((_list->base_addr + _idx * _list->data_size), (_list->base_addr + (_idx + 1) * _list->data_size), (_list->size - _idx) * _list->data_size);
    _list->size--;
    if (LIST_BUF_SIZE * _list->data_size < _list->capacity && _list->size * _list->data_size + LIST_BUF_SIZE * _list->data_size < _list->capacity)
    {
        void *tmp;
        _list->capacity -= LIST_BUF_SIZE * _list->data_size;
        if ((tmp = realloc(_list->base_addr, _list->capacity)) == NULL)
        {
            free(_list->base_addr);
            printf("Error: unable to allocate new heap space\n");
            exit(EX_OSERR);
        }
        else
        {
            _list->base_addr = tmp;
        }
    }
    return;
}

void init_ListInt(ListInt *_list)
{
    if (_list == NULL)
    {
        printf("Error: Cannot invoke \"init_ListInt(ListInt *_list)\" because \"<local1>\" is null\n");
        exit(EX_USAGE);
    }
    _list->size = 0;
    _list->capacity = LIST_BUF;
    if ((_list->base_addr = (int *)malloc(LIST_BUF)) == NULL)
    {
        printf("Error: unable to allocate new heap space\n");
        exit(EX_OSERR);
    }
    return;
}
void asList_ListInt(ListInt *_list, const int *_array, long _size)
{
    if (_list == NULL)
    {
        printf("Error: Cannot invoke \"asListInt(ListInt *_list, int *_array, long _size)\" because \"<local1>\" is null\n");
        exit(EX_USAGE);
    }
    if (_array == NULL)
    {
        printf("Error: Cannot invoke \"asListInt(ListInt *_list, int *_array, long _size)\" because \"<local2>\" is null\n");
        exit(EX_USAGE);
    }
    _list->size = _size;
    _list->capacity = (_size / LIST_BUF + 1) * LIST_BUF * sizeof(int);
    if ((_list->base_addr = (int *)malloc(_list->capacity)) == NULL)
    {
        printf("Error: unable to allocate new heap space\n");
        exit(EX_OSERR);
    }
    memcpy(_list->base_addr, _array, _list->capacity);
    return;
}
void free_ListInt(ListInt *_list)
{
    if (_list == NULL)
    {
        printf("Error: Cannot invoke \"freeListInt(ListInt *_list)\" because \"<local1>\" is null\n");
        exit(EX_USAGE);
    }
    _list->size = 0;
    _list->capacity = 0;
    free(_list->base_addr);
    _list->base_addr = NULL;
    return;
}
void copy_ListInt(ListInt *_list_dst, const ListInt *_list_src)
{
    if (_list_dst == NULL)
    {
        printf("Error: Cannot invoke \"copyListInt(ListInt *_list_dst, const ListInt *_list_src)\" because \"<local1>\" is null\n");
        exit(EX_USAGE);
    }
    if (_list_src == NULL)
    {
        printf("Error: Cannot invoke \"copyListInt(ListInt *_list_dst, const ListInt *_list_src)\" because \"<local2>\" is null\n");
        exit(EX_USAGE);
    }
    _list_dst->size = _list_src->size;
    _list_dst->capacity = _list_src->capacity;
    if ((_list_dst->base_addr = (int *)malloc(_list_dst->capacity)) == NULL)
    {
        printf("Error: unable to allocate new heap space\n");
        exit(EX_OSERR);
    }
    memcpy(_list_dst->base_addr, _list_src->base_addr, _list_src->capacity);
    return;
}
int get_ListInt(const ListInt *_list, long _idx)
{
    if (_list == NULL)
    {
        printf("Error: Cannot invoke \"getListInt(ListInt *_list, int _idx)\" because \"<local1>\" is null\n");
        exit(EX_USAGE);
    }
    if (_idx < 0 || _list->size < _idx)
    {
        printf("Error: Index %ld out of bounds for length %ld\n", _idx, _list->size);
        exit(EX_USAGE);
    }
    return _list->base_addr[_idx];
}
void set_ListInt(ListInt *_list, int _element, long _idx)
{
    if (_list == NULL)
    {
        printf("Error: Cannot invoke \"setListInt(ListInt *_list, int _element, int _idx)\" because \"<local1>\" is null\n");
        exit(EX_USAGE);
    }
    if (_idx < 0 || _list->size <= _idx)
    {
        printf("Error: Index %ld out of bounds for length %ld\n", _idx, _list->size);
        exit(EX_USAGE);
    }
    _list->base_addr[_idx] = _element;
    return;
}
long indexOf_ListInt(const ListInt *_list, int _element)
{
    if (_list == NULL)
    {
        printf("Error: Cannot invoke \"indexOf_ListInt(const ListInt *_list, int _element)\" because \"<local1>\" is null\n");
        exit(EX_USAGE);
    }
    long i;
    for (i = 0; i < _list->size; i++)
    {
        if (_list->base_addr[i] == _element)
        {
            return i;
        }
    }
    return -1;
}
void add_ListInt(ListInt *_list, int _element, long _idx)
{
    if (_list == NULL)
    {
        printf("Error: Cannot invoke \"addListInt(ListInt *_list, int _element, int _idx)\" because \"<local1>\" is null\n");
        exit(EX_USAGE);
    }
    if (_idx < 0 || _list->size < _idx)
    {
        printf("Error: Index %ld out of bounds for length %ld\n", _idx, _list->size);
        exit(EX_USAGE);
    }
    if (_list->capacity <= _list->size * sizeof(int))
    {
        int *tmp;
        _list->capacity += LIST_BUF;
        if ((tmp = (int *)realloc(_list->base_addr, _list->capacity)) == NULL)
        {
            free(_list->base_addr);
            printf("Error: unable to allocate new heap space\n");
            exit(EX_OSERR);
        }
        else
        {
            _list->base_addr = tmp;
        }
    }
    memmove(_list->base_addr + (_idx + 1), _list->base_addr + _idx, (_list->size - _idx) * sizeof(int));
    _list->base_addr[_idx] = _element;
    _list->size++;
    return;
}
void remove_ListInt(ListInt *_list, long _idx)
{
    if (_list == NULL)
    {
        printf("Error: Cannot invoke \"removeListInt(ListInt *_list, int _idx)\" because \"<local1>\" is null\n");
        exit(EX_USAGE);
    }
    if (_idx < 0 || _list->size < _idx)
    {
        printf("Error: Index %ld out of bounds for length %ld\n", _idx, _list->size);
        exit(EX_USAGE);
    }
    memmove(_list->base_addr + _idx, _list->base_addr + _idx + 1, (_list->size - _idx) * sizeof(int));
    _list->size--;
    if (LIST_BUF < _list->capacity && _list->size * sizeof(int) + LIST_BUF < _list->capacity)
    {
        int *tmp;
        _list->capacity -= LIST_BUF;
        if ((tmp = (int *)realloc(_list->base_addr, _list->capacity)) == NULL)
        {
            free(_list->base_addr);
            printf("Error: unable to allocate new heap space\n");
            exit(EX_OSERR);
        }
        else
        {
            _list->base_addr = tmp;
        }
    }
    return;
}
void push_ListInt(ListInt *_list, int _element)
{
    if (_list == NULL)
    {
        printf("Error: Cannot invoke \"push_ListInt(ListInt *_list, int _element)\" because \"<local1>\" is null\n");
        exit(EX_USAGE);
    }
    if (_list->capacity <= _list->size * sizeof(int))
    {
        int *tmp;
        _list->capacity += LIST_BUF;
        if ((tmp = (int *)realloc(_list->base_addr, _list->capacity)) == NULL)
        {
            free(_list->base_addr);
            printf("Error: unable to allocate new heap space\n");
            exit(EX_OSERR);
        }
        else
        {
            _list->base_addr = tmp;
        }
    }
    _list->base_addr[_list->size] = _element;
    _list->size++;
    return;
}
int peek_ListInt(const ListInt *_list)
{
    if (_list == NULL)
    {
        printf("Error: Cannot invoke \"peekListInt(ListInt *_list)\" because \"<local1>\" is null\n");
        exit(EX_USAGE);
    }
    if (_list->size == 0)
    {
        return 0;
    }
    return _list->base_addr[_list->size - 1];
}
int pop_ListInt(ListInt *_list)
{
    if (_list == NULL)
    {
        printf("Error: Cannot invoke \"pop_ListInt(ListInt *_list)\" because \"<local1>\" is null\n");
        exit(EX_USAGE);
    }
    if (_list->size == 0)
    {
        return 0;
    }
    _list->size--;
    int element = _list->base_addr[_list->size];
    if (LIST_BUF < _list->capacity && _list->size * sizeof(int) + LIST_BUF < _list->capacity)
    {
        int *tmp;
        _list->capacity -= LIST_BUF;
        if ((tmp = (int *)realloc(_list->base_addr, _list->capacity)) == NULL)
        {
            free(_list->base_addr);
            printf("Error: unable to allocate new heap space\n");
            exit(EX_OSERR);
        }
        else
        {
            _list->base_addr = tmp;
        }
    }
    return element;
}
void qsort_ListInt(ListInt *_list, long _left, long _right, int SORT_OPTION)
{
    if (_list == NULL)
    {
        printf("Error: Cannot invoke \"qsortListInt(ListInt *_list, long _left, long _right, int SORT_OPTION)\" because \"<local1>\" is null\n");
        exit(EX_USAGE);
    }
    int i, j, left, right;
    int tmp, pivot;
    ListInt left_list, right_list;
    init_ListInt(&left_list);
    init_ListInt(&right_list);
    push_ListInt(&left_list, _left);
    push_ListInt(&right_list, _right);

    if (SORT_OPTION == ACS_SORT)
    {
        while (left_list.size != 0 && right_list.size != 0)
        {
            left = pop_ListInt(&left_list);
            right = pop_ListInt(&right_list);
            i = left;
            j = right;
            pivot = _list->base_addr[(i + j) / 2];
            while (1)
            {
                while (_list->base_addr[i] < pivot)
                {
                    i++;
                }
                while (pivot < _list->base_addr[j])
                {
                    j--;
                }
                if (j <= i)
                {
                    break;
                }

                tmp = _list->base_addr[i];
                _list->base_addr[i] = _list->base_addr[j];
                _list->base_addr[j] = tmp;
                i++;
                j--;
            }
            if (j + 1 < right)
            {
                push_ListInt(&left_list, j + 1);
                push_ListInt(&right_list, right);
            }
            if (left < i - 1)
            {
                push_ListInt(&left_list, left);
                push_ListInt(&right_list, i - 1);
            }
        }
    }
    else
    {
        while (left_list.size != 0 && right_list.size != 0)
        {
            left = pop_ListInt(&left_list);
            right = pop_ListInt(&right_list);
            i = left;
            j = right;
            pivot = _list->base_addr[(i + j) / 2];
            while (1)
            {
                while (pivot < _list->base_addr[i])
                {
                    i++;
                }
                while (_list->base_addr[j] < pivot)
                {
                    j--;
                }
                if (j <= i)
                {
                    break;
                }

                tmp = _list->base_addr[i];
                _list->base_addr[i] = _list->base_addr[j];
                _list->base_addr[j] = tmp;
                i++;
                j--;
            }
            if (j + 1 < right)
            {
                push_ListInt(&left_list, j + 1);
                push_ListInt(&right_list, right);
            }
            if (left < i - 1)
            {
                push_ListInt(&left_list, left);
                push_ListInt(&right_list, i - 1);
            }
        }
    }
    free_ListInt(&left_list);
    free_ListInt(&right_list);
    return;
}
void toArray_ListInt(int *_array, const ListInt *_list)
{
    if (_array == NULL)
    {
        printf("Error: Cannot invoke \"toArray_ListInt(int *_array, const ListInt *_list)\" because \"<local1>\" is null\n");
        exit(EX_USAGE);
    }
    if (_list == NULL)
    {
        printf("Error: Cannot invoke \"toArray_ListInt(int *_array, const ListInt *_list)\" because \"<local2>\" is null\n");
        exit(EX_USAGE);
    }
    if ((_array = (int *)malloc(_list->size * sizeof(int))) == NULL)
    {
        printf("Error: unable to allocate new heap space\n");
        exit(EX_OSERR);
    }
    memcpy(_array, _list->base_addr, _list->size * sizeof(int));
    return;
}
void show_ListInt(ListInt *_list)
{
    int i;
    printf("size: %ld\n", _list->size);
    printf("[");
    for (i = 0; i < _list->size; i++)
    {
        printf("%d", _list->base_addr[i]);
        if (i < _list->size - 1)
        {
            printf(", ");
        }
    }
    printf("]\n");
    return;
}

void init_ListDouble(ListDouble *_list)
{
    if (_list == NULL)
    {
        printf("Error: Cannot invoke \"initListDouble(ListDouble *_list)\" because \"<local1>\" is null\n");
        exit(EX_USAGE);
    }
    _list->size = 0;
    _list->capacity = LIST_BUF;
    if ((_list->base_addr = (double *)malloc(LIST_BUF)) == NULL)
    {
        printf("Error: unable to allocate new heap space\n");
        exit(EX_OSERR);
    }
    return;
}
void asList_ListDouble(ListDouble *_list, const double *_array, long _size)
{
    if (_list == NULL)
    {
        printf("Error: Cannot invoke \"asListDouble(ListDouble *_list, double *_array, long _size)\" because \"<local1>\" is null\n");
        exit(EX_USAGE);
    }
    if (_array == NULL)
    {
        printf("Error: Cannot invoke \"asListDouble(ListDouble *_list, double *_array, long _size)\" because \"<local2>\" is null\n");
        exit(EX_USAGE);
    }
    _list->size = _size;
    _list->capacity = (_size / LIST_BUF + 1) * LIST_BUF * sizeof(double);
    if ((_list->base_addr = (double *)malloc(_list->capacity)) == NULL)
    {
        printf("Error: unable to allocate new heap space\n");
        exit(EX_OSERR);
    }
    memcpy(_list->base_addr, _array, _list->capacity);
    return;
}
void free_ListDouble(ListDouble *_list)
{
    if (_list == NULL)
    {
        printf("Error: Cannot invoke \"freeListDouble(ListDouble *_list)\" because \"<local1>\" is null\n");
        exit(EX_USAGE);
    }
    _list->size = 0;
    _list->capacity = 0;
    free(_list->base_addr);
    _list->base_addr = NULL;
    return;
}
void copy_ListDouble(ListDouble *_list_dst, const ListDouble *_list_src)
{
    if (_list_dst == NULL)
    {
        printf("Error: Cannot invoke \"copyListDouble(ListDouble *_list_dst, const ListDouble *_list_src)\" because \"<local1>\" is null\n");
        exit(EX_USAGE);
    }
    if (_list_src == NULL)
    {
        printf("Error: Cannot invoke \"copyListDouble(ListDouble *_list_dst, const ListDouble *_list_src)\" because \"<local2>\" is null\n");
        exit(EX_USAGE);
    }
    _list_dst->size = _list_src->size;
    _list_dst->capacity = _list_src->capacity;
    if ((_list_dst->base_addr = (double *)malloc(_list_dst->capacity)) == NULL)
    {
        printf("Error: unable to allocate new heap space\n");
        exit(EX_OSERR);
    }
    memcpy(_list_dst->base_addr, _list_src->base_addr, _list_src->capacity);
    return;
}
double get_ListDouble(const ListDouble *_list, long _idx)
{
    if (_list == NULL)
    {
        printf("Error: Cannot invoke \"getListDouble(ListDouble *_list, int _idx)\" because \"<local1>\" is null\n");
        exit(EX_USAGE);
    }
    if (_idx < 0 || _list->size < _idx)
    {
        printf("Error: Index %ld out of bounds for length %ld\n", _idx, _list->size);
        exit(EX_USAGE);
    }
    return _list->base_addr[_idx];
}
void set_ListDouble(ListDouble *_list, double _element, long _idx)
{
    if (_list == NULL)
    {
        printf("Error: Cannot invoke \"setListDouble(ListDouble *_list, double _element, int _idx)\" because \"<local1>\" is null\n");
        exit(EX_USAGE);
    }
    if (_idx < 0 || _list->size <= _idx)
    {
        printf("Error: Index %ld out of bounds for length %ld\n", _idx, _list->size);
        exit(EX_USAGE);
    }
    _list->base_addr[_idx] = _element;
    return;
}
long indexOf_ListDouble(const ListDouble *_list, double _element)
{
    if (_list == NULL)
    {
        printf("Error: Cannot invoke \"indexOf_ListDouble(const ListDouble *_list, double _element)\" because \"<local1>\" is null\n");
        exit(EX_USAGE);
    }
    long i;
    for (i = 0; i < _list->size; i++)
    {
        if (_list->base_addr[i] == _element)
        {
            return i;
        }
    }
    return -1;
}
void add_ListDouble(ListDouble *_list, double _element, long _idx)
{
    if (_list == NULL)
    {
        printf("Error: Cannot invoke \"addListDouble(ListDouble *_list, double _element, int _idx)\" because \"<local1>\" is null\n");
        exit(EX_USAGE);
    }
    if (_idx < 0 || _list->size < _idx)
    {
        printf("Error: Index %ld out of bounds for length %ld\n", _idx, _list->size);
        exit(EX_USAGE);
    }
    if (_list->capacity <= _list->size * sizeof(double))
    {
        double *tmp;
        _list->capacity += LIST_BUF;
        if ((tmp = (double *)realloc(_list->base_addr, _list->capacity)) == NULL)
        {
            free(_list->base_addr);
            printf("Error: unable to allocate new heap space\n");
            exit(EX_OSERR);
        }
        else
        {
            _list->base_addr = tmp;
        }
    }
    memmove(_list->base_addr + (_idx + 1), _list->base_addr + _idx, (_list->size - _idx) * sizeof(double));
    _list->base_addr[_idx] = _element;
    _list->size++;
    return;
}
void remove_ListDouble(ListDouble *_list, long _idx)
{
    if (_list == NULL)
    {
        printf("Error: Cannot invoke \"removeListDouble(ListDouble *_list, int _idx)\" because \"<local1>\" is null\n");
        exit(EX_USAGE);
    }
    if (_idx < 0 || _list->size < _idx)
    {
        printf("Error: Index %ld out of bounds for length %ld\n", _idx, _list->size);
        exit(EX_USAGE);
    }
    memmove(_list->base_addr + _idx, _list->base_addr + _idx + 1, (_list->size - _idx) * sizeof(double));
    _list->size--;
    if (LIST_BUF < _list->capacity && _list->size * sizeof(double) + LIST_BUF < _list->capacity)
    {
        double *tmp;
        _list->capacity -= LIST_BUF;
        if ((tmp = (double *)realloc(_list->base_addr, _list->capacity)) == NULL)
        {
            free(_list->base_addr);
            printf("Error: unable to allocate new heap space\n");
            exit(EX_OSERR);
        }
        else
        {
            _list->base_addr = tmp;
        }
    }
    return;
}
void push_ListDouble(ListDouble *_list, double _element)
{
    if (_list == NULL)
    {
        printf("Error: Cannot invoke \"pushListDouble(ListDouble *_list, double _element)\" because \"<local1>\" is null\n");
        exit(EX_USAGE);
    }
    if (_list->capacity <= _list->size * sizeof(double))
    {
        double *tmp;
        _list->capacity += LIST_BUF;
        if ((tmp = (double *)realloc(_list->base_addr, _list->capacity)) == NULL)
        {
            free(_list->base_addr);
            printf("Error: unable to allocate new heap space\n");
            exit(EX_OSERR);
        }
        else
        {
            _list->base_addr = tmp;
        }
    }
    _list->base_addr[_list->size] = _element;
    _list->size++;
    return;
}
double peek_ListDouble(const ListDouble *_list)
{
    if (_list == NULL)
    {
        printf("Error: Cannot invoke \"peekListDouble(ListDouble *_list)\" because \"<local1>\" is null\n");
        exit(EX_USAGE);
    }
    if (_list->size == 0)
    {
        return 0.0;
    }
    return _list->base_addr[_list->size - 1];
}
double pop_ListDouble(ListDouble *_list)
{
    if (_list == NULL)
    {
        printf("Error: Cannot invoke \"popListDouble(ListDouble *_list)\" because \"<local1>\" is null\n");
        exit(EX_USAGE);
    }
    if (_list->size == 0)
    {
        return 0.0;
    }
    _list->size--;
    double element = _list->base_addr[_list->size];
    if (LIST_BUF < _list->capacity && _list->size * sizeof(double) + LIST_BUF < _list->capacity)
    {
        double *tmp;
        _list->capacity -= LIST_BUF;
        if ((tmp = (double *)realloc(_list->base_addr, _list->capacity)) == NULL)
        {
            free(_list->base_addr);
            printf("Error: unable to allocate new heap space\n");
            exit(EX_OSERR);
        }
        else
        {
            _list->base_addr = tmp;
        }
    }
    return element;
}
void qsort_ListDouble(ListDouble *_list, long _left, long _right, int SORT_OPTION)
{
    if (_list == NULL)
    {
        printf("Error: Cannot invoke \"qsortListDouble(ListDouble *_list, long _left, long _right, int SORT_OPTION)\" because \"<local1>\" is null\n");
        exit(EX_USAGE);
    }
    int i, j, left, right;
    double tmp, pivot;
    ListInt left_list, right_list;
    init_ListInt(&left_list);
    init_ListInt(&right_list);
    push_ListInt(&left_list, _left);
    push_ListInt(&right_list, _right);

    if (SORT_OPTION == ACS_SORT)
    {
        while (left_list.size != 0 && right_list.size != 0)
        {
            left = pop_ListInt(&left_list);
            right = pop_ListInt(&right_list);
            i = left;
            j = right;
            pivot = _list->base_addr[(i + j) / 2];
            while (1)
            {
                while (_list->base_addr[i] < pivot)
                {
                    i++;
                }
                while (pivot < _list->base_addr[j])
                {
                    j--;
                }
                if (j <= i)
                {
                    break;
                }

                tmp = _list->base_addr[i];
                _list->base_addr[i] = _list->base_addr[j];
                _list->base_addr[j] = tmp;
                i++;
                j--;
            }
            if (j + 1 < right)
            {
                push_ListInt(&left_list, j + 1);
                push_ListInt(&right_list, right);
            }
            if (left < i - 1)
            {
                push_ListInt(&left_list, left);
                push_ListInt(&right_list, i - 1);
            }
        }
    }
    else
    {
        while (left_list.size != 0 && right_list.size != 0)
        {
            left = pop_ListInt(&left_list);
            right = pop_ListInt(&right_list);
            i = left;
            j = right;
            pivot = _list->base_addr[(i + j) / 2];
            while (1)
            {
                while (pivot < _list->base_addr[i])
                {
                    i++;
                }
                while (_list->base_addr[j] < pivot)
                {
                    j--;
                }
                if (j <= i)
                {
                    break;
                }

                tmp = _list->base_addr[i];
                _list->base_addr[i] = _list->base_addr[j];
                _list->base_addr[j] = tmp;
                i++;
                j--;
            }
            if (j + 1 < right)
            {
                push_ListInt(&left_list, j + 1);
                push_ListInt(&right_list, right);
            }
            if (left < i - 1)
            {
                push_ListInt(&left_list, left);
                push_ListInt(&right_list, i - 1);
            }
        }
    }
    free_ListInt(&left_list);
    free_ListInt(&right_list);
    return;
}
void toArray_ListDouble(double *_array, const ListDouble *_list)
{
    if (_array == NULL)
    {
        printf("Error: Cannot invoke \"toArray_ListDouble(double *_array, const ListDouble *_list)\" because \"<local1>\" is null\n");
        exit(EX_USAGE);
    }
    if (_list == NULL)
    {
        printf("Error: Cannot invoke \"toArray_ListDouble(double *_array, const ListDouble *_list)\" because \"<local2>\" is null\n");
        exit(EX_USAGE);
    }
    if ((_array = (double *)malloc(_list->size * sizeof(double))) == NULL)
    {
        printf("Error: unable to allocate new heap space\n");
        exit(EX_OSERR);
    }
    memcpy(_array, _list->base_addr, _list->size * sizeof(double));
    return;
}
void show_ListDouble(ListDouble *_list)
{
    int i;
    printf("size: %ld\n", _list->size);
    printf("[");
    for (i = 0; i < _list->size; i++)
    {
        printf("%f", _list->base_addr[i]);
        if (i < _list->size - 1)
        {
            printf(", ");
        }
    }
    printf("]\n");
    return;
}

void init_ListString(ListString *_list)
{
    if (_list == NULL)
    {
        printf("Error: Cannot invoke \"initListString(ListString *_list)\" because \"<local1>\" is null\n");
        exit(EX_USAGE);
    }
    _list->size = 0;
    _list->capacity = LIST_BUF;
    _list->allocated = 0;
    if ((_list->base_addr = (char **)malloc(LIST_BUF)) == NULL)
    {
        printf("Error: unable to allocate new heap space\n");
        exit(EX_OSERR);
    }
    return;
}
void asList_ListString(ListString *_list, const char **_string_array, long _size)
{
    if (_list == NULL)
    {
        printf("Error: Cannot invoke \"asList_ListString(ListString *_list, const char **_string_array, long _size)\" because \"<local1>\" is null\n");
        exit(EX_USAGE);
    }
    if (_string_array == NULL)
    {
        printf("Error: Cannot invoke \"asList_ListString(ListString *_list, const char **_string_array, long _size)\" because \"<local2>\" is null\n");
        exit(EX_USAGE);
    }
    _list->size = _size;
    _list->capacity = (_size / LIST_BUF + 1) * LIST_BUF * sizeof(char *);
    _list->allocated = 0;
    if ((_list->base_addr = (char **)malloc(_list->capacity)) == NULL)
    {
        printf("Error: unable to allocate new heap space\n");
        exit(EX_OSERR);
    }
    int i;
    for (i = 0; i < _size; i++)
    {
        if ((_list->base_addr[i] = (char *)calloc((strlen(_string_array[i]) + 1), sizeof(char))) == NULL)
        {
            printf("Error: unable to allocate new heap space\n");
            exit(EX_OSERR);
        }
        _list->allocated += strlen(_string_array[i]) + 1;
        strcpy(_list->base_addr[i], _string_array[i]);
    }
    return;
}
void free_ListString(ListString *_list)
{
    if (_list == NULL)
    {
        printf("Error: Cannot invoke \"freeListString(ListString *_list)\" because \"<local1>\" is null\n");
        exit(EX_USAGE);
    }
    int i;
    for (i = 0; i < _list->size; i++)
    {
        free(_list->base_addr[i]);
    }
    _list->size = 0;
    _list->capacity = 0;
    _list->allocated = 0;
    free(_list->base_addr);
    _list->base_addr = NULL;
    return;
}
void copy_ListString(ListString *_list_dst, const ListString *_list_src)
{
    if (_list_dst == NULL)
    {
        printf("Error: Cannot invoke \"copy_ListString(ListString *_list_dst, const ListString *_list_src)\" because \"<local1>\" is null\n");
        exit(EX_USAGE);
    }
    if (_list_src == NULL)
    {
        printf("Error: Cannot invoke \"copy_ListString(ListString *_list_dst, const ListString *_list_src)\" because \"<local2>\" is null\n");
        exit(EX_USAGE);
    }
    _list_dst->size = _list_src->size;
    _list_dst->capacity = _list_src->capacity;
    _list_dst->allocated = _list_src->allocated;
    if ((_list_dst->base_addr = (char **)malloc(_list_dst->capacity)) == NULL)
    {
        printf("Error: unable to allocate new heap space\n");
        exit(EX_OSERR);
    }
    int i;
    for (i = 0; i < _list_dst->size; i++)
    {
        if ((_list_dst->base_addr[i] = (char *)calloc((strlen(_list_src->base_addr[i]) + 1), sizeof(char))) == NULL)
        {
            printf("Error: unable to allocate new heap space\n");
            exit(EX_OSERR);
        }
        strcpy(_list_dst->base_addr[i], _list_src->base_addr[i]);
    }
    return;
}
char *get_ListString(const ListString *_list, long _idx)
{
    if (_list == NULL)
    {
        printf("Error: Cannot invoke \"get_ListString(const ListString *_list, long _idx)\" because \"<local1>\" is null\n");
        exit(EX_USAGE);
    }
    if (_idx < 0 || _list->size < _idx)
    {
        printf("Error: Index %ld out of bounds for length %ld\n", _idx, _list->size);
        exit(EX_USAGE);
    }
    char *string_ptr = (char *)calloc((strlen(_list->base_addr[_idx]) + 1), sizeof(char));
    strcpy(string_ptr, _list->base_addr[_idx]);
    return string_ptr;
}
void set_ListString(ListString *_list, const char *_string, long _idx)
{
    if (_list == NULL)
    {
        printf("Error: Cannot invoke \"set_ListString(ListString *_list, char *_string, long _idx)\" because \"<local1>\" is null\n");
        exit(EX_USAGE);
    }
    if (_string == NULL)
    {
        printf("Error: Cannot invoke \"set_ListString(ListString *_list, char *_string, long _idx)\" because \"<local2>\" is null\n");
        exit(EX_USAGE);
    }
    if (_idx < 0 || _list->size <= _idx)
    {
        printf("Error: Index %ld out of bounds for length %ld\n", _idx, _list->size);
        exit(EX_USAGE);
    }
    _list->allocated -= strlen(_list->base_addr[_idx]);
    char *tmp;
    if ((tmp = (char *)realloc(_list->base_addr[_idx], (strlen(_string) + 1) * sizeof(char))) == NULL)
    {
        free(_list->base_addr[_idx]);
        printf("Error: unable to allocate new heap space\n");
        exit(EX_OSERR);
    }
    else
    {
        _list->base_addr[_idx] = tmp;
    }
    _list->allocated += strlen(_string);
    strcpy(_list->base_addr[_idx], _string);
    _list->base_addr[_idx][strlen(_string)] = '\0';
    return;
}
long indexOf_ListString(const ListString *_list, const char *_string)
{
    if (_list == NULL)
    {
        printf("Error: Cannot invoke \"indexOf_ListString(const ListString *_list, const char *_string)\" because \"<local1>\" is null\n");
        exit(EX_USAGE);
    }
    if (_string == NULL)
    {
        printf("Error: Cannot invoke \"indexOf_ListString(const ListString *_list, const char *_string)\" because \"<local2>\" is null\n");
        exit(EX_USAGE);
    }
    long i;
    for (i = 0; i < _list->size; i++)
    {
        if (strcmp(_list->base_addr[i], _string) == 0)
        {
            return i;
        }
    }
    return -1;
}
void inputFile_ListString(ListString *_list, const char *_file_name, const char *_token, const unsigned _LINE_SPLIT)
{
    if (_list == NULL)
    {
        printf("Error: Cannot invoke \"inputFile_ListString(ListString *_list, const char *_file_name)\" because \"<local1>\" is null\n");
        exit(EX_USAGE);
    }
    if (_list == NULL)
    {
        printf("Error: Cannot invoke \"inputFile_ListString(ListString *_list, const char *_file_name)\" because \"<local2>\" is null\n");
        exit(EX_USAGE);
    }
    const unsigned buf_size = 1024;
    FILE *fp;
    if ((fp = fopen(_file_name, "r")) == NULL)
    {
        printf("Error: %s (No such file or directory)\n", _file_name);
        exit(EX_NOINPUT);
    }
    char buf[buf_size];
    char *tmp, *line, *string_tmp;
    unsigned line_size = buf_size;
    if ((line = (char *)calloc(buf_size + 1, sizeof(char))) == NULL)
    {
        printf("Error: unable to allocate new heap space\n");
        exit(EX_OSERR);
    }
    _list->size = 0;
    _list->capacity = LIST_BUF;
    _list->allocated = 0;
    if ((_list->base_addr = (char **)malloc(_list->capacity)) == NULL)
    {
        printf("Error: unable to allocate new heap space\n");
        exit(EX_OSERR);
    }
    int next_line = 1;
    while (fgets(buf, buf_size, fp) != NULL)
    {
        if (next_line == 1)
        {
            strcpy(line, buf);
        }
        else
        {
            if (line_size < strlen(line) + buf_size)
            {
                line_size += buf_size;
                if ((string_tmp = (char *)realloc(line, line_size * sizeof(char))) == NULL)
                {
                    free(string_tmp);
                    printf("Error: unable to allocate new heap space\n");
                    exit(EX_OSERR);
                }
                else
                {
                    line = string_tmp;
                }
            }
            strcat(line, buf);
        }
        if (line[strlen(line) - 1] == '\n')
        {
            if (_token == NULL)
            {
                line[strlen(line) - 1] = '\0';
                push_ListString(_list, line);
                next_line = 1;
            }
            else
            {
                tmp = line;
                while ((string_tmp = strstr(tmp, _token)) != NULL)
                {
                    *(string_tmp) = '\0';
                    push_ListString(_list, tmp);
                    tmp = string_tmp + strlen(_token);
                }
                next_line = 1;
                if (_LINE_SPLIT == LINE_SPLIT_FALSE)
                {
                    strcpy(line, tmp);
                    next_line = 0;
                }
                else
                {
                    tmp[strlen(tmp) - 1] = '\0';
                    push_ListString(_list, tmp);
                }
            }
        }
        else
        {
            next_line = 0;
        }
    }
    if (next_line == 0)
    {
        push_ListString(_list, line);
    }
    if (_token != NULL)
    {
        _list->base_addr[_list->size - 1][strlen(_list->base_addr[_list->size - 1]) - strlen(_token)] = '\0';
    }
    free(line);
    fclose(fp);
}
void add_ListString(ListString *_list, const char *_string, long _idx)
{
    if (_list == NULL)
    {
        printf("Error: Cannot invoke \"add_ListString(ListString *_list, char *_string, long _idx)\" because \"<local1>\" is null\n");
        exit(EX_USAGE);
    }
    if (_string == NULL)
    {
        printf("Error: Cannot invoke \"add_ListString(ListString *_list, char *_string, long _idx)\" because \"<local2>\" is null\n");
        exit(EX_USAGE);
    }
    if (_idx < 0 || _list->size < _idx)
    {
        printf("Error: Index %ld out of bounds for length %ld\n", _idx, _list->size);
        exit(EX_USAGE);
    }
    if (_list->capacity <= _list->size * sizeof(char *))
    {
        char **tmp;
        _list->capacity += LIST_BUF;
        if ((tmp = (char **)realloc(_list->base_addr, _list->capacity)) == NULL)
        {
            free(_list->base_addr);
            printf("Error: unable to allocate new heap space\n");
            exit(EX_OSERR);
        }
        else
        {
            _list->base_addr = tmp;
        }
    }
    memmove(_list->base_addr + (_idx + 1), _list->base_addr + _idx, (_list->size - _idx) * sizeof(char *));
    if ((_list->base_addr[_idx] = (char *)calloc((strlen(_string) + 1), sizeof(char))) == NULL)
    {
        printf("Error: unable to allocate new heap space\n");
        exit(EX_OSERR);
    }
    _list->allocated += strlen(_string) + 1;
    strcpy(_list->base_addr[_idx], _string);
    _list->size++;
    return;
}
void remove_ListString(ListString *_list, long _idx)
{
    if (_list == NULL)
    {
        printf("Error: Cannot invoke \"remove_ListString(ListString *_list, long _idx)\" because \"<local1>\" is null\n");
        exit(EX_USAGE);
    }
    if (_idx < 0 || _list->size < _idx)
    {
        printf("Error: Index %ld out of bounds for length %ld\n", _idx, _list->size);
        exit(EX_USAGE);
    }
    _list->allocated -= strlen(_list->base_addr[_idx]) + 1;
    free(_list->base_addr[_idx]);
    memmove(_list->base_addr + _idx, _list->base_addr + _idx + 1, (_list->size - _idx) * sizeof(char *));
    _list->size--;
    if (LIST_BUF < _list->capacity && _list->size * sizeof(char *) + LIST_BUF < _list->capacity)
    {
        char **tmp;
        _list->capacity -= LIST_BUF;
        if ((tmp = (char **)realloc(_list->base_addr, _list->capacity)) == NULL)
        {
            free(_list->base_addr);
            printf("Error: unable to allocate new heap space\n");
            exit(EX_OSERR);
        }
        else
        {
            _list->base_addr = tmp;
        }
    }
    return;
}
void push_ListString(ListString *_list, const char *_string)
{
    if (_list == NULL)
    {
        printf("Error: Cannot invoke \"push_ListString(ListString *_list, char *_string)\" because \"<local1>\" is null\n");
        exit(EX_USAGE);
    }
    if (_string == NULL)
    {
        printf("Error: Cannot invoke \"push_ListString(ListString *_list, char *_string)\" because \"<local2>\" is null\n");
        exit(EX_USAGE);
    }
    if (_list->capacity <= _list->size * sizeof(char *))
    {
        char **tmp;
        _list->capacity += LIST_BUF;
        if ((tmp = (char **)realloc(_list->base_addr, _list->capacity)) == NULL)
        {
            free(_list->base_addr);
            printf("Error: unable to allocate new heap space\n");
            exit(EX_OSERR);
        }
        else
        {
            _list->base_addr = tmp;
        }
    }
    if ((_list->base_addr[_list->size] = (char *)calloc((strlen(_string) + 1), sizeof(char))) == NULL)
    {
        printf("Error: unable to allocate new heap space\n");
        exit(EX_OSERR);
    }
    _list->allocated += strlen(_string) + 1;
    strcpy(_list->base_addr[_list->size], _string);
    _list->size++;
    return;
}
char *peek_ListString(const ListString *_list)
{
    if (_list == NULL)
    {
        printf("Error: Cannot invoke \"peek_ListString(const ListString *_list)\" because \"<local1>\" is null\n");
        exit(EX_USAGE);
    }
    if (_list->size == 0)
    {
        return NULL;
    }
    char *string_ptr = (char *)calloc(strlen(_list->base_addr[_list->size - 1]) + 1, sizeof(char));
    strcpy(string_ptr, _list->base_addr[_list->size - 1]);
    return string_ptr;
}
char *pop_ListString(ListString *_list)
{
    if (_list == NULL)
    {
        printf("Error: Cannot invoke \"popListDouble(ListDouble *_list)\" because \"<local1>\" is null\n");
        exit(EX_USAGE);
    }
    if (_list->size == 0)
    {
        return NULL;
    }
    _list->size--;
    char *string_ptr = (char *)calloc(strlen(_list->base_addr[_list->size]) + 1, sizeof(char));
    strcpy(string_ptr, _list->base_addr[_list->size]);
    _list->allocated -= strlen(_list->base_addr[_list->size]) + 1;
    free(_list->base_addr[_list->size]);
    if (LIST_BUF < _list->capacity && _list->size * sizeof(char *) + LIST_BUF < _list->capacity)
    {
        char **tmp;
        _list->capacity -= LIST_BUF;
        if ((tmp = (char **)realloc(_list->base_addr, _list->capacity)) == NULL)
        {
            free(_list->base_addr);
            printf("Error: unable to allocate new heap space\n");
            exit(EX_OSERR);
        }
        else
        {
            _list->base_addr = tmp;
        }
    }
    return string_ptr;
}
void qsort_ListString(ListString *_list, long _left, long _right, int SORT_OPTION)
{
    if (_list == NULL)
    {
        printf("Error: Cannot invoke \"qsort_ListString(ListString *_list, long _left, long _right, int SORT_OPTION)\" because \"<local1>\" is null\n");
        exit(EX_USAGE);
    }
    int left, right;
    long i, j, max_len = -1;
    char *tmp, *string_tmp, *pivot;
    ListInt left_list, right_list;
    init_ListInt(&left_list);
    init_ListInt(&right_list);
    push_ListInt(&left_list, _left);
    push_ListInt(&right_list, _right);

    for (i = 0; i < _list->size; i++)
    {
        if (max_len < (long)strlen(_list->base_addr[i]))
        {
            max_len = (long)strlen(_list->base_addr[i]);
        }
    }
    if ((pivot = (char *)calloc(max_len + 1, sizeof(char))) == NULL)
    {
        printf("Error: unable to allocate new heap space\n");
        exit(EX_OSERR);
    }
    if ((string_tmp = (char *)calloc(max_len + 1, sizeof(char))) == NULL)
    {
        printf("Error: unable to allocate new heap space\n");
        exit(EX_OSERR);
    }
    if (SORT_OPTION == ACS_SORT)
    {
        while (left_list.size != 0 && right_list.size != 0)
        {
            left = pop_ListInt(&left_list);
            right = pop_ListInt(&right_list);
            i = left;
            j = right;
            strcpy(pivot, _list->base_addr[(i + j) / 2]);
            while (1)
            {
                while (strcmp(_list->base_addr[i], pivot) < 0)
                {
                    i++;
                }
                while (strcmp(pivot, _list->base_addr[j]) < 0)
                {
                    j--;
                }
                if (j <= i)
                {
                    break;
                }

                strcpy(string_tmp, _list->base_addr[i]);
                if ((tmp = (char *)realloc(_list->base_addr[i], (strlen(_list->base_addr[j]) + 1) * sizeof(char))) == NULL)
                {
                    free(_list->base_addr[i]);
                    printf("Error: unable to allocate new heap space\n");
                    exit(EX_OSERR);
                }
                else
                {
                    _list->base_addr[i] = tmp;
                }
                strcpy(_list->base_addr[i], _list->base_addr[j]);
                if ((tmp = (char *)realloc(_list->base_addr[j], (strlen(string_tmp) + 1) * sizeof(char))) == NULL)
                {
                    free(_list->base_addr[j]);
                    printf("Error: unable to allocate new heap space\n");
                    exit(EX_OSERR);
                }
                else
                {
                    _list->base_addr[j] = tmp;
                }
                strcpy(_list->base_addr[j], string_tmp);
                i++;
                j--;
            }
            if (j + 1 < right)
            {
                push_ListInt(&left_list, j + 1);
                push_ListInt(&right_list, right);
            }
            if (left < i - 1)
            {
                push_ListInt(&left_list, left);
                push_ListInt(&right_list, i - 1);
            }
        }
    }
    else
    {
        while (left_list.size != 0 && right_list.size != 0)
        {
            left = pop_ListInt(&left_list);
            right = pop_ListInt(&right_list);
            i = left;
            j = right;
            strcpy(pivot, _list->base_addr[(i + j) / 2]);
            while (1)
            {
                while (0 < strcmp(_list->base_addr[i], pivot))
                {
                    i++;
                }
                while (0 < strcmp(pivot, _list->base_addr[j]))
                {
                    j--;
                }
                if (j <= i)
                {
                    break;
                }

                strcpy(string_tmp, _list->base_addr[i]);
                if ((tmp = (char *)realloc(_list->base_addr[i], (strlen(_list->base_addr[j]) + 1) * sizeof(char))) == NULL)
                {
                    free(_list->base_addr[i]);
                    printf("Error: unable to allocate new heap space\n");
                    exit(EX_OSERR);
                }
                else
                {
                    _list->base_addr[i] = tmp;
                }
                strcpy(_list->base_addr[i], _list->base_addr[j]);
                if ((tmp = (char *)realloc(_list->base_addr[j], (strlen(string_tmp) + 1) * sizeof(char))) == NULL)
                {
                    free(_list->base_addr[j]);
                    printf("Error: unable to allocate new heap space\n");
                    exit(EX_OSERR);
                }
                else
                {
                    _list->base_addr[j] = tmp;
                }
                strcpy(_list->base_addr[j], string_tmp);
                i++;
                j--;
            }
            if (j + 1 < right)
            {
                push_ListInt(&left_list, j + 1);
                push_ListInt(&right_list, right);
            }
            if (left < i - 1)
            {
                push_ListInt(&left_list, left);
                push_ListInt(&right_list, i - 1);
            }
        }
    }
    free(pivot);
    free(string_tmp);
    free_ListInt(&left_list);
    free_ListInt(&right_list);
    return;
}
void show_ListString(ListString *_list)
{
    long i;
    printf("size: %ld\n", _list->size);
    printf("allocated: %zu\n", _list->allocated);
    printf("[\n");
    for (i = 0; i < _list->size; i++)
    {
        printf("%16ld:  %s\n", i, _list->base_addr[i]);
    }
    printf("]\n");
    return;
}