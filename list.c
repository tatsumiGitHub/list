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
int get_ListInt(ListInt *_list, long _idx)
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
int peek_ListInt(ListInt *_list)
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
double get_ListDouble(ListDouble *_list, long _idx)
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
        _list->capacity -= sizeof(double);
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
double peek_ListDouble(ListDouble *_list)
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