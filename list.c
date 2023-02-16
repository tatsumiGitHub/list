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
    _list->size = -1;
    _list->capacity = -1;
    free(_list->ptr);
    _list->ptr = NULL;
    return;
}
int getListInt(ListInt *_list, int _idx)
{
    if (_list == NULL)
    {
        printf("Error: Cannot invoke \"getListInt(ListInt *_list, int _idx)\" because \"<local1>\" is null\n");
        exit(EX_USAGE);
    }
    if (_idx < LIST_END || _list->size < _idx)
    {
        printf("Error: Index %d out of bounds for 0~length %d\n", _idx, _list->size);
        exit(EX_USAGE);
    }
    else if (_idx == LIST_END)
    {
        _idx = _list->size;
    }
    return _list->ptr[_idx];
}
void addListInt(ListInt *_list, int _element, int _idx)
{
    if (_list == NULL)
    {
        printf("Error: Cannot invoke \"addListInt(ListInt *_list, int _element, int _idx)\" because \"<local1>\" is null\n");
        exit(EX_USAGE);
    }
    if (_idx < LIST_END || _list->size < _idx)
    {
        printf("Error: Index %d out of bounds for 0~length %d\n", _idx, _list->size);
        exit(EX_USAGE);
    }
    else if (_idx == LIST_END)
    {
        _idx = _list->size;
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
void removeListInt(ListInt *_list, int _idx)
{
    if (_list == NULL)
    {
        printf("Error: Cannot invoke \"removeListInt(ListInt *_list, int _idx)\" because \"<local1>\" is null\n");
        exit(EX_USAGE);
    }
    if (_idx < LIST_END || _list->size < _idx)
    {
        printf("Error: Index %d out of bounds for 0~length %d\n", _idx, _list->size);
        exit(EX_USAGE);
    }
    else if (_idx == LIST_END)
    {
        _idx = _list->size;
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
int popListInt(ListInt *_list)
{
    if (_list == NULL)
    {
        printf("Error: Cannot invoke \"popListInt(ListInt *_list)\" because \"<local1>\" is null\n");
        exit(EX_USAGE);
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
    _list->size = -1;
    _list->capacity = -1;
    free(_list->ptr);
    _list->ptr = NULL;
    return;
}
double getListDouble(ListDouble *_list, int _idx)
{
    if (_list == NULL)
    {
        printf("Error: Cannot invoke \"getListDouble(ListDouble *_list, int _idx)\" because \"<local1>\" is null\n");
        exit(EX_USAGE);
    }
    if (_idx < LIST_END || _list->size < _idx)
    {
        printf("Error: Index %d out of bounds for 0~length %d\n", _idx, _list->size);
        exit(EX_USAGE);
    }
    else if (_idx == LIST_END)
    {
        _idx = _list->size;
    }
    return _list->ptr[_idx];
}
void addListDouble(ListDouble *_list, double _element, int _idx)
{
    if (_list == NULL)
    {
        printf("Error: Cannot invoke \"addListDouble(ListDouble *_list, double _element, int _idx)\" because \"<local1>\" is null\n");
        exit(EX_USAGE);
    }
    if (_idx < LIST_END || _list->size < _idx)
    {
        printf("Error: Index %d out of bounds for 0~length %d\n", _idx, _list->size);
        exit(EX_USAGE);
    }
    else if (_idx == LIST_END)
    {
        _idx = _list->size;
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
void removeListDouble(ListDouble *_list, int _idx)
{
    if (_list == NULL)
    {
        printf("Error: Cannot invoke \"removeListDouble(ListDouble *_list, int _idx)\" because \"<local1>\" is null\n");
        exit(EX_USAGE);
    }
    if (_idx < LIST_END || _list->size < _idx)
    {
        printf("Error: Index %d out of bounds for 0~length %d\n", _idx, _list->size);
        exit(EX_USAGE);
    }
    else if (_idx == LIST_END)
    {
        _idx = _list->size;
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
double popListDouble(ListDouble *_list)
{
    if (_list == NULL)
    {
        printf("Error: Cannot invoke \"popListDouble(ListDouble *_list)\" because \"<local1>\" is null\n");
        exit(EX_USAGE);
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