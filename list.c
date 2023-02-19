#include "list.h"

void initListInt(ListInt *_list)
{
    if (_list == NULL)
    {
        printf("Error: Cannot invoke \"initListInt(ListInt *_list)\" because \"<local1>\" is null\n");
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
void freeListInt(ListInt *_list)
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
int getListInt(ListInt *_list, unsigned long _idx)
{
    if (_list == NULL)
    {
        printf("Error: Cannot invoke \"getListInt(ListInt *_list, int _idx)\" because \"<local1>\" is null\n");
        exit(EX_USAGE);
    }
    if (_list->size < _idx)
    {
        printf("Error: Index %zu out of bounds for length %zu\n", _idx, _list->size);
        exit(EX_USAGE);
    }
    return _list->ptr[_idx];
}
void addListInt(ListInt *_list, int _element, unsigned long _idx)
{
    if (_list == NULL)
    {
        printf("Error: Cannot invoke \"addListInt(ListInt *_list, int _element, int _idx)\" because \"<local1>\" is null\n");
        exit(EX_USAGE);
    }
    if (_list->size < _idx)
    {
        printf("Error: Index %zu out of bounds for length %zu\n", _idx, _list->size);
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
void removeListInt(ListInt *_list, unsigned long _idx)
{
    if (_list == NULL)
    {
        printf("Error: Cannot invoke \"removeListInt(ListInt *_list, int _idx)\" because \"<local1>\" is null\n");
        exit(EX_USAGE);
    }
    if (_list->size < _idx)
    {
        printf("Error: Index %zu out of bounds for length %zu\n", _idx, _list->size);
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
void pushListInt(ListInt *_list, int _element)
{
    if (_list == NULL)
    {
        printf("Error: Cannot invoke \"pushListInt(ListInt *_list, int _element)\" because \"<local1>\" is null\n");
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
int peekListInt(ListInt *_list)
{
    if (_list == NULL)
    {
        printf("Error: Cannot invoke \"popListInt(ListInt *_list)\" because \"<local1>\" is null\n");
        exit(EX_USAGE);
    }
    if (_list->size == 0)
    {
        return 0;
    }
    return _list->ptr[_list->size - 1];
}
int popListInt(ListInt *_list)
{
    if (_list == NULL)
    {
        printf("Error: Cannot invoke \"popListInt(ListInt *_list)\" because \"<local1>\" is null\n");
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
void qsortListInt(ListInt *_list, unsigned long _left, unsigned long _right, int SORT_OPTION)
{
    if (_list == NULL)
    {
        printf("Error: Cannot invoke \"popListInt(ListInt *_list)\" because \"<local1>\" is null\n");
        exit(EX_USAGE);
    }
    int i, j, left, right;
    int tmp, pivot;
    ListInt left_list, right_list;
    initListInt(&left_list);
    initListInt(&right_list);
    pushListInt(&left_list, _left);
    pushListInt(&right_list, _right);

    if (SORT_OPTION == ACS_SORT)
    {
        while (left_list.size != 0 && right_list.size != 0)
        {
            left = popListInt(&left_list);
            right = popListInt(&right_list);
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
                pushListInt(&left_list, j + 1);
                pushListInt(&right_list, right);
            }
            if (left < i - 1)
            {
                pushListInt(&left_list, left);
                pushListInt(&right_list, i - 1);
            }
        }
    }
    else
    {
        while (left_list.size != 0 && right_list.size != 0)
        {
            left = popListInt(&left_list);
            right = popListInt(&right_list);
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
                pushListInt(&left_list, j + 1);
                pushListInt(&right_list, right);
            }
            if (left < i - 1)
            {
                pushListInt(&left_list, left);
                pushListInt(&right_list, i - 1);
            }
        }
    }
    return;
}
void showListInt(ListInt *_list)
{
    int i;
    printf("size: %zu\n", _list->size);
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

void initListDouble(ListDouble *_list)
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
void freeListDouble(ListDouble *_list)
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
double getListDouble(ListDouble *_list, unsigned long _idx)
{
    if (_list == NULL)
    {
        printf("Error: Cannot invoke \"getListDouble(ListDouble *_list, int _idx)\" because \"<local1>\" is null\n");
        exit(EX_USAGE);
    }
    if (_list->size < _idx)
    {
        printf("Error: Index %zu out of bounds for length %zu\n", _idx, _list->size);
        exit(EX_USAGE);
    }
    return _list->ptr[_idx];
}
void addListDouble(ListDouble *_list, double _element, unsigned long _idx)
{
    if (_list == NULL)
    {
        printf("Error: Cannot invoke \"addListDouble(ListDouble *_list, double _element, int _idx)\" because \"<local1>\" is null\n");
        exit(EX_USAGE);
    }
    if (_list->size < _idx)
    {
        printf("Error: Index %zu out of bounds for length %zu\n", _idx, _list->size);
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
    _list->size++;
    _list->ptr[_idx] = _element;
    return;
}
void removeListDouble(ListDouble *_list, unsigned long _idx)
{
    if (_list == NULL)
    {
        printf("Error: Cannot invoke \"removeListDouble(ListDouble *_list, int _idx)\" because \"<local1>\" is null\n");
        exit(EX_USAGE);
    }
    if (_list->size < _idx)
    {
        printf("Error: Index %zu out of bounds for length %zu\n", _idx, _list->size);
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
void pushListDouble(ListDouble *_list, double _element)
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
double peekListDouble(ListDouble *_list)
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
    return _list->ptr[_list->size - 1];
}
double popListDouble(ListDouble *_list)
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
void qsortListDouble(ListDouble *_list, unsigned long _left, unsigned long _right, int SORT_OPTION)
{
    if (_list == NULL)
    {
        printf("Error: Cannot invoke \"popListInt(ListInt *_list)\" because \"<local1>\" is null\n");
        exit(EX_USAGE);
    }
    int i, j, left, right;
    double tmp, pivot;
    ListInt left_list, right_list;
    initListInt(&left_list);
    initListInt(&right_list);
    pushListInt(&left_list, _left);
    pushListInt(&right_list, _right);

    if (SORT_OPTION == ACS_SORT)
    {
        while (left_list.size != 0 && right_list.size != 0)
        {
            left = popListInt(&left_list);
            right = popListInt(&right_list);
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
                pushListInt(&left_list, j + 1);
                pushListInt(&right_list, right);
            }
            if (left < i - 1)
            {
                pushListInt(&left_list, left);
                pushListInt(&right_list, i - 1);
            }
        }
    }
    else
    {
        while (left_list.size != 0 && right_list.size != 0)
        {
            left = popListInt(&left_list);
            right = popListInt(&right_list);
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
                pushListInt(&left_list, j + 1);
                pushListInt(&right_list, right);
            }
            if (left < i - 1)
            {
                pushListInt(&left_list, left);
                pushListInt(&right_list, i - 1);
            }
        }
    }
    return;
}
void showListDouble(ListDouble *_list)
{
    int i;
    printf("size: %zu\n", _list->size);
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