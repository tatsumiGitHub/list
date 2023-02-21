#include "list.h"

void init_ListInt(ListInt *_list)
{
    if (_list == NULL)
    {
        printf("Error: Cannot invoke \"init_ListInt(ListInt *_list)\" because \"<local1>\" is null\n");
        exit(EX_USAGE);
    }
    _list->size = 0;
    _list->capacity = LIST_BUF;
    if ((_list->ptr = (int *)malloc(LIST_BUF)) == NULL)
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
    if ((_list->ptr = (int *)malloc(_list->capacity)) == NULL)
    {
        printf("Error: unable to allocate new heap space\n");
        exit(EX_OSERR);
    }
    memcpy(_list->ptr, _array, _list->capacity);
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
    free(_list->ptr);
    _list->ptr = NULL;
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
    if ((_list_dst->ptr = (int *)malloc(_list_dst->capacity)) == NULL)
    {
        printf("Error: unable to allocate new heap space\n");
        exit(EX_OSERR);
    }
    memcpy(_list_dst->ptr, _list_src->ptr, _list_src->capacity);
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
    return _list->ptr[_idx];
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
    _list->ptr[_idx] = _element;
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
        if (_list->ptr[i] == _element)
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
        if ((tmp = (int *)realloc(_list->ptr, _list->capacity)) == NULL)
        {
            free(_list->ptr);
            printf("Error: unable to allocate new heap space\n");
            exit(EX_OSERR);
        }
        else
        {
            _list->ptr = tmp;
        }
    }
    memmove(_list->ptr + (_idx + 1), _list->ptr + _idx, (_list->size - _idx) * sizeof(int));
    _list->ptr[_idx] = _element;
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
    memmove(_list->ptr + _idx, _list->ptr + _idx + 1, (_list->size - _idx) * sizeof(int));
    _list->size--;
    if (LIST_BUF < _list->capacity && _list->size * sizeof(int) + LIST_BUF < _list->capacity)
    {
        int *tmp;
        _list->capacity -= LIST_BUF;
        if ((tmp = (int *)realloc(_list->ptr, _list->capacity)) == NULL)
        {
            free(_list->ptr);
            printf("Error: unable to allocate new heap space\n");
            exit(EX_OSERR);
        }
        else
        {
            _list->ptr = tmp;
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
        if ((tmp = (int *)realloc(_list->ptr, _list->capacity)) == NULL)
        {
            free(_list->ptr);
            printf("Error: unable to allocate new heap space\n");
            exit(EX_OSERR);
        }
        else
        {
            _list->ptr = tmp;
        }
    }
    _list->ptr[_list->size] = _element;
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
    return _list->ptr[_list->size - 1];
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
    int element = _list->ptr[_list->size];
    if (LIST_BUF < _list->capacity && _list->size * sizeof(int) + LIST_BUF < _list->capacity)
    {
        int *tmp;
        _list->capacity -= LIST_BUF;
        if ((tmp = (int *)realloc(_list->ptr, _list->capacity)) == NULL)
        {
            free(_list->ptr);
            printf("Error: unable to allocate new heap space\n");
            exit(EX_OSERR);
        }
        else
        {
            _list->ptr = tmp;
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
            pivot = _list->ptr[(i + j) / 2];
            while (1)
            {
                while (_list->ptr[i] < pivot)
                {
                    i++;
                }
                while (pivot < _list->ptr[j])
                {
                    j--;
                }
                if (j <= i)
                {
                    break;
                }

                tmp = _list->ptr[i];
                _list->ptr[i] = _list->ptr[j];
                _list->ptr[j] = tmp;
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
            pivot = _list->ptr[(i + j) / 2];
            while (1)
            {
                while (pivot < _list->ptr[i])
                {
                    i++;
                }
                while (_list->ptr[j] < pivot)
                {
                    j--;
                }
                if (j <= i)
                {
                    break;
                }

                tmp = _list->ptr[i];
                _list->ptr[i] = _list->ptr[j];
                _list->ptr[j] = tmp;
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
    memcpy(_array, _list->ptr, _list->size * sizeof(int));
    return;
}
void show_ListInt(ListInt *_list)
{
    int i;
    printf("size: %ld\n", _list->size);
    printf("[");
    for (i = 0; i < _list->size; i++)
    {
        printf("%d", _list->ptr[i]);
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
    if ((_list->ptr = (double *)malloc(LIST_BUF)) == NULL)
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
    if ((_list->ptr = (double *)malloc(_list->capacity)) == NULL)
    {
        printf("Error: unable to allocate new heap space\n");
        exit(EX_OSERR);
    }
    memcpy(_list->ptr, _array, _list->capacity);
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
    free(_list->ptr);
    _list->ptr = NULL;
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
    if ((_list_dst->ptr = (double *)malloc(_list_dst->capacity)) == NULL)
    {
        printf("Error: unable to allocate new heap space\n");
        exit(EX_OSERR);
    }
    memcpy(_list_dst->ptr, _list_src->ptr, _list_src->capacity);
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
    return _list->ptr[_idx];
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
    _list->ptr[_idx] = _element;
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
        if (_list->ptr[i] == _element)
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
        if ((tmp = (double *)realloc(_list->ptr, _list->capacity)) == NULL)
        {
            free(_list->ptr);
            printf("Error: unable to allocate new heap space\n");
            exit(EX_OSERR);
        }
        else
        {
            _list->ptr = tmp;
        }
    }
    memmove(_list->ptr + (_idx + 1), _list->ptr + _idx, (_list->size - _idx) * sizeof(double));
    _list->ptr[_idx] = _element;
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
    memmove(_list->ptr + _idx, _list->ptr + _idx + 1, (_list->size - _idx) * sizeof(double));
    _list->size--;
    if (LIST_BUF < _list->capacity && _list->size * sizeof(double) + LIST_BUF < _list->capacity)
    {
        double *tmp;
        _list->capacity -= LIST_BUF;
        if ((tmp = (double *)realloc(_list->ptr, _list->capacity)) == NULL)
        {
            free(_list->ptr);
            printf("Error: unable to allocate new heap space\n");
            exit(EX_OSERR);
        }
        else
        {
            _list->ptr = tmp;
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
        if ((tmp = (double *)realloc(_list->ptr, _list->capacity)) == NULL)
        {
            free(_list->ptr);
            printf("Error: unable to allocate new heap space\n");
            exit(EX_OSERR);
        }
        else
        {
            _list->ptr = tmp;
        }
    }
    _list->ptr[_list->size] = _element;
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
    return _list->ptr[_list->size - 1];
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
    double element = _list->ptr[_list->size];
    if (LIST_BUF < _list->capacity && _list->size * sizeof(double) + LIST_BUF < _list->capacity)
    {
        double *tmp;
        _list->capacity -= LIST_BUF;
        if ((tmp = (double *)realloc(_list->ptr, _list->capacity)) == NULL)
        {
            free(_list->ptr);
            printf("Error: unable to allocate new heap space\n");
            exit(EX_OSERR);
        }
        else
        {
            _list->ptr = tmp;
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
            pivot = _list->ptr[(i + j) / 2];
            while (1)
            {
                while (_list->ptr[i] < pivot)
                {
                    i++;
                }
                while (pivot < _list->ptr[j])
                {
                    j--;
                }
                if (j <= i)
                {
                    break;
                }

                tmp = _list->ptr[i];
                _list->ptr[i] = _list->ptr[j];
                _list->ptr[j] = tmp;
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
            pivot = _list->ptr[(i + j) / 2];
            while (1)
            {
                while (pivot < _list->ptr[i])
                {
                    i++;
                }
                while (_list->ptr[j] < pivot)
                {
                    j--;
                }
                if (j <= i)
                {
                    break;
                }

                tmp = _list->ptr[i];
                _list->ptr[i] = _list->ptr[j];
                _list->ptr[j] = tmp;
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
    memcpy(_array, _list->ptr, _list->size * sizeof(double));
    return;
}
void show_ListDouble(ListDouble *_list)
{
    int i;
    printf("size: %ld\n", _list->size);
    printf("[");
    for (i = 0; i < _list->size; i++)
    {
        printf("%f", _list->ptr[i]);
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
    if ((_list->ptr = (char **)malloc(LIST_BUF)) == NULL)
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
    if ((_list->ptr = (char **)malloc(_list->capacity)) == NULL)
    {
        printf("Error: unable to allocate new heap space\n");
        exit(EX_OSERR);
    }
    int i;
    for (i = 0; i < _size; i++)
    {
        if ((_list->ptr[i] = (char *)calloc((strlen(_string_array[i]) + 1), sizeof(char))) == NULL)
        {
            printf("Error: unable to allocate new heap space\n");
            exit(EX_OSERR);
        }
        _list->allocated += strlen(_string_array[i]) + 1;
        strcpy(_list->ptr[i], _string_array[i]);
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
        free(_list->ptr[i]);
    }
    _list->size = 0;
    _list->capacity = 0;
    _list->allocated = 0;
    free(_list->ptr);
    _list->ptr = NULL;
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
    if ((_list_dst->ptr = (char **)malloc(_list_dst->capacity)) == NULL)
    {
        printf("Error: unable to allocate new heap space\n");
        exit(EX_OSERR);
    }
    int i;
    for (i = 0; i < _list_dst->size; i++)
    {
        if ((_list_dst->ptr[i] = (char *)calloc((strlen(_list_src->ptr[i]) + 1), sizeof(char))) == NULL)
        {
            printf("Error: unable to allocate new heap space\n");
            exit(EX_OSERR);
        }
        strcpy(_list_dst->ptr[i], _list_src->ptr[i]);
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
    char *string_ptr = (char *)calloc((strlen(_list->ptr[_idx]) + 1), sizeof(char));
    strcpy(string_ptr, _list->ptr[_idx]);
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
    _list->allocated -= strlen(_list->ptr[_idx]);
    char *tmp;
    if ((tmp = (char *)realloc(_list->ptr[_idx], (strlen(_string) + 1) * sizeof(char))) == NULL)
    {
        free(_list->ptr[_idx]);
        printf("Error: unable to allocate new heap space\n");
        exit(EX_OSERR);
    }
    else
    {
        _list->ptr[_idx] = tmp;
    }
    _list->allocated += strlen(_string);
    strcpy(_list->ptr[_idx], _string);
    _list->ptr[_idx][strlen(_string)] = '\0';
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
        if (strcmp(_list->ptr[i], _string) == 0)
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
    if ((_list->ptr = (char **)malloc(_list->capacity)) == NULL)
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
        _list->ptr[_list->size - 1][strlen(_list->ptr[_list->size - 1]) - strlen(_token)] = '\0';
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
        if ((tmp = (char **)realloc(_list->ptr, _list->capacity)) == NULL)
        {
            free(_list->ptr);
            printf("Error: unable to allocate new heap space\n");
            exit(EX_OSERR);
        }
        else
        {
            _list->ptr = tmp;
        }
    }
    memmove(_list->ptr + (_idx + 1), _list->ptr + _idx, (_list->size - _idx) * sizeof(char *));
    if ((_list->ptr[_idx] = (char *)calloc((strlen(_string) + 1), sizeof(char))) == NULL)
    {
        printf("Error: unable to allocate new heap space\n");
        exit(EX_OSERR);
    }
    _list->allocated += strlen(_string) + 1;
    strcpy(_list->ptr[_idx], _string);
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
    _list->allocated -= strlen(_list->ptr[_idx]) + 1;
    free(_list->ptr[_idx]);
    memmove(_list->ptr + _idx, _list->ptr + _idx + 1, (_list->size - _idx) * sizeof(char *));
    _list->size--;
    if (LIST_BUF < _list->capacity && _list->size * sizeof(char *) + LIST_BUF < _list->capacity)
    {
        char **tmp;
        _list->capacity -= LIST_BUF;
        if ((tmp = (char **)realloc(_list->ptr, _list->capacity)) == NULL)
        {
            free(_list->ptr);
            printf("Error: unable to allocate new heap space\n");
            exit(EX_OSERR);
        }
        else
        {
            _list->ptr = tmp;
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
        if ((tmp = (char **)realloc(_list->ptr, _list->capacity)) == NULL)
        {
            free(_list->ptr);
            printf("Error: unable to allocate new heap space\n");
            exit(EX_OSERR);
        }
        else
        {
            _list->ptr = tmp;
        }
    }
    if ((_list->ptr[_list->size] = (char *)calloc((strlen(_string) + 1), sizeof(char))) == NULL)
    {
        printf("Error: unable to allocate new heap space\n");
        exit(EX_OSERR);
    }
    _list->allocated += strlen(_string) + 1;
    strcpy(_list->ptr[_list->size], _string);
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
    char *string_ptr = (char *)calloc(strlen(_list->ptr[_list->size - 1]) + 1, sizeof(char));
    strcpy(string_ptr, _list->ptr[_list->size - 1]);
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
    char *string_ptr = (char *)calloc(strlen(_list->ptr[_list->size]) + 1, sizeof(char));
    strcpy(string_ptr, _list->ptr[_list->size]);
    _list->allocated -= strlen(_list->ptr[_list->size]) + 1;
    free(_list->ptr[_list->size]);
    if (LIST_BUF < _list->capacity && _list->size * sizeof(char *) + LIST_BUF < _list->capacity)
    {
        char **tmp;
        _list->capacity -= LIST_BUF;
        if ((tmp = (char **)realloc(_list->ptr, _list->capacity)) == NULL)
        {
            free(_list->ptr);
            printf("Error: unable to allocate new heap space\n");
            exit(EX_OSERR);
        }
        else
        {
            _list->ptr = tmp;
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
        if (max_len < (long)strlen(_list->ptr[i]))
        {
            max_len = (long)strlen(_list->ptr[i]);
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
            strcpy(pivot, _list->ptr[(i + j) / 2]);
            while (1)
            {
                while (strcmp(_list->ptr[i], pivot) < 0)
                {
                    i++;
                }
                while (strcmp(pivot, _list->ptr[j]) < 0)
                {
                    j--;
                }
                if (j <= i)
                {
                    break;
                }

                strcpy(string_tmp, _list->ptr[i]);
                if ((tmp = (char *)realloc(_list->ptr[i], (strlen(_list->ptr[j]) + 1) * sizeof(char))) == NULL)
                {
                    free(_list->ptr[i]);
                    printf("Error: unable to allocate new heap space\n");
                    exit(EX_OSERR);
                }
                else
                {
                    _list->ptr[i] = tmp;
                }
                strcpy(_list->ptr[i], _list->ptr[j]);
                if ((tmp = (char *)realloc(_list->ptr[j], (strlen(string_tmp) + 1) * sizeof(char))) == NULL)
                {
                    free(_list->ptr[j]);
                    printf("Error: unable to allocate new heap space\n");
                    exit(EX_OSERR);
                }
                else
                {
                    _list->ptr[j] = tmp;
                }
                strcpy(_list->ptr[j], string_tmp);
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
            strcpy(pivot, _list->ptr[(i + j) / 2]);
            while (1)
            {
                while (0 < strcmp(_list->ptr[i], pivot))
                {
                    i++;
                }
                while (0 < strcmp(pivot, _list->ptr[j]))
                {
                    j--;
                }
                if (j <= i)
                {
                    break;
                }

                strcpy(string_tmp, _list->ptr[i]);
                if ((tmp = (char *)realloc(_list->ptr[i], (strlen(_list->ptr[j]) + 1) * sizeof(char))) == NULL)
                {
                    free(_list->ptr[i]);
                    printf("Error: unable to allocate new heap space\n");
                    exit(EX_OSERR);
                }
                else
                {
                    _list->ptr[i] = tmp;
                }
                strcpy(_list->ptr[i], _list->ptr[j]);
                if ((tmp = (char *)realloc(_list->ptr[j], (strlen(string_tmp) + 1) * sizeof(char))) == NULL)
                {
                    free(_list->ptr[j]);
                    printf("Error: unable to allocate new heap space\n");
                    exit(EX_OSERR);
                }
                else
                {
                    _list->ptr[j] = tmp;
                }
                strcpy(_list->ptr[j], string_tmp);
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
        printf("%16ld:  %s\n", i, _list->ptr[i]);
    }
    printf("]\n");
    return;
}