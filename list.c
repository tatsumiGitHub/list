#include "list.h"

int initListInt(ListInt *_list)
{
    if (_list == NULL)
    {
        return -1;
    }
    _list->size = 0;
    _list->capacity = LIST_BUF;
    if ((_list->ptr = (int *)malloc(LIST_BUF)) == NULL)
    {
        return 0;
    }
    return 1;
}
int freeListInt(ListInt *_list)
{
    if (_list == NULL)
    {
        return -1;
    }
    _list->size = -1;
    _list->capacity = -1;
    free(_list->ptr);
    _list->ptr = NULL;
    return 1;
}
int getListInt(ListInt *_list, int _idx)
{
    if (_list == NULL)
    {
        return -1;
    }
    if (_idx < LIST_END || _list->size < _idx)
    {
        return 0;
    }
    else if (_idx == LIST_END)
    {
        _idx = _list->size;
    }
    return _list->ptr[_idx];
}
int addListInt(ListInt *_list, int _element, int _idx)
{
    if (_list == NULL)
    {
        return -1;
    }
    if (_idx < LIST_END || _list->size < _idx)
    {
        return 0;
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
            return 0;
        }
        else
        {
            _list->ptr = tmp;
        }
    }
    memmove(_list->ptr + (_idx + 1), _list->ptr + _idx, (_list->size - _idx) * sizeof(int));
    _list->size++;
    _list->ptr[_idx] = _element;
    return 1;
}
int removeListInt(ListInt *_list, int _idx)
{
    if (_list == NULL)
    {
        return -1;
    }
    if (_idx < LIST_END || _list->size < _idx)
    {
        return 0;
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
            return 0;
        }
        else
        {
            _list->ptr = tmp;
        }
    }
    return 1;
}

int initListDouble(ListDouble *_list)
{
    if (_list == NULL)
    {
        return -1;
    }
    _list->size = 0;
    _list->capacity = LIST_BUF;
    if ((_list->ptr = (double *)malloc(LIST_BUF)) == NULL)
    {
        return 0;
    }
    return 1;
}
int freeListDouble(ListDouble *_list)
{
    if (_list == NULL)
    {
        return -1;
    }
    _list->size = -1;
    _list->capacity = -1;
    free(_list->ptr);
    _list->ptr = NULL;
    return 1;
}
double getListDouble(ListDouble *_list, int _idx)
{
    if (_list == NULL)
    {
        return -1;
    }
    if (_idx < LIST_END || _list->size < _idx)
    {
        return 0;
    }
    else if (_idx == LIST_END)
    {
        _idx = _list->size;
    }
    return _list->ptr[_idx];
}
int addListDouble(ListDouble *_list, double _element, int _idx)
{
    if (_list == NULL)
    {
        return -1;
    }
    if (_idx < LIST_END || _list->size < _idx)
    {
        return 0;
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
            return 0;
        }
        else
        {
            _list->ptr = tmp;
        }
    }
    memmove(_list->ptr + (_idx + 1), _list->ptr + _idx, (_list->size - _idx) * sizeof(double));
    _list->size++;
    _list->ptr[_idx] = _element;
    return 1;
}
int removeListDouble(ListDouble *_list, int _idx)
{
    if (_list == NULL)
    {
        return -1;
    }
    if (_idx < LIST_END || _list->size < _idx)
    {
        return 0;
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
            return 0;
        }
        else
        {
            _list->ptr = tmp;
        }
    }
    return 1;
}